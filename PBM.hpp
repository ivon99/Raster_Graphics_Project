#ifndef _PBM_HPP_
#define _PBM_HPP_
#include "IImage.hpp"
#include <fstream>


class PBM  //  : //public IImage
{
  int m_rows;
  int m_col;
  char** m_bitmap;
  char* m_filename;

  void copyFrom(const PBM& other);
  int* extractBits(char* ch);
  char convertBinaryToChar(int int_sequence[]);

   public:
   //==THE BIG 4==
   PBM();
   PBM(int rows, int col);
   PBM(const PBM& other);
   PBM& operator=(const PBM& other);
   virtual ~PBM(){
     for(int i=0; i<m_rows; i++)
     {
         delete[] m_bitmap[i];
     }
     delete[] m_bitmap;
     delete[] m_filename;
     std::cout<<"PBM destructor called"<<std::endl;
   }

   //==getters 
   const char* getType() const  ;
    char getAtIndex(int row, int col) ;
    void  setAtIndex(int row, int col, char value) ;
    void printPBM();

    //==images methods
     // void grayscale()=0; NOT allowed !!
    //void monochrome()=0; NOT allowed!!
     void negative();
     PBM& rotate(const char* direction);
     PBM& collage(const char* direction, PBM& other);

   //==files methods
   friend PBM& readPBMFromASCIIFile(std::ifstream& infile);
   friend PBM& readPBMFromBinaryFile(std::ifstream& infile);

   friend void writePBMToASCIIFile(std::ofstream&outfile, PBM& obj);
   friend void writePBMToBinaryFile(std::ofstream&outfile, PBM& obj);
};

PBM& readPBMFromASCIIFile(std::ifstream& infile);
PBM& readPBMFromBinaryFile(std::ifstream& infile);

void writePBMToASCIIFile(std::ofstream&outfile, PBM& obj);
void writePBMToBinaryFile(std::ofstream&outfile, PBM& obj);

#endif