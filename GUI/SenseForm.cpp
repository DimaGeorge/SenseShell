#include "SenseForm.h"
#include "ssGUIManager.h"
#include<QTextEdit>
#include <QAbstractItemModel>
#include<QWidget>
#include<QListView>

SenseForm::SenseForm(QWidget *parent)
:QWidget(parent),status(ssStatusTable::getInstance()),manager(ssGUIManager::getInstance()),completer(0)
{
    setupUi(this);
}

void SenseForm::setupUi(QWidget *senseForm)
{
    if (senseForm->objectName().isEmpty())
        senseForm->setObjectName(QString::fromUtf8("senseForm"));
     senseForm->resize(620, 455);
    commandTextBox = new TextEdit(this);
    commandTextBox->setObjectName(QString::fromUtf8("commandTextBox"));
    commandTextBox->setGeometry(QRect(5, 5, 611, 271));
    completer = new QCompleter(this);
    completer->setModel(modelFromFile("GUI/resources/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    tweak(completer);
    commandTextBox->setCompleter(completer);
   
    suggestionTextBox = new QTextEdit(senseForm);
    suggestionTextBox->setObjectName(QString::fromUtf8("suggestionTextBox"));
    suggestionTextBox->setGeometry(QRect(5, 280, 611, 111));
   
    retranslateUi(senseForm);

} // setupUi

void SenseForm::retranslateUi(QWidget *senseForm)
{
    senseForm->setWindowTitle(QApplication::translate("senseForm", "Form", 0, QApplication::UnicodeUTF8));
} // retranslateUi

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