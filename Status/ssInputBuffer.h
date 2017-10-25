#ifndef _SSINPUTBUFFER_H
#define _SSINPUTBUFFER_H

#include<ssBuffer.h>

class ssInputBuffer : public ssBuffer 
{
public:
    enum Execution
    {
        Ready,
        InProcess,
        Done
    };

    friend class ssGUIManager;
    
    std::string read(void);

    bool isReadyToExecute(void) { return (execution == Execution::Ready) ? true : false; }
    void executionDone (void);
    /*debug*/
    ssInputBuffer(const char*, int);
    /*debug*/
private:
    /* interfata destinata numai layer-ului gui */
    Execution execution;
    std::mutex executionMutex;

    void execute(void);

    void set(const char *, int);
    void clean(void);
    void push(char ch);
    void pop(void);

    std::vector<char> data; 
};

#endif