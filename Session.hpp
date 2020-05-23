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
    IImage* get_loaded_image_by_filename(const char* filename);

    IImage *load(const char *filename);
    void close();
    void save();
    void save_as(const char* filename);
    void help();
    void exit();

    void grayscale();
    void monochrome();
    void negative();
    void rotate(const char *direction);
    //void collage(IImage* first_image,const char* direction,IImage* second_image);
   void collage(const char* direction,const char* first_image_filename,const char* second_image_filename, const char* out_filename);
    void undo();
   // void addImage();
    void sessionInfo();
};

#endif
