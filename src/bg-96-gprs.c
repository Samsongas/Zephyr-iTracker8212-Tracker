#include "bg-96-uart.h"
#include "bg-96-gprs.h"
#include "http_post.h"
#include <string.h>
#include <zephyr.h>

/* AT Commands to be sent to BG96 */
const char GPRS_CFG_1[30] = "AT+QCFG=\"nbsibscramble\",0";
const char GPRS_CFG_2[30] = "AT+QCFG=\"band\",0,0,80,1";
const char GPRS_CFG_3[30] = "AT+QCFG=\"nwscanmode\",3,1";
const char GPRS_CFG_4[30] = "AT+QCFG=\"nwscanseq\",030201,1";
const char GPRS_CFG_5[30] = "AT+QCFG=\"iotopmode\",1,1";
const char GPRS_CFG_6[30] = "AT+QCFG=\"servicedomain\",1,1";
const char GPRS_GDCONT[30] = "AT+CGDCONT=1,\"IP\",\"internet\"";
const char GPRS_FUN[10] = "AT+CFUN=1";
const char GPRS_OPS[30] = "AT+COPS=1,2,\"22001\",0";
const char GPRS_IACT[20] = "AT+QIACT=1";
/* add ip and port as 79.114.83.116\",16666" */
const char GPRS_IOPEN[50] = "AT+QIOPEN=1,0,\"TCP\",\"";
const char GPRS_ICLOSE[30] = "AT+QICLOSE=0";
const char GPRS_ISENDEX[30] = "AT+QISENDEX=0,\"48656C6C6F\"";

/* BG96 responses */
const char GPRS_OK[] = "OK"; /* OK message */

/* GPS global variables */
char gprs_buff[BUFF_MAX_LENGTH] = "";


int uart_send_ok(const char *buff)
{
	int ret;
	/* Sending the received command */
	ret = uart_send(buff);
	/* return -1 if sending fails */
	if (ret == -1)
		return ret;
	/* Reading the response */
	ret = uart_read(gprs_buff);
	/* 0 if successful, -1 otherwise */
	if (ret == -1 || strcmp(gprs_buff, GPRS_OK) !=0)
		return -1;
	else
		return 0;
}


/*
 * Turns ON the GPRS on LTE mode
 * UART shall be turn on before calling this function.
 */
int gprs_init(void)
{
	int ret;
	/* Enable scrambling */
	ret = uart_send_ok(GPRS_CFG_1);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Set baud */
	ret = uart_send_ok(GPRS_CFG_2);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Set LTE mode */
	ret = uart_send_ok(GPRS_CFG_3);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Set priority NB1 > M1 > 2G */
	ret = uart_send_ok(GPRS_CFG_4);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Select CAT-NB1 */
	ret = uart_send_ok(GPRS_CFG_5);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Set PS domain */
	ret = uart_send_ok(GPRS_CFG_6);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Set APN provided */
	ret = uart_send_ok(GPRS_GDCONT);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Set full functionality */
	ret = uart_send_ok(GPRS_FUN);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Set MCC and MNC provided */
	ret = uart_send_ok(GPRS_OPS);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Set MCC and MNC provided */
	ret = uart_send_ok(GPRS_OPS);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Activate PDP context */
	ret = uart_send_ok(GPRS_OPS);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	return 0;
}

/*
 * Opens a TCP socket with the selected ip and port.
 * Sends contents of buffer.
 * Closes the connection.
 */
int gprs_send(char *ip, char *port, char *buff)
{
	int ret;
	/* Crafring of opening socket command */
	char command[BUFF_MAX_LENGTH];
	strcpy(command,GPRS_IOPEN);
	strcpy(command,ip);
	strcpy(command,"\",");
	strcpy(command,port);
	/* Open the socket */
	ret = uart_send_ok(GPRS_IOPEN);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Crafring of message sending */
	char message[BUFF_MAX_LENGTH];
	strcpy(message,GPRS_ISENDEX);
	convert_to_post(buff);
	strcpy(message,buff);
	strcpy(message,"\"");
	/* Open the socket */
	ret = uart_send_ok(message);
	if(ret != 0) return -1;
	k_sleep(K_MSEC(1000));
	/* Close the socket */
	ret = uart_send_ok(GPRS_ICLOSE);
	if(ret != 0) return -1;
	return 0;
}
