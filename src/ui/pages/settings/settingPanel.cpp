#include "settingPanel.h"

#include <ElaCheckBox.h>
#include <ElaComboBox.h>
#include <ElaPushButton.h>
#include <ElaSlider.h>
#include <ElaText.h>
#include <ElaToggleSwitch.h>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace {
QFrame* makeDivider(QWidget* parent) {
    auto* line = new QFrame(parent);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Plain);
    line->setFixedHeight(1);
    return line;
}

QHBoxLayout* makeRow(const QString& title, const QString& subtitle, QWidget* control, QWidget* parent) {
    auto* titleText = new ElaText(title, parent);
    titleText->setTextPixelSize(15);

    auto* subtitleText = new ElaText(subtitle, parent);
    subtitleText->setTextPixelSize(12);

    auto* textLayout = new QVBoxLayout();
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(3);
    textLayout->addWidget(titleText);
    textLayout->addWidget(subtitleText);

    auto* row = new QHBoxLayout();
    row->setContentsMargins(0, 6, 0, 6);
    row->setSpacing(16);
    row->addLayout(textLayout);
    row->addStretch();
    row->addWidget(control);
    return row;
}
}

SettingPanel::SettingPanel(QWidget* parent): ElaDialog(parent) {
    setWindowTitle("Settings");
    setFixedSize(520, 560);
    setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);

    auto* titleText = new ElaText("Settings", this);
    titleText->setTextPixelSize(26);

    auto* subtitleText = new ElaText("Application preferences", this);
    subtitleText->setTextPixelSize(13);

    auto* themeCombo = new ElaComboBox(this);
    themeCombo->setFixedSize(160, 34);
    themeCombo->addItems({"System", "Light", "Dark"});

    auto* densityCombo = new ElaComboBox(this);
    densityCombo->setFixedSize(160, 34);
    densityCombo->addItems({"Comfortable", "Compact", "Spacious"});

    auto* animationToggle = new ElaToggleSwitch(this);
    animationToggle->setIsToggled(true);

    auto* notificationToggle = new ElaToggleSwitch(this);
    notificationToggle->setIsToggled(true);

    auto* lowStockCheck = new ElaCheckBox("Low stock alerts", this);
    lowStockCheck->setChecked(true);

    auto* receiptCheck = new ElaCheckBox("Receipt updates", this);
    receiptCheck->setChecked(true);

    auto* pageSizeSlider = new ElaSlider(Qt::Horizontal, this);
    pageSizeSlider->setFixedWidth(160);
    pageSizeSlider->setRange(20, 80);
    pageSizeSlider->setValue(50);

    auto* cacheButton = new ElaPushButton("Clear Cache", this);
    cacheButton->setFixedSize(130, 34);

    auto* exportButton = new ElaPushButton("Export Data", this);
    exportButton->setFixedSize(130, 34);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(28, 24, 28, 24);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(titleText);
    mainLayout->addWidget(subtitleText);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(makeRow("Theme", "Choose the visual appearance.", themeCombo, this));
    mainLayout->addLayout(makeRow("Density", "Adjust spacing for product tables.", densityCombo, this));
    mainLayout->addLayout(makeRow("Animations", "Enable page transition effects.", animationToggle, this));
    mainLayout->addWidget(makeDivider(this));
    mainLayout->addLayout(makeRow("Notifications", "Show application notices.", notificationToggle, this));
    mainLayout->addWidget(lowStockCheck);
    mainLayout->addWidget(receiptCheck);
    mainLayout->addWidget(makeDivider(this));
    mainLayout->addLayout(makeRow("Products per page", "Preview page size preference.", pageSizeSlider, this));
    mainLayout->addLayout(makeRow("Local cache", "Remove temporary UI data.", cacheButton, this));
    mainLayout->addLayout(makeRow("Data export", "Prepare a product data package.", exportButton, this));
    mainLayout->addStretch();
}
