#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogconnect.h"
#include "simulator.h"
#include "dialogdata.h"
#include "dialogsend.h"
#include "dialogaddtopic.h"
#include "dashboard.h"
#include <QDebug>
#include <QtMqtt/QtMqtt>
#include <QMessageBox>
#include <QPixmap>
#include <Qt>
#include <QMetaType>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(onDialogConnect()));
    connect(ui->actionSimulator, SIGNAL(triggered()), this, SLOT(onSimulatorConnect()));
    connect(ui->actionSnapshot, SIGNAL(triggered()), this, SLOT(onActionSnapshot()));
    connect(ui->actionOpen_dashboard, SIGNAL(triggered()), this, SLOT(onDashboardSelected()));

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

void MainWindow::onDashboardSelected()
{

    Dashboard *dashboardInstance = new Dashboard;
    connect(client, SIGNAL(messageReceived(const QByteArray &, const QMqttTopicName &)), dashboardInstance, SLOT(onMessageReceived(const QByteArray &, const QMqttTopicName &)));
    dashboardInstance->show();
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



    //smazu prvni pismeno, pokud je to lomitko
    if(topic_full[0] == "/") {
        topic_full.remove(0, 1);
    }

    messages.insert(topic_full, message);

    QString::const_iterator i = topic_full.begin();

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

        QPixmap pixmap;
        if(pixmap.loadFromData(message)) {
            temp->setText(1, "Image");
            temp->setTextColor(1, QColor(0, 0, 255));
        } else {
            temp->setText(1, message);
        }

        temp->setData(1, Qt::UserRole, message);




    } else {
        child->setText(0, topic_current);

        QPixmap pixmap;
        if(pixmap.loadFromData(message)) {
            child->setText(1, "Image");
            child->setTextColor(1, QColor(0, 0, 255));
        } else {
            child->setText(1, message);
        }

        child->setData(1, Qt::UserRole, message);
    }




}




void MainWindow::on_tree_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(this);
    menu.addAction(ui->actionShow_Data);
    menu.addAction(ui->actionPublish);
    menu.addAction(ui->actionAdd_Topic);

    ui->actionShow_Data->setData(QVariant(pos));


    menu.exec( ui->tree->mapToGlobal(pos) );
}



void MainWindow::on_actionShow_Data_triggered()
{
    QTreeWidgetItem *clickedItem = ui->tree->itemAt(ui->actionShow_Data->data().toPoint());

    DialogData *window = new DialogData(clickedItem->data(1, Qt::UserRole).value<QByteArray>());
    window->show();

}


void MainWindow::on_actionPublish_triggered()
{
    QTreeWidgetItem *clickedItem = ui->tree->itemAt(ui->actionShow_Data->data().toPoint());

    QString topic = clickedItem->text(0);
    clickedItem = clickedItem->parent();

    while(clickedItem) {
        topic.prepend("/");
        topic.prepend(clickedItem->text(0));
        clickedItem = clickedItem->parent();
    }



    DialogSend *window = new DialogSend(topic, client);
    window->show();

}


void MainWindow::on_actionAdd_Topic_triggered()
{
    QTreeWidgetItem *clickedItem = ui->tree->itemAt(ui->actionShow_Data->data().toPoint());

    QTreeWidgetItem *tempItem = clickedItem;
    QString topic = tempItem->text(0);
    tempItem = tempItem->parent();

    while(tempItem) {
        topic.prepend("/");
        topic.prepend(tempItem->text(0));
        tempItem = tempItem->parent();
    }


    DialogAddTopic *window = new DialogAddTopic(topic, &(this->subscriptions), this->client, clickedItem);
    window->show();


}

void MainWindow::onActionSnapshot()
{
    QString basedir = "";
    basedir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(basedir == "") {
        return;
    }

    QString fullpath;
    QDir dir;

    QMap<QString, QByteArray>::iterator i;

    for(i = messages.begin(); i != messages.end(); i++) {
        fullpath = basedir;
        fullpath.append("/");
        fullpath.append(i.key());

        dir.mkpath(fullpath);

        QPixmap pixmap;
        if(pixmap.loadFromData(i.value())) {

            fullpath.append("/payload.jpg");
            QFile file(fullpath);
            file.open(QIODevice::WriteOnly);
            file.write(i.value());

        } else {
            fullpath.append("/payload.txt");
            QFile file(fullpath);
            file.open(QIODevice::WriteOnly);
            file.write(i.value());
        }

    }

}












