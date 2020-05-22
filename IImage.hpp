#ifndef _IIMAGE_HPP_
#define _IIMAGE_HPP_
#include <iostream>
#include "Pixel.hpp"

class IImage
{
public:
    //==getters
    virtual const char *getType() const = 0;
    virtual const char *getFilename() const = 0;
    virtual int getNumRows() const = 0;
    virtual int getNumCol() const = 0;
    virtual char getAtIndex(int row, int col) const = 0;
    virtual Pixel getAtIndex(int row, int col, int unused) const = 0;

    //==setters
    virtual void setAtIndex(int row, int col, char value) = 0;
    virtual void setFilname(const char *filename) = 0;
    virtual void print() = 0;

    //===image methods
    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;
    virtual IImage *collage(const char *direction, IImage *second_image) = 0;
    virtual IImage *rotate(const char *direction) = 0;

    virtual void writeToASCIIFile(std::ofstream &outfile) = 0;
    virtual void writeToBinaryFile(std::ofstream &outfile) = 0;

    virtual ~IImage()
    {
        std::cout << "IImage destructor called" << std::endl;
    }
};

#endif