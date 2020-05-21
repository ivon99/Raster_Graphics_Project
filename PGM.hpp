#ifndef _PGM_HPP_
#define _PGM_HPP_
#include <iostream>
#include <fstream>
#include "IImage.hpp"
using namespace std;

class PGM: public IImage
{
    int m_rows;
    int m_col;
    int m_grayscale;
    char** m_bitmap;
    char* m_filename;

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
    virtual const char* getType() const override;
    virtual const char* getFilename() const override;
    friend char getAtIndex(PGM& obj,int row, int col); 
    virtual void setAtIndex(int row, int col, char value) override;
    virtual void setFilname (const char* filename) override;
    virtual void print() override;

    //==images methods
    virtual void grayscale() override;
    virtual void monochrome() override;
    virtual void negative() override;

    virtual IImage* rotate(const char *direction) override;
    friend IImage* collage(PGM& first_PGM,const char *direction, PGM& other) ;
    
    //==files methods
    friend PGM& readPGMFromASCIIFile(std::ifstream &infile);
    friend PGM& readPGMFromBinaryFile(std::ifstream &infile);
    virtual void writeToASCIIFile(std::ofstream& outfile) override;
    virtual void writeToBinaryFile(std::ofstream& outfile) override;
};

char getAtIndex(PGM& obj,int row, int col); 
IImage* collage(PGM& first_PGM, const char *direction, PGM& other) ;

PGM &readPGMFromASCIIFile(std::ifstream &infile);
PGM &readPGMFromBinaryFile(std::ifstream &infile);

#endif