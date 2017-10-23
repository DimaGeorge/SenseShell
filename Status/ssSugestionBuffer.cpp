#include <ssSugestionBuffer.h>

std::string ssSugestionBuffer::read()
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();
    
    std::string sugestionText = "";
    std::vector<std::string>::iterator it;
    for(it = data.begin(); it != data.end(); ++it)
    {
        sugestionText += *it;
        sugestionText += '\n';
    }

    stateMutex.lock();
    state = Unmodified;
    stateMutex.unlock();

    return sugestionText;
}
   
void ssSugestionBuffer::set(const char *begining, int size)
{
    this->clean();
    
    std::string dataS = "";
    for(int i = 0; i < size; i++)
    {
        dataS += (begining[i]);
    }
    
    this->add(dataS);
}

void ssSugestionBuffer::clean(void)
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    data.clear();
    
    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();
}

void ssSugestionBuffer::add(std::string dataS) 
{
    stateMutex.lock();
    state = Modifying;
    stateMutex.unlock();

    data.push_back(dataS);

    stateMutex.lock();
    state = Modified;
    stateMutex.unlock();
}