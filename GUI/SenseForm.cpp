#include "SenseForm.h"
#include "ssGUIManager.h"
#include <QTextEdit>
#include <QAbstractItemModel>
#include <QWidget>
#include <QListView>
#include <QEvent>

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
    completer->setModel(modelFromFile("GUI/resources/wordlist.txt"));
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
    static QTextCursor oldCursor = commandTextBox->textCursor();

    commandTextBox->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    commandTextBox->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);

    QString command;
    command = commandTextBox->textCursor().selectedText();

    QByteArray ba = command.toLatin1();
    char *c_str2 = ba.data(); 
    manager.sendCommand(c_str2);
    ssOutputBuffer &out=status.getRefToOutputBuffer();
    QString outputCommand=out.read().data();
    commandTextBox->append(outputCommand);
    
    commandTextBox->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

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
            qDebug("enter received!");
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Return)
            {
                executeCommandReady();
                
            }
                
        }
    }
    return QObject::eventFilter(obj, event);
}