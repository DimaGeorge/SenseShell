#ifndef _SSGUIMANAGER_H
#define _SSGUIMANAGER_H

#include <ssStatusTable.h>
#include <stdio.h>
#include <stdlib.h> // prevents error for exit on line 18 when compiling with gcc

#include <QtGui>

class ssGUIManager
{
public:
    static ssGUIManager& getInstance (void);
    static void destroyInstance(void);
    static void run();

    void hello();

private:
    ssStatusTable &statusTable;

    static ssGUIManager *instance;

    ssGUIManager();
    ~ssGUIManager();

    /* nu sunt implementate */
    ssGUIManager( const ssGUIManager&)              = delete;
    ssGUIManager operator= (const ssGUIManager&)    = delete;
};


#endif