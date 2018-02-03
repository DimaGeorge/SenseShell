#ifndef _SSINTERPRETER_H
#define _SSINTERPRETER_H

#include <string>
#include <QString>

class ssInterpreter
{
public:
    QString execute (QString);

private:
    void cdProcedure(QString);
};

#endif