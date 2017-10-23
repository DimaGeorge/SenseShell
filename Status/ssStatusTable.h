#ifndef _SSSTATUSTABLE_H
#define _SSSTATUSTABLE_H

#include<ssInputBuffer.h>

class ssStatusTable
{
public:
    /* creare si distrugere */
    static ssStatusTable& getInstance();
    static void destroyInstance();

    /* actiuni */
    void hello();
    ssInputBuffer& getRefToInputBuffer();

private:
    /*fields*/
    ssInputBuffer inputBuffer;

    static ssStatusTable* instance;
    
    ssStatusTable();
    ~ssStatusTable();

    /*nu vor fi implementate */
    ssStatusTable(const ssStatusTable&)             = delete;
    ssStatusTable operator= (const ssStatusTable&)  = delete;
};

#endif