#include <drivers/uart.h>

#define UART_DEVICE_NAME CONFIG_UART_CONSOLE_ON_DEV_NAME
#define BUFF_MAX_LENGTH 50

/* 
 * Initialization of UART.
 * Must be run before any other function.
 */
static int uart_init(void);
/* 
 * Read from the UART until an end of line char is read.
 * Save data to buffer parameter.
 */
static int uart_read(char *buff);
/* 
 * Write to the UART from buffer parameter.
 */
static int uart_send(char *buff);