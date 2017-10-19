#include <stdio.h>

#include <ssGUIManager.h>
#include <ssBusinessManager.h>

// ramura creata din vscode

int main ()
{
    printf("\nHello SenseShell!\n");
    
    ssGUIManager gui;
    ssBusinessManager business;

    gui.hello();
    business.hello();
    
    return 0;
}