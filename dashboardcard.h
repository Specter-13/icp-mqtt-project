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
    void onMessageReceivedUpdateData(QString message, QString topic);

private:
    Ui::DashboardCard *ui;
private:
    QString TopicName;
private:
    QByteArray *Data;
private:
    Dashboard *DashBoardInstance;
};

#endif // DASHBOARDCARD_H
