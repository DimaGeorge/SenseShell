#include <ssBusinessManager.h>
#include <ssDataManager.h>
#include <ssInterpreter.h>
#include <ssAdvisor.h>
#include <iostream>
#include <thread>
#include <QFile>

ssBusinessManager* ssBusinessManager::instance = NULL;

ssBusinessManager::ssBusinessManager() : statusTable(ssStatusTable::getInstance())
{
    QFile TextFile("/root/SenseShell/Business/wordlist.txt");
    TextFile.open(QIODevice::ReadOnly);
    while(!TextFile.atEnd())
    {
        suggestions.append(TextFile.readLine().trimmed());
    }
    TextFile.close();
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
        ssDataManager data;
        data.hello();
}

void ssBusinessManager::run()
{
        ssStatusTable &statusTableLocalRef = ssStatusTable::getInstance();
        
        ssOutputBuffer &outputBuffer = statusTableLocalRef.getRefToOutputBuffer();
        ssInputBuffer &inputBuffer = statusTableLocalRef.getRefToInputBuffer();
        ssSugestionBuffer &suggestionBuffer = statusTableLocalRef.getRefToSuggestionBuffer();

        ssInterpreter interpreter;
        ssAdvisor advisor;

    while(statusTableLocalRef.getProcessStatus() == ssStatusTable::ProcessStatus::On)
    {
        std::chrono::milliseconds timeToSleep(10);
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
            std::string inputTillNow = inputBuffer.read();
            std::string output = advisor.suggestFrom(inputTillNow);
            outputBuffer.set(output.c_str(), output.size());
            inputBuffer.executionDone();
            continue;

        }

    }
}