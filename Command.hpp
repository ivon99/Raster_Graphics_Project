#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

class Command
{
   char* m_command; 
   char* m_direction;

  public:
  Command(const char* command,const char* direction = "null");
  Command(const Command& other);
  Command& operator=(const Command& other);
  ~Command();

 const char* getCommand()const;
 const char* getDirection() const;
  void printCommand() const;
}; 

#endif