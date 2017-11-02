#include <stdint.h>
#include "systemtimer.h"

void delayus(int us) {
	uint64_t end = systemtimer_get() + us;
	while (systemtimer_get() < end);
}

void delayms(int ms) {
	delayus(ms * 1000);
}
