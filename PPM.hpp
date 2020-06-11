#ifndef _PPM_HPP_
#define _PPM_HPP_
#include <iostream>
#include "Pixel.hpp"
#include "IImage.hpp"
using namespace std;

/**
 * Class for portable pixmap format (PPM) encoded images
 * PPM images encode colour images
 * representing each pixel as 3 bytes (1 byte per Red, Green, Blue)
 * Pixel values range from 0 up to colourscale value for every RGB byte
 */

class PPM : public IImage
{
  //int m_rows;
  //int m_col;
  int m_colourscale; ///< maximum value for every byte in RGB
  Pixel **m_bitmap;  //< pixel map is represented as 2D array of RGB pixels
  char *m_filename;  //< holds filename from which PPM image is read

  void copyFrom(const PPM &other);

public:
  //==THE BIG 4==
  PPM();
  PPM(int rows, int col);
  PPM(const PPM &other);
  PPM &operator=(const PPM &other);
  virtual ~PPM()
  {
    for (int i = 0; i < m_rows; i++)
    {
      delete[] m_bitmap[i];
    }
    delete[] m_bitmap;
    delete[] m_filename;
    std::cout << "PPM destructor called" << std::endl;
  }

  //==getters
  virtual const char *getType() const override;
  virtual const char *getFilename() const override;
  virtual int getNumRows() const override;
  virtual int getNumCol() const override;
  virtual char getAtIndex(int row, int col) const override;
  /// returns RGB pixel at given coordinates
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
  /// reads PPM from ASCII encoded file
  /// & returns: newly read PPM image
  friend PPM &readPPMFromASCIIFile(std::ifstream &infile);
  /// reads PPM from binary encoded file
  /// & returns: newly read PPM image
  friend PPM &readPPMFromBinaryFile(std::ifstream &infile);
  virtual void writeToASCIIFile(std::ofstream &outfile) override;
  virtual void writeToBinaryFile(std::ofstream &outfile) override;
};

Pixel getAtIndex(PPM &obj, int row, int col);

IImage *collage(PPM &first_PPM, const char *direction, PPM &other);

PPM &readPPMFromASCIIFile(std::ifstream &infile);
PPM &readPPMFromBinaryFile(std::ifstream &infile);

#endif