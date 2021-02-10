#include "bg-96-uart.h"
#include "bg-96-gps.h"
#include <string.h>

/* GPS global variables */
char gps_buff[BUFF_MAX_LENGTH] = "";

/*
 * Turns ON the GPS
 * UART shall be turn on before calling this function.
 */
static int gps_init(void)
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
 * Gets location from the GPS
 * Writes the string returned from the BG-96 to a+
 * buffer passed as parameter.
 * UART shall be turn on before calling this function.
 */
static int get_location(char *buff)
{
	int ret;
	/* Sending the command to turn ON */
	ret = uart_send(GPS-ON);
	/* return -1 if sending fails */
	if (ret == -1)
		return ret;
	/* Reading the response */
	ret = uart_read(gps_buff);
	/* return -1 if response is unexpected */
	char received[strlen(GPS-POS) + 1];
	strncpy(gps_buff, received, strlen(GPS-POS));
	received[strlen(GPS-POS)] = '\0';
	if(strcmp(received, GPS-POS) != 0)
		return -1;
	/* If the result has been as expected, copy the string to the buffer */
	strncpy(gps_buff,buff, strlen(gps_buff));
	return 0;
}

