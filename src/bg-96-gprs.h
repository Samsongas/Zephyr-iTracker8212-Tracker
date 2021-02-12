#ifndef __BG_96_GPRS_H__
#define __BG_96_GPRS_H__

#include <zephyr.h>
#include <kernel.h>

int gprs_init(void);
int gprs_send(char *ip, char *port, char *buff);

#endif
