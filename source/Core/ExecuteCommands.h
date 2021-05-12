#pragma once
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class ExecuteCommands
{
private:
    std::string m_Command;
    std::string m_Result;
    std::string m_MultipleResult;
    int m_CommandCount;
    char *MultipleCommand[];

public:
    ExecuteCommands() : m_CommandCount(0){};

    void ExecuteSingleCommand(std::string command);
    
    void FetchSingleCommand(std::string command);

    void ExecuteMultipleCommands(char *command[], int numberOfCommand);

    std::string GetSingleResult() { return m_Result; }

    inline std::string GetSingleCommand() { return m_Command; }

    inline std::string GetMultipleResult() { return m_MultipleResult; }

    inline char *GetMultipleCommand() { return *MultipleCommand; }
};
