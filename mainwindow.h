/**
* @file mainwindow.h
*
* @brief Třída pro hlavní okno aplikace.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMqtt/QtMqtt>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/**
* @class MainWindow
*
* @brief Třída pro hlavní okno aplikace.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor třídy.
     *
     * @param parent rodičovský objekt
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMqttClient *client = new QMqttClient(this);
    QList<QMqttSubscription*> subscriptions;
    int max;
    QString topics;
    QMap<QString, QByteArray> messages;

private slots:
    /**
     * @brief Slot pro vytvoření dialogu připojení k brokerovi.
     */
    void onDialogConnect();
    /**
     * @brief Slot pro vytvoření simulátoru.
     */
    void onSimulatorConnect();
    /**
     * @brief Slot pro vytvoření dashboardu.
     */
    void onDashboardSelected();
    /**
     * @brief Slot pro připojení k brokerovi.
     *
     * @param addr adresa serveru
     * @param port číslo portu
     * @param max maximální počet zpráv v historii
     * @param topics témata k odběru
     */
    void onConnect(QString addr, int port, int max, QString topics);
    /**
     * @brief Slot pro vytvoření odběru.
     */
    void onSubscribe();
    /**
     * @brief Slot pro přijetí zprávy.
     *
     * @param message data zprávy
     * @param topic téma zprávy
     */
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    /**
     * @brief Slot pro vytvoření kontetového menu nad položkou stromu.
     *
     * @param pos pozice kurzoru
     */
    void on_tree_customContextMenuRequested(const QPoint &pos);
    /**
     * @brief Slot pro zobrazení dat zprávy.
     */
    void on_actionShow_Data_triggered();
    /**
     * @brief Slot pro odeslání zprávy.
     */
    void on_actionPublish_triggered();
    /**
     * @brief Slot pro přidání nového tématu.
     */
    void on_actionAdd_Topic_triggered();
    /**
     * @brief Slot pro vytvoření snímku aktuálního stavu.
     */
    void onActionSnapshot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
