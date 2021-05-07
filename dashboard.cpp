#include "dashboard.h"
#include "ui_dashboard.h"
#include "dashboardcard.h"
#include "dialogadditem.h"
#include <QtMqtt/QtMqtt>

Dashboard::Dashboard(QWidget *parent, QMqttClient *client) :
    QDialog(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    this->Client = client;
    connect(ui->addItemButton, SIGNAL(clicked()), this, SLOT(onAddItemClicked()));
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    emit topicDataSignal(topic.name(), message);
}

void Dashboard::onAddItemClicked()
{
    QVBoxLayout* layout = ui->verticalLayout;

    DialogAddItem *itemDialog = new DialogAddItem(nullptr,layout, this, Client);
    itemDialog->show();


}
