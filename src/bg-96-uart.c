#include "bg-96-uart.h"
#include <string.h>

/* UART configuration */
struct uart_config uart_cfg_check;
const struct uart_config uart_cfg = {
		.baudrate = 115200,
		.parity = UART_CFG_PARITY_NONE,
		.stop_bits = UART_CFG_STOP_BITS_1,
		.data_bits = UART_CFG_DATA_BITS_8,
		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE
	};

/* UART Global variables */
const struct device *uart_dev;

/* 
 * Initialization of UART.
 * Must be run before any other function.
 */
static int uart_init(void)
{
	*uart_dev = device_get_binding(UART_DEVICE_NAME);
	/* If the binding has not been possible */
	if (!uart_dev) {
		/* Return -1 */
		return -1;
	}

	/* Set device configuration using data in cfg */
	int ret = uart_configure(uart_dev, &uart_cfg);

	/* 0 if successful, -1 otherwise */
	return (ret == 0) ? 0 : -1;

}

/* 
 * Read from the UART until an end of line char is read.
 * Save data to buffer parameter.
 */
static int uart_read(char *buff)
{
	uint8_t recvData;
	int ret;
	uint8_t cnt = 0;
	do {
		ret = uart_fifo_read(dev, &recvData, 1);
		if(ret != 1)
			break;
		buff[cnt] = recvData;
	}
	while ((recvData == '\n') || (recvData == '\r'));
	/* 0 if successful, -1 otherwise */
	return (ret == 0)? 0 : -1;
}

/* 
 * Write to the UART from buffer parameter.
 */
static int uart_send(char *buff)
{
	int ret;
	ret = uart_fifo_fill(dev, (uint8_t *)&buff, strlen(buff));
	/* 0 if successful, -1 otherwise */
	return (ret == strlen(buff))? 0 : -1;
}