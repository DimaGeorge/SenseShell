#ifndef _SSBUFFER_H
#define _SSBUFFER_H

#include <vector>
#include <mutex>
#include <string>

class ssBuffer
{
public:
    enum State
    {
        Modified,
        Unmodified,
        Modifying
    };

    virtual void set(const char *, int)       = 0;
    virtual void clean(void)            = 0;

    virtual void push(char ch)          = 0;
    virtual void pop(void)              = 0;
    
    virtual std::string read()          = 0;

    bool wasModified(void);
    
protected:
    State state;
    std::mutex stateMutex;
};


#endif