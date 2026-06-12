#pragma once

#include <ElaWidgetTools/ElaTableView.h>

class CartList : public ElaTableView
{
    Q_OBJECT

public:
    explicit CartList(QWidget* parent = nullptr)
        : ElaTableView(parent)
    {
    }
};
