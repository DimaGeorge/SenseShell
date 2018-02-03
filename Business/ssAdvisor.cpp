#include <ssAdvisor.h>
#include <ssBusinessManager.h>
#include <QFile>
#include <QAbstractItemModel>
#include <QStringListModel>
#include "utils.h"

QStringList ssAdvisor::suggestions;
QCompleter *ssAdvisor::completer;

QCompleter *ssAdvisor::getCompleter(void)
{
    if(!completer)
    {
        QFile TextFile("/root/SenseShell/Business/wordlist.txt");
        TextFile.open(QIODevice::ReadOnly);
        while(!TextFile.atEnd())
        {
            suggestions.append(TextFile.readLine().trimmed());
        }
        TextFile.close();

        completer = new QCompleter(suggestions, NULL);
        completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
        completer->setWrapAround(false);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setModelSorting(QCompleter::CaseSensitivelySortedModel);
    }
    return completer;
}


void ssAdvisor::addSugestion(QString word)
{
    suggestions << word;
}

void ssAdvisor::reviseCompleter(void)
{
    QStringListModel *model = new QStringListModel();
    model->setStringList(suggestions);

    qDebug("==============================================<"); 
    completer->setModel(model);
    qDebug("==============================================<");
}