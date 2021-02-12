#ifndef __BG_96_UART_H__
#define __BG_96_UART_H__

#include <drivers/uart.h>

#define UART_DEVICE_NAME "UART_0"
#define BUFF_MAX_LENGTH 50

/* 
 * Initialization of UART.
 * Must be run before any other function.
 */
int uart_init(void);
/* 
 * Read from the UART until an end of line char is read.
 * Save data to buffer parameter.
 */
int uart_read(char *buff);
/* 
 * Write to the UART from buffer parameter.
 */
int uart_send(const char *buff);

#endif
