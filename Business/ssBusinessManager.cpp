#include <ssBusinessManager.h>
#include <ssDataManager.h>
#include <ssInterpreter.h>
#include <ssAdvisor.h>
#include <iostream>
#include <thread>
#include <QFile>

ssBusinessManager* ssBusinessManager::instance = NULL;
QString ssBusinessManager::ibuff;
QString ssBusinessManager::obuff;
bool ssBusinessManager::executingComand;
QMutex ssBusinessManager::mutexOutputBuffer;

ssBusinessManager::ssBusinessManager() : statusTable(ssStatusTable::getInstance())
{
    
}

ssBusinessManager::~ssBusinessManager()
{
    /*nimic */
}

ssBusinessManager& ssBusinessManager::getInstance ()
{
    if(instance == NULL)
    {
        instance = new ssBusinessManager;
    }
    return *instance;
}

void  ssBusinessManager::destroyInstance ()
{
    if(instance != NULL)
    {
        delete instance;
        instance = NULL;
    }
}

void  ssBusinessManager::setInputBuffer(QString command)
{
    ibuff = command;
    executingComand = true;
}
QString  ssBusinessManager::getOutputBuffer(void)
{
    mutexOutputBuffer.lock();
    QString obuff1 = obuff;
    obuff.clear();
    mutexOutputBuffer.unlock();
    return obuff1;
}

void ssBusinessManager::produceOutput(QString prod)
{
    mutexOutputBuffer.lock();
    if(obuff.isEmpty())
    {
        obuff = prod;
    }
    else
    {
        obuff += prod;
    }
    mutexOutputBuffer.unlock();
}

void ssBusinessManager::run()
{
    ssInterpreter interpreter;
    while(ssStatusTable::getInstance().getProcessStatus() == ssStatusTable::ProcessStatus::On)
    {
        std::chrono::milliseconds timeToSleep(10);
        std::this_thread::sleep_for(timeToSleep);
        if(executingComand)
        {
            obuff.clear();
            interpreter.execute(ibuff);
            executingComand = false;
        }

    }
}