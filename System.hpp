#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_
#include "List.hpp"
#include "Session.hpp"
#include <iostream>
using namespace std;

class System
{
  List<Session*> m_loaded_sessions;
  int m_current_sessionID;

  public:
  System();
  System& operator=(const Session& other) =delete;
  System(const Session& other) =delete;
  int run();
  Session& switchSessions(int sessionID);
  void addSession(Session* session);
  void help();
};

#endif