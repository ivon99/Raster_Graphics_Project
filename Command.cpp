#include "Command.hpp"
#include <cstring>
#include <iostream>
using namespace std;

Command::Command(const char *command, const char *direction)
{
    m_command = new char[strlen(command) + 1];
    strcpy(m_command, command);

    m_direction = new char[strlen(direction) + 1];
    strcpy(m_direction, direction);
}

Command::Command(const Command &other)
{
    if (this != &other)
    {
        m_command = new char[strlen(other.m_command) + 1];
        strcpy(m_command, other.m_command);
        m_direction = new char[strlen(other.m_direction) + 1];
        strcpy(m_direction, other.m_direction);
    }
}

Command &Command::operator=(const Command &other)
{
    if (this != &other)
    {
        delete[] m_command;
        delete[] m_direction;
        m_command = new char[strlen(other.m_command) + 1];
        strcpy(m_command, other.m_command);
        if (other.m_direction != nullptr)
        {
            m_direction = new char[strlen(other.m_direction) + 1];
            strcpy(m_direction, other.m_direction);
        }
        else
        {
            m_direction = nullptr;
        }
    }
    return *this;
}

Command::~Command()
{
    delete[] m_command;
    delete[] m_direction;
}

const char* Command::getCommand() const
{
  return m_command;
}

const char* Command::getDirection() const
{
    return m_direction;
}

void Command::printCommand() const
{
    cout << m_command << " ";
    if (strcmp(m_direction, "null") != 0)
    {
        cout << m_direction;
    }
}