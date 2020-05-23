#include "System.hpp"
#include <cstring>
const int MAX_FILENAME_SIZE=1000;
const int MAX_DIRECTION_SIZE= 20;
const int MAX_COMMAND_SIZE =20;

System::System()
{
  m_loaded_sessions = List<Session*>();
  m_current_sessionID=0;
}

void clearCommand(char command[])
{
    for (int i = 0; i < 20; i++)
    {
        command[i] = ' ';
    }
}

Session& System::switchSessions(int sessionID)
{
 return *m_loaded_sessions.getElement(sessionID);
} 

void System::addSession(Session *session)
{
   m_loaded_sessions.addElement(session);
}

void System::help()
{
    cout << "The following commands are supported:\n"
         << "load <filename>  \t\t loads an image from filename and starts a new session "
         << "add <filename>   \t\t adss a new image to current session \n"
         << "close            \t\t closes currently opened files\n"
         << "save             \t\t applies transformations and saves the currently opened files\n"
         << "saveas <filename>\t\t saves the currently opened files in <file>\n"
         << "grayscale        \t\t applies grayscale to loaded images\n"
         << "monochrome       \t\t transform loaded images to black and white\n"
         << "negative         \t\t applies colour inversion to loaded images\n"
         << "rotate <direction>\t\t rotates images to the left or right\n"
         << "undo             \t\t removes the last transformation\n"  
         << "session info     \t\t prints information about opened images and transformations in session\n"
         << "switch <session> \t\t switches to session with <session> id"
         << "collage <direction> <image1> <image2> <outimage>\t\t collages two images\n"
         << "exit             \t\t exits programs\n"
         << "help            \t\t prints information about supported commands\n" << endl;
}


int System::run()
{
  cout << "Welcome to Project Raster Graphics. Please enter command:" << endl;
  char command[MAX_COMMAND_SIZE];
  command[0] = 'z';
  while(strcmp(command,"exit")!=0)
  {
      cin>>command;
      if(strcmp(command,"load")==0)
      {
        clearCommand(command);
        cin.get();
        char* filename = new char[MAX_FILENAME_SIZE];
        cin>>filename;
        Session* new_session = new Session();
        new_session->load(filename);
        m_loaded_sessions.addElement(new_session);
        m_current_sessionID= m_loaded_sessions.getSize()-1;
      }
      if(strcmp(command,"add")==0)
      {
        clearCommand(command);
        cin.get();
        char* filename = new char[MAX_FILENAME_SIZE];
        cin>>filename;
        m_loaded_sessions[m_current_sessionID]->load(filename);
      }
      if(strcmp(command,"close")==0)
      {
        clearCommand(command);
        cin.get();
        m_loaded_sessions.deleteElement(m_current_sessionID);
        }
      if(strcmp(command,"save")==0)
      {
        clearCommand(command);
        cin.get();
        m_loaded_sessions[m_current_sessionID]->save();
      }
      if(strcmp(command,"save as")==0)
      {
        clearCommand(command);
        cin.get();
        char* filename = new char[MAX_FILENAME_SIZE];
        cin>>filename;
        m_loaded_sessions[m_current_sessionID]->save_as(filename);
      }
      if(strcmp(command,"grayscale")==0)
      {
        clearCommand(command);
        cin.get();
        m_loaded_sessions[m_current_sessionID]->grayscale();
      }
      if(strcmp(command,"monochrome")==0)
      {
        clearCommand(command);
        cin.get();
        m_loaded_sessions[m_current_sessionID]->monochrome();
      }
      if(strcmp(command,"negative")==0)
      {
        clearCommand(command);
        cin.get();
        m_loaded_sessions[m_current_sessionID]->negative();
      }
      if(strcmp(command,"rotate")==0)
      {
        clearCommand(command);
        cin.get();
        char* direction = new char[MAX_DIRECTION_SIZE];
        cin>>direction;
        m_loaded_sessions[m_current_sessionID]->rotate(direction);
      }
     if(strcmp(command,"undo")==0)
      {
        clearCommand(command);
        cin.get();
        m_loaded_sessions[m_current_sessionID]->undo();
      }
      if(strcmp(command,"session")==0)
      {
        clearCommand(command);
        cin.get();
        char* info= new char[MAX_COMMAND_SIZE];
        cin>>info;
        if(strcmp(info, "info")==0)
        {
             m_loaded_sessions[m_current_sessionID]->sessionInfo();
        }
        else
        {
            cout<<"Command not recognised.Try: help()" <<endl;
        }
      }
      if(strcmp(command,"switch")==0)
      {
        clearCommand(command);
        cin.get();
        int session_ID;
        cin>>session_ID;
        m_current_sessionID= session_ID;
      }
      if(strcmp(command,"collage")==0)
      {
        clearCommand(command);
        cin.get();
        char* direction= new char[MAX_DIRECTION_SIZE];
        char* first_image_filename= new char[MAX_FILENAME_SIZE];
        char* second_image_filename= new char[MAX_FILENAME_SIZE];
        char* out_filename = new char[MAX_FILENAME_SIZE];
        cin>>direction;
        cin>>first_image_filename;
        cin>>second_image_filename;
        cin>>out_filename;
        m_loaded_sessions[m_current_sessionID]->collage(direction,first_image_filename,second_image_filename,out_filename);
      }
      if(strcmp(command,"help")==0)
      {
        clearCommand(command);
        cin.get();
        help();
      }
  }
  return 0;
}