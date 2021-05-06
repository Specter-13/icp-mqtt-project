#include "dialogsend.h"
#include "ui_dialogsend.h"
#include <QFileDialog>

DialogSend::DialogSend(QString topic, QMqttClient *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSend)
{
    ui->setupUi(this);
    this->topic = topic;
    this->client = client;

    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(onLoad()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(onSend()));


}

DialogSend::~DialogSend()
{
    delete ui;
}

void DialogSend::onLoad()
{

    QString fileName = "";
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home");
    if(fileName != "") {
        this->file = true;
        ui->fileLabel->setText(fileName);
    }
}

void DialogSend::onSend()
{

    if(file) {

        QFile file(ui->fileLabel->text());
        if(!file.open(QIODevice::ReadOnly)) {
            return;
        }

        QByteArray data = file.readAll();
        client->publish(QMqttTopicName(topic), data);

    } else {
        client->publish(QMqttTopicName(topic), ui->messageText->toPlainText().toUtf8());
    }

    this->close();

}
