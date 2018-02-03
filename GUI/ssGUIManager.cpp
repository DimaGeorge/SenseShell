#include <ssGUIManager.h>
#include <stdio.h>
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
    ssBusinessManager::getInstance().setInputBuffer(QString(command));
}

void ssGUIManager::run()
{
    QApplication app(0, NULL);
    SenseForm senseWindow;
    senseWindow.show();
    app.exec();
    ssStatusTable::getInstance().setProcessOff();
}
