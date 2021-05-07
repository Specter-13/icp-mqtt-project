#ifndef DASHBOARDCARDSETTER_H
#define DASHBOARDCARDSETTER_H

#include <QWidget>
#include "dashboard.h"
#include <QtMqtt/QtMqtt>

namespace Ui {
class DashboardCardSetter;
}

class DashboardCardSetter : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardCardSetter(QWidget *parent = nullptr ,
                                 QString topicName = "",
                                 Dashboard *dashboard = nullptr,
                                 QMqttClient *client = nullptr);
    ~DashboardCardSetter();
private slots:
     void onMessageReceivedUpdateData(QString topic, QByteArray message) ;
     void onSendClicked() ;
     void onRemoveClicked() ;
private:
    Dashboard *DashboardInstance;
private:
    QString TopicName;
private:
    QMqttClient *Client;
private:
    Ui::DashboardCardSetter *ui;
};

#endif // DASHBOARDCARDSETTER_H
