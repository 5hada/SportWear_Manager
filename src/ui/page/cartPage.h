#include "app/appContext.h"
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>

class CartPage : public QWidget {
    AppContext app;

    QTabWidget *tab = nullptr;
    QListWidget *cartList = nullptr;
    QLabel *cartTotalLabel = nullptr;
    QLineEdit *addressEdit = nullptr;
public:
    explicit CartPage(QWidget *parent = nullptr);

    void buildInterface();
    void refreshCart();
};
