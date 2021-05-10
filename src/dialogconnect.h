/**
* @file dialogconnect.h
*
* @brief Třída pro dialog na připojení k brokerovi.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#ifndef DIALOGCONNECT_H
#define DIALOGCONNECT_H

#include <QDialog>

namespace Ui {
class DialogConnect;
}


/**
* @class DialogConnect
*
* @brief Třída pro dialog na připojení k brokerovi.
*/
class DialogConnect : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor třídy.
     *
     * @param parent rodičovský objekt
     *
     *
     */
    explicit DialogConnect(QWidget *parent = nullptr);
    ~DialogConnect();

signals:
    /**
     * @brief Signál pro připojení k brokerovi.
     *
     * @param address adresa serveru
     * @param port číslo portu
     * @param max maximální počet zpráv v historii
     * @param topics témata k odběru
     *
     *
     */
    void Connecting(QString address, int port, int max, QString topics);

private slots:
    /**
     * @brief Slot pro odeslání připojení.
     */
    void onOkButton();

private:
    Ui::DialogConnect *ui;
};

#endif // DIALOGCONNECT_H
