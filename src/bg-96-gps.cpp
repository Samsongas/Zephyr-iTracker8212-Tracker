#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string>

#include <zephyr.h>
#include <arch/cpu.h>
#include <sys/byteorder.h>
#include <logging/log.h>
#include <sys/util.h>

#include <device.h>
#include <init.h>
#include <drivers/uart.h>

#define LOG_MODULE_NAME hci_uart
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

static const struct device *hci_uart_dev;
static K_THREAD_STACK_DEFINE(tx_thread_stack, CONFIG_BT_HCI_TX_STACK_SIZE);
static struct k_thread tx_thread_data;
static K_FIFO_DEFINE(tx_queue);

/* RX in terms of bluetooth communication */
static K_FIFO_DEFINE(uart_tx_queue);

const String GPS-ON = "AT+QGPS=1" /* Turn on the GPS */
const String GPS-LOC = "AT+QGPSLOC?" /* Receive GPS location */
const String GPS-OFF = "AT+QGPSEND" /* Turn off the GPS */

/* Receiver states. */
const String GPS-OK = "OK" /* OK message */
const String GPS-POS = "+QGPSLOC:"	/* Receiving location. */

/* uart config parameters*/
static QT_UART_CONF_PARA uart1_conf =
{
	NULL,
	QT_UART_PORT_01,
	NULL,
	0,
	NULL,
	0,
	115200
};