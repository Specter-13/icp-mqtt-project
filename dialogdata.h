/**
* @file dialogdata.h
*
* @brief Třída pro dialog na zobrazení dat zprávy.
* @author Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo01)
*/
#ifndef DIALOGDATA_H
#define DIALOGDATA_H

#include <QDialog>

namespace Ui {
class DialogData;
}

/**
* @class DialogData
*
* @brief Třída pro dialog na zobrazení dat zprávy.
*/
class DialogData : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor třídy.
     *
     * @param data binární podoba dat
     * @param parent rodičovský objekt
     *
     *
     */
    explicit DialogData(QByteArray data, QWidget *parent = nullptr);
    ~DialogData();

private:
    Ui::DialogData *ui;
    QByteArray data;
};

#endif // DIALOGDATA_H
