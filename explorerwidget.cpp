#include "explorerwidget.h"
#include "ui_explorerwidget.h"

ExplorerWidget::ExplorerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExplorerWidget)
{
    ui->setupUi(this);
}

ExplorerWidget::~ExplorerWidget()
{
    delete ui;
}
