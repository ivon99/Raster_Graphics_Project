#include <iostream>
#include <cstring>
#include "Session.hpp"
using namespace std;

int main()
{
    cout<<"Welcome to hell"<<endl;
    Session s1;
    //s1.load("zaj.pbm");
    //s1.load("zabinary.pbm");
    //s1.load("zcfeep.pgm");
    //s1.load("zcfeep-bin.pgm");
    //s1.load("zlrainbow.ppm");
    s1.load("bell_206.ppm"); //FIXME: not able to read binary
    s1.grayscale();
    //s1.monochrome();
    //s1.negative();
    //const char* direction = "left";
    //const char* l_direction = "right";
   // s1.rotate(direction);
    //s1.rotate(l_direction);
   // s1.undo(); 
    s1.sessionInfo();
    s1.save();
   //s1.save_as();
    
    
    //PPM test(3,4);
   // test.setAtIndex(2,3,{0,0,255});
    //test.setAtIndex(1,0,{255,0,0});
   // test.negative();
    //test.printPPM(); 
     //test.negative();
   //  test.printPPM();
    //test.monochrome();
    //test.printPGM();
  /* std::ofstream outfile("output_PPM.txt");
   if(!outfile)
   {
       cout<<"Problem loading file"<<endl;
   }

   writePPMToBinaryFile(outfile,test);
   outfile.close(); */


   /*const char* r_rot = "right";
    PPM* r_rotated = &test.rotate(r_rot);
    r_rotated->printPPM();

   const char* l_rot="left";
    PPM* l_rotated=&test.rotate(l_rot);
    l_rotated->printPPM(); 

     const char* direction = "vertical";
    PPM* new_collage= &test.collage(direction,test);
    new_collage->printPPM();

     const char* direction_h = "horizontal";
    PPM* new_hcollage= &test.collage(direction_h,test);
    new_hcollage->printPPM(); 
    */
   // importImagefromFile("6colours.ppm");
    //PPM* test = &readPGMFromASCIIFile("feep.pgm");

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
  /*std::ofstream outfile("outputbinaryfile.txt");
   if(!outfile)
   {
       cout<<"Problem loading file"<<endl;
   }

   writePGMToBinaryFile(outfile,test);
   outfile.close();  */
   /*PBM* test = new PBM(10,6);
   cout<<"pls:"<<endl;
   char ch= test->getAtIndex(1,0);
   cout<<"Character is: "<<ch<<"!"<<endl; */

    return 0;
}