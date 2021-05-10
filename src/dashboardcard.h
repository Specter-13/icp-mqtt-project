/**
* @file dashboardcard.h
*
* @brief Trieda obsahujúca generickú dashboard kartu.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#ifndef DASHBOARDCARD_H
#define DASHBOARDCARD_H

#include <QWidget>
#include <QtMqtt/QtMqtt>
#include "dashboard.h"
namespace Ui {
class DashboardCard;
}
/**
* @class DashboardCard
*
* @brief DasboardCard trieda
*/
class DashboardCard : public QWidget
{
    Q_OBJECT

public:
/**
 * @brief Konstruktor triedy.
 *
 * @param rodičovský objekt
 * @param názov topicu, ktorý bude karta zobrazovať
 * @param ukazatel na Dashboard komponentu
 *
 *
 */
    explicit DashboardCard(QWidget *parent = nullptr,
                           QString name = "",
                           Dashboard *dashboard = nullptr);
    ~DashboardCard();
private slots:
    /**
     * @brief Slot pre zachytenie MQTT správy.
     * @param názov správy
     * @param dáta
     */
    void onMessageReceivedUpdateData(QString topic, QByteArray message) ;
    /**
     * @brief Slot pre zachytenie akcie vymazania karty.
     */
    void onRemoveClicked();
signals:
    /**
     * @brief Slot pre vymazanie karty, ktorý sa zachýtáva v Dashboard komponente.
     */
        void RemovedItemSignal();
private:
    Ui::DashboardCard *ui;
private:
    QString TopicName;
private:
    Dashboard *DashboardInstance;
};

#endif // DASHBOARDCARD_H
