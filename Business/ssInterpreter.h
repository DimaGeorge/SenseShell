#ifndef _SSINTERPRETER_H
#define _SSINTERPRETER_H

#include <string>
#include <QString>

class ssInterpreter
{
public:
    void execute (QString);
    static void stopAnyExecutingCommand(void);
    static QString getFunnyErrorMessage(void);
private:
    static void pipeReader(int fd);
    static int ChildPid;
    void cdProcedure(QString);
    void exitProcedure(QString);
};

#endif