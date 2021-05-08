#ifndef DASHBOARDCARDSWITCH_H
#define DASHBOARDCARDSWITCH_H

#include <QWidget>
#include "dashboard.h"
#include <QtMqtt/QtMqtt>
namespace Ui {
class DashboardCardSwitch;
}

class DashboardCardSwitch : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardCardSwitch(QWidget *parent = nullptr,
                                 QString name = "",
                                 Dashboard *dashboard = nullptr,
                                 QMqttClient *client = nullptr);
    ~DashboardCardSwitch();
private slots:
     void onMessageReceivedUpdateData(QString topic, QByteArray message) ;
     void onTurnOnClicked() ;
     void onTurnOffClicked() ;
     void onRemoveClicked() ;
signals:
        void RemovedItemSignal();
private:
    Dashboard *DashboardInstance;
private:
    QString TopicName;
private:
    QMqttClient *Client;
private:
    Ui::DashboardCardSwitch *ui;
};

#endif // DASHBOARDCARDSWITCH_H
