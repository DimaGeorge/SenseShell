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
bool ssBusinessManager::semaforComanda;

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
    semaforComanda = true;
}
QString  ssBusinessManager::getOutputBuffer(void)
{
    while(semaforComanda)
    {
        std::chrono::milliseconds timeToSleep(10);
        std::this_thread::sleep_for(timeToSleep);
    }
    return obuff;
}

void ssBusinessManager::run()
{
    ssInterpreter interpreter;
    while(ssStatusTable::getInstance().getProcessStatus() == ssStatusTable::ProcessStatus::On)
    {
        std::chrono::milliseconds timeToSleep(10);
        std::this_thread::sleep_for(timeToSleep);
        if(semaforComanda)
        {
            obuff = interpreter.execute(ibuff);
            semaforComanda = false;
            continue;
        }

    }
}