#include <ssBusinessManager.h>
#include <ssDataManager.h>
#include <ssInterpreter.h>
#include <iostream>
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
        
        ssOutputBuffer &outputBuffer = statusTableLocalRef.getRefToOutputBuffer();
        ssInputBuffer &inputBuffer = statusTableLocalRef.getRefToInputBuffer();
        
        ssInterpreter interpreter;

    while(statusTableLocalRef.getProcessStatus() == ssStatusTable::ProcessStatus::On)
    {
        std::chrono::milliseconds timeToSleep(500);
        std::this_thread::sleep_for(timeToSleep);

        if(inputBuffer.isReadyToExecute())
        {
            std::string inputCommand = inputBuffer.read();
            std::string output = interpreter.execute(inputCommand);
            outputBuffer.set(output.c_str(), output.size());
            inputBuffer.executionDone();
            continue;
        }

        if(inputBuffer.wasModified())
        {
            std::cout << "modification arised in input buffer" << std::endl;
        }

        std::cout << "ssBusinessManager - thread " << std::endl; 
    }
}