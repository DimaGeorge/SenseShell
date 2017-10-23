#include <ssBuffer.h>

/* empty */

bool ssBuffer::wasModified(void)
{
    if(state == Modified)
    {
        return true;
    }
    else
    {
        return false;
    }
}

