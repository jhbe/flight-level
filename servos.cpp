#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "systemtimer.h"
#include "servos.h"

Servos::Servos(int gpioNumber0, int gpioNumber1, int gpioNumber2,
		int gpioNumber3) {
	m_gpioNumbers[0] = gpioNumber0;
	m_gpioNumbers[1] = gpioNumber1;
	m_gpioNumbers[2] = gpioNumber2;
	m_gpioNumbers[3] = gpioNumber3;

	m_pulseLengths[0] = 1000;
	m_pulseLengths[1] = 1000;
	m_pulseLengths[2] = 1000;
	m_pulseLengths[3] = 1000;

	m_current = -1;
	m_startCycleTime = 0;
	m_startTime = 0;

	for (int i = 0; i < 4; i++) {
		gpio_set_output (m_gpioNumbers[i]);
		gpio_clear(m_gpioNumbers[i]);
	}
}

void Servos::Set(int channel, int pulseLength) {
	if (pulseLength < 1000) {
		pulseLength = 1000;
	} else if (pulseLength > 2000) {
		pulseLength = 2000;
	}
	m_pulseLengths[channel] = pulseLength;
}

void Servos::OnTimerIsr(void) {
	uint64_t now = systemtimer_get();

	//
	// Time to start a new cycle?
	//
	if (m_current == -1 && (m_startCycleTime == 0 || (unsigned int)(now - m_startCycleTime) > 20000)) {
		m_startCycleTime = now;
		m_current = 0;
		gpio_set(m_gpioNumbers[0]);
		systemtimer_set_alarm(SERVOS_TIMER_CHANNEL, m_pulseLengths[0]);
	} else if (m_current >= 0 && (unsigned int)(now - m_startTime) > m_pulseLengths[m_current]) {
		gpio_clear(m_gpioNumbers[m_current]);
		m_current++;
		m_startTime = now;
		if (m_current < 4) {
			gpio_set(m_gpioNumbers[m_current]);
			systemtimer_set_alarm(SERVOS_TIMER_CHANNEL, m_pulseLengths[m_current]);
		} else {
			m_current = -1;
			unsigned int elapsedTime = (unsigned int)(now - m_startCycleTime);
			unsigned int remainingTime = 20000 - elapsedTime;
			systemtimer_set_alarm(SERVOS_TIMER_CHANNEL, remainingTime);
		}
	}
}
