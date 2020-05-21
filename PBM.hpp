#ifndef _PBM_HPP_
#define _PBM_HPP_
#include "IImage.hpp"
#include <fstream>

class PBM: public IImage
{
  int m_rows;
  int m_col;
  char **m_bitmap;
  char *m_filename;

  void copyFrom(const PBM &other);
  int *extractBits(char *ch);
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
  virtual const char* getType() const override;
  friend char getAtIndex(PBM& obj,int row, int col);  //TODO: implement
  virtual const char* getFilename() const override;
  virtual void setAtIndex(int row, int col, char value) override;
  virtual void setFilname (const char* filename) override;
  virtual void print() override;

  //==images methods
  virtual void grayscale() override;
  virtual void monochrome()override;
  virtual void negative()override;

  virtual IImage* rotate(const char* direction) override;
  friend IImage* collage(PBM& first_PBM,const char* direction, PBM& other) ;

  //==files methods
  friend PBM &readPBMFromASCIIFile(std::ifstream &infile);
  friend PBM &readPBMFromBinaryFile(std::ifstream &infile);
  virtual void writeToASCIIFile(std::ofstream& outfile) override;
  virtual void writeToBinaryFile(std::ofstream& outfile) override;
};

 char getAtIndex(PBM& obj,int row, int col); 
 IImage* collage(PBM& first_PBM, const char* direction, PBM& other) ;

PBM &readPBMFromASCIIFile(std::ifstream &infile);
PBM &readPBMFromBinaryFile(std::ifstream &infile);

#endif