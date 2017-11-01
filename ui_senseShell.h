/********************************************************************************
** Form generated from reading UI file 'senseShell.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSESHELL_H
#define UI_SENSESHELL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_senseForm
{
public:
    QTextEdit *commandTextBox;
    QTextEdit *suggestionTextBox;
    QPushButton *pushButton;

    void setupUi(QWidget *senseForm)
    {
        if (senseForm->objectName().isEmpty())
            senseForm->setObjectName(QString::fromUtf8("senseForm"));
        senseForm->resize(710, 400);
        commandTextBox = new QTextEdit(senseForm);
        commandTextBox->setObjectName(QString::fromUtf8("commandTextBox"));
        commandTextBox->setGeometry(QRect(5, 5, 611, 271));
        suggestionTextBox = new QTextEdit(senseForm);
        suggestionTextBox->setObjectName(QString::fromUtf8("suggestionTextBox"));
        suggestionTextBox->setGeometry(QRect(5, 280, 611, 111));
        pushButton = new QPushButton(senseForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(620, 250, 90, 28));

        retranslateUi(senseForm);

        QMetaObject::connectSlotsByName(senseForm);
    } // setupUi

    void retranslateUi(QWidget *senseForm)
    {
        senseForm->setWindowTitle(QApplication::translate("senseForm", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("senseForm", "Send!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class senseForm: public Ui_senseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSESHELL_H
