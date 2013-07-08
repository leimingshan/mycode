#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_tcp_item 256

/* IP conversatoin*/
struct tcp_item {
	struct in_addr ip_src;
	struct in_addr ip_dst;
	u_short port;
};

static int count = 0;    /* Packent number */
static struct tcp_item item[MAX_tcp_item];  /* IP conversation*/
static int item_num = 0;
static FILE *fp;         /* File used for output */
static long begin_time = 0; /* the begin time of capture*/

	
/* default snap length (maximum bytes per packet to capture) */
#define SNAP_LEN 1518

/* ethernet headers are always exactly 14 bytes [1] */
#define SIZE_ETHERNET 14

/* Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN	6

/* Ethernet header */
struct sniff_ethernet {
        u_char  ether_dhost[ETHER_ADDR_LEN];    /* destination host address */
        u_char  ether_shost[ETHER_ADDR_LEN];    /* source host address */
        u_short ether_type;                     /* IP? ARP? RARP? etc */
};

/* IP header */
struct sniff_ip {
        u_char  ip_vhl;                 /* version << 4 | header length >> 2 */
        u_char  ip_tos;                 /* type of service */
        u_short ip_len;                 /* total length */
        u_short ip_id;                  /* identification */
        u_short ip_off;                 /* fragment offset field */
        #define IP_RF 0x8000            /* reserved fragment flag */
        #define IP_DF 0x4000            /* dont fragment flag */
        #define IP_MF 0x2000            /* more fragments flag */
        #define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
        u_char  ip_ttl;                 /* time to live */
        u_char  ip_p;                   /* protocol */
        u_short ip_sum;                 /* checksum */
        struct  in_addr ip_src,ip_dst;  /* source and dest address */
};
#define IP_HL(ip)               (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)                (((ip)->ip_vhl) >> 4)

/* TCP header */
typedef u_int tcp_seq;

struct sniff_tcp {
        u_short th_sport;               /* source port */
        u_short th_dport;               /* destination port */
        tcp_seq th_seq;                 /* sequence number */
        tcp_seq th_ack;                 /* acknowledgement number */
        u_char  th_offx2;               /* data offset, rsvd */
#define TH_OFF(th)      (((th)->th_offx2 & 0xf0) >> 4)
        u_char  th_flags;
        #define TH_FIN  0x01
        #define TH_SYN  0x02
        #define TH_RST  0x04
        #define TH_PUSH 0x08
        #define TH_ACK  0x10
        #define TH_URG  0x20
        #define TH_ECE  0x40
        #define TH_CWR  0x80
        #define TH_FLAGS        (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
        u_short th_win;                 /* window */
        u_short th_sum;                 /* checksum */
        u_short th_urp;                 /* urgent pointer */
};

/* Modbus TCP header*/
#define SIZE_MODBUS_HEADER 8;
struct sniff_modbus {
		u_short transaction_id;
        u_short protocol_id;
        u_short len;
        u_char unit_id;
        u_char function_code;
};

//print help text
void print_app_usage(void)
{

	printf("Usage: Modbus-Capture [interface]\n");
	printf("\n");
	printf("Options:\n");
	printf("    interface    Listen on <interface> for packets.\n");
	printf("\n");

	return;
}

//find whether the itemection appeared before
int tcp_item_find(struct in_addr src, struct in_addr dst, u_short port)
{
	int i;
	for (i = 0; i < item_num; i++) {
		if (((item[i].ip_src.s_addr == src.s_addr) && (item[i].ip_dst.s_addr == dst.s_addr)) ||
			((item[i].ip_src.s_addr == dst.s_addr) && (item[i].ip_dst.s_addr == src.s_addr)))
			if (item[i].port == port)
				return i;
	}
	
	return -1; //not found
}

//add a new ip itemection
int tcp_item_add(struct in_addr src, struct in_addr dst, u_short port)
{
	if (item_num == MAX_tcp_item)
		return -1;
	else {
		item[item_num].ip_src = src;
		item[item_num].ip_dst = dst;
		item[item_num].port = port;
		item_num++;
	}
	return 0;
}

static char *human_time(time_t t)
{
    static char str[sizeof("YY-MM-DD HH:MM:SS.NNNNNNNNN +ZZZZ")];

    struct tm const *tm = localtime(&t);
    if (tm == NULL)
        return ctime(&t);

    if (strftime(str, sizeof(str), "%y-%m-%d %H:%M:%S", tm) == 0)
        fprintf(stderr, "strftime returned 0");
    return str;
}

/* print time according to the header and the begin time*/
void print_time(const struct pcap_pkthdr *header)
{
	fprintf(fp, "%-15ld ", header->ts.tv_sec * 1000000 + header->ts.tv_usec - begin_time);
}

