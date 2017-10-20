#include <stdio.h>
#include <thread>

#include <ssGUIManager.h>
#include <ssBusinessManager.h>

int main ()
{
    printf("\nHello SenseShell!\n");
    
    ssGUIManager gui;
    ssBusinessManager business;

    std::thread guiThread(ssGUIManager::run);               //spawn thread for gui
    std::thread businessThread(ssBusinessManager::run);     //spawn thread for business

    gui.hello();
    business.hello();
    
    guiThread.join();
    businessThread.join();

    return 0;
}