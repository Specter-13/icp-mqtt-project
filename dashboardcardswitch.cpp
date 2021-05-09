/**
* @file dashboardcardswitch.cpp
*
* @brief Trieda obsahujúca Dashboard kartu typu spínač.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#include "dashboardcardswitch.h"
#include "ui_dashboardcardswitch.h"

DashboardCardSwitch::DashboardCardSwitch(QWidget *parent,
                                         QString topicName,
                                         Dashboard * dashboard,
                                         QMqttClient *client) :
    QWidget(parent),
    ui(new Ui::DashboardCardSwitch)
{
    DashboardInstance = dashboard;
    TopicName = topicName;
    ui->setupUi(this);
    ui->topicName->setText(TopicName);
    this->Client = client;
    connect(DashboardInstance, SIGNAL(topicDataSignal(QString,QByteArray)), this, SLOT(onMessageReceivedUpdateData(QString, QByteArray)));
    connect(ui->removeButton, SIGNAL(clicked()),this,SLOT(onRemoveClicked()));
    connect(ui->turnOnButton, SIGNAL(clicked()),this,SLOT(onTurnOnClicked()));
    connect(ui->turnOffButton, SIGNAL(clicked()),this,SLOT(onTurnOffClicked()));
    connect(this, SIGNAL(RemovedItemSignal()), DashboardInstance, SLOT(onRemoveItemSignal()));
}

DashboardCardSwitch::~DashboardCardSwitch()
{
    delete ui;
}

void DashboardCardSwitch::onMessageReceivedUpdateData(QString topic, QByteArray message)
{
   if(TopicName == topic)
   {
       ui->topicData->setText(QString(message));
   }
}

void DashboardCardSwitch::onTurnOnClicked()
{
    QString message = "on";
    Client->publish(QMqttTopicName(TopicName), message.toUtf8());
}
void DashboardCardSwitch::onTurnOffClicked()
{
    QString message = "off";
    Client->publish(QMqttTopicName(TopicName), message.toUtf8());
}

void DashboardCardSwitch::onRemoveClicked()
{
     emit RemovedItemSignal();
    delete this;
}
