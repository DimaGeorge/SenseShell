#include "SenseForm.h"
#include "ssGUIManager.h"
#include <QTextEdit>
#include <QAbstractItemModel>
#include <QWidget>
#include <QListView>
#include <QHostInfo>
#include <QEvent>
#include <unistd.h>
#include <stdio.h>

SenseForm::SenseForm(QWidget *parent):
                    QWidget(parent),
                    status(ssStatusTable::getInstance()),
                    manager(ssGUIManager::getInstance()),
                    completer(0)
{
    setupUi(this); /*builds the widget tree on the parent widget
                    *http://doc.qt.io/archives/qt-4.8/designer-using-a-ui-file.html
                    */
}

void SenseForm::setupUi(QWidget *senseForm)
{
    qApp->installEventFilter(this);
    commandTextBox = new TextEdit(this);
    commandTextBox->setGeometry(QRect(5, 5, 610, 445));
    
    // setting the color for commandTextBox
    QPalette p = commandTextBox->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    commandTextBox->setPalette(p);

    ///* Setting the completer */
    //
    completer = new QCompleter(this);
    completer->setModel(modelFromFile("/root/SenseShell/GUI/resources/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setWrapAround(false);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModelSorting(QCompleter::CaseSensitivelySortedModel);
    QListView * view = (QListView *)completer->popup();
    view->setUniformItemSizes(true);
    view->setLayoutMode(QListView::Batched);
    //


    commandTextBox->setCompleter(completer);
    retranslateUi(senseForm);
    userAhost();
}

void SenseForm::retranslateUi(QWidget *senseForm)
{
    senseForm->setWindowTitle(QApplication::translate("senseForm",
                                                        "SenseShell v1.0.1", 
                                                        0, 
                                                        QApplication::UnicodeUTF8
                                                        ));
}


void SenseForm::executeCommandReady()
{
    static int antet = userAhost(false);

    commandTextBox->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    commandTextBox->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);

    QString command;
    command = commandTextBox->textCursor().selectedText();
    qDebug() << command;
    command = command.mid(antet + 1, command.length());
    qDebug() << command;
    QByteArray ba = command.toLatin1();
    char *c_str2 = ba.data(); 
    manager.sendCommand(c_str2);
    ssOutputBuffer &out=status.getRefToOutputBuffer();
    QString outputCommand=out.read().data();
    commandTextBox->append(outputCommand);
    antet = userAhost();
    commandTextBox->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}

int SenseForm::userAhost(bool print)
{
    QString redHtml = "<font color=\"Red\">";
    QString blueHtml = "<font color=\"Blue\">";
    QString endHtml = "</font> <font color=\"White\">";

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    QString workingDir = cwd;

    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    name += "@";
    name += QHostInfo::localHostName();

    QString line = redHtml % name;
    line = line % endHtml;
    line = line % blueHtml;
    line = line % workingDir;
    line = line % endHtml;

    name += workingDir;
    if(print)
    {
        commandTextBox->moveCursor(QTextCursor::End);
        commandTextBox->insertHtml(line);
        commandTextBox->moveCursor(QTextCursor::End);
    }
 

    return name.length();
}

QAbstractItemModel* SenseForm::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    /* Application override cursors are intended for showing the user that 
    *  the application is in a special state, for example during an 
    *  operation that might take some time.
    */
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    return new QStringListModel(words, completer);
}


bool SenseForm::eventFilter(QObject *obj, QEvent *event)
{ 
    if (event->type() == QEvent::KeyPress)
    {
        
        if(obj == commandTextBox)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Return)
            {
                qDebug("enter received in SenseForm");
                executeCommandReady();
            }
                
        }
    }
    return QObject::eventFilter(obj, event);
}