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
    IImage* get_loaded_image(int index);

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
    void collage(IImage* first_image,const char* direction,IImage* second_image);
    void undo();
    //void addImage();
    void sessionInfo();
    //void switchSession(int sessionID);

};

#endif
