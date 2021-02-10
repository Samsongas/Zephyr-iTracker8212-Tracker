/* AT Commands to be sent to BG96 */
const char GPS-ON[] = "AT+QGPS=1\n" /* Turn on the GPS */
const char GPS-LOC[] = "AT+QGPSLOC?\n" /* Receive GPS location */
const char GPS-OFF[] = "AT+QGPSEND\n" /* Turn off the GPS */

/* BG96 responses */
const char GPS-OK[] = "OK\n" /* OK message */
const char GPS-POS[] = "+QGPSLOC:"	/* Receiving location. Starting string */

/*
 * Turns ON the GPS
 * UART shall be turn on before calling this function.
 */
static int gps_init(void);
/*
 * Gets location from the GPS
 * Writes the string returned from the BG-96 to a+
 * buffer passed as parameter.
 * UART shall be turn on before calling this function.
 */
static int get_location(char *buff);