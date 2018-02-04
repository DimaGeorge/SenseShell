#include "SenseForm.h"
#include "ssGUIManager.h"
#include <ssAdvisor.h>
#include <QTextEdit>
#include <QAbstractItemModel>
#include <QWidget>
#include <QListView>
#include <QHostInfo>
#include <QEvent>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <ssBusinessManager.h>

SenseForm::SenseForm(QWidget *parent):
                    QWidget(parent),
                    status(ssStatusTable::getInstance()),
                    manager(ssGUIManager::getInstance()),
                    completer(ssAdvisor::getCompleter())
{
    setupUi(this); /*builds the widget tree on the parent widget
                    *http://doc.qt.io/archives/qt-4.8/designer-using-a-ui-file.html
                    */
}

void SenseForm::setupUi(QWidget *senseForm)
{
    qApp->installEventFilter(this);
    commandTextBox = new TextEdit(this);
    this->setFixedSize(710,440);
    commandTextBox->setGeometry(QRect(-1, -1, 720, 445)); // 720 / 445 = 1.618 (numarul de aur)

    // setting the color for commandTextBox
    QPalette p = commandTextBox->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    commandTextBox->setPalette(p);

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
    command = command.mid(antet + 1, command.length());
    command = command.trimmed();
    QByteArray ba = command.toLatin1();
    char *c_str2 = ba.data(); 
    manager.sendCommand(c_str2);
    while(ssBusinessManager::commandIsBeingExecuted() || !ssBusinessManager::isOutputBufferEmpty())
    {
        //std::chrono::milliseconds timeToSleep(100);
        //std::this_thread::sleep_for(timeToSleep);
        QString outputCommand = ssBusinessManager::getInstance().getOutputBuffer();
        if(!outputCommand.isEmpty())
        {
            outputCommand = outputCommand.trimmed();
            commandTextBox->append(outputCommand);
            QApplication::processEvents();
        }
    }
    commandTextBox->append("");
    antet = userAhost();
    commandTextBox->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    ssAdvisor::reviseCompleter();
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

bool SenseForm::eventFilter(QObject *obj, QEvent *event)
{ 
    if (event->type() == QEvent::KeyPress)
    {
        
        if(obj == commandTextBox)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Return)
            {
                executeCommandReady();
            }
                
        }
    }
    return QObject::eventFilter(obj, event);
}