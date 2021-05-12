#include "ExecuteCommands.h"

void ExecuteCommands::ExecuteSingleCommand(std::string command)
{
    m_Command = command;
    std::string data;
    FILE *stream;
    const int max_buffer = 1024;
    char buffer[max_buffer];
    m_Command.append(" 2>&1");

    stream = popen(m_Command.c_str(), "r");

    if (stream)
    {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL)
                data.append(buffer);
        pclose(stream);
    }
    
    data.pop_back();
    m_Result = data;
}

void ExecuteCommands::ExecuteMultipleCommands(char *command[], int numberOfCommand)
{
    for (int i = 0; i < numberOfCommand; i++)
    {
        ExecuteSingleCommand(command[i]);
        m_MultipleResult.append(m_Result);
        MultipleCommand[i] = command[i];
    }
    m_CommandCount = numberOfCommand;
}