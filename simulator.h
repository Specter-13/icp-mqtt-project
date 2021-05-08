#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QDialog>
#include <QtMqtt/QtMqtt>

namespace Ui {
class Simulator;
}

class Simulator : public QDialog
{
    Q_OBJECT

public:
    explicit Simulator(QMqttClient *client, QWidget *parent = nullptr);
    ~Simulator();

private:
    Ui::Simulator *ui;

    QMqttClient *client;
    QTimer *timer = new QTimer(this);
    int period = 1000;
    int tempSetpoint = 20;
    int humCount = 0;
    int scanCount = 0;
    int relayCount = 0;
    int camCount = 0;
    QByteArray imgdata;

private slots:

    void onStart();
    void onStop();
    void onSend();
    void onConfig();
    void onMessage(const QByteArray &message, const QMqttTopicName &topic);

};

#endif // SIMULATOR_H
