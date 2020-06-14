#include <iostream>
#include <cstring>
#include "System.hpp"
using namespace std;
const int MAX_COMMAND_SIZE = 20;

void help()
{
  cout << "The following commands are supported:\n"
       << "load <filename>  \t\t loads an image from filename and starts a new session\n"
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
       << "switch <session> \t\t switches to session with <session id>\n"
       << "collage <direction> <image1> <image2> <outimage> collages two images\n"
       << "exit             \t\t exits programs\n"
       << "help            \t\t prints information about supported commands"
       << endl;
}

int main()
{
  cout << "Welcome to Project Raster Graphics. Please enter command:" << endl;
  char *command = new char[MAX_COMMAND_SIZE];
  command[0] = 'z';
  while (strcmp(command, "exit") != 0)
  {
    cin >> command;
    if (strcmp(command, "load") == 0)
    {
      System new_system;
      if (new_system.run() == 0)
      {
        cout << "Thank you for using project Raster Graphics! See you again." << endl;
        delete[] command;
        return 0;
      }
      continue;
    }
    if (strcmp(command, "help") == 0)
    {
      help();
      continue;
    }
    else if (strcmp(command, "exit") != 0)
    {
      cout << "Command not recognised! Try loading an image from file or try help." << endl;
      continue;
    }
  }
  cout << "Thank you for using project Raster Graphics! See you again." << endl;
  delete[] command;

  return 0;
}