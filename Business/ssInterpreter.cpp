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

void ssInterpreter::execute(QString command)
{
    QString obuff;
    if (command.indexOf("cd") != -1)
    {
        cdProcedure(command);
        ssBusinessManager::produceOutput(obuff);
    }

    FILE *pipe = popen(command.toLatin1().data(), "r");
    if(!pipe)
    {
        printf("error!");
    }   

    char buffer[1024];
    while(!feof(pipe))
    {
        if(fgets(buffer, 1023, pipe) != NULL)
        {
            obuff = buffer;
            qDebug("producer >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
            qDebug(obuff.toLatin1().data());
            ssBusinessManager::produceOutput(obuff);
            obuff.clear();
        }
    }
    ssAdvisor::addSugestion(command);
    
}

void ssInterpreter::stopAnyExecutingCommand(void)
{
    qDebug("muita!");
}