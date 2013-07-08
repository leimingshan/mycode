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
	
	// 返回HTTP头部
	evhttp_add_header(evhttp_request_get_output_headers(req), "Content-Type", "text/html; charset=gb2312");
	evhttp_add_header(evhttp_request_get_output_headers(req), "Server", "my_httpd");
	//evhttp_add_header(evhttp_request_get_output_headers(req), "Connection", "keep-alive"); 
	evhttp_add_header(evhttp_request_get_output_headers(req), "Connection", "close");
	
	evbuffer_add_printf(buf, "<html>\n<head>\n"
		"<title>我的第一个 HTML 页面</title>\n"
		"</head>\n"
		"<body>\n"
		"<h1 align=\"center\">This is heading 1</h1>"
		"<p>body 元素的内容会显示在浏览器中。</p>\n"
		"<p>title 元素的内容会显示在浏览器的标题栏中。</p>\n"
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
	
	// 生成事件载体
    struct event_base *base = event_base_new();
	if(base == NULL) {
		fprintf(stderr, "Error: Unable to open event base!\n");
		exit(1);
	}
	
	//根据host_ip和host_port创建一个addrinfo结构体,然后创建一个socket,绑定到这个socket后,
    //根据这些信息得到得到一个event(回调函数设置为accept_socket),然后将这个event关联到对应的event_base,
    //之后插入到&http->sockets队列中,然后返回&http
	struct evhttp *http_server = evhttp_new(base);
	if(http_server == NULL) {
		fprintf(stderr, "Error: Unable to create http server\n");
		exit(1);
	}
	// 服务绑定
    if(0 != evhttp_bind_socket(http_server, http_addr, http_port))
    {
        fprintf(stderr, "Error: Unable to listen on %s:%d\n\n", http_addr, http_port);
        exit(1);
    }
	// 设置请求超时时间
	evhttp_set_timeout(http_server, timeout);
	// 设置请求的处理函数
	evhttp_set_gencb(http_server, generic_request_handler, NULL);

	fprintf(stdout, "Server started on port %d\n", http_port);
	
	event_base_dispatch(base);
	
	evhttp_free(http_server);
	
	event_base_free(base);

	return 0;
}