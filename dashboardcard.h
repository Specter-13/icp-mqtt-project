#ifndef DASHBOARDCARD_H
#define DASHBOARDCARD_H

#include <QWidget>
#include <QtMqtt/QtMqtt>
#include "dashboard.h"
namespace Ui {
class DashboardCard;
}

class DashboardCard : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardCard(QWidget *parent = nullptr,
                           QString name = "",
                           QByteArray *data = nullptr,
                           Dashboard *dashboard = nullptr);
    ~DashboardCard();
private slots:
    void onMessageReceivedUpdateData(QString topic, QByteArray message) ;
    void onRemoveClicked();
signals:
        void RemovedItemSignal();
private:
    Ui::DashboardCard *ui;
private:
    QString TopicName;
private:
    QByteArray *Data;
private:
    Dashboard *DashboardInstance;
};

#endif // DASHBOARDCARD_H
