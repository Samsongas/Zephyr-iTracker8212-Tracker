#include "bg-96-uart.h"
#include "bg-96-gps.h"
#include "bg-96-gprs.h"
#include "http_post.h"

#define MAX_FAIL 10

/* Program parameters */
const char dest_ip[] = "0.0.0.0"; /* Destination IP */
const char dest_port[] = "8080"; /* Destination port */

void parse_position(char *buff)
{
	char message[BUFFER_MAX_HTTP_POST];
	if(strncmp((char)buff[0],"-",1) == 0)
		strncpy(message,buff,9);
	else
		strncpy(message,buff,8);
	strcpy(message,",");
	if(strncmp(buff[0],"-",1) == 0)
		strcpy(message,buff+9);
	else
		strcpy(message,buff+8);
	buff[0] = "\0";
	strcpy(buff,message);
}

int main(void){
	int ret;
	char buffer[BUFFER_MAX_HTTP_POST] = "";
	uint8_t cnt = 0;
	while(1){
		do {
			ret = uart_init();
		} while(ret != 0);
		do {
			ret = gps_init();
		} while(ret != 0);
		do {
			ret = gprs_init();
		} while(ret != 0);
		while(1) {
			cnt = 0;
			do {
				ret = get_location(buffer);
				cnt++;
			} while(ret != 0);
			if (cnt > MAX_FAIL)
				break;
			cnt = 0;
			parse_position(buffer);
			do {
				ret = gprs_send(&buffer,dest_ip,dest_port);
				cnt++;
			} while(ret != 0);
			if (cnt > MAX_FAIL)
				break;
		}
		// Dissconnect uart, gps and gprs?
	}
}
