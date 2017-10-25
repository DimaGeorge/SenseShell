#include <ssStatusTable.h>
#include <stdio.h>

ssStatusTable* ssStatusTable::instance = NULL;

ssStatusTable::ssStatusTable() : processStatus(ProcessStatus::On), inputBuffer("ls -l", 5)
{
    /*nimic aici*/
}

ssStatusTable::~ssStatusTable()
{
    /*nimic aici*/
}

ssStatusTable& ssStatusTable::getInstance()
{
    if(instance == NULL)
    {
        instance = new ssStatusTable;
    }

    return *instance;
}

void ssStatusTable::destroyInstance()
{
    if(instance != NULL)
    {
        delete instance;
        instance = NULL;
    }
}

ssInputBuffer& ssStatusTable::getRefToInputBuffer()
{
    return inputBuffer;
}

ssOutputBuffer& ssStatusTable::getRefToOutputBuffer()
{
    return outputBuffer;
}

void ssStatusTable::hello()
{
    printf("Hello from StatusTable");
}