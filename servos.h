#ifndef SERVOS_H
#define SERVOS_H

#include <inttypes.h>

#define SERVOS_TIMER_CHANNEL 3

enum ServoChannel {
	Throttle = 0, Ailerons = 1, Elevator = 2, Rudder = 3
};

class Servos {
public:
	Servos(int gpioNumber0, int gpioNumber1, int gpioNumber2, int gpioNumber3);

	void SetPulseLength(ServoChannel channel,
			int pulseLength /* 0 - 1000  us */);
	void SetAngle(ServoChannel channel, float angle /*-45.0 - 45.0 */);
	void SetThrottle(ServoChannel channel, float throttle /* 0.0 - 1.0 */);

	void OnTimerIsr(void);

private:
	int m_gpioNumbers[4];
	int m_pulseLengths[4];
	int m_current;

	uint64_t m_startCycleTime;
	uint64_t m_startTime;
};

#endif
