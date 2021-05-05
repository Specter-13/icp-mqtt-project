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

private slots:

    void onStart();
    void onStop();
    void onSend();

};

#endif // SIMULATOR_H
