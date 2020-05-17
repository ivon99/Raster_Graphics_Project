#ifndef _SESSION_HPP_
#define _SESSION_HPP_
#include "List.hpp"
#include "IImage.hpp"

class Session
{
    List<IImage*> m_loaded_images;
    static int m_sessionID;

};

#endif