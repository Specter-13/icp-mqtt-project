#include "simulator.h"
#include "ui_simulator.h"
#include <QDebug>
#include <string>

Simulator::Simulator(QMqttClient *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Simulator)
{
    ui->setupUi(this);

    this->client = client;

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onStart()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(onStop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(onSend()));
}

Simulator::~Simulator()
{
    delete ui;
}

void Simulator::onStart()
{
    timer->start(1000);
}

void Simulator::onStop()
{
    timer->stop();
}

void Simulator::onSend()
{
    QString message;

    message = QString::number(qrand() % 101);
    client->publish(QMqttTopicName("kitchen/temperature"), message.toUtf8());

    message = QString::number(qrand() % 101);
    client->publish(QMqttTopicName("livingroom/temperature"), message.toUtf8());

    message = QString::number(qrand() % 101);
    client->publish(QMqttTopicName("bedroom/temperature"), message.toUtf8());

    message = QString::number(qrand() % 101);
    client->publish(QMqttTopicName("kitchen/humidity"), message.toUtf8());

    message = QString::number(qrand() % 101);
    client->publish(QMqttTopicName("livingroom/humidity"), message.toUtf8());

    message = QString::number(qrand() % 101);
    client->publish(QMqttTopicName("bedroom/humidity"), message.toUtf8());




}
