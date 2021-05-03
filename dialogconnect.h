#ifndef DIALOGCONNECT_H
#define DIALOGCONNECT_H

#include <QDialog>

namespace Ui {
class DialogConnect;
}

class DialogConnect : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnect(QWidget *parent = nullptr);
    ~DialogConnect();

signals:
    void Connecting(QString address, int port, int max, QString topics);

private slots:
    void onOkButton();

private:
    Ui::DialogConnect *ui;
};

#endif // DIALOGCONNECT_H
