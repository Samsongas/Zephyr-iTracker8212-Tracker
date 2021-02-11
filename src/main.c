#include "bg-96-uart.h"
#include "bg-96-gps.h"
#include "http-post.h"

#define MAX_FAIL 10

/* Program parameters */
const char dest_ip[] = "0.0.0.0" /* Destination IP */
const char dest_port[] = "8080" /* Destination port */

int main(void){
	int ret;
	char buff[BUFFER_MAX_HTTP_POST] = "";
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
				ret = get_location(buff);
				cnt++;
			} while(ret != 0);
			if (cnt > MAX_FAIL)
				break;
			cnt = 0;
			do {
				ret = gprs_send(buff,dest_ip,dest_port);
				cnt++;
			} while(ret != 0);
			if (cnt > MAX_FAIL)
				break;
		}
		// Dissconnect uart, gps and gprs?
	}
}