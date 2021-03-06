/**
* @file dialogconnect.cpp
*
* @brief Třída pro dialog na připojení k brokerovi.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#include "dialogconnect.h"
#include "ui_dialogconnect.h"

DialogConnect::DialogConnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnect)
{
    ui->setupUi(this);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onOkButton()));
}

DialogConnect::~DialogConnect()
{
    delete ui;
}

void DialogConnect::onOkButton()
{
    emit Connecting(ui->addr->text(), ui->port->text().toInt(), ui->maxMess->text().toInt(), ui->topics->toPlainText());
    this->close();
}
