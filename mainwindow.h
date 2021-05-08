#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMqtt/QtMqtt>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMqttClient *client = new QMqttClient(this);
    QList<QMqttSubscription*> subscriptions;
    int max;
    QString topics;
    QMap<QString, QByteArray> messages;

private slots:
    void onDialogConnect();
    void onSimulatorConnect();
    void onDashboardSelected();

    void onConnect(QString addr, int port, int max, QString topics);

    void onSubscribe();

    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

    void on_tree_customContextMenuRequested(const QPoint &pos);

    void on_actionShow_Data_triggered();

    void on_actionPublish_triggered();

    void on_actionAdd_Topic_triggered();

    void onActionSnapshot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
