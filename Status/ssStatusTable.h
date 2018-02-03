#ifndef _SSSTATUSTABLE_H
#define _SSSTATUSTABLE_H


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
    void            setProcessOff (void)       {   processStatus = ProcessStatus::Off;         };
    ProcessStatus   getProcessStatus (void)    {   return processStatus;                       };


private:
    /*fields*/
    ProcessStatus processStatus;

    static ssStatusTable* instance;
    
    ssStatusTable();
    ~ssStatusTable();

    /*nu vor fi implementate */
    ssStatusTable(const ssStatusTable&)             = delete;
    ssStatusTable operator= (const ssStatusTable&)  = delete;
};

#endif