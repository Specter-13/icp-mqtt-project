/**
* @file dialogadditem.h
*
* @brief Trieda pre pridanie nového itemu do Dashboardu
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#ifndef DIALOGADDITEM_H
#define DIALOGADDITEM_H

#include <QDialog>
#include <QVBoxLayout>
#include <dashboard.h>
#include <QtMqtt/QtMqtt>

namespace Ui {
class DialogAddItem;
}
/**
* @class DialogAddItem
*
* @brief DialogAddItem trieda
*/
class DialogAddItem : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor triedy.
     *
     * @param rodičovský objekt
     * @param layout objektu, do ktorého sa pridávajú karty
     * @param ukazatel na Dashboard komponentu
     * @param ukazatel na Mqtt klienta
     *
     *
     */
    explicit DialogAddItem(QWidget *parent = nullptr,
                           QVBoxLayout *layout = nullptr,
                           Dashboard *dashboard = nullptr,
                           QMqttClient *client = nullptr);
    ~DialogAddItem();


private:
    Ui::DialogAddItem *ui;
signals:
    /**
     * @brief Signál vysielajúci udalosť pridania itemu do Dashboardu
     */
    void AddedItemSignal();
private slots:
    /**
     * @brief Slot zachytávajúci udalosť potrvednia vytvorenia novej karty, obsahuj́uci samotnú logiku pridania karty do Dashboardu.
     */
    void onOkButton();

private:
    QVBoxLayout *Layout;
private:
    QMqttClient *Client;
private:
    Dashboard *DashboardInstance;
};

#endif // DIALOGADDITEM_H
