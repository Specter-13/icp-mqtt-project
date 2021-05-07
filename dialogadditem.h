#ifndef DIALOGADDITEM_H
#define DIALOGADDITEM_H

#include <QDialog>
#include <QVBoxLayout>
#include <dashboard.h>
#include <QtMqtt/QtMqtt>

namespace Ui {
class DialogAddItem;
}

class DialogAddItem : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddItem(QWidget *parent = nullptr,
                           QVBoxLayout *layout = nullptr,
                           Dashboard *dashboard = nullptr,
                           QMqttClient *client = nullptr);
    ~DialogAddItem();


private:
    Ui::DialogAddItem *ui;

private slots:
    void onOkButton();

private:
    QVBoxLayout *Layout;
private:
    QMqttClient *Client;
private:
    Dashboard *DashboardInstance;
};

#endif // DIALOGADDITEM_H
