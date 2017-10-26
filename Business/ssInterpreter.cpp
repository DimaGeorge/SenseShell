#include <ssInterpreter.h>
#include <stdio.h>

std::string ssInterpreter::execute(std::string command)
{
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