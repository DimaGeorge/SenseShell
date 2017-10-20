#include <ssBusinessManager.h>
#include <ssDataManager.h>
#include <stdio.h>

void ssBusinessManager::hello()
{
    printf("Hello from Business manager!\n");
    ssDataManager data;
    data.hello();
}

void ssBusinessManager::run()
{
    for(int i = 0; i < 100; i++)
    {
        printf("bussines\n");
    }
}