#include "cartWidget.h"
#include "ElaTableView.h"
#include "ui/common/tableItemUtil.h"

#include <QHeaderView>
#include <QStandardItemModel>

CartWidget::CartWidget(QWidget* parent): ElaDockWidget("Cart", parent) {
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Product ID", "Quantity", "Unit Price", "Total"});
    centerHeaderItems(model);

    cartList = new ElaTableView(this);
    cartList->setModel(model);
    cartList->verticalHeader()->setHidden(true);
    cartList->horizontalHeader()->setStretchLastSection(false);
    cartList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    cartList->horizontalHeader()->setMinimumSectionSize(1);
    connect(cartList, &ElaTableView::tableViewShow, this, [this]() {
        cartList->horizontalHeader()->resizeSection(0, 80);
        cartList->horizontalHeader()->resizeSection(1, 80);
        cartList->horizontalHeader()->resizeSection(2, 90);
        cartList->horizontalHeader()->resizeSection(3, 90);
    });

    setWidget(cartList);
}

void CartWidget::setCart(const Cart& cart) {
    model->removeRows(0, model->rowCount());

    for (const auto& item : cart.getItems()) {
        QList<QStandardItem*> row;
        row << centeredItem(QString::number(item.id));
        row << centeredItem(QString::number(item.count));
        row << centeredItem(QString::number(item.price));
        row << centeredItem(QString::number(item.price * item.count));
        model->appendRow(row);
    }
}
