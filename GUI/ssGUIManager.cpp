#include <ssGUIManager.h>
#include <stdio.h>
#include <ssInputBuffer.h>
#include "SenseForm.h"

ssGUIManager* ssGUIManager::instance = NULL;

ssGUIManager::ssGUIManager() : statusTable (ssStatusTable::getInstance())
{
    /*nimic aici*/
}

ssGUIManager::~ssGUIManager()
{
    /*nimic aici*/
}

ssGUIManager& ssGUIManager::getInstance (void)
{
    if(instance == NULL)
    {
        printf("---------------------------------------here");
        instance = new ssGUIManager;
    }
    return *instance;
}

void ssGUIManager::destroyInstance(void)
{
    if(instance != NULL)
    {
        delete instance;
        instance = NULL;
    }
}

void ssGUIManager::sendCommand(char* command)
{
    ssInputBuffer &inputBuffer=statusTable.getRefToInputBuffer();
    inputBuffer.set(command,strlen(command)+1);
    inputBuffer.execute();
}

void ssGUIManager::run()
{
    QApplication app(0, NULL);
    SenseForm senseWindow;
    senseWindow.show();
    app.exec();
    ssStatusTable::getInstance().setProcessOff();
}
