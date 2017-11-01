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

    std::thread businessThread(ssBusinessManager::run);     //spawn thread for business
    std::chrono::milliseconds timeToSleep(500);
    std::this_thread::sleep_for(timeToSleep);
    std::thread guiThread(ssGUIManager::run);               //spawn thread for gui
    

  
    guiThread.join();
    ssGUIManager::destroyInstance();
    businessThread.join();
    ssBusinessManager::destroyInstance();
    ssStatusTable::destroyInstance();

    

    return 0;
}