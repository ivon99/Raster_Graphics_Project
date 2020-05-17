#ifndef _IIMAGE_HPP_
#define _IIMAGE_HPP_
#include <iostream>

class IImage
{
    public:
    virtual const char* getType() const =0;
    virtual char getAtIndex(int row, int col)=0;
     virtual void  setAtIndex(int row, int col, char value)=0;
    //void grayscale()=0;
    //void monochrome()=0;
    //void negative()=0;
    //void rotate(const char* direction)=0;
   //IImage& collage(const char* direction, IImage& other) =0;

    virtual ~IImage()
    {
     std::cout<<"IImage destructor called"<<std::endl; 
    }
};

#endif