#ifndef _SSINTERPRETER_H
#define _SSINTERPRETER_H

#include <string>
#include <QString>

class ssInterpreter
{
public:
    void execute (QString);
    static void stopAnyExecutingCommand(void);
private:
    void cdProcedure(QString);
};

#endif