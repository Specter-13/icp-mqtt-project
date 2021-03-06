/**
* @file dashboardcard.cpp
*
* @brief Trieda obsahujúca generickú Dashboard kartu.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#include "dashboardcard.h"
#include "ui_dashboardcard.h"

DashboardCard::DashboardCard(QWidget *parent,
                             QString name,
                             Dashboard *dashboard) :
    QWidget(parent),
    ui(new Ui::DashboardCard)
{
    ui->setupUi(this);
    ui->topicName->setText(name);
    TopicName = name;
    DashboardInstance = dashboard;

     connect(DashboardInstance, SIGNAL(topicDataSignal(QString,QByteArray)), this, SLOT(onMessageReceivedUpdateData(QString, QByteArray)));
     connect(this, SIGNAL(RemovedItemSignal()), DashboardInstance, SLOT(onRemoveItemSignal()));
     connect(ui->removeButton, SIGNAL(clicked()),this,SLOT(onRemoveClicked()));


}


DashboardCard::~DashboardCard()
{
    delete ui;
}

void DashboardCard::onMessageReceivedUpdateData(QString topic, QByteArray message)
{
    QPixmap pixmap;

    if(TopicName == topic)
    {
        if(pixmap.loadFromData(message)) {
            ui->dataLabel->setPixmap(pixmap);
        } else {
            ui->dataLabel->setText(QString(message));
        }

    }
}

void DashboardCard::onRemoveClicked()
{
    emit RemovedItemSignal();
    delete this;
}
