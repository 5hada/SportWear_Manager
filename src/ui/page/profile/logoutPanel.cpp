#include "logoutPanel.h"

#include <ElaPushButton.h>
#include <ElaText.h>
#include <QHBoxLayout>
#include <QVBoxLayout>

LogoutPanel::LogoutPanel(QWidget* parent): QWidget(parent) {
    titleText = new ElaText("Logout", this);
    titleText->setTextPixelSize(26);

    descText = new ElaText("End the current session and return to guest mode.", this);
    descText->setTextPixelSize(15);
    descText->setWordWrap(true);

    cancelButton = new ElaPushButton("Cancel", this);
    logoutButton = new ElaPushButton("Logout", this);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(logoutButton);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(32, 28, 32, 28);
    mainLayout->setSpacing(14);
    mainLayout->addWidget(titleText);
    mainLayout->addWidget(descText);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}
