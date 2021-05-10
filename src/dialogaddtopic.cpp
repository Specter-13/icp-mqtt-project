/**
* @file dialogaddtopic.cpp
*
* @brief Třída pro dialog na přidávání tématu do hierarchie stromu.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#include "dialogaddtopic.h"
#include "ui_dialogaddtopic.h"
#include <QMessageBox>

DialogAddTopic::DialogAddTopic(QString topic, QList<QMqttSubscription*> *subscriptions, QMqttClient *client, QTreeWidgetItem *item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddTopic)
{
    ui->setupUi(this);
    this->root = item;
    this->client = client;
    this->subscriptions = subscriptions;
    this->topic = topic;
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAdd()));
}

DialogAddTopic::~DialogAddTopic()
{
    delete ui;
}

void DialogAddTopic::onAdd()
{
    topic.append("/");
    topic.append(ui->topic->text());

    auto sub = client->subscribe(QMqttTopicFilter(topic));
    if (!sub) {
            QMessageBox::critical(this, QString("Error"), QString("Could not subscribe."));
            return;
        }
    subscriptions->append(sub);

    auto child = new QTreeWidgetItem(root);
    child->setText(0, ui->topic->text());
    child->setText(1, "");

    this->close();

}
