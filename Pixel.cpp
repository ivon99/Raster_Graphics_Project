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

Pixel& Pixel::operator-(int value)
{
    m_R-=value;
    m_G-=value;
    m_B-=value;
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

