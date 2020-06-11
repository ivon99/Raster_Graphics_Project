#ifndef _IIMAGE_HPP_
#define _IIMAGE_HPP_
#include <iostream>
#include "Pixel.hpp"

/**
 * Abstract class for images
 * consists only of pure virtual methods which will be overriden  
 * in the different classes for image file types
 * declares all common image methods:
 * getters and setters, methods which modify an image
 * and writing image to a file 
 */
class IImage
{
protected:
    int m_rows; ///< stores number of rows in image
    int m_col;  ///< stores number of columns in image

public:
    //==getters
    /// returns type of image
    virtual const char *getType() const = 0;
    /// returns filename from which the image was imported
    virtual const char *getFilename() const = 0;
    /// returns height of image
    virtual int getNumRows() const = 0;
    /// returns width of image
    virtual int getNumCol() const = 0;
    /// returns single pixel for images that are not RGB encoded
    virtual char getAtIndex(int row, int col) const = 0;
    /// returns Pixel data for RGB encoded images
    virtual Pixel getAtIndex(int row, int col, int unused) const = 0;

    //==setters
    /// sets a pixel with given value at given coordinates
    /// used in non RGB encoded images
    virtual void setAtIndex(int row, int col, char value) = 0;
    /// renames an image's filename
    virtual void setFilname(const char *filename) = 0;
    /// prints image in console
    virtual void print() = 0;

    //===image methods
    ///applies greyscale to image
    virtual void grayscale() = 0;
    /// applies monochrome to image
    virtual void monochrome() = 0;
    /// makes an image negative
    virtual void negative() = 0;
    /// collages two images in given direction
    /// &returns: pointer to new collaged image
    virtual IImage *collage(const char *direction, IImage *second_image) = 0;
    /// rotates an image at 90 degrees in given direction
    /// &returns: pointer to new rotated image
    virtual IImage *rotate(const char *direction) = 0;

    //==file methods
    /// writes image to ASCII format
    virtual void writeToASCIIFile(std::ofstream &outfile) = 0;
    /// writes image to binary format
    virtual void writeToBinaryFile(std::ofstream &outfile) = 0;

    //==virtual destructor
    /// virtual destructor for abstract class
    virtual ~IImage()
    {
        std::cout << "IImage destructor called" << std::endl;
    }
};

#endif