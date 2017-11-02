#ifndef SERVOS_H
#define SERVOS_H

#include <inttypes.h>

#define SERVOS_TIMER_CHANNEL 3


class Servos {
public:
	Servos(int gpioNumber0, int gpioNumber1, int gpioNumber2, int gpioNumber3);

	void Set(int channel, int pulseLength);
	void OnTimerIsr(void);

private:
	int m_gpioNumbers[4];
	int m_pulseLengths[4];
	int m_current;

	uint64_t m_startCycleTime;
	uint64_t m_startTime;
};

#endif
