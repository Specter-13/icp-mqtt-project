/**
* @file dialogdata.cpp
*
* @brief Třída pro dialog na zobrazení dat zprávy.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo01)
*/
#include "dialogdata.h"
#include "ui_dialogdata.h"
#include <QLabel>

DialogData::DialogData(QByteArray data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogData)
{
    ui->setupUi(this);
    this->data = data;
    QLabel *label = new QLabel();

    QPixmap pixmap;
    if(pixmap.loadFromData(data)) {
        label->setPixmap(pixmap);
    } else {
        label->setText(this->data);
    }

    ui->verticalLayout->addWidget(label);
}

DialogData::~DialogData()
{
    delete ui;
}
