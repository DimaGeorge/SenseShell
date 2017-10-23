#include <stdio.h>
#include <thread>

#include <ssGUIManager.h>
#include <ssBusinessManager.h>
#include <ssStatusTable.h>

int main ()
{
    printf("\nHello SenseShell!\n");

    ssGUIManager &gui = ssGUIManager::getInstance();
    ssBusinessManager &business = ssBusinessManager::getInstance();
    ssStatusTable &status = ssStatusTable::getInstance();

    std::thread guiThread(ssGUIManager::run);               //spawn thread for gui
    std::thread businessThread(ssBusinessManager::run);     //spawn thread for business
    
    gui.hello();
    business.hello();
    status.hello();

    guiThread.join();
    ssGUIManager::destroyInstance();
    
    businessThread.join();
    ssBusinessManager::destroyInstance();
    ssStatusTable::destroyInstance();

    return 0;
}