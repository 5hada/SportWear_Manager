#pragma once

#include <QStandardItem>
#include <QStandardItemModel>
#include <Qt>

inline QStandardItem* centeredItem(const QString& text = QString()) {
    auto* item = new QStandardItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

inline void centerHeaderItems(QStandardItemModel* model) {
    if (model == nullptr) {
        return;
    }
    for (int column = 0; column < model->columnCount(); ++column) {
        model->setHeaderData(column, Qt::Horizontal, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}
