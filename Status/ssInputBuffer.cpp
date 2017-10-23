#include <ssInputBuffer.h>

void ssInputBuffer::set(const char *begining, int size)
{
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

    printf("Debug: ssInputBuffer::set");
}
void ssInputBuffer::clean(void)
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    data.clear();

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();

    printf("Debug: ssInputBuffer::clean");
}

void ssInputBuffer::push(char ch)
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    data.push_back(ch);

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();

    printf("Debug: ssInputBuffer::push");
}

void ssInputBuffer::pop(void)
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    data.pop_back();

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();

    printf("Debug: ssInputBuffer::pop");
}

bool ssInputBuffer::wasModified()
{
    return true;
}

std::string ssInputBuffer::read()
{
    std::string dataS(data.begin(), data.end());
    return dataS;
}