//dissect/print packet
void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
	
	/* declare pointers to packet headers */
	const struct sniff_ethernet *ethernet;  /* The ethernet header [1] */
	const struct sniff_ip *ip;              /* The IP header */
	const struct sniff_tcp *tcp;            /* The TCP header */
	const char *payload;                    /* Packet payload */
	const struct sniff_modbus *modbus;

	int size_ip;
	int size_tcp;
	int size_payload;
	
	int item_index;
	
	/* other modbus field*/
	u_char  *mb_begin;      // the beginning after modbus header
	u_short mb_ref_num;
	u_short mb_word_count;
	u_char  mb_byte_count;
	u_char  *mb_data;
	int i;
	
	//fprintf(fp, "\nPacket number %d:\n", count);
	count++;
	
	if (begin_time == 0) {
		begin_time = header->ts.tv_sec * 1000000 + header->ts.tv_usec;
		fprintf(fp, "0 Epoch %s %ld\n", human_time(header->ts.tv_sec), header->ts.tv_usec);
	}
	
	/* timestamp*/
	print_time(header);
	/* define ethernet header */
	ethernet = (struct sniff_ethernet*)(packet);
	
	/* define/compute ip header offset */
	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		fprintf(fp, "   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}

	/* print source and destination IP addresses */
	/*
	fprintf(fp, "       From: %s\n", inet_ntoa(ip->ip_src));
	fprintf(fp, "         To: %s\n", inet_ntoa(ip->ip_dst));
	*/
	/* determine protocol */
	/*
	switch(ip->ip_p) {
		case IPPROTO_TCP:
			fprintf(fp, "   Protocol: TCP\n");
			break;
		case IPPROTO_UDP:
			fprintf(fp, "   Protocol: UDP\n");
			return;
		case IPPROTO_ICMP:
			fprintf(fp, "   Protocol: ICMP\n");
			return;
		case IPPROTO_IP:
			fprintf(fp, "   Protocol: IP\n");
			return;
		default:
			fprintf(fp, "   Protocol: unknown\n");
			return;
	}
	*/
	/*
	 *  OK, this packet is TCP.
	 */
	
	/* define/compute tcp header offset */
	tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
	size_tcp = TH_OFF(tcp)*4;
	if (size_tcp < 20) {
		fprintf(fp, "   * Invalid TCP header length: %u bytes\n", size_tcp);
		return;
	}
	/*
	fprintf(fp, "   Src port: %d\n", ntohs(tcp->th_sport));
	fprintf(fp, "   Dst port: %d\n", ntohs(tcp->th_dport));
	*/
	/* find in ip item*/	
	if (ntohs(tcp->th_sport) == 502) {
		if ((item_index = tcp_item_find(ip->ip_dst, ip->ip_src, tcp->th_dport)) < 0) {
			//new tcp connection
			tcp_item_add(ip->ip_dst, ip->ip_src, tcp->th_dport);		
			fprintf(fp, "%s ", inet_ntoa(item[item_num - 1].ip_dst) + 8);
			
			fprintf(fp, "NEW %s %d\n", 
					inet_ntoa(item[item_num - 1].ip_src) + 8,
					ntohs(item[item_num - 1].port)
					);
					
			//another line
			/* timestamp*/
			print_time(header);
			fprintf(fp, "%s ", inet_ntoa(item[item_num - 1].ip_dst) + 8);
		} else
			fprintf(fp, "%s ", inet_ntoa(item[item_index].ip_dst) + 8);
	} else {
		if ((item_index = tcp_item_find(ip->ip_src, ip->ip_dst, tcp->th_sport)) < 0) {
			tcp_item_add(ip->ip_src, ip->ip_dst, tcp->th_sport);					
			fprintf(fp, "%s ", inet_ntoa(item[item_num - 1].ip_dst) + 8);
			fprintf(fp, "NEW %s %d\n", 
					inet_ntoa(item[item_num - 1].ip_src) + 8,
					ntohs(item[item_num - 1].port)
					);
			//another line
			/* timestamp*/
			print_time(header);
			fprintf(fp, "%s ", inet_ntoa(item[item_num - 1].ip_dst) + 8);
		} else
			fprintf(fp, "%s ", inet_ntoa(item[item_index].ip_dst) + 8);
	}
				
	/* define/compute tcp payload (segment) offset */
	payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
	
	modbus = (struct sniff_modbus*)payload;
	
	/* compute tcp payload (segment) size */
	size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);
	
	/* judge tcp retransmit packet*/

	
	
	/* Make sure there's at least enough data to determine its a Modbus packet */
	if (size_payload < 8) {
		fprintf(fp, "ERR\n");
		return;
	}
	
    /* check that it actually looks like Modbus/TCP */
    /* protocol id == 0 */
    if(modbus->protocol_id != 0 ){
        fprintf(fp, "ERR\n");
		return;
    }
    /* length is at least 2 (unit_id + function_code) */
    if(modbus->len < 2 ){
        fprintf(fp, "ERR\n");
		return;
    }
	
	mb_begin = (u_char *)modbus + 8;
	/* modbus tcp frame format*/
	if ((modbus->function_code & 0x7F) == 3) {
		if (ntohs(tcp->th_dport) == 502) {
			mb_ref_num = ntohs(*(u_short *)mb_begin);
			mb_word_count = ntohs(*(u_short *)(mb_begin + 2));
			fprintf(fp, "> R %d \n", mb_ref_num - 1000);
		} else {
			mb_byte_count = *(u_char *)(mb_begin);
			mb_data = mb_begin + 1;
			fprintf(fp, "< R");
			
			for (i = 0; i < (mb_byte_count / 2); i+=2)
				fprintf(fp, " %d", (*(mb_data + i)) * 256 + (*(mb_data + i + 1)));
			fprintf(fp, "\n");
		}
	} else if((modbus->function_code & 0x7F) == 6) {
		mb_ref_num = ntohs(*(u_short *)mb_begin);
		mb_data = mb_begin + 2;
		if (ntohs(tcp->th_dport) == 502)		
			fprintf(fp, "> ");
		else
			fprintf(fp, "< ");
		fprintf(fp, "W %d %d\n", mb_ref_num - 1000, ntohs(*(u_short *)mb_data));
	}
	return;
}

