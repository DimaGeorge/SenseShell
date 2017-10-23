#include <ssBusinessManager.h>
#include <ssDataManager.h>
#include <stdio.h>
#include <thread>

ssBusinessManager* ssBusinessManager::instance = NULL;

ssBusinessManager::ssBusinessManager() : statusTable(ssStatusTable::getInstance())
{
    /*nimic */
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

void ssBusinessManager::hello()
{
    printf("Hello from Business manager!\n");
        ssDataManager data;
        data.hello();
    }

    void ssBusinessManager::run()
    {
        ssStatusTable &statusTableLocalRef = ssStatusTable::getInstance();

    while(statusTableLocalRef.getProcessStatus() == ssStatusTable::ProcessStatus::On)
    {
        std::chrono::milliseconds timeToSleep(500);
        std::this_thread::sleep_for(timeToSleep);
        printf("ssBusinessManager::run\n");
    }
}