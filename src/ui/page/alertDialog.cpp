
#include"alertDialog.h"
#include<ElaPushButton.h>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<ElaText.h>


AlertDialog::AlertDialog(QWidget* parent): ElaDialog(parent){
    ElaText* title = new ElaText("Logout");
    title->setTextPixelSize(32);
    ElaText* desc = new ElaText("really want to logout?\ncant cancelled.");
    desc->setTextPixelSize(18);
    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(title);
    textLayout->addWidget(desc);
    

    cancelButton = new ElaPushButton();
    cancelButton->setText("Cancel");
    exitButton = new ElaPushButton();
    exitButton->setText("Exit");
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(exitButton);


    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(textLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(cancelButton, &ElaPushButton::pressed, this, &AlertDialog::close);
    connect(exitButton, &ElaPushButton::pressed, this, 
        [=](void){emit exitClicked(); close();});
}
