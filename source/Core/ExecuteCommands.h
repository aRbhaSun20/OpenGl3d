#pragma once
#include <Precomz/precomz.h>

#include "LogFile.h"

class ExecuteCommands
{
private:
    std::vector<std::string> m_MultipleResult;
    Logger::LogFile &execute_File;

public:
    ExecuteCommands(Logger::LogFile &LogFile)
        : execute_File(LogFile){
          CORE_INFO("Execution Starting");
    };

~ExecuteCommands(){
    CORE_WARN("Execution Closing");
}
    std::string ExecuteSingleCommand(std::string command);

    void ExecuteMultipleCommands(std::vector<std::string> commands);

    inline std::vector<std::string> GetMultipleResult() { return m_MultipleResult; }
};
