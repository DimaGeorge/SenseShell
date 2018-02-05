#ifndef _SSBUSINESSMANAGER_H
#define _SSBUSINESSMANAGER_H

#include <ssStatusTable.h>
#include <ssAdvisor.h>
#include <QStringList>
#include <QMutex>

class ssBusinessManager
{
public:
    ssAdvisor Advisor;
    
    static ssBusinessManager&   getInstance ();
    static void                 destroyInstance ();
    static void run();

    void setInputBuffer(QString command);
    QString getOutputBuffer(void);
    static bool commandIsBeingExecuted (void) {return executingComand;}
    static bool isOutputBufferEmpty(void) {return obuff.isEmpty();}
    static void produceOutput(QString);
private:
    static QMutex mutexOutputBuffer;
    static QString ibuff;
    static QString obuff;
    static bool executingComand;
    ssBusinessManager();
    ~ssBusinessManager();

    static ssBusinessManager* instance;
    ssStatusTable &statusTable;
    /* nu sunt implementate */
    ssBusinessManager(const ssBusinessManager&)             = delete;
    ssBusinessManager operator= (const ssBusinessManager&)  = delete;
};



#endif