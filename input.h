#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

class Input {
public:
	Input(int gpioNumber);

	int Get(void); // In us
	void Service(void);

private:
	int m_gpioNumber;
	int m_pulseLength;

	bool m_pulseAsserted;
	uint64_t m_startTime;
};

#endif
