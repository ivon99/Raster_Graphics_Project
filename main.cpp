#include <iostream>
#include <cstring>
#include "PBM.hpp"
using namespace std;
/*
bool open(const char *filename)
{
    std::ifstream infile;
    infile.open(filename);
    if (infile)
    {
        readPBMFromFile(infile, *mypbm);
        cout << "Succesfully read from " << filename << endl;
        infile.close();
        return *mypbm;
    }
    else
    { //creates a new empty file
        std::ofstream tmpfile;
        tmpfile.open(filename);
        infile.open(filename);
        cout << "Error in reading " << filename << ". A new filename with this name was generated" << endl;
        if (infile)
        {
            infile.close();
            return *mypbm;
        }
        else
        {
            cout << "Error:can't read from file." << endl;
            return *mypbm;
        }
    }
} */

bool importImagefromFile(const char *filename)
{
    std::ifstream infile;
    infile.open(filename);
    if (infile)
    {
        char magic_number[3];
        infile>>magic_number;
        cout<<magic_number;
        if(strcmp(magic_number,"P1")==0)
        {
            //PBM* new_pbm = new PBM();
            PBM* new_PBM =&readPBMFromASCIIFile(infile);
            cout << "Succesfully read from txt .pbm from " << filename << endl;
        infile.close();
        return true;
        }
         if(strcmp(magic_number,"P4")==0)
        {   
            infile.close();
            std::ifstream bin_infile(filename, std::ios::binary);
            if(bin_infile){
               readPBMFromBinaryFile(bin_infile);
                cout << "Succesfully read from binary .pbm from " << filename << endl;
            }
            else
            {
                cout<<"Unable to open file!"<<endl;
            }
            bin_infile.close();
            return true;
        }
         if(strcmp(magic_number,"P2")==0)
        {
           // readPGMfromASCIIFile();
           //cout << "Succesfully read from txt .pgm from " << filename << endl;
        } 
        if(strcmp(magic_number,"P5")==0)
        {
            //readPGMfromBinaryFile();
             //cout << "Succesfully read from binary .pgm from " << filename << endl;
        }
         if(strcmp(magic_number,"P3")==0)
        {
            //readPPMfromASCIIFile();
             //cout << "Succesfully read from txt .ppm from " << filename << endl;
        }
         if(strcmp(magic_number,"P6")==0)
        {
            //readPPMfromBinaryFile();
             //cout << "Succesfully read from txt .ppm from " << filename << endl;
        }
       
    }
    else
    { //creates a new empty file
        std::ofstream tmpfile;
        tmpfile.open(filename);
        infile.open(filename);
        //writeToFile(null picture)
        cout << "Error in reading " << filename << ". A new filename with this name was generated" << endl;
        if (infile)
        {
            infile.close();
            return true;;
        }
        else
        {
            cout << "Error:can't read from file." << endl;
            return false;
        }
    }
}



int main()
{
    cout<<"Welcome to hell"<<endl;
    //importImagefromFile("binary_example");
   // PBM test = readPBMFromASCIIFile("j.pbm");
   PBM test(10,6);
   std::ofstream outfile("outputbinaryfile.txt");
   if(!outfile)
   {
       cout<<"Problem loading file"<<endl;
   }

   writePBMToBinaryFile(outfile,test);
   outfile.close();
   /*PBM* test = new PBM(10,6);
   cout<<"pls:"<<endl;
   char ch= test->getAtIndex(1,0);
   cout<<"Character is: "<<ch<<"!"<<endl; */

    return 0;
}