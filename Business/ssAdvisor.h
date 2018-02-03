#ifndef _SSADVISOR_H
#define _SSADVISOR_H

#include <QCompleter>

class ssAdvisor
{
private:
    static QStringList suggestions;
    static QCompleter *completer;
public:
    static QCompleter *getCompleter(void);
    static void addSugestion(QString);
    static void reviseCompleter(void);
};

#endif