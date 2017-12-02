#ifndef LED_H_
#define LED_H_

/**
 * This class provides control over a GPIO pin. A connected LED can be set to
 * on, off or to flash at 10Hz.
 *
 * The user must invoke Service() at about 10Hz.
 */
class Led {
public:
	/**
	 * Use GPIO "gpioNumber". Set "invert" to true if a low output will light
	 * a connected LED.
	 */
	Led(int gpioNumber, bool invert);
	~Led();

	/**
	 * Set the LED to on (emit light).
	 */
	void Set(void);

	/**
	 * Turn LED off.
	 */
	void Clear(void);

	/**
	 * Make the LED flash at 10Hz.
	 */
	void Flash(void);

	/**
	 * Call this method regularly (10Hz).
	 */
	void Service(void);

private:
	void Assert(void);
	void Deassert(void);

private:
	bool m_invert;
	int m_gpioNumber;

	bool m_flash;         // True if the LED shall flash.
	bool m_flashOn;       // True of a flashing LED is currently lit.
	uint64_t m_lastFlash; // Time when a flashing LED was last turned on.
};

#endif
