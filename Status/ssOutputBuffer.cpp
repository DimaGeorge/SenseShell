#include <ssOutputBuffer.h>
#include <stdio.h>

void ssOutputBuffer::set(const char *begining, int size)
{
    this->clean();
    
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    for(int i = 0; i < size; i++)
    {
        data.push_back(begining[i]);
    }

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();

    printf("Debug: ssOutputBuffer::set");
}

void ssOutputBuffer::clean(void)
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    data.clear();

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();

    printf("Debug: ssOutputBuffer::clean");
}


std::string ssOutputBuffer::read()
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    std::string dataS(data.begin(), data.end());
    
    stateMutex.lock();
    state = Unmodified;
    stateMutex.unlock();

    return dataS;
}