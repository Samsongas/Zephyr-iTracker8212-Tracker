#include "bg-96-uart.h"
#include "bg-96-gps.h"

/* Program parameters */
const char dest_ip[] = "0.0.0.0" /* Destination IP */
const char dest_port[] = "8080" /* Destination port */

/*
 * Parses the coordinates in the buffer received as parameters
 * and turns them into the format "x_position,y_position"
 */
void parse_location(char buff*);

int main(void){
	int ret;
	char buff[BUFF_MAX_LENGTH] = "";
	while(1){
		ret = uart_init();
		if (ret == 0){
			gps_init();
			// Not implemented
			// gprs_init();
		}
		while(1) {
			ret = get_location(buff);
			if (ret == 0);
				parse_location(buff);
				// Not implemented
				// send_data(buff,dest_ip,dest_port);
		}
	}
}