#ifndef __BG_96_GPS_H__
#define __BG_96_GPS_H__

/*
 * Turns ON the GPS
 * UART shall be turn on before calling this function.
 */
int gps_init(void);
/*
 * Gets location from the GPS
 * Writes the string returned from the BG-96 to a+
 * buffer passed as parameter.
 * UART shall be turn on before calling this function.
 */
int get_location(char *buff);

#endif
