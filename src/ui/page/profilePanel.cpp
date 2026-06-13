#include "profilePanel.h"
#include "profile/formPanelWidget.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <Qstackedwidget>
#include <QFrame>
#include <qnamespace.h>

ProfilePanel::ProfilePanel(QWidget* parent): ElaDialog(parent) {
    initPanel();


    widgets = new QStackedWidget(this);
    FormPanelWidget* formWidget = new FormPanelWidget();
    widgets->addWidget(formWidget);
    widgets->setCurrentWidget(formWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(widgets);
}

ProfilePanel::~ProfilePanel() {}

void ProfilePanel::initPanel(){
    setFixedSize(600, 400);
    setAppBarHeight(0);
    this->setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);
}
