/**
* @file dashboardcardsetter.cpp
*
* @brief Trieda obsahujúca nastavovaciu Dashboard kartu.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#include "dashboardcardsetter.h"
#include "ui_dashboardcardsetter.h"

DashboardCardSetter::DashboardCardSetter(QWidget *parent,
                                         QString topicName,
                                         Dashboard * dashboard,
                                         QMqttClient *client) :
    QWidget(parent),
    ui(new Ui::DashboardCardSetter)
{
    ui->setupUi(this);
    this->Client = client;
    this->TopicName = topicName;
    this->DashboardInstance = dashboard;
    ui->topicName->setText(TopicName);
    connect(DashboardInstance, SIGNAL(topicDataSignal(QString,QByteArray)), this, SLOT(onMessageReceivedUpdateData(QString, QByteArray)));
    connect(ui->removeButton, SIGNAL(clicked()),this,SLOT(onRemoveClicked()));
    connect(ui->sendButton, SIGNAL(clicked()),this, SLOT(onSendClicked()));
    connect(this, SIGNAL(RemovedItemSignal()), DashboardInstance, SLOT(onRemoveItemSignal()));
}

void DashboardCardSetter::onMessageReceivedUpdateData(QString topic, QByteArray message)
{
   if(TopicName == topic)
   {
       ui->topicData->setText(QString(message));
   }
}

void DashboardCardSetter::onSendClicked()
{
    QString insertedData = ui->dataTextbox->text();
    if(insertedData != nullptr)
    {
        Client->publish(QMqttTopicName(TopicName), insertedData.toUtf8());
    }
}

DashboardCardSetter::~DashboardCardSetter()
{
    delete ui;
}

void DashboardCardSetter::onRemoveClicked()
{
    emit RemovedItemSignal();
    delete this;
}
