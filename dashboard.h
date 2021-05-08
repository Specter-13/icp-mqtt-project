#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <QtMqtt/QtMqtt>
namespace Ui {
class Dashboard;
}

class Dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr, QMqttClient *client = nullptr);
    ~Dashboard();

signals:
 void topicDataSignal(QString topicName, QByteArray data);

public slots:
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void onAddItemClicked();
    void onSaveConfig();
    void onAddedItemSignal();
    void onRemoveItemSignal();
private:
    void LoadDashboardConfig();
private:
    QString getCardType(QString cardName );
private:
    QMqttClient *Client;
private:
    Ui::Dashboard *ui;
private:
    int DashboardItemsCount;
};

#endif // DASHBOARD_H
