#ifndef _SSBUSINESSMANAGER_H
#define _SSBUSINESSMANAGER_H

#include <ssStatusTable.h>
#include <ssAdvisor.h>
#include <QStringList>

class ssBusinessManager
{
public:
    QStringList suggestions;
    ssAdvisor Advisor;
    static ssBusinessManager&   getInstance ();
    static void                 destroyInstance ();
    static void run();

    void hello();
private:
    ssBusinessManager();
    ~ssBusinessManager();

    static ssBusinessManager* instance;
    ssStatusTable &statusTable;
    /* nu sunt implementate */
    ssBusinessManager(const ssBusinessManager&)             = delete;
    ssBusinessManager operator= (const ssBusinessManager&)  = delete;
};



#endif