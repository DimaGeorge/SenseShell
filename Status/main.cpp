#include <stdio.h>
#include <thread>

#include <ssGUIManager.h>
#include <ssBusinessManager.h>
#include <ssStatusTable.h>

int main ()
{
    printf("\nHello SenseShell!\n");

    // iau instantele singleton-urilor ce monitorizeaza fiecare layer
    ssGUIManager        &gui        = ssGUIManager::getInstance();
    ssBusinessManager   &business   = ssBusinessManager::getInstance();
    ssStatusTable       &status     = ssStatusTable::getInstance();

    // ridica thread-ul pentru layer-ul de bussines
    std::thread businessThread(ssBusinessManager::run);
    
    // ridica thread-ul pentru layer-ul de interfata grafica
    std::thread guiThread(ssGUIManager::run);

    /*
    *   thread inutil. astept sa se termine cele 2 thread-uri ca sa le inchid
    */
    
    // inchiderea thread-urilor pentru gui si business
    guiThread.join();
    businessThread.join();
    
    // dezalocare singleton-uri
    ssBusinessManager::destroyInstance ();
    ssStatusTable::destroyInstance ();
    ssGUIManager::destroyInstance ();
    

    return 0;
}