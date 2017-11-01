#include "SenseForm.h"
#include "ssGUIManager.h"


SenseForm::SenseForm(QWidget *parent)
    :QWidget(parent),status(ssStatusTable::getInstance()),manager(ssGUIManager::getInstance())
{
    ui.setupUi(this);
}   
void SenseForm::on_commandTextBox_textChanged()
{
    
    
}
void SenseForm::on_pushButton_clicked()
{
    manager.sendCommand("ls -l");
    ssOutputBuffer &out=status.getRefToOutputBuffer();
    QString outputCommand=out.read().data();
    ui.suggestionTextBox->setText(outputCommand);

}
