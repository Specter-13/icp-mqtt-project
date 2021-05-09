/**
* @file dashboard.h
*
* @brief Trieda obsahujúca dashboard komponentu.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <QtMqtt/QtMqtt>
namespace Ui {
class Dashboard;
}
/**
* @class Dashboard
*
* @brief Dasboard komponenta
*/
class Dashboard : public QDialog
{
    Q_OBJECT

public:
/**
 * @brief Konstruktor triedy.
 *
 * @param rodičovský objekt
 * @param client ukazatel na klienta
 *
 *
 */
    explicit Dashboard(QWidget *parent = nullptr, QMqttClient *client = nullptr);
    ~Dashboard();

signals:
/**
 * @brief Signál prijatia správy, ktorý emituje novú správu pre karty dashbordu
 *
 * @param názov správy
 * @param dáta
 *
 *
 */
 void topicDataSignal(QString topicName, QByteArray data);

public slots:
 /**
  * @brief Slot pre zachytiene správy od MQTT klienta
  * @param dáta
  * @param názov správy
  */
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
/**
 * @brief slot na zachytenie spravy na vytvorenie nového dialogového okna pre vytvorenie dashboard karty
 */
    void onAddItemClicked();
/**
 * @brief Slot pre vykonanie uloženie konfigurácie dashboardu.
 */
    void onSaveConfig();
/**
 * @brief Slot, ktorý zachytáva signál pridania itemu do dasboardu a pripočítava počet itemov do premmenej
 */
    void onAddedItemSignal();
/**
 * @brief Slot, ktorý zachytáva signál odobranie itemu z dasboardu a odpočitáva pocet itemov z premmenej
 */
    void onRemoveItemSignal();
private:
/**
 * @brief Metóda na načítanie konfigurácie dashboardu zo súboru, prípadne vytvorenia novej konfigúrácie ak neexistuje
 */
    void LoadDashboardConfig();
private:
/**
 * @brief metóda na získanie typu kartičky z názvu triedy korešpondujúcej karty
 * @param názov triedy karty
 */
    QString getCardType(QString cardName );
private:
    QMqttClient *Client;
private:
    Ui::Dashboard *ui;
private:
    int DashboardItemsCount;
};

#endif // DASHBOARD_H
