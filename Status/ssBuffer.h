#ifndef _SSBUFFER_H
#define _SSBUFFER_H

#include <vector>
#include <mutex>

class ssBuffer
{
public:
    enum State
    {
        Modified,
        Unmodified,
        Modifying
    };

    virtual void set(char *, int)       = 0;
    virtual void clean(void)            = 0;

    virtual void push(char ch)          = 0;
    virtual void pop(void)              = 0;
    
    virtual std::vector<char> read()    = 0;

    bool wasModified(void);
    
protected:
    State state;
    std::mutex stateMutex;
};


#endif