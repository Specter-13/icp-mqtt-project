#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(onConnect()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnect()
{
    QWidget *connectW = new QWidget;
    connectW->show();
}


