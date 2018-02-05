#include "SenseForm.h"
#include "ssGUIManager.h"
#include <ssAdvisor.h>
#include <QTextEdit>
#include <QAbstractItemModel>
#include <QWidget>
#include <QListView>
#include <QHostInfo>
#include <QEvent>
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
    currentCursor=commandTextBox->textCursor();
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

    manager.sendCommand(command.toLatin1().data());
    QString outputCommand = ssBusinessManager::getInstance().getOutputBuffer();
    commandTextBox->append(outputCommand);
    antet = userAhost();
    commandTextBox->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    ssAdvisor::reviseCompleter();
}

int SenseForm::userAhost(bool print)
{
    QString redHtml = "<font color=\"Red\">";
    QString greenHtml = "<font color=\"Green\">";
    QString endHtml = "</font> <font color=\"White\">";

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    QString workingDir = cwd;
    workingDir+="#";
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    name += "@";
    name += QHostInfo::localHostName();
    name += ":";

    QString line = redHtml % name;
    line = line % endHtml;
    line = line % greenHtml;
    line = line % workingDir;
    line = line % endHtml;
    name += workingDir;

    if(print)
    {
        commandTextBox->moveCursor(QTextCursor::End);
        commandTextBox->insertHtml(line);
        commandTextBox->moveCursor(QTextCursor::End);
    }
    

    
    currentCursor=commandTextBox->textCursor();
    commandTextBox->setTextCursor(currentCursor);
    antetLength=currentCursor.position();
    return name.length();

}
bool SenseForm::eventFilter(QObject *obj, QEvent *event)
{ 
    QChar currentChar;


    if (event->type() == QEvent::KeyPress)
    {
        
        if(obj == commandTextBox)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            switch(keyEvent->key())
            {
                case Qt::Key_Return:
                    executeCommandReady();
                break;
                case Qt::Key_Left:
                qDebug("ANTET: %d",antetLength);
                if((currentCursor.position()) <= antetLength)
                {
                    qDebug("LIMIT");
                    commandTextBox->setTextCursor(currentCursor);
                }
                else 
                {
                    currentCursor.movePosition(QTextCursor::Left);
                    qDebug("POZITIA: %d",currentCursor.position());
                }
                break;
                case Qt::Key_Right:
                    if((currentCursor.position()) <= antetLength)
                    {
                        commandTextBox->setTextCursor(currentCursor);
                    }

                break;
                case Qt::Key_Backspace:
                   if((currentCursor.position()) <= antetLength)
                    {
                        qDebug("LIMIT");
                        commandTextBox->setTextCursor(currentCursor);
                        return 0;
                    }
                    else 
                    {
                        currentCursor.movePosition(QTextCursor::Left);
                        currentCursor.deleteChar();
                        commandTextBox->setTextCursor(currentCursor);
                        qDebug("POZITIA: %d",currentCursor.position());
                    }
                break;
                default:
                  //   currentCursor.movePosition(QTextCursor::Right);
                  //  qDebug("POZITIA: %d",currentCursor.position());
                break;
            }
  
                
        }
    }
    return QObject::eventFilter(obj, event);
}