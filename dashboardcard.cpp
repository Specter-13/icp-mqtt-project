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
    DashboardInstance = dashboard;

     connect(DashboardInstance, SIGNAL(topicDataSignal(QString,QByteArray)), this, SLOT(onMessageReceivedUpdateData(QString, QByteArray)));
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
    delete this;
}