int main(int argc, char *argv[])
{
	pcap_t *handle;			/* Session handle */
	char *dev = NULL;			/* The device to sniff on */
	char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
	
	struct bpf_program filter;		/* The compiled filter */
	char filter_exp[] = "tcp port 502";	/* The filter expression */
	
	//bpf_u_int32 mask;		/* Our netmask */
	//bpf_u_int32 net;		/* Our IP */
	
	struct pcap_pkthdr header;	/* The header that pcap gives us */
	const u_char *packet;		/* The actual packet */
	
	char *filename = NULL;
	int i;

	/* check for capture file name on command-line */
	if (argc == 2) {
		dev = argv[1];
		fp = stdout;
	} else if (argc == 3) {
		dev = argv[1];
		filename = argv[2];
	} else {
		fprintf(stderr, "error: unrecognized command-line options\n\n");
		print_app_usage();
		exit(EXIT_FAILURE);
	}
		
	if (filename != NULL) {
		if ((fp = fopen(filename, "w+")) < 0) {
			fprintf(stderr, "Couldn't open file \"%s\" for output\n",
				filename);
			exit(EXIT_FAILURE);
		}
	}
	
	/* print capture info */
	fprintf(fp, "Device: %s\n", dev);
	
	/* open the capture file*/
	handle = pcap_open_offline(dev, errbuf);
	if (handle == NULL) {
		fprintf(stderr, "Couldn't open capture FILE %s: %s\n", dev, errbuf);
		exit(EXIT_FAILURE);
	}
	
	/* make sure we're capturing on an Ethernet device [2] */
	if (pcap_datalink(handle) != DLT_EN10MB) {
		fprintf(stderr, "%s is not an Ethernet\n", dev);
		exit(EXIT_FAILURE);
	}

	/* compile the filter expression */
	if (pcap_compile(handle, &filter, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
		fprintf(stderr, "Couldn't parse filter %s: %s\n",
		    filter_exp, pcap_geterr(handle));
		exit(EXIT_FAILURE);
	}

	/* apply the compiled filter */
	if (pcap_setfilter(handle, &filter) == -1) {
		fprintf(stderr, "Couldn't install filter %s: %s\n",
		    filter_exp, pcap_geterr(handle));
		exit(EXIT_FAILURE);
	}
	
	pcap_loop(handle, -1, got_packet, NULL);      
	

	for (i = 0; i < item_num; i++) {
		fprintf(fp, "t                        %s", 
				inet_ntoa(item[i].ip_dst) + 8
				);
		fprintf(fp, "END %s %d\n", 
				inet_ntoa(item[i].ip_src) + 8,
				ntohs(item[i].port)
				);
	}
	
	fprintf(fp, "Captured %d packets\n", count);
	
	/* And close the session */
	pcap_close(handle);
	
	fprintf(fp, "\nCapture complete.\n");
	fclose(fp);
	return 0;
}
