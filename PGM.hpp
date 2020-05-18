#ifndef _PGM_HPP_
#define _PGM_HPP_
#include <iostream>
#include <fstream>
using namespace std;

class PGM{
 int m_rows;
  int m_col;
  int m_grayscale;
  char** m_bitmap;
  char* m_filename;

  void copyFrom(const PGM& other);

   public:
   //==THE BIG 4==
   PGM();
   PGM(int rows, int col);
   PGM(const PGM& other);
   PGM& operator=(const PGM& other);
   virtual ~PGM(){
     for(int i=0; i<m_rows; i++)
     {
         delete[] m_bitmap[i];
     }
     delete[] m_bitmap;
     delete[] m_filename;
     std::cout<<"PGM destructor called"<<std::endl;
   }

   //==getters 
   const char* getType() const  ;
    char getAtIndex(int row, int col) ;
    void  setAtIndex(int row, int col, char value) ;
    void printPGM();
    //int* extractBitsPGM(char* ch);
  //char convertBinaryToCharPGM(int int_sequence[]);

    //==images methods
     // void grayscale()=0; NOT allowed !!
     void monochrome();
     void negative();
     PGM& rotate(const char* direction);
     PGM& collage(const char* direction, PGM& other);

   //==files methods
   friend PGM& readPGMFromASCIIFile(std::ifstream& infile);
   friend PGM& readPGMFromBinaryFile(std::ifstream& infile);

   friend void writePGMToASCIIFile(std::ofstream&outfile, PGM& obj);
   friend void writePGMToBinaryFile(std::ofstream&outfile, PGM& obj);
};

PGM& readPGMFromASCIIFile(std::ifstream& infile);
PGM& readPGMFromBinaryFile(std::ifstream& infile);

void writePGMToASCIIFile(std::ofstream&outfile, PGM& obj);
void writePGMToBinaryFile(std::ofstream&outfile, PGM& obj);


#endif