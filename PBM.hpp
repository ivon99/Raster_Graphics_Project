#ifndef _PBM_HPP_
#define _PBM_HPP_
#include "IImage.hpp"
#include "Pixel.hpp"
#include <fstream>

/**
 * Class for portable bitmap format (PBM) encoded images
 * PBM images encode black and white images 
 * representing each pixel with a single bit.
 * Pixel values are 1(black) and 0(white)
 */

class PBM : public IImage
{
  //int m_rows;
  // int m_col;
  char **m_bitmap; ///< pixel map of image represented as a multi-dimensional array of bytes
  char *m_filename;  ///< stores filename from which the image is imported

  void copyFrom(const PBM &other);
  /// converts bit sequence of values to a byte
  /// &returns: a byte
  char convertBinaryToChar(int int_sequence[]);

public:
  //==THE BIG 4==

  PBM();
  PBM(int rows, int col);
  PBM(const PBM &other);
  PBM &operator=(const PBM &other);
  virtual ~PBM()
  {
    for (int i = 0; i < m_rows; i++)
    {
      delete[] m_bitmap[i];
    }
    delete[] m_bitmap;
    delete[] m_filename;
    std::cout << "PBM destructor called" << std::endl;
  }

  //==getters

  virtual const char *getType() const override;
  virtual const char *getFilename() const override;
  virtual int getNumRows() const override;
  virtual int getNumCol() const override;
  virtual char getAtIndex(int row, int col) const override;
  /// undefined method for PBM encoded files
  virtual Pixel getAtIndex(int row, int col, int unused) const override;
  
  //==setters

  virtual void setAtIndex(int row, int col, char value) override;
  virtual void setFilname(const char *filename) override;
  virtual void print() override;

  //==images methods

  /// method not defined for PBM images, as already B&W
  virtual void grayscale() override;
 /// method not defined for PBM images, as already B&W
  virtual void monochrome() override;
  /// inverses B&W values
  virtual void negative() override;
  virtual IImage *rotate(const char *direction) override;
  virtual IImage *collage(const char *direction, IImage *second_image) override;

  //==files methods

  /// reads PBM from ASCII encoded file
  /// & returns: newly read PBM image
  friend PBM &readPBMFromASCIIFile(std::ifstream &infile);
  /// reads PBM from binary encoded file
  /// & returns: newly read PBM image
  friend PBM &readPBMFromBinaryFile(std::ifstream &infile);
  virtual void writeToASCIIFile(std::ofstream &outfile) override;
  virtual void writeToBinaryFile(std::ofstream &outfile) override;
};

PBM &readPBMFromASCIIFile(std::ifstream &infile);
PBM &readPBMFromBinaryFile(std::ifstream &infile);

#endif