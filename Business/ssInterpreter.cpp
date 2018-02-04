#include <ssInterpreter.h>
#include "ssBusinessManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <thread>
#include <string.h>
int ssInterpreter::ChildPid = 0;

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
        return;
    }
    
    int pipeFileDesc[2];
    if(pipe(pipeFileDesc))
    {
        qDebug("pipe failed");
        return;
    }
    else
    {
        qDebug("pipe works");
    }

    ChildPid = fork();
    if(ChildPid == 0)
    {
        close(pipeFileDesc[0]);
        close(1);
        dup(pipeFileDesc[1]);

        QStringList list = command.split(' ');
        char *c_args[100];
        for(int i = 0 ; i < 100; i++)
            c_args[i] = NULL;

        for(int i = 0; i < list.count(); i++)
        {
            c_args[i] = new char[list[i].toLatin1().size() + 1];
            strcpy(c_args[i], list[i].toLatin1().constData());
            c_args[i][list[i].toLatin1().size()] = '\0';
        } 

        for(int i = 0; i < list.count(); i++)
        {
            qDebug(c_args[i]);
        }     
        execvp(c_args[0], c_args);
        close(pipeFileDesc[1]);
    }
    else
    {
        close(pipeFileDesc[1]);
        char buffer[1024];
        while(int len = read(pipeFileDesc[0], buffer, 1023))
        {
            buffer[len] = '\0';
            obuff = buffer;
            qDebug(obuff.toLatin1().data());
            ssBusinessManager::produceOutput(obuff);
            obuff.clear();
        }
        close(pipeFileDesc[0]);
        ssInterpreter::stopAnyExecutingCommand();
    }

    ssAdvisor::addSugestion(command);
    
}

void ssInterpreter::stopAnyExecutingCommand(void)
{
    if(ChildPid != 0)
    {
        kill(ChildPid, SIGKILL);
    }
    ChildPid = 0;
}