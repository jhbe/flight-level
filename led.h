#ifndef LED_H_
#define LED_H_

class Led {
public:
  Led(int gpioNumber, bool invert);
  ~Led();

  void Set(void);
  void Clear(void);
  void Flash(void);

  void Service(void);

private:
  void Assert(void);
  void Deassert(void);
  
private:
  bool m_invert;
  int m_gpioNumber;

  bool m_flash;
  bool m_flashOn;
  uint64_t m_lastFlash;
};

#endif /* LED_H_ */
