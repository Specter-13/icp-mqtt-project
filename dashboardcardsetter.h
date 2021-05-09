/**
* @file dashboardcardsetter.h
*
* @brief Trieda obsahujúca nastavovaciu dashboard kartu.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#ifndef DASHBOARDCARDSETTER_H
#define DASHBOARDCARDSETTER_H

#include <QWidget>
#include "dashboard.h"
#include <QtMqtt/QtMqtt>

namespace Ui {
class DashboardCardSetter;
}
/**
* @class DashboardCardSetter
*
* @brief DasboardCardSetter trieda
*/
class DashboardCardSetter : public QWidget
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
    explicit DashboardCardSetter(QWidget *parent = nullptr ,
                                 QString topicName = "",
                                 Dashboard *dashboard = nullptr,
                                 QMqttClient *client = nullptr);
    ~DashboardCardSetter();
private slots:
    /**
     * @brief Slot pre zachytenie MQTT správy.
     * @param názov správy
     * @param dáta
     */
     void onMessageReceivedUpdateData(QString topic, QByteArray message) ;
     /**
      * @brief Slot zachytávajúci udalosť odoslania správy na server.
      */
     void onSendClicked() ;
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
    Ui::DashboardCardSetter *ui;
};

#endif // DASHBOARDCARDSETTER_H
