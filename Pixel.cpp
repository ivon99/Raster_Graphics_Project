#include "Pixel.hpp"
#include <iostream>
using namespace std;

Pixel::Pixel(unsigned char R,unsigned char G,unsigned char B)
{
  m_R=R;
  m_G=G;
  m_B=B;
}

Pixel& Pixel::operator=(const Pixel& other)
{
  m_R=other.m_R;
  m_G = other.m_G;
  m_B= other.m_B;
  return *this;
}

bool Pixel::isWhite() const
{
  if((m_R==255)&&
      (m_G==255)&&
      (m_B==255))
      {
          return true;
      }
    else
    {
        return false;
    }  
}

bool Pixel::isGrey() const
{
  if((m_R==m_G)&&(m_R==m_B)&&(m_B==m_G))
  {
    return true;
  }
  else
  {
    return false;
  }
}


Pixel& Pixel::operator-(int value)
{
  unsigned char old_R =m_R;
  unsigned char old_G= m_G;
  unsigned char old_B= m_B;
    m_R=value-old_R;
    m_G=value-old_G;
    m_B=value-old_B;
    return *this;
}

bool Pixel::operator>(int value)
{
   if((m_R>value)&&
      (m_G>value)&&
      (m_B>value))
      {
          return true;
      }
    else
    {
        return false;
    }  
}


std::ostream& operator<<(std::ostream& out, Pixel& other)
{
     out<<other.m_R<<other.m_G<<other.m_B;
     return out;
}

