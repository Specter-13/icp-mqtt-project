#ifndef DIALOGDATA_H
#define DIALOGDATA_H

#include <QDialog>

namespace Ui {
class DialogData;
}

class DialogData : public QDialog
{
    Q_OBJECT

public:
    explicit DialogData(QByteArray data, QWidget *parent = nullptr);
    ~DialogData();

private:
    Ui::DialogData *ui;
    QByteArray data;
};

#endif // DIALOGDATA_H
