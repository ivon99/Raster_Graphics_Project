#ifndef _PIXEL_HPP_
#define _PIXEL_HPP_
#include <iostream>

/**
 * Pixel structure
 * represent RGB pixel for colour images 
 */

struct Pixel
{
  unsigned char m_R; ///< red colour value
  unsigned char m_G; ///< green colour value
  unsigned char m_B; ///< blue colour value

  /// constructor for pixel
  /// default value: creates a black pixel
  Pixel(unsigned char R=0,unsigned char G=0,unsigned char B=0);
  ///asignment operator for Pixel
  Pixel& operator=(const Pixel& other);

  /// returns true if pixel represents white colour
  bool isWhite() const;
  /// returns true if pixel represents a grey colour
  bool isGrey() const;

  /// substracts value to every colour value in RGB
  Pixel& operator-(int value);
  /// compares every colour value to a given value
  bool operator>(int value);
  friend std::ostream& operator<<(std::ostream& out, Pixel& other);
};
/// output operator for a RGB pixel
std::ostream& operator<<(std::ostream& out, Pixel& other);

#endif