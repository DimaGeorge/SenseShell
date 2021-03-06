#include <ssInterpreter.h>
#include "ssBusinessManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <QString>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <thread>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QFile>
#include <QTextStream>
#include <time.h>   
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

void ssInterpreter::exitProcedure(QString command)
{
    exit(0);
}

void ssInterpreter::pipeReader(int fd)
{
    QString obuff;
    char buffer[1024];
    while(int len = read(fd, buffer, 1023))
        {
            qDebug("readin thread here ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            buffer[len] = '\0';
            obuff = buffer;
            ssBusinessManager::produceOutput(obuff);
            obuff.clear();
        }
}

void ssInterpreter::execute(QString command)
{
    QString obuff;
    if (command.isEmpty())
    {
        ssBusinessManager::produceOutput(obuff);
        return;
    }

    if (command.indexOf("cd") != -1)
    {
        cdProcedure(command);
        ssBusinessManager::produceOutput(obuff);
        return;
    }

     if (command.indexOf("exit") != -1)
    {
        exitProcedure(command);
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

    int errorFD = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ChildPid = fork();
    if(ChildPid == 0)
    {
        close(pipeFileDesc[0]);
        close(1);
        dup(pipeFileDesc[1]);
        close(2);
        dup(errorFD);
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

        execvp(c_args[0], c_args);
        exit(5);
    }
    else
    {        
        close(pipeFileDesc[1]);
        close(errorFD);

        std::thread readerThread(pipeReader, pipeFileDesc[0]);
        //pipeReader(pipeFileDesc[0]);
        int status;  
        pid_t result = waitpid(ChildPid, &status, WNOHANG);
        while(result == 0)
        {
            result = waitpid(ChildPid, &status, WNOHANG);
            if (result == 0) {
                qDebug("Copilului ii merge bine");
            } else if (result == -1) {
                qDebug("eroare in copil!!!!!!!");
            } else {
                if(WEXITSTATUS(status) == 5)
                {
                    wait(&status);
                    ssBusinessManager::produceOutput(ssInterpreter::getFunnyErrorMessage());
                }
            }
        }
        readerThread.join();
        
        QFile f("temp");
        if (!f.open(QFile::ReadOnly | QFile::Text)) 
            return;
        QTextStream in(&f);
        QString fileS = in.readAll();
        ssBusinessManager::produceOutput(fileS);
    
        wait(&status);
        ChildPid = 0;
        close(pipeFileDesc[0]);
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

QString ssInterpreter::getFunnyErrorMessage(void)
{
    srand(time(NULL));
    switch(rand() % 13)
    {
        case 0:
        return QString("In spatele unei erori a computer-ului sunt cel putin 2 erori umane, una fiind aceea de a da vina pe computer.");
        
        case 1:
        return QString("Prietenee.. ce comanda e asta?");

        case 2:
        return QString("Too many errors on one line (make fewer).");

        case 3:
        return QString("Hmm... nope!");

        case 4:
        return QString("Un program pentru calculator face ceea ce ii spui tu sa faca, nu ceea ce vrei tu sa faca.");

        case 5:
        return QString("Erorile nedetectabile sunt infinite in varietate, spre deosebire de erorile detectabile care sunt limitate prin definitie.");

        case 6:
        return QString("Backup: O operatie care niciodata nu este efectuata la timp.");

        case 7:
        return QString("Fisier: Acea parte a sistemului care nu poate fi gasita.");

        case 8:
        return QString("Un afisaj digital furnizeaza informatii gresite cu o precizie mai mare decat a fost posibil anterior.");

        case 9:
        return QString("Inteligenta artificiala nu se poate compara cu prostia naturala.");

        case 10:
        return QString("Toate computerele asteapta cu aceiasi viteza.");

        case 11:
        return QString("Computerele nu gresesc, ele o fac intentionat.");

        default:
        return QString("Comanda cu continut neadecvat.");
    }
}