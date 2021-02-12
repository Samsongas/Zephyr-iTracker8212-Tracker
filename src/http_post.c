#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_MAX_HTTP_POST 150

const char http_post_header[BUFFER_MAX_HTTP_POST] = "POST /session HTTP/1.1\r\nHost: localhost:8000\r\nContent-Type: text/plain\r\nContent-Length:";

void convert_to_post(char *buff)
{
	int m_size = strlen(buff);
	char message[m_size+1];
	strcpy(message, buff);
	buff[0] = "\0";
	strcpy(buff, http_post_header);
	char m_len[3];
	m_len[0] = '0' + m_size/10;
	m_len[1] = '0' + m_size%10;
	m_len[2] = '\0';
	strcpy(buff, m_len);
	strcpy(buff, "\r\n\r\n");
	strcpy(buff, message);
}
