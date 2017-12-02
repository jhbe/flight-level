#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

/**
 * This class represent one channel from the RC receiver, such as the elevator
 * or rudder channel.
 *
 * The constructor takes the raspberry pi GPIO number the receiver channel is
 * connected to and configures that GPIO to raise an interrupt when that channel
 * goes from low to high or high to low. When that interrupt fires the user must
 * call Service().
 *
 * The user call Get to get the current channel value. It returns the pulse
 * length of the signal, typically in the range 1000 to 2000 us.
 *
 * The GPIO is configured to activate a pulldown resistor. As a result, an
 * unconnected channel will never trigger the interrupt so the Service() function
 * should be called periodically as well, typically every 100ms. This allow the
 * class to set the value of the channel to 1000us (zero throttle) when the signal
 * is lost.
 */
class Input {
public:
	Input(int gpioNumber);

	int GetPulseLength(void); // In us
	float GetAngle(void); // In degrees
	void Service(void);

private:
	int m_gpioNumber;
	int m_pulseLength; // 1000 - 2000 us

	bool m_pulseAsserted;
	uint64_t m_startTime; // Time of the most recent low-to-high transition.
};

#endif
