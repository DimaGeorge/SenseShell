#include "SenseForm.h"
#include "ssGUIManager.h"


SenseForm::SenseForm(QWidget *parent)
    :QWidget(parent),status(ssStatusTable::getInstance()),manager(ssGUIManager::getInstance())
{
    ui.setupUi(this);
    qApp->installEventFilter(this);
}   

bool SenseForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if(obj == ui.commandTextBox)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Return)
                ui.suggestionTextBox->setText("ENTER!!!");
          
        }
    }
    return QObject::eventFilter(obj, event);
}

void SenseForm::on_pushButton_clicked()
{
    manager.sendCommand("man egrep");
    ssOutputBuffer &out=status.getRefToOutputBuffer();
    QString outputCommand=out.read().data();
    ui.suggestionTextBox->setText(outputCommand);
}


