#ifndef _SSSUGESTIONBUFFER_H
#define _SSSUGESTIONBUFFER_H

#include <ssBuffer.h>
#include <string>
#include <vector>

class ssSugestionBuffer : ssBuffer
{
public:
    friend class ssBusinessManager;

    std::string read();

private:
    std::vector<std::string> data;
    
    void set (const char *, int);  // in acest context set() apeleaza in fapt add(). pentru golire sa se fol clean()
    void clean (void);
    void add (std::string);

};



#endif