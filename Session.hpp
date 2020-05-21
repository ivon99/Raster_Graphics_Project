#ifndef _SESSION_HPP_
#define _SESSION_HPP_
#include <fstream>
#include "List.hpp"
#include "IImage.hpp"
#include "PBM.hpp"
#include "PGM.hpp"
#include "PPM.hpp"
#include "Command.hpp"

class Session
{
    List<IImage *> m_loaded_images;
    List<Command *> m_pending_commands;
    static int m_sessionID;
    //bool saveToASCIIFile(const char *filename, IImage *image);

public:
    Session();
    IImage *load(const char *filename);
    void close();
    void save();
    void save_as();
    void help();
    void exit();

    void grayscale();
    void monochrome();
    void negative();
    void rotate(const char *direction);
    void undo();
    //void addImage();
    void sessionInfo();
    /*
    void switchSession(int sessionID);
    void collage(const char* direction, PBM& first, PBM& other); //TODO:outputs image which will be added to current session
    void collage(const char* direction, PGM& first, PGM& other);
    void collage(const char* direction, PPM& first, PPM& other); */
   /* void savePBMToASCIIFile(std::ofstream &outfile, IImage* obj);
    void savePBMToBinaryFile(std::ofstream &outfile,IImage* obj);

    void savePGMToASCIIFile(std::ofstream &outfile,IImage* obj);
    void savePGMToBinaryFile(std::ofstream &outfile,IImage* obj);

    void savePPMToASCIIFile(std::ofstream &outfile,IImage* obj);
    void savePPMToBinaryFile(std::ofstream &outfile,IImage* obj); */
};

#endif
