#include "dashboardcard.h"
#include "ui_dashboardcard.h"

DashboardCard::DashboardCard(QWidget *parent,
                             QString name,
                             QByteArray *data,
                             Dashboard *dashboard) :
    QWidget(parent),
    ui(new Ui::DashboardCard)
{
    ui->setupUi(this);
    ui->label->setText(name);
    TopicName = name;
    Data = data;
    DashBoardInstance = dashboard;

     connect(DashBoardInstance, SIGNAL(topicDataSignal(QString,QString)), this, SLOT(onMessageReceivedUpdateData(QString, QString)));
     connect(ui->removeButton, SIGNAL(clicked()),this,SLOT(onRemoveButtonClicked()));

}

DashboardCard::~DashboardCard()
{
    delete ui;
}

void DashboardCard::onMessageReceivedUpdateData(QString topic, QString message)
{
    if(TopicName == topic)
    {
        ui->label_2->setText(QString(message));
    }
}

void DashboardCard::onRemoveButtonClicked()
{
    delete this;
}
