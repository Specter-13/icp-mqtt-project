/**
* @file dashboardcardswitch.h
*
* @brief Trieda obsahujúca Dashboard kartu typu spínač.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#ifndef DASHBOARDCARDSWITCH_H
#define DASHBOARDCARDSWITCH_H

#include <QWidget>
#include "dashboard.h"
#include <QtMqtt/QtMqtt>
namespace Ui {
class DashboardCardSwitch;
}
/**
* @class DashboardCardSwitch
*
* @brief DasboardCardSwitch trieda
*/
class DashboardCardSwitch : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor triedy.
     *
     * @param rodičovský objekt
     * @param názov topicu, ktorý bude karta zobrazovať
     * @param ukazatel na Dashboard komponentu
     * @param ukazatel na Mqtt klienta
     *
     *
     */
    explicit DashboardCardSwitch(QWidget *parent = nullptr,
                                 QString name = "",
                                 Dashboard *dashboard = nullptr,
                                 QMqttClient *client = nullptr);
    ~DashboardCardSwitch();
private slots:
    /**
     * @brief Slot pre zachytenie MQTT správy.
     * @param názov správy
     * @param dáta
     */
     void onMessageReceivedUpdateData(QString topic, QByteArray message) ;
     /**
      * @brief Slot zachytávajúci udalosti zapnutia spínača
      */
     void onTurnOnClicked() ;
     /**
      * @brief Slot zachytávajúci udalosti vypnutia spínača
      */
     void onTurnOffClicked() ;
     /**
      * @brief Slot pre zachytenie akcie vymazania karty.
      */
     void onRemoveClicked() ;
signals:
     /**
      * @brief Signal pre vymazanie karty, ktorý sa zachýtáva v Dashboard komponente.
      */
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
