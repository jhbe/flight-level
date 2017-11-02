#include "gpio.h"
#include "systemtimer.h"
#include "led.h"

Led::Led(int gpioNumber, bool invert) {
	m_invert = invert;
	m_gpioNumber = gpioNumber;
	m_flash = false;
	gpio_set_output(m_gpioNumber);
}

Led::~Led(void) {
	m_gpioNumber = -1;
}

void Led::Assert(void) {
	if (m_invert) {
		gpio_clear(m_gpioNumber);
	} else {
		gpio_set(m_gpioNumber);
	}
}

void Led::Deassert(void) {
	if (m_invert) {
		gpio_set(m_gpioNumber);
	} else {
		gpio_clear(m_gpioNumber);
	}
}

void Led::Set(void) {
	m_flash = false;
	Assert();
}

void Led::Clear(void) {
	m_flash = false;
	Deassert();
}

void Led::Flash(void) {
	if (!m_flash) {
		m_flash = true;
		m_flashOn = false;
		m_lastFlash = 0;
	}
}

void Led::Service(void) {
	if (m_flash) {
		uint64_t now = systemtimer_get();
		if ((unsigned int) (now - m_lastFlash) > 100000) {
			if (m_flashOn) {
				Deassert();
			} else {
				Assert();
			}
			m_flashOn = !m_flashOn;
			m_lastFlash = now;
		}
	}
}
