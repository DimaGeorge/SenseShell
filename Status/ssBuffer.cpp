#include <ssBuffer.h>


// wasModified - pentru a verifica daca buffer-ul a fost scris recent
bool ssBuffer::wasModified (void)
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

