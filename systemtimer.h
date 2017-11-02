#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

#include <stdint.h>

uint64_t systemtimer_get(void);
void systemtimer_set_alarm(int channel, int us);
int systemtimer_pending_interrupt(int channel);

#endif
