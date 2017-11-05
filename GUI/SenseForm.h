#include <QWidget>
#include "textedit.h"

class ssGUIManager;
class ssStatusTable;
class QTextEdit;
class QString;
class QWidget;
class QAbstractItemModel;
class QListView;
class QEvent;


class SenseForm : public QWidget
{
    Q_OBJECT

public:
    SenseForm(QWidget *parent=0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void tweak(QCompleter *);
    void tweak(QListView* );
    void setupUi(QWidget *senseForm);
    void retranslateUi(QWidget *senseForm);
    void executeCommandReady();
    QAbstractItemModel* modelFromFile(const QString& fileName);
    TextEdit *commandTextBox;
   // QTextEdit *suggestionTextBox;
    QCompleter* completer;
    ssGUIManager &manager;
    ssStatusTable &status;
};
