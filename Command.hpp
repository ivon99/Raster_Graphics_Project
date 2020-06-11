#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

/**
 * class for command
 */
class Command
{
  char *m_command; ///< holds name of command
  char *m_direction; ///< holds direction for command

public:
  /// creates a command by given command name
  /// default constructor: creates a null command
  Command(const char *command="null", const char *direction = "null");
  Command(const Command &other);
  Command &operator=(const Command &other);
  ~Command();

  /// returns name of command
  const char *getCommand() const;
  /// returns direction of command
  const char *getDirection() const;
  /// prints command
  void printCommand() const;
};

#endif