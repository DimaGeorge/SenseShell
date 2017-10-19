#include <ssBusinessManager.h>
#include <ssDataManager.h>
#include <stdio.h>

void ssBusinessManager::hello()
{
    printf("Hello from Business manager!\n");
    ssDataManager data;
    data.hello();
}
