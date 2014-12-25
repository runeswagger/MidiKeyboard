#ifndef _MIDIKEYBOARDC_H_
#define _MIDIKEYBOARDC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <avr/interrupt.h>
#include <util/delay.h>
#include "osccal.h"
#include "usbdrv/usbdrv.h"

void usbBegin();
void usbPollWrapper();

char usbSend(char *data, char len);

#ifdef __cplusplus
}
#endif

#endif
