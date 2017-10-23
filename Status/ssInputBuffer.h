#ifndef _SSINPUTBUFFER_H
#define _SSINPUTBUFFER_H

#include<ssBuffer.h>

class ssInputBuffer : ssBuffer 
{
public:
    friend class ssGUIManager;
    
    std::string read(void);

private:
    void set(const char *, int);
    
    void clean(void);
    
    void push(char ch);
    void pop(void);

    std::vector<char> data; 
};

#endif