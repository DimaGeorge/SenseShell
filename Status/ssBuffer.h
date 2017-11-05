#ifndef _SSBUFFER_H
#define _SSBUFFER_H

/*
*   ssBuffer - clasa abstracta ce defineste trasaturile comune ale bufferelor
*
*/


#include <vector>
#include <mutex>
#include <string>

class ssBuffer
{
public:

    enum State
    {
        Modified,
        Modifying,
        Unmodified
    };

    /******* metode *******/
    
    // citire
    virtual std::string read ()          = 0;

    // scriere
    virtual void set (const char *, int) = 0;

    // golire
    virtual void clean (void)            = 0;
    

    bool wasModified (void);
    
protected:
    State       state;
    std::mutex  stateMutex;
};


#endif