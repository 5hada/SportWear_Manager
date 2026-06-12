
#include "app/appContext.h"

#include <QMainWindow>

class QLabel;
class QLineEdit;
class QListWidget;
class QPushButton;
class QSpinBox;
class QTabWidget;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    AppContext app;
    
    QLabel *sessionLabel = nullptr;

    


    void buildInterface();
    
    int selectedProductId() const;
    bool requireLogin();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};
