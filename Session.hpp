#ifndef _SESSION_HPP_
#define _SESSION_HPP_
#include <fstream>
#include "List.hpp"
#include "IImage.hpp"
#include "PBM.hpp"
#include "PGM.hpp"
#include "PPM.hpp"
#include "Command.hpp"

/**
 * class holding currently loaded images 
 * as well as pending commands
 * characterised by session ID
 */

class Session
{
    List<IImage *> m_loaded_images; ///< holds currently loaded images
    List<Command *> m_pending_commands; ///< hold commands waiting to be executed
    static int m_sessionID;  ///< characterises a unique session

private:
    /// returns index of image in loaded images list
    int get_index_of_loaded_image_by_filename(const char* filename);

public:
    /// default constructor creating a session with no images and no pending commands
    /// sets a unique session ID
    Session();
    /// returns pointer to loaded image at given index
    IImage *get_loaded_image(int index);
    /// returns pointer to loaded image by given filename of image
    IImage *get_loaded_image_by_filename(const char *filename);
    /// adds an image to loaded images repository
    IImage *load(const char *filename);
    /// removes given loaded image from session
    void close(const char* filename);
    /// applies all the pending commands to all the loaded images in session
    void save();
    /// saves an image to an ASCII encoded file with provided filename
    void save_as(const char* image_filename, const char * save_to_filename);
    /// adds grayscale() command to pending commands
    void grayscale();
    /// adds monochrome() command to pending commands
    void monochrome();
    /// adds negative() command to pending commands
    void negative();
    /// adds rotate() command to pending commands
    void rotate(const char *direction);
    /// adds result of collage command to loaded images in session
    void collage(const char *direction, const char *first_image_filename, const char *second_image_filename, const char *out_filename);
    /// removes last pending command
    void undo();
    /// prints filenames of loaded images and pending commands
    void sessionInfo();
};

#endif
