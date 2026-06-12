#include "app/appContext.h"
#include <QWidget>
#include <QListWidget>

class OrderPage : public QWidget {
    AppContext app;

    QTabWidget *tab = nullptr;
    QListWidget *orderList = nullptr;
public:
    explicit OrderPage(QWidget *parent = nullptr);
    
    void buildInterface();
    void refreshOrders();
};
