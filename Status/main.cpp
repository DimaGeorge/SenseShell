#include <stdio.h>

#include <ssGUIManager.h>
#include <ssBusinessManager.h>

int main ()
{
    printf("\nHello SenseShell!\n");
    
    ssGUIManager gui;
    ssBusinessManager business;

    gui.hello();
    business.hello();
    
    return 0;
}