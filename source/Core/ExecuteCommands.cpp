#include "ExecuteCommands.h"

std::string ExecuteCommands::ExecuteSingleCommand(std::string command)
{
    std::string data;
    FILE *stream;
    const int max_buffer = 1024;
    char buffer[max_buffer];
    command.append(" 2>&1");

    stream = popen(command.c_str(), "r");

    if (stream)
    {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL)
                data.append(buffer);
        pclose(stream);
    }

    data.pop_back();

    return data;
}

void ExecuteCommands::ExecuteMultipleCommands(std::vector<std::string> commands) 
{
    for (int i = 0; i < commands.size(); i++)
        m_MultipleResult.push_back(ExecuteSingleCommand(commands[i]));   
}