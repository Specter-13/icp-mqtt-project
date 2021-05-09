/**
* @file dashboard.cpp
*
* @brief Trieda obsahujúca logiku Dashboardu.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#include "dashboard.h"
#include "ui_dashboard.h"
#include "dashboardcard.h"
#include "dashboardcardsetter.h"
#include "dashboardcardswitch.h"
#include "dialogadditem.h"
#include <QtMqtt/QtMqtt>
#include <QLabel>

Dashboard::Dashboard(QWidget *parent, QMqttClient *client) :
    QDialog(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    this->Client = client;
    this->DashboardItemsCount = 0;
    connect(ui->addItemButton, SIGNAL(clicked()), this, SLOT(onAddItemClicked()));
    connect(ui->saveConfigButton, SIGNAL(clicked()), this, SLOT(onSaveConfig()));
    this->setWindowTitle("Dashboard");
    LoadDashboardConfig();
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::onSaveConfig()
{

    QJsonArray jsonArray;

    for (int i = 0; i <  DashboardItemsCount; i++)
    {
      QWidget *widget =  ui->verticalLayout->itemAt(i)->widget();
      QString cardType = getCardType(widget->objectName().toLower());
      QString topicName = widget->findChild<QLabel*>("topicName")->text();

      QJsonObject arrayItem;
      arrayItem.insert("topic-name",topicName);
      arrayItem.insert("card-type",cardType);

      jsonArray.insert(i, arrayItem);

    }

    QJsonDocument doc(jsonArray);

    QString path = "dashboard-config.json";
    QFile file(path);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate) ;
    //create file if doesn't exists
    file.write(doc.toJson());
    file.close();


}

void Dashboard::onAddedItemSignal()
{
    DashboardItemsCount++;
}

void Dashboard::onRemoveItemSignal()
{
    DashboardItemsCount--;
}


QString Dashboard::getCardType(QString cardName)
{
    if (cardName == "dashboardcardsetter")
    {
        return "setter";
    }
    else if (cardName == "dashboardcardswitch")
    {
        return "switch";
    }
    else
    {
       return  "generic";
    }
}

void Dashboard::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    emit topicDataSignal(topic.name(), message);
}

void Dashboard::onAddItemClicked()
{
    QVBoxLayout* layout = ui->verticalLayout;

    DialogAddItem *itemDialog = new DialogAddItem(nullptr,layout, this,  Client );
    itemDialog->show();


}

void Dashboard::LoadDashboardConfig()
{
    QString path = "dashboard-config.json";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //create file if doesn't exists
        file.open(QIODevice::ReadWrite);
        file.close();
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonArray array = document.array();
    foreach (const QJsonValue & v, array)
    {
            QString topicName = v.toObject().value("topic-name").toString();
            QString cardType = v.toObject().value("card-type").toString();
            if(cardType == "generic")
            {
                ui->verticalLayout->addStretch();
                DashboardCard * card = new DashboardCard(nullptr, topicName, this);
                ui->verticalLayout->insertWidget(0,card);
            }
            else if(cardType == "switch")
            {
                ui->verticalLayout->addStretch();
                DashboardCardSwitch * card = new DashboardCardSwitch(nullptr, topicName, this, Client);
                ui->verticalLayout->insertWidget(0,card);
            }
            else if(cardType == "setter")
            {
                ui->verticalLayout->addStretch();
                DashboardCardSetter* card = new DashboardCardSetter(nullptr, topicName, this, Client);
                ui->verticalLayout->insertWidget(0,card);
            }
            DashboardItemsCount++;
    }
}
