#include <iostream>
#include <cstring>
#include "PBM.hpp"
#include "PGM.hpp"
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
           readPBMFromASCIIFile(infile);
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
           readPGMFromASCIIFile(infile);
           cout << "Succesfully read from txt .pgm from " << filename << endl;
        } 
        if(strcmp(magic_number,"P5")==0)
        {
            infile.close();
            std::ifstream bin_infile(filename, std::ios::binary);
            if(bin_infile){
               readPGMFromBinaryFile(bin_infile);
                cout << "Succesfully read from binary .pgm from " << filename << endl;
            }
            else
            {
                cout<<"Unable to open file!"<<endl;
            }
            bin_infile.close();
            return true;
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
    return false;
}



int main()
{
    cout<<"Welcome to hell"<<endl;
    PGM test(3,4);
    test.setAtIndex(2,3,1);
    test.setAtIndex(1,0,1);
    //test.negative();
    //test.printPGM(); 
    //test.monochrome();
    //test.printPGM();
   /* std::ofstream outfile("output_PGM.txt");
   if(!outfile)
   {
       cout<<"Problem loading file"<<endl;
   }

   writePGMToASCIIFile(outfile,test);
   outfile.close(); */


  /*  const char* r_rot = "right";
    PGM* r_rotated = &test.rotate(r_rot);
    r_rotated->printPGM();

   const char* l_rot="left";
    PGM* l_rotated=&test.rotate(l_rot);
    l_rotated->printPGM(); 

     const char* direction = "vertical";
    PGM* new_collage= &test.collage(direction,test);
    new_collage->printPGM();

     const char* direction_h = "horizontal";
    PGM* new_hcollage= &test.collage(direction_h,test);
    new_hcollage->printPGM(); */

  //  importImagefromFile("baboon.pgm");
  // PGM* test = &readPGMFromASCIIFile("feep.pgm");

   /*PBM test(4,3);
   test.setAtIndex(2,3,1);
   test.setAtIndex(1,0,1);
   test.setAtIndex(0,0,1);
   test.printPBM();

   PBM test2(4,3);
   test2.setAtIndex(2,3,1);
   test2.setAtIndex(1,0,1);
   test2.setAtIndex(3,1,1);
   test2.printPBM(); 

   const char* direction = "vertical";
  PBM* new_collage= &test.collage(direction,test2);
  new_collage->printPBM(); */

   //test.negative();
   //test.printPBM();
   //const char* direction = "left";
     
  // PBM* rotated= &test.rotate(direction);
   //rotated->printPBM();
  /*
  const char* r_direction = "right";
   test.rotate(r_direction);
   PBM* rotated_right = &test.rotate(r_direction);
   rotated_right->printPBM(); */

   //==test files
  std::ofstream outfile("outputbinaryfile.txt");
   if(!outfile)
   {
       cout<<"Problem loading file"<<endl;
   }

   writePGMToBinaryFile(outfile,test);
   outfile.close(); 
   /*PBM* test = new PBM(10,6);
   cout<<"pls:"<<endl;
   char ch= test->getAtIndex(1,0);
   cout<<"Character is: "<<ch<<"!"<<endl; */

    return 0;
}