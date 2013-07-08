#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>

void generic_request_handler(struct evhttp_request *req, void *arg)
{
	struct evbuffer *buf = evbuffer_new();
	
	// ����HTTPͷ��
	evhttp_add_header(evhttp_request_get_output_headers(req), "Content-Type", "text/html; charset=gb2312");
	evhttp_add_header(evhttp_request_get_output_headers(req), "Server", "my_httpd");
	//evhttp_add_header(evhttp_request_get_output_headers(req), "Connection", "keep-alive"); 
	evhttp_add_header(evhttp_request_get_output_headers(req), "Connection", "close");
	
	evbuffer_add_printf(buf, "<html>\n<head>\n"
		"<title>�ҵĵ�һ�� HTML ҳ��</title>\n"
		"</head>\n"
		"<body>\n"
		"<h1 align=\"center\">This is heading 1</h1>"
		"<p>body Ԫ�ص����ݻ���ʾ��������С�</p>\n"
		"<p>title Ԫ�ص����ݻ���ʾ��������ı������С�</p>\n"
		"</body>\n"
		"</html>\n");
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
	evbuffer_free(buf);
	return;
}

int main(int argc, char **argv)
{
	short http_port = 8080;
	const char *http_addr = "192.168.0.183";
	int timeout = 10;
	
	// �����¼�����
    struct event_base *base = event_base_new();
	if(base == NULL) {
		fprintf(stderr, "Error: Unable to open event base!\n");
		exit(1);
	}
	
	//����host_ip��host_port����һ��addrinfo�ṹ��,Ȼ�󴴽�һ��socket,�󶨵����socket��,
    //������Щ��Ϣ�õ��õ�һ��event(�ص���������Ϊaccept_socket),Ȼ�����event��������Ӧ��event_base,
    //֮����뵽&http->sockets������,Ȼ�󷵻�&http
	struct evhttp *http_server = evhttp_new(base);
	if(http_server == NULL) {
		fprintf(stderr, "Error: Unable to create http server\n");
		exit(1);
	}
	// �����
    if(0 != evhttp_bind_socket(http_server, http_addr, http_port))
    {
        fprintf(stderr, "Error: Unable to listen on %s:%d\n\n", http_addr, http_port);
        exit(1);
    }
	// ��������ʱʱ��
	evhttp_set_timeout(http_server, timeout);
	// ��������Ĵ�����
	evhttp_set_gencb(http_server, generic_request_handler, NULL);

	fprintf(stdout, "Server started on port %d\n", http_port);
	
	event_base_dispatch(base);
	
	evhttp_free(http_server);
	
	event_base_free(base);

	return 0;
}