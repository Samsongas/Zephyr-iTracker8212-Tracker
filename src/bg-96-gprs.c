#include "bg-96-uart.h"
#include "bg-96-gprs.h"
#include "http_post.h"
#include <string.h>
#include <zephyr.h>

/* GPS global variables */
char gprs_buff[BUFF_MAX_LENGTH] = "";


int uart_send_ok(char buff*)
{
	int ret;
	/* Sending the command to turn ON */
	ret = uart_send(GPS-ON);
	/* return -1 if sending fails */
	if (ret == -1)
		return ret;
	/* Reading the response */
	ret = uart_read(gps_buff);
	/* 0 if successful, -1 otherwise */
	if (ret == -1 || strcmp(gps_buff, GPS-OK) !=0)
		return -1;
	else
		return 0;
}


/*
 * Turns ON the GPRS on LTE mode
 * UART shall be turn on before calling this function.
 */
static int gprs_init(void)
{
	int ret;
	/* Enable scrambling */
	ret = uart_send_ok(GPRS-CFG_1);
	ret != 0? return -1;
	k_sleep(1000);
	/* Set baud */
	ret = uart_send_ok(GPRS-CFG_2);
	ret != 0? return -1;
	k_sleep(1000);
	/* Set LTE mode */
	ret = uart_send_ok(GPRS-CFG_3);
	ret != 0? return -1;
	k_sleep(1000);
	/* Set priority NB1 > M1 > 2G */
	ret = uart_send_ok(GPRS-CFG_4);
	ret != 0? return -1;
	k_sleep(1000);
	/* Select CAT-NB1 */
	ret = uart_send_ok(GPRS-CFG_5);
	ret != 0? return -1;
	k_sleep(1000);
	/* Set PS domain */
	ret = uart_send_ok(GPRS-CFG_6);
	ret != 0? return -1;
	k_sleep(1000);
	/* Set APN provided */
	ret = uart_send_ok(GPRS-GDCONT);
	ret != 0? return -1;
	k_sleep(1000);
	/* Set full functionality */
	ret = uart_send_ok(GPRS-FUN);
	ret != 0? return -1;
	k_sleep(1000);
	/* Set MCC and MNC provided */
	ret = uart_send_ok(GPRS-OPS);
	ret != 0? return -1;
	k_sleep(1000);
	/* Set MCC and MNC provided */
	ret = uart_send_ok(GPRS-OPS);
	ret != 0? return -1;
	k_sleep(1000);
	/* Activate PDP context */
	ret = uart_send_ok(GPRS-OPS);
	ret != 0? return -1;
	k_sleep(1000);
	return 0;
}

/*
 * Opens a TCP socket with the selected ip and port.
 * Sends contents of buffer.
 * Closes the connection.
 */
static int gprs_send(char *ip, char *port, char *buff)
{
	/* Crafring of opening socket command */
	char command[BUFF_MAX_LENGTH];
	strcpy(command,GPRS-IOPEN);
	strcpy(command,ip);
	strcpy(command,"\",");
	strcpy(command,port);
	/* Open the socket */
	ret = uart_send_ok(GPRS-IOPEN);
	ret != 0? return -1;
	k_sleep(1000);
	/* Crafring of message sending */
	char message[BUFF_MAX_LENGTH];
	strcpy(message,GPRS-ISENDEX);
	convert_to_post(buff);
	strcpy(message,buff);
	strcpy(message,"\"");
	/* Open the socket */
	ret = uart_send_ok(message);
	ret != 0? return -1;
	k_sleep(1000);
	/* Close the socket */
	ret = uart_send_ok(GPRS-ICLOSE);
	ret != 0? return -1;
	return 0;
}