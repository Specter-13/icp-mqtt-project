#include "dialogadditem.h"
#include "ui_dialogadditem.h"
#include "dashboardcard.h"
DialogAddItem::DialogAddItem(QWidget *parent,
                             QVBoxLayout *layout,
                             Dashboard *dashboard) :
    QDialog(parent),
    ui(new Ui::DialogAddItem)
{
    ui->setupUi(this);

    Layout = layout;
    DashboardInstance = dashboard;

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onOkButton()));


}

DialogAddItem::~DialogAddItem()
{
    delete ui;
}

void DialogAddItem::onOkButton()
{
    Layout->addStretch();
    DashboardCard * card = new DashboardCard(nullptr, ui->lineEdit->text(), nullptr, DashboardInstance);
    Layout->insertWidget(0,card);

}
