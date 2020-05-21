#ifndef _IIMAGE_HPP_
#define _IIMAGE_HPP_
#include <iostream>

class IImage
{
public:
    virtual const char *getType() const = 0;
    virtual const char* getFilename() const = 0;
    virtual void setAtIndex(int row, int col, char value) = 0;
    virtual void setFilname (const char* filename) =0;
    virtual void print() = 0;
    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;

    virtual IImage* rotate(const char *direction) = 0;
    virtual void writeToASCIIFile(std::ofstream& outfile) =0;
    virtual void writeToBinaryFile(std::ofstream& outfile) =0;
    virtual ~IImage()
    {
        std::cout << "IImage destructor called" << std::endl;
    }
};

#endif