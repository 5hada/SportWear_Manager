#include "app/appContext.h"
#include <QWidget>
#include <QListWidget>

class ProductPage : public QWidget {
    AppContext app;

    QTabWidget *tab = nullptr;
    QListWidget *productList = nullptr;
    QSpinBox *quantitySpin = nullptr;
public:
    explicit ProductPage(QWidget *parent = nullptr);
    
    void buildInterface();
    void refreshProducts();
};
