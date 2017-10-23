#ifndef _SSOUTPUTBUFFER_H
#define _SSOUTPUTBUFFER_H

#include <ssBuffer.h>

class ssOutputBuffer : ssBuffer
{
public:
    friend class ssBusinessManager;
    std::string read(void);

private:
    /* interfata destinata numai layer-ului business */
    void set(const char *, int);
    void clean(void);
    

    std::vector<char> data; 
};


#endif