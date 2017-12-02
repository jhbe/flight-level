#ifndef XYZ_H
#define XYZ_H

/**
 * This class hold a triplet of floats and provides scalar operators.
 */
class XYZ {
public:
  XYZ() {
    m_x = 0.0; m_y = 0.0; m_z = 0.0;
  }
  XYZ(float x, float y, float z)  {
    m_x = x; m_y = y; m_z = z;
  }

  float X(void) {return m_x;}
  float Y(void) {return m_y;}
  float Z(void) {return m_z;}
  
  void Reset() {
    m_x = 0.0; m_y = 0.0; m_z = 0.0;
  }
  
  void Add(float x, float y, float z) {
    m_x += x; m_y += y; m_z += z;
  }

  XYZ operator/(const float v) {
    return XYZ(m_x / v, m_y / v, m_z / v);
  }

  void operator/=(const float v) {
    m_x /= v;
    m_y /= v;
    m_z /= v;
  }

private:
  float m_x;
  float m_y;
  float m_z;  
};

#endif
