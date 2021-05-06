#ifndef DIALOGSEND_H
#define DIALOGSEND_H

#include <QDialog>
#include <QtMqtt/QtMqtt>

namespace Ui {
class DialogSend;
}

class DialogSend : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSend(QString topic, QMqttClient *client, QWidget *parent = nullptr);
    ~DialogSend();

private:
    Ui::DialogSend *ui;
    QString topic;
    QMqttClient *client;
    bool file = false;

private slots:
    void onLoad();
    void onSend();
};

#endif // DIALOGSEND_H
