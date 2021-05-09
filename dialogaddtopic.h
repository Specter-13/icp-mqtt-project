/**
* @file dialogaddtopic.h
*
* @brief Třída pro dialog na přidávání tématu do hierarchie stromu.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/

#ifndef DIALOGADDTOPIC_H
#define DIALOGADDTOPIC_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QMqttClient>

namespace Ui {
class DialogAddTopic;
}


/**
* @class DialogAddTopic
*
* @brief Třída pro dialog na přidávání tématu do hierarchie stromu.
*/
class DialogAddTopic : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor třídy.
     *
     * @param topic nové téma k odběru
     * @param subscriptions ukazatel na seznam všech odběrů
     * @param client ukazatel na objekt klienta
     * @param item ukazatel na označený prvek ve stromu
     * @param parent rodičovský objekt
     *
     *
     */
    explicit DialogAddTopic(QString topic, QList<QMqttSubscription*> *subscriptions, QMqttClient *client, QTreeWidgetItem *item, QWidget *parent = nullptr);
    ~DialogAddTopic();

private:
    Ui::DialogAddTopic *ui;
    QTreeWidgetItem *root;
    QMqttClient *client;
    QList<QMqttSubscription*> *subscriptions;
    QString topic;

private slots:
    /**
     * @brief Slot pro přidání tématu.
     */
    void onAdd();
};

#endif // DIALOGADDTOPIC_H
