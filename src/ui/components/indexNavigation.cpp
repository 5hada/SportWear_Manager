#include "indexNavigation.h"

#include "ElaText.h"
#include "ElaLineEdit.h"
#include "ElaIconButton.h"



IndexNavigation::IndexNavigation(QWidget* parent):
    QHBoxLayout(parent), currentIndex(0), maxIndex(0) {
    init();
}

void IndexNavigation::init() {
    setContentsMargins(0, 0, 0, 0);
    setSpacing(0);

    auto* leftEndArrow = new ElaIconButton(ElaIconType::AnglesLeft);
    leftEndArrow->setFixedWidth(40);
    auto* leftArrow = new ElaIconButton(ElaIconType::AngleLeft);
    leftArrow->setFixedWidth(40);
    pageIndex = new ElaText("1");
    pageIndex->setFixedWidth(70);
    pageIndex->setFixedHeight(30);
    pageIndex->setAlignment(Qt::AlignCenter);
    pageIndex->setTextPixelSize(12);
    pageIndexInput = new ElaLineEdit();
    pageIndexInput->setFixedWidth(50);
    pageIndexInput->setFixedHeight(30);
    auto* rightArrow = new ElaIconButton(ElaIconType::AngleRight);
    rightArrow->setFixedWidth(40);
    auto* rightEndArrow = new ElaIconButton(ElaIconType::AnglesRight);
    rightEndArrow->setFixedWidth(40);

    auto* indexLayout = new QHBoxLayout();
    indexLayout->addWidget(pageIndex);
    indexLayout->addSpacing(20);
    indexLayout->addWidget(pageIndexInput);

    addStretch();
    addWidget(leftEndArrow);
    addWidget(leftArrow);
    addSpacing(20);
    addLayout(indexLayout);
    addSpacing(20);
    addWidget(rightArrow);
    addWidget(rightEndArrow);
    addStretch();

    connect(leftEndArrow, &ElaIconButton::clicked, this, [this]() {
        if (currentIndex == 0) {
            return;
        }
        emit indexChanged(0);
        currentIndex = 0;
    });
    connect(leftArrow, &ElaIconButton::clicked, this, [this]() {
        if (currentIndex <= 0) {
            return;
        }
        const int nextIndex = currentIndex - 1;
        emit indexChanged(nextIndex);
        currentIndex = nextIndex;
    });
    connect(rightArrow, &ElaIconButton::clicked, this, [this]() {
        if (currentIndex >= maxIndex) {
            return;
        }
        const int nextIndex = currentIndex + 1;
        emit indexChanged(nextIndex);
        currentIndex = nextIndex;
    });
    connect(rightEndArrow, &ElaIconButton::clicked, this, [this]() {
        if (currentIndex == maxIndex) {
            return;
        }
        emit indexChanged(maxIndex);
        currentIndex = maxIndex;
    });
    connect(pageIndexInput, &ElaLineEdit::returnPressed, this, [this]() {
        bool ok = false;
        const int page = pageIndexInput->text().toInt(&ok);
        const int nextIndex = page - 1;
        if (ok && nextIndex >= 0 && nextIndex <= maxIndex) {
            emit indexChanged(nextIndex);
            currentIndex = nextIndex;
        }
    });
}

void IndexNavigation::setIndex(int maxIndex, int currentIndex) {
    this->maxIndex = maxIndex;
    this->currentIndex = currentIndex;
    updateText();
}


void IndexNavigation::updateText() {
    pageIndex->setText(QString("%1 / %2").arg(currentIndex + 1).arg(maxIndex + 1));
    const QString currentIndexText = QString::number(currentIndex + 1);
    if (pageIndexInput->text() != currentIndexText) {
        pageIndexInput->clear();
    }
}
