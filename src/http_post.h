#include <stdlib.h>
#include <string.h>

#define BUFFER_MAX_HTTP_POST 150

const char http_post_header[BUFFER_MAX_HTTP_POST] = "POST /session HTTP/1.1\r\nHost: localhost:8000\r\nContent-Type: text/plain\r\nContent-Length:";

void convert_to_post(char *buff)
{
	uint8_t m_size = strlen(buff);
	char message[m_size+1];
	strcpy(message, buff);
	buff[0] = "\0";
	strcpy(buff, http_post_header);
	strcpy(buff, itoa(m_size));
	strcpy(buff, "\r\n\r\n");
	strcpy(buff, message);
}