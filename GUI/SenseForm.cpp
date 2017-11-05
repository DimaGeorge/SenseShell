#include "SenseForm.h"
#include "ssGUIManager.h"
#include <QTextEdit>
#include <QAbstractItemModel>
#include <QWidget>
#include <QListView>
#include <QEvent>

SenseForm::SenseForm(QWidget *parent)
:QWidget(parent),status(ssStatusTable::getInstance()),manager(ssGUIManager::getInstance()),completer(0)
{
    setupUi(this);
}

void SenseForm::setupUi(QWidget *senseForm)
{
    qApp->installEventFilter(this);

    if (senseForm->objectName().isEmpty())
        senseForm->setObjectName(QString::fromUtf8("senseForm"));
     senseForm->resize(620, 455);

    commandTextBox = new TextEdit(this);
    commandTextBox->setObjectName(QString::fromUtf8("commandTextBox"));
    commandTextBox->setGeometry(QRect(5, 5, 610, 445));
    completer = new QCompleter(this);
    completer->setModel(modelFromFile("GUI/resources/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    tweak(completer);
    commandTextBox->setCompleter(completer);
   
   // suggestionTextBox = new QTextEdit(senseForm);
   // suggestionTextBox->setObjectName(QString::fromUtf8("suggestionTextBox"));
   // suggestionTextBox->setGeometry(QRect(5, 280, 611, 111));
   
    retranslateUi(senseForm);

} // setupUi

void SenseForm::retranslateUi(QWidget *senseForm)
{
    senseForm->setWindowTitle(QApplication::translate("senseForm", "SenseShell v1.0.1", 0, QApplication::UnicodeUTF8));
} // retranslateUi


void SenseForm::executeCommandReady()
{
    QString command;
    command=commandTextBox->toPlainText();

   
    QByteArray ba = command.toLatin1();
    char *c_str2 = ba.data(); 
    manager.sendCommand(c_str2);
    ssOutputBuffer &out=status.getRefToOutputBuffer();
    QString outputCommand=out.read().data();
    commandTextBox->setText(outputCommand);
}

QAbstractItemModel* SenseForm::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
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

void SenseForm::tweak(QCompleter *completer)
{
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModelSorting(QCompleter::CaseSensitivelySortedModel);
    tweak((QListView *)completer->popup());
}
void SenseForm::tweak(QListView* view)
{
    view->setUniformItemSizes(true);
    view->setLayoutMode(QListView::Batched);
}


bool SenseForm::eventFilter(QObject *obj, QEvent *event)
{ 
    if (event->type() == QEvent::KeyPress)
    {
        if(obj == commandTextBox)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Return)
                executeCommandReady();
        }
    }
    return QObject::eventFilter(obj, event);
}