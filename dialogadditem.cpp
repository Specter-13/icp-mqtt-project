#include "dialogadditem.h"
#include "ui_dialogadditem.h"
#include "dashboardcard.h"
#include "dashboardcardswitch.h"
#include "dashboardcardsetter.h"
DialogAddItem::DialogAddItem(QWidget *parent,
                             QVBoxLayout *layout,
                             Dashboard *dashboard,
                             QMqttClient *client) :
    QDialog(parent),
    ui(new Ui::DialogAddItem)
{
    ui->setupUi(this);
    this->Client = client;
    Layout = layout;
    DashboardInstance = dashboard;
    ui->genericRadioButton->setChecked(true);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onOkButton()));
    connect(this, SIGNAL(AddedItemSignal()), DashboardInstance, SLOT(onAddedItemSignal()));
    this->setWindowTitle("Add new item");


}

DialogAddItem::~DialogAddItem()
{
    delete ui;
}

void DialogAddItem::onOkButton()
{
    if(ui->genericRadioButton->isChecked())
    {

        Layout->addStretch();
        DashboardCard * card = new DashboardCard(nullptr, ui->lineEdit->text(), nullptr, DashboardInstance);
        Layout->insertWidget(0,card);

    }
    else if(ui->switchRadioButton->isChecked())
    {
        Layout->addStretch();
        DashboardCardSwitch * card = new DashboardCardSwitch(nullptr, ui->lineEdit->text(), DashboardInstance, Client);
        Layout->insertWidget(0,card);

    }
    else if(ui->setterRadioButton->isChecked())
    {
        Layout->addStretch();
        DashboardCardSetter* card = new DashboardCardSetter(nullptr, ui->lineEdit->text(), DashboardInstance, Client);
        Layout->insertWidget(0,card);

    }
    emit AddedItemSignal();

}
