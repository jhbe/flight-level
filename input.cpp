#include "input.h"
#include "gpio.h"
#include "systemtimer.h"

Input::Input(int gpioNumber) {
	m_gpioNumber = gpioNumber;
	m_pulseAsserted = false;
	m_pulseLength = 0;
	m_startTime = 0;

	/*
	 * Ensure an unconnected pin does not float.
	 */
	gpio_set_pullupdown(m_gpioNumber, GPIO_MODE_DOWN);

	/*
	 * Set the GPIO as an input and enable edge-detect interrupts.
	 */
	gpio_set_input(m_gpioNumber, true);
}

int Input::GetPulseLength(void) {
	return m_pulseLength;
}

float Input::GetAngle(void) {
	return ((float)m_pulseLength - 1500.0) / 500.0 * 45.0;
}

void Input::Service(void) {
	uint64_t now = systemtimer_get();

	if (m_pulseAsserted && gpio_get(m_gpioNumber) == 0) {
		m_pulseLength = (int) (now - m_startTime);
		m_pulseAsserted = false;
	} else if (!m_pulseAsserted && gpio_get(m_gpioNumber) == 1) {
		m_startTime = now;
		m_pulseAsserted = true;
	} else if ((unsigned int) (now - m_startTime) > 100000) {
		/*
		 * We have not detected a pulse starting in the last 100ms. Reset to
		 * the shortest pulse possible. That will turn off any ESCs.
		 */
		m_pulseLength = 1000;
		m_pulseAsserted = false;
	}
}
