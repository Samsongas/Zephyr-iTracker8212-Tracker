#include "bg-96-uart.h"
#include "bg-96-gps.h"
#include <string.h>

/* AT Commands to be sent to BG96 */
const char GPS_ON[] = "AT+QGPS=1"; /* Turn on the GPS */
/* mode 2 <latitude>,<longitude> format: (-)dd.ddddd,(-)ddd.ddddd */
const char GPS_LOC[] = "AT+QGPSLOC=2"; /* Receive GPS location */
const char GPS_OFF[] = "AT+QGPSEND"; /* Turn off the GPS */

/* BG96 responses */
const char GPS_OK[] = "OK"; /* OK message */
const char GPS_POS[] = "+QGPSLOC:";	/* Receiving location. Starting string */

/* GPS global variables */
char gps_buff[BUFF_MAX_LENGTH] = "";

/*
 * Turns ON the GPS
 * UART shall be turn on before calling this function.
 */
int gps_init(void)
{
	int ret;
	/* Sending the command to turn ON */
	ret = uart_send(GPS_ON);
	/* return -1 if sending fails */
	if (ret == -1)
		return ret;
	/* Reading the response */
	ret = uart_read(gps_buff);
	/* 0 if successful, -1 otherwise */
	if (ret == -1 || strcmp(gps_buff, GPS_OK) !=0)
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
int get_location(char *buff)
{
	int ret;
	/* Sending the command to turn ON */
	ret = uart_send(GPS_ON);
	/* return -1 if sending fails */
	if (ret == -1)
		return ret;
	/* Reading the response */
	ret = uart_read(gps_buff);
	/* return -1 if response is unexpected */
	char received[strlen(GPS_POS) + 1];
	strncpy(gps_buff, received, strlen(GPS_POS));
	received[strlen(GPS_POS)] = '\0';
	if(strcmp(received, GPS_POS) != 0)
		return -1;
	/* If the result has been as expected, copy the string to the buffer */
	strncpy(gps_buff,buff, strlen(gps_buff));
	return 0;
}

