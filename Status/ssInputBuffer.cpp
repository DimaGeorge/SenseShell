#include <ssInputBuffer.h>

void ssInputBuffer::set(char *begining, int size)
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

    printf("aici +++++++++");
}
void ssInputBuffer::clean(void)
{

}

void ssInputBuffer::push(char ch)
{

}

void ssInputBuffer::pop(void)
{

}

bool ssInputBuffer::wasModified()
{
    return true;
}

std::vector<char> ssInputBuffer::read()
{
    return data;
}