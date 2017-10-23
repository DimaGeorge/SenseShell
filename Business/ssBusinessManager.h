#ifndef _SSBUSINESSMANAGER_H
#define _SSBUSINESSMANAGER_H

class ssBusinessManager
{
public:
    static ssBusinessManager&   getInstance ();
    static void                 destroyInstance ();
    static void run();

    void hello();
private:
    ssBusinessManager();
    ~ssBusinessManager();

    static ssBusinessManager* instance;

    /* nu sunt implementate */
    ssBusinessManager(const ssBusinessManager&)             = delete;
    ssBusinessManager operator= (const ssBusinessManager&)  = delete;
};



#endif