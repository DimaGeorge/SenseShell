#include <ssInterpreter.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


std::string ssInterpreter::execute(std::string command)
{
    if (command.find("cd") != std::string::npos)
    {
        printf("+++++++++++++++++++++++%s\n", command.substr(4, command.length()).c_str());
        chdir(command.substr(4, command.length()).c_str());
        std::string output = "";
        return output;
    }

    FILE *pipe = popen(command.c_str(), "r");
    if(!pipe)
    {
        printf("error!");
    }   

    char buffer[1024];
    std::string output = "";
    while(!feof(pipe))
    {
        if(fgets(buffer, 1023, pipe) != NULL)
        {
            output += buffer;
        }
    }

    return output;
}