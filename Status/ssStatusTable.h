#ifndef _SSSTATUSTABLE_H
#define _SSSTATUSTABLE_H

#include<ssInputBuffer.h>
#include<ssOutputBuffer.h>

class ssStatusTable
{
public:
    enum ProcessStatus
    {
        On,
        Off
    };

    /* creare si distrugere */
    static ssStatusTable& getInstance ();
    static void destroyInstance ();

    /* actiuni */
    void hello();
    ssInputBuffer&      getRefToInputBuffer ();
    ssOutputBuffer&     getRefToOutputBuffer ();

    void            setProcessOff (void)       {   processStatus = ProcessStatus::Off;         };
    ProcessStatus   getProcessStatus (void)    {   return processStatus;                       };
private:
    /*fields*/
    ssInputBuffer   inputBuffer;
    ssOutputBuffer  outputBuffer;

    ProcessStatus processStatus;

    static ssStatusTable* instance;
    
    ssStatusTable();
    ~ssStatusTable();

    /*nu vor fi implementate */
    ssStatusTable(const ssStatusTable&)             = delete;
    ssStatusTable operator= (const ssStatusTable&)  = delete;
};

#endif