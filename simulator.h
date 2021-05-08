/**
* @file simulator.h
*
* @brief Třída pro okno simulátoru.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo01)
*/
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QDialog>
#include <QtMqtt/QtMqtt>

namespace Ui {
class Simulator;
}

/**
* @class Simulator
*
* @brief Třída pro okno simulátoru.
*/
class Simulator : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor třídy.
     *
     * @param client ukazatel na klienta
     * @param parent rodičovský objekt
     */
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

    /**
     * @brief Slot pro start simulátoru.
     */
    void onStart();
    /**
     * @brief Slot pro zastavení simulátoru.
     */
    void onStop();
    /**
     * @brief Slot pro zaslání zpráv.
     */
    void onSend();
    /**
     * @brief Slot pro načtení konfigurace.
     */
    void onConfig();
    /**
     * @brief Slot pro přijetí zprávy.
     *
     * @param message data zprávy
     * @param topic téma zprávy
     */
    void onMessage(const QByteArray &message, const QMqttTopicName &topic);

};

#endif // SIMULATOR_H
