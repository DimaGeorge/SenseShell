#include <ssInterpreter.h>
#include "ssBusinessManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <QString>

#include <dirent.h>
#include <unistd.h>

void ssInterpreter::cdProcedure(QString command)
{
    command.remove(0,2);
    command = command.trimmed();
    chdir(command.toLatin1().data());
    
    DIR *d = opendir(".");
    struct dirent *ds;
    while(ds = readdir(d))
    {
        QString entryName = ds->d_name;
        ssAdvisor::addSugestion(entryName);
    }
    void rewinddir(DIR *dir);
    int closedir(DIR *dir);
}

QString ssInterpreter::execute(QString command)
{
    if (command.indexOf("cd") != -1)
    {
        cdProcedure(command);
        QString output = "";
        return output;
    }

    FILE *pipe = popen(command.toLatin1().data(), "r");
    if(!pipe)
    {
        printf("error!");
    }   

    char buffer[1024];
    QString output = "";
    while(!feof(pipe))
    {
        if(fgets(buffer, 1023, pipe) != NULL)
        {
            output += buffer;
        }
    }
    ssAdvisor::addSugestion(command);
    
    return output;
}