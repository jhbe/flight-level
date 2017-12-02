#include "systemtimer.h"

#define SYSTEMTIMER_BASE    0x20003000UL

typedef struct {
	volatile uint32_t cs;
	volatile uint32_t clo;
	volatile uint32_t clh;
	volatile uint32_t c0;
	volatile uint32_t c1;
	volatile uint32_t c2;
	volatile uint32_t c3;
} SYSTEMTIMER;
SYSTEMTIMER *st = (SYSTEMTIMER *)SYSTEMTIMER_BASE;

uint64_t systemtimer_get(void) {
	return ((uint64_t)(st->clh) << 32) | (uint64_t)(st->clo);
}

void systemtimer_set_alarm(int channel, int us) {
	//
	// Put a new value in CX. It may overflow, but that's fine as long as it
	// doesn't overflow more than once.
	//
	switch (channel) {
	case 0:
		st->c0 = st->clo + us;
		st->cs = 0x00000001;  // Clear any interrupt for M0.
		break;
	case 1:
		st->c1 = st->clo + us;
		st->cs = 0x00000002;  // Clear any interrupt for M1.
		break;
	case 2:
		st->c2 = st->clo + us;
		st->cs = 0x00000004;  // Clear any interrupt for M2.
		break;
	case 3:
		st->c3 = st->clo + us;
		st->cs = 0x00000008;  // Clear any interrupt for M3.
		break;
	}
}

bool systemtimer_pending_interrupt(int channel) {
	switch (channel) {
	case 0:
		return (st->cs & 0x00000001) != 0;
		break;
	case 1:
		return (st->cs & 0x00000002) != 0;
		break;
	case 2:
		return (st->cs & 0x00000004) != 0;
		break;
	case 3:
		return (st->cs & 0x00000008) != 0;
		break;
	}

	return false;
}
