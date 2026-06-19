#include "indexNavigation.h"
#include "ElaText.h"
#include "ElaLineEdit.h"
#include "ElaIconButton.h"



IndexNavigation::IndexNavigation(QWidget* parent):
    QHBoxLayout(parent), currentIndex(0), maxIndex(0) {
    init();
}

void IndexNavigation::init() {
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

    auto* indexNavigation = new QHBoxLayout();
    indexNavigation->addStretch();
    indexNavigation->addWidget(leftEndArrow);
    indexNavigation->addWidget(leftArrow);
    indexNavigation->addSpacing(20);
    indexNavigation->addLayout(indexLayout);
    indexNavigation->addSpacing(20);
    indexNavigation->addWidget(rightArrow);
    indexNavigation->addWidget(rightEndArrow);
    indexNavigation->addStretch();

    connect(leftEndArrow, &ElaIconButton::clicked, this, [this]() {
        indexChanged(0);
        currentIndex = 0;
    });
    connect(leftArrow, &ElaIconButton::clicked, this, [this]() {
        indexChanged(currentIndex - 1);
        currentIndex--;
    });
    connect(rightArrow, &ElaIconButton::clicked, this, [this]() {
        indexChanged(currentIndex + 1);
        currentIndex++;
    });
    connect(rightEndArrow, &ElaIconButton::clicked, this, [this]() {
        indexChanged(maxIndex);
        currentIndex = maxIndex;
    });
    connect(pageIndexInput, &ElaLineEdit::returnPressed, this, [this]() {
        bool ok = false;
        const int page = pageIndexInput->text().toInt(&ok);
        if (ok) {
            indexChanged(page - 1);
            currentIndex = page - 1;
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