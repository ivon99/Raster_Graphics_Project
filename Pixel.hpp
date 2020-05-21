#ifndef _PIXEL_HPP_
#define _PIXEL_HPP_
#include <iostream>

struct Pixel
{
  unsigned char m_R;
  unsigned char m_G;
  unsigned char m_B;

  Pixel(unsigned char R=0,unsigned char G=0,unsigned char B=0);

  operator int() const;
  Pixel& operator=(const Pixel& other);
  Pixel& operator-(int value);
  bool operator>(int value);
  friend std::ostream& operator<<(std::ostream& out, Pixel& other);
};

std::ostream& operator<<(std::ostream& out, Pixel& other);

#endif