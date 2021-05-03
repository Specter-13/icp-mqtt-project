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

    QMqttClient* client = new QMqttClient(this);
    QMqttSubscription* subscription;
    int max;
    QString topics;

private slots:
    void onDialogConnect();

    void onConnect(QString addr, int port, int max, QString topics);

    void onSubscribe();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
