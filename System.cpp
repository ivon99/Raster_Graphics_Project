#include "System.hpp"
#include <cstring>
const int MAX_FILENAME_SIZE = 1000;
const int MAX_DIRECTION_SIZE = 20;
const int MAX_COMMAND_SIZE = 20;


System::System()
{
  m_loaded_sessions = List<Session *>();
  m_current_sessionID = 0;
}

Session &System::switchSessions(int sessionID)
{
  //return *m_loaded_sessions.getElement(sessionID);
  if(((sessionID-1)>m_loaded_sessions.getSize())||((sessionID-1)<0))
  {
    cout<<"No session with this ID!"<<endl;
    return *m_loaded_sessions.getElement(0);
  }
  m_current_sessionID = sessionID-1;
  cout<<"You switched to session with ID:" <<sessionID<<"!"<<endl;
  m_loaded_sessions[m_current_sessionID]->sessionInfo();
  return *m_loaded_sessions.getElement(sessionID);
}

void System::addSession(Session *session)
{
  m_loaded_sessions.addElement(session);
}

void System::help()
{
  cout << "The following commands are supported:\n"
       << "load <filename>  \t\t loads an image from filename and starts a new session\n"
       << "add <filename>   \t\t adss a new image to current session \n"
       << "close            \t\t closes currently opened files\n"
       << "save             \t\t applies transformations and saves the currently opened files\n"
       << "saveas<filename_image> <filename_to_save>: \n saves image <filename_image> to a <filename_to_save>\n"
       << "grayscale        \t\t applies grayscale to loaded images\n"
       << "monochrome       \t\t transform loaded images to black and white\n"
       << "negative         \t\t applies colour inversion to loaded images\n"
       << "rotate <direction>\t\t rotates images to the left or right\n"
       << "undo             \t\t removes the last transformation\n"
       << "session info     \t\t prints information about opened images and transformations in session\n"
       << "switch <sessionID> \t\t switches to session with <session id>\n"
       << "collage <direction> <image1> <image2> <outimage> collages two images\n"
       << "exit             \t\t exits programs\n"
       << "help            \t\t prints information about supported commands"
       << endl;
}

int System::run()
{
  char *command = new char[MAX_COMMAND_SIZE];
  char *filename = new char[MAX_FILENAME_SIZE];
  char *direction = new char[MAX_DIRECTION_SIZE];
  command[0] = 'z';

  //loads first image 
  /*
  cin >> filename;
  Session *new_session = new Session();
  new_session->load(filename);
  m_loaded_sessions.addElement(new_session);
  m_current_sessionID = m_loaded_sessions.getSize() - 1; */
  Session *new_session = new Session();
  while(cin.peek()!='\n')
  {
    cin>>filename;
    new_session->load(filename);  // adds image to the new session

  }
  m_loaded_sessions.addElement(new_session); //adds session to list of sessions
  m_current_sessionID = m_loaded_sessions.getSize() - 1;  //sets current session ID


  while (strcmp(command, "exit") != 0)
  {
    cin >> command;
    if (strcmp(command, "load") == 0)
    {
      cin >> filename;
      Session *new_session = new Session();
      new_session->load(filename);
      m_loaded_sessions.addElement(new_session);
      m_current_sessionID = m_loaded_sessions.getSize() - 1;
      continue;
    }
    if (strcmp(command, "add") == 0)
    {
      cin >> filename;
      m_loaded_sessions[m_current_sessionID]->load(filename);
      continue;
    }
    if (strcmp(command, "close") == 0)
    {
      //m_loaded_sessions.deleteElement(m_current_sessionID);
      cin>>filename;
      m_loaded_sessions[m_current_sessionID]->close(filename);
      continue;
    }
    if (strcmp(command, "save") == 0)
    {
      m_loaded_sessions[m_current_sessionID]->save();
      cout<<"Successfully saved images to their files"<<endl;
      continue;
    }
    if (strcmp(command, "saveas") == 0)
    {
      cin >> filename;
      char* filename_to_save = new char[MAX_FILENAME_SIZE];
      cin>>filename_to_save;
      m_loaded_sessions[m_current_sessionID]->save_as(filename,filename_to_save);
      continue;
    }
    if (strcmp(command, "grayscale") == 0)
    {
      m_loaded_sessions[m_current_sessionID]->grayscale();
      continue;
    }
    if (strcmp(command, "monochrome") == 0)
    {
      m_loaded_sessions[m_current_sessionID]->monochrome();
      continue;
    }
    if (strcmp(command, "negative") == 0)
    {
      m_loaded_sessions[m_current_sessionID]->negative();
      continue;
    }
    if (strcmp(command, "rotate") == 0)
    {
      cin >> direction;
      m_loaded_sessions[m_current_sessionID]->rotate(direction);
      continue;
    }
    if (strcmp(command, "undo") == 0)
    {
      m_loaded_sessions[m_current_sessionID]->undo();
      continue;
    }
    if (strcmp(command, "session") == 0)
    {
      char *info = new char[MAX_COMMAND_SIZE];
      cin >> info;
      if (strcmp(info, "info") == 0)
      {
        m_loaded_sessions[m_current_sessionID]->sessionInfo();
        continue;
      }
      else
      {
        cout << "Command not recognised.Try: help()" << endl;
        continue;
      }
    }
    if (strcmp(command, "switch") == 0)
    {
      int session_ID;
      cin >> session_ID;
      //m_current_sessionID = session_ID;
      switchSessions(session_ID);
      continue;
    }
    if (strcmp(command, "collage") == 0)
    {
      char *second_image_filename = new char[MAX_FILENAME_SIZE];
      char *out_filename = new char[MAX_FILENAME_SIZE];
      cin >> direction;
      cin >> filename;
      cin >> second_image_filename;
      cin >> out_filename;
      m_loaded_sessions[m_current_sessionID]->collage(direction, filename, second_image_filename, out_filename);
      continue;
    }
    if (strcmp(command, "help") == 0)
    {
      help();
      continue;
    }
    else if(strcmp(command,"exit")!=0)
    {
      cout << "Unknown command, please try help to see supported functionalities" << endl;
      continue;
    }
  }
  return 0;
}