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

#define UART_DEVICE_NAME CONFIG_UART_CONSOLE_ON_DEV_NAME

/* UART configuration */
struct uart_config uart_cfg_check;
const struct uart_config uart_cfg = {
		.baudrate = 115200,
		.parity = UART_CFG_PARITY_NONE,
		.stop_bits = UART_CFG_STOP_BITS_1,
		.data_bits = UART_CFG_DATA_BITS_8,
		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE
	};

/* AT Commands to be sent to BG96 */
const String GPS-ON = "AT+QGPS=1" /* Turn on the GPS */
const String GPS-LOC = "AT+QGPSLOC?" /* Receive GPS location */
const String GPS-OFF = "AT+QGPSEND" /* Turn off the GPS */

/* BG96 responses */
const String GPS-OK = "OK" /* OK message */
const String GPS-POS = "+QGPSLOC:"	/* Receiving location. Starting string */

/* UART Global variables */
static volatile bool data_transmitted;
static volatile bool data_received;
static int char_sent;

static void uart_fifo_callback(const struct device *dev, void *user_data)
{
	uint8_t recvData;
	static int tx_data_idx;

	ARG_UNUSED(user_data);

	/* Verify uart_irq_update() */
	if (!uart_irq_update(dev)) {
		TC_PRINT("retval should always be 1\n");
		return;
	}

	/* Verify uart_irq_tx_ready() */
	/* Note that TX IRQ may be disabled, but uart_irq_tx_ready() may
	 * still return true when ISR is called for another UART interrupt,
	 * hence additional check for i < DATA_SIZE.
	 */
	if (uart_irq_tx_ready(dev) && tx_data_idx < DATA_SIZE) {
		/* We arrive here by "tx ready" interrupt, so should always
		 * be able to put at least one byte into a FIFO. If not,
		 * well, we'll fail test.
		 */
		if (uart_fifo_fill(dev,
				   (uint8_t *)&fifo_data[tx_data_idx++], 1) > 0) {
			data_transmitted = true;
			char_sent++;
		}

		if (tx_data_idx == DATA_SIZE) {
			/* If we transmitted everything, stop IRQ stream,
			 * otherwise main app might never run.
			 */
			uart_irq_tx_disable(dev);
		}
	}

	/* Verify uart_irq_rx_ready() */
	if (uart_irq_rx_ready(dev)) {
		/* Verify uart_fifo_read() */
		uart_fifo_read(dev, &recvData, 1);
		TC_PRINT("%c", recvData);

		if ((recvData == '\n') || (recvData == '\r')) {
			data_received = true;
		}
	}
}

static int uart_read(const struct device *uart, uint8_t *buf, size_t len)
{
	const struct device *uart_dev = device_get_binding(UART_DEVICE_NAME);

	/* Verify uart_irq_callback_set() */
	uart_irq_callback_set(uart_dev, uart_fifo_callback);

	/* Enable Tx/Rx interrupt before using fifo */
	/* Verify uart_irq_rx_enable() */
	uart_irq_rx_enable(uart_dev);

	TC_PRINT("Please send characters to serial console\n");

	data_received = false;
	while (data_received == false) {
	}

	/* Verify uart_irq_rx_disable() */
	uart_irq_rx_disable(uart_dev);

	return TC_PASS;

}

static int uart_send(struct net_buf *buf)
{
	const struct device *uart_dev = device_get_binding(UART_DEVICE_NAME);
	char_sent = 0;
	/* Verify uart_irq_callback_set() */
	uart_irq_callback_set(uart_dev, uart_fifo_callback);
	/* Enable Tx/Rx interrupt before using fifo */
	/* Verify uart_irq_tx_enable() */
	uart_irq_tx_enable(uart_dev);
	k_sleep(K_MSEC(500));
	/* Verify uart_irq_tx_disable() */
	uart_irq_tx_disable(uart_dev);

	if (!data_transmitted) {
		return TC_FAIL;
	}

	if (char_sent == DATA_SIZE) {
		return TC_PASS;
	} else {
		return TC_FAIL;
	}
}