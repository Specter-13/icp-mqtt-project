#include "simulator.h"
#include "ui_simulator.h"
#include <QDebug>
#include <string>
#include <QFileDialog>

Simulator::Simulator(QMqttClient *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Simulator)
{
    ui->setupUi(this);

    this->client = client;


    connect(client, SIGNAL(messageReceived(const QByteArray &, const QMqttTopicName &)), this, SLOT(onMessage(const QByteArray &, const QMqttTopicName &)));

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onStart()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(onStop()));
    connect(ui->configButton, SIGNAL(clicked()), this, SLOT(onConfig()));
    connect(timer, SIGNAL(timeout()), this, SLOT(onSend()));

    QFile file("/home/vojta/Downloads/kekw.jpg");
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }

    imgdata = file.readAll();

}

Simulator::~Simulator()
{
    delete ui;
}

void Simulator::onStart()
{
    timer->start(period);
}

void Simulator::onStop()
{
    timer->stop();
}

void Simulator::onSend()
{
    QString message;
    QString topic;

    for (int i = 0; i < humCount; ++i) {

        message = QString::number(qrand() % 101);
        message.append("%");
        topic = "humidity/hum";
        topic.append(QString::number(i));
        client->publish(QMqttTopicName(topic), message.toUtf8());

    }

    for (int i = 0; i < scanCount; ++i) {

        int number = qrand() % 2;

        if(number == 0) {
            message = "triggered";
        } else {
            message = "idle";
        }

        topic = "scanners/scan";
        topic.append(QString::number(i));
        client->publish(QMqttTopicName(topic), message.toUtf8());

    }

    for (int i = 0; i < relayCount; ++i) {

        int number = qrand() % 2;

        if(number == 0) {
            message = "on";
        } else {
            message = "off";
        }

        topic = "relays/rel";
        topic.append(QString::number(i));
        client->publish(QMqttTopicName(topic), message.toUtf8());

    }

    for (int i = 0; i < camCount; ++i) {


        topic = "cameras/cam";
        topic.append(QString::number(i));
        client->publish(QMqttTopicName(topic), imgdata);

    }

    topic = "thermostat/temperature";
    int number = qrand() % 31;
    message = QString::number(number);
    client->publish(QMqttTopicName(topic), message.toUtf8());

    topic = "thermostat/state";

    if(number < tempSetpoint) {
        message = "on";
    } else {
        message = "off";
    }
    client->publish(QMqttTopicName(topic), message.toUtf8());

    topic = "thermostat/setpoint";
    message = QString::number(tempSetpoint);
    client->publish(QMqttTopicName(topic), message.toUtf8());





}

void Simulator::onConfig()
{

    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home");
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QByteArray data = file.readAll();

    QJsonDocument json = QJsonDocument::fromJson(data);

    QJsonObject jsondata = json.object();


    period = jsondata.value("period").toInt();
    tempSetpoint = jsondata.value("tempSetpoint").toInt();
    humCount = jsondata.value("humCount").toInt();
    scanCount = jsondata.value("scanCount").toInt();
    relayCount = jsondata.value("relayCount").toInt();
    camCount = jsondata.value("camCount").toInt();

}

void Simulator::onMessage(const QByteArray &message, const QMqttTopicName &topic)
{
    if(topic.name() == "thermostat/setpoint") {
        this->tempSetpoint = message.toInt();
    }
}
