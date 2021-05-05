#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogconnect.h"
#include "simulator.h"
#include <QDebug>
#include <QtMqtt/QtMqtt>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(onDialogConnect()));
    connect(ui->actionSimulator, SIGNAL(triggered()), this, SLOT(onSimulatorConnect()));



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

void MainWindow::onSimulatorConnect()
{
    Simulator *simulatorW = new Simulator(client);
    simulatorW->show();
}

void MainWindow::onConnect(QString addr, int port, int max, QString topics)
{
    client->setHostname(addr);
    client->setPort(port);
    client->connectToHost();
    connect(client, SIGNAL(connected()), this, SLOT(onSubscribe()));

    this->max = max;
    this->topics = topics;

    connect(client, SIGNAL(messageReceived(const QByteArray &, const QMqttTopicName &)), this, SLOT(onMessageReceived(const QByteArray &, const QMqttTopicName &)));


}

void MainWindow::onSubscribe()
{
    auto subscription = client->subscribe(topics, 0);
    if (!subscription) {
            QMessageBox::critical(this, QString("Error"), QString("Could not subscribe."));
            return;
        }
    subscriptions.append(subscription);
}

void MainWindow::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    QString topic_full = topic.name();
    QString topic_current = "";
    QTreeWidgetItem *root = ui->tree->invisibleRootItem();
    QTreeWidgetItem *child;
    QTreeWidgetItem *temp;


    QString::const_iterator i = topic_full.begin();

    //preskocim prvni pismeno, pokud je to lomitko
    if(*i == '/') {
        i++;
    }

    for (i; i != topic_full.end(); i++) {
        QChar c = *i;
        child = nullptr;

        if(c == '/') {

            //projdu vsechny potomky a zjistim jestli nekterej uz tam neni
            for (int j = 0; j < root->childCount(); j++) {
                if(root->child(j)->text(0) == topic_current) {
                    child = root->child(j);
                    break;
                }
            }

            //pokud nebyl potomek nalezen
            if (child == nullptr) {

                temp = new QTreeWidgetItem(root);
                temp->setText(0, topic_current);
                temp->setText(1, "");

                root = temp;

            } else {
                root = child;
            }

            topic_current = "";

        } else {
            topic_current.append(c);
        }

    }

    //jeste jeden prubeh cyklu, protoze na konci neni lomitko

    //projdu vsechny potomky a zjistim jestli nekterej uz tam neni
    for (int j = 0; j < root->childCount(); j++) {
        if(root->child(j)->text(0) == topic_current) {
            child = root->child(j);
            break;
        }
    }

    //pokud nebyl potomek nalezen
    if (child == nullptr) {

        temp = new QTreeWidgetItem(root);
        temp->setText(0, topic_current);
        temp->setText(1, message);

    } else {
        child->setText(0, topic_current);
        child->setText(1, message);
    }




}


