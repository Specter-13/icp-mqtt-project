/**
* @file dialogsend.h
*
* @brief Třída pro dialog na odeslání zprávy.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#ifndef DIALOGSEND_H
#define DIALOGSEND_H
#include <QDialog>
#include <QtMqtt/QtMqtt>
#include <QTreeWidgetItem>

namespace Ui {
class DialogSend;
}


/**
* @class DialogSend
*
* @brief Třída pro dialog na odeslání zprávy.
*/
class DialogSend : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor třídy.
     *
     * @param topic téma zprávy
     * @param client ukazatel na klienta
     * @param parent rodičovský objekt
     *
     *
     */
    explicit DialogSend( QString topic, QMqttClient *client, QWidget *parent = nullptr);
    ~DialogSend();

private:
    Ui::DialogSend *ui;
    QString topic;
    QMqttClient *client;
    bool file = false;

private slots:
    /**
     * @brief Slot pro načtení souboru.
     */
    void onLoad();
    /**
     * @brief Slot pro odeslání zprávy.
     */
    void onSend();
};

#endif // DIALOGSEND_H
