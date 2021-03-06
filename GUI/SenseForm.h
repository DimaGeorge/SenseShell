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
    int userAhost(bool print = true);
    void setupUi(QWidget *senseForm);
    void retranslateUi(QWidget *senseForm);
    void executeCommandReady();

    /* fields */
    ssGUIManager    &manager;
    ssStatusTable   &status;

    //QAbstractItemModel  *modelFromFile(const QString& fileName);
    TextEdit            *commandTextBox;
    QCompleter          *completer;
    QTextCursor          currentCursor;
    int                  position;
    int                  antetLength;
};
