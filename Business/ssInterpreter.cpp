#include <ssInterpreter.h>
#include "ssBusinessManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <QString>

#include <dirent.h>
#include <unistd.h>

void ssInterpreter::cdProcedure(std::string command)
{
    chdir(command.substr(3, command.length()).c_str());
    
    DIR *d = opendir(".");
    struct dirent *ds;
    while(ds = readdir(d))
    {
        QString entryName = ds->d_name;
        ssBusinessManager::getInstance().suggestions << entryName;
    }
    void rewinddir(DIR *dir);
    int closedir(DIR *dir);
}


std::string ssInterpreter::execute(std::string command)
{
    
    
    if (command.find("cd") != std::string::npos)
    {
        cdProcedure(command);
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

    if(!ssBusinessManager::getInstance().suggestions.contains(command.c_str()))
    {
        QString qcommand = command.c_str();
        QStringList lst = qcommand.split(' ');
        ssBusinessManager::getInstance().suggestions << lst;
    }

    return output;
}