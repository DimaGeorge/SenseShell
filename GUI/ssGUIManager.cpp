#include <ssGUIManager.h>
#include <stdio.h>

void ssGUIManager::hello()
{
    printf("Hello from ssGUIManager!\n");
}

void ssGUIManager::run()
{
    for(int i = 0; i < 100; i++)
    {
        printf("gui\n");
    }
}