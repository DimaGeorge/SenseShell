#include "ui_senseShell.h"

class ssGUIManager;
class ssStatusTable;

class SenseForm : public QWidget
{
    Q_OBJECT

public:
    SenseForm(QWidget *parent=0);
public slots:
    void on_commandTextBox_textChanged();
    void on_pushButton_clicked();

private:
    Ui::senseForm ui;
    ssGUIManager &manager;
    ssStatusTable &status;
};
