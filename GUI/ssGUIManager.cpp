#include <ssGUIManager.h>
#include <stdio.h>
#include <ssInputBuffer.h>

ssGUIManager* ssGUIManager::instance = NULL;

ssGUIManager::ssGUIManager() : statusTable (ssStatusTable::getInstance())
{
    /*nimic aici*/
}

ssGUIManager::~ssGUIManager()
{
    /*nimic aici*/
}

ssGUIManager& ssGUIManager::getInstance (void)
{
    if(instance == NULL)
    {
        printf("---------------------------------------here");
        instance = new ssGUIManager;
    }
    return *instance;
}

void ssGUIManager::destroyInstance(void)
{
    if(instance != NULL)
    {
        delete instance;
        instance = NULL;
    }
}

void ssGUIManager::hello()
{
    printf("Hello from ssGUIManager!\n");
}

void ssGUIManager::run()
{
    
    Display *d;
    int s;
    Window w;
    XEvent e;
 
                         // open connection with the server 
    d=XOpenDisplay(NULL);
    if(d==NULL) {
      printf("Cannot open display\n");
      exit(1);
    }
    s=DefaultScreen(d);
 
                         // create window 
    w=XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 500, 500, 50,
                          WhitePixel(d, s), BlackPixel(d, s));
 
    // Process Window Close Event through event handler so XNextEvent does Not fail
    Atom delWindow = XInternAtom( d, "WM_DELETE_WINDOW", 0 );
    XSetWMProtocols(d , w, &delWindow, 1);
 
                         // select kind of events we are interested in
    XSelectInput(d, w, ExposureMask | KeyPressMask);
 
                         // map (show) the window
    XMapWindow(d, w);
 
                         // event loop
    while(1) {
      XNextEvent(d, &e);
                         // draw or redraw the window
      if(e.type==Expose) {
        XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
      }
                         // exit on key press
      if(e.type==KeyPress)
        break;
 
      // Handle Windows Close Event
      if(e.type==ClientMessage)
         break;
    }
 
                         // destroy our window
    XDestroyWindow(d, w);

                         // close connection to server
    XCloseDisplay(d);
 

}
