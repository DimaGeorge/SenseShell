#include <ssGUIManager.h>
#include <stdio.h>
#include <ssInputBuffer.h>

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

void ssGUIManager::hello()
{
    printf("Hello from ssGUIManager!\n");
}

void ssGUIManager::run()
{
    QApplication app(0, NULL);
    QLabel label("Hello, world!");
    label.show();
    app.exec();

    ssStatusTable::getInstance().setProcessOff();
}
