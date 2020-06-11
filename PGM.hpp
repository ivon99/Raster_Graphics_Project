#ifndef _PGM_HPP_
#define _PGM_HPP_
#include <iostream>
#include <fstream>
#include "IImage.hpp"
using namespace std;

/**
 * Class for portable greymap format (PGM) encoded images
 * PGM images encode greyscale images 
 * representing each pixel with a single byte.
 * Pixel values range from 0 to greyscale value.  
 */

class PGM : public IImage
{
    // int m_rows;
    //int m_col;
    int m_grayscale;          //< hold max value for pixel (numbers of greys between black and white)
    unsigned char **m_bitmap; //< represents pixels of images as a two dimensional bytes array
    char *m_filename;         //< holds name from which PGM file is read

    void copyFrom(const PGM &other);

public:
    //==THE BIG 4==
    PGM();
    PGM(int rows, int col);
    PGM(const PGM &other);
    PGM &operator=(const PGM &other);
    virtual ~PGM()
    {
        for (int i = 0; i < m_rows; i++)
        {
            delete[] m_bitmap[i];
        }
        delete[] m_bitmap;
        delete[] m_filename;
        std::cout << "PGM destructor called" << std::endl;
    }

    //==getters
    virtual const char *getType() const override;
    virtual const char *getFilename() const override;
    virtual int getNumRows() const override;
    virtual int getNumCol() const override;
    virtual char getAtIndex(int row, int col) const override;
    /// undefined as PGM doesn't encode pixels in RGB format
    virtual Pixel getAtIndex(int row, int col, int unused) const override;

    //==setters
    virtual void setAtIndex(int row, int col, char value) override;
    virtual void setFilname(const char *filename) override;
    virtual void print() override;

    //==images methods
    virtual void grayscale() override;
    virtual void monochrome() override;
    virtual void negative() override;

    virtual IImage *rotate(const char *direction) override;
    virtual IImage *collage(const char *direction, IImage *second_image) override;

    //==files methods

    /// reads PGM from ASCII encoded file
    /// & returns: newly read PGM image
    friend PGM &readPGMFromASCIIFile(std::ifstream &infile);  
    /// reads PGM from binary encoded file
    /// & returns: newly read PGM image
    friend PGM &readPGMFromBinaryFile(std::ifstream &infile);
    virtual void writeToASCIIFile(std::ofstream &outfile) override;
    virtual void writeToBinaryFile(std::ofstream &outfile) override;
};

char getAtIndex(PGM &obj, int row, int col);

PGM &readPGMFromASCIIFile(std::ifstream &infile);
PGM &readPGMFromBinaryFile(std::ifstream &infile);

#endif
