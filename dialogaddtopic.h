#ifndef DIALOGADDTOPIC_H
#define DIALOGADDTOPIC_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QMqttClient>

namespace Ui {
class DialogAddTopic;
}

class DialogAddTopic : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddTopic(QString topic, QList<QMqttSubscription*> *subscriptions, QMqttClient *client, QTreeWidgetItem *item, QWidget *parent = nullptr);
    ~DialogAddTopic();

private:
    Ui::DialogAddTopic *ui;
    QTreeWidgetItem *root;
    QMqttClient *client;
    QList<QMqttSubscription*> *subscriptions;
    QString topic;

private slots:
    void onAdd();
};

#endif // DIALOGADDTOPIC_H
