#include "cartWidget.h"
#include "ElaTableView.h"

#include <QHeaderView>
#include <QStandardItemModel>

CartWidget::CartWidget(QWidget* parent): ElaDockWidget("Cart", parent) {
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Product ID", "Quantity", "Unit Price", "Total"});

    cartList = new ElaTableView(this);
    cartList->setModel(model);
    cartList->verticalHeader()->setHidden(true);
    cartList->horizontalHeader()->setStretchLastSection(true);

    setWidget(cartList);
}

void CartWidget::setCart(const Cart& cart) {
    model->removeRows(0, model->rowCount());

    for (const auto& item : cart.getItems()) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(item.id));
        row << new QStandardItem(QString::number(item.count));
        row << new QStandardItem(QString::number(item.price));
        row << new QStandardItem(QString::number(item.price * item.count));
        model->appendRow(row);
    }
}
