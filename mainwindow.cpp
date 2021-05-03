#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogconnect.h"
#include <QDebug>
#include <QtMqtt/QtMqtt>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(onDialogConnect()));



}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onDialogConnect()
{

    DialogConnect *connectW = new DialogConnect;
    connect(connectW, SIGNAL(Connecting(QString, int, int, QString)), this, SLOT(onConnect(QString, int, int, QString)));
    connectW->show();
}

void MainWindow::onConnect(QString addr, int port, int max, QString topics)
{
    client->setHostname(addr);
    client->setPort(port);
    client->connectToHost();
    connect(client, SIGNAL(connected()), this, SLOT(onSubscribe()));

    this->max = max;
    this->topics = topics;


}

void MainWindow::onSubscribe()
{
    subscription = client->subscribe(topics, 0);
    if (!subscription) {
            QMessageBox::critical(this, QString("Error"), QString("Could not subscribe."));
            return;
        }
}


