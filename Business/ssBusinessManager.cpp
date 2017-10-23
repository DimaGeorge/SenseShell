#include <ssBusinessManager.h>
#include <ssDataManager.h>
#include <stdio.h>

ssBusinessManager* ssBusinessManager::instance = NULL;

ssBusinessManager::ssBusinessManager()
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
    for(int i = 0; i < 100; i++)
    {
        printf("bussines\n");
    }
}