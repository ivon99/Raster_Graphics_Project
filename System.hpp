#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_
#include "List.hpp"
#include "Session.hpp"
#include <iostream>
using namespace std;

/**
 * class holding all sessions ;
 * implements the user interface
 */
class System
{
  List<Session *> m_loaded_sessions; ///< list of all sessionsin system
  int m_current_sessionID; ///< holds the sessionID of the current working session

private:
  /// returns session with provided sessionID
  Session &switchSessions(int sessionID);
  /// adds a new session to current sessions
  void addSession(Session *session);
  /// prints information about the supported functionalities
  void help();

public:
  ///system default constructor
  /// creates a system with empty list of loaded sessions
  System();
  /// deleted assignment operator, as we don't wont system to be assigned
  System &operator=(const Session &other) = delete;
  /// deleted copy constructor as we dont want system to be copied
  System(const Session &other) = delete;
  int run();
};

#endif