#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>

#include "service.h"
#include <QtBluetooth>
#include <QApplication>


#include <qbluetoothaddress.h>
#include <qbluetoothlocaldevice.h>
#include <QMenu>
#include <QDebug>
#include <qbluetoothserviceinfo.h>
#include <qbluetoothuuid.h>
#include <qobject.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),  ui(new Ui::MainWindow) , localDevice(new QBluetoothLocalDevice)
{
   ui->setupUi(this);
   discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
  connect(ui->micon, SIGNAL(clicked()), this, SLOT(start_scan()));
  connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
          this, SLOT(addDevice(QBluetoothDeviceInfo)));


  connect(discoveryAgent, SIGNAL(finished()), this, SLOT(finished_scan()));  //discover_signal send finished
  connect(ui->list, SIGNAL(itemActivated(QListWidgetItem*)),
          this, SLOT(itemActivated(QListWidgetItem*)));

  ui->list->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->list, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(displayPairingMenu(QPoint)));
  connect(localDevice, SIGNAL(pairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing))
           , this, SLOT(pairingDone(QBluetoothAddress,QBluetoothLocalDevice::Pairing)));
}

MainWindow::~MainWindow()
{
    delete discoveryAgent;

    //delete ui;    original
}


void MainWindow::start_scan()
{
        discoveryAgent->start();
        ui->micon->setEnabled(false);
        qDebug()<<"startscan";
}

void MainWindow::finished_scan()
{
    ui->micon->setEnabled(true);
    qDebug()<<"finished_scan";
}
void MainWindow::addDevice(const QBluetoothDeviceInfo &info)
{
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());
    QList<QListWidgetItem *> items = ui->list->findItems(label, Qt::MatchExactly);
    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            item->setForeground(QColor(Qt::green));
        else
            item->setForeground(QColor(Qt::black));

        ui->list->addItem(item);
    }
    qDebug()<<"test8 " ;
}
void MainWindow::displayPairingMenu(const QPoint &pos)
{
    if (ui->list->count() == 0)
        return;
    QMenu menu(this);
    QAction *pairAction = menu.addAction("Pair");
    QAction *removePairAction = menu.addAction("Remove Pairing");
    QAction *chosenAction = menu.exec(ui->list->viewport()->mapToGlobal(pos));
    QListWidgetItem *currentItem = ui->list->currentItem();

    QString text = currentItem->text();
    int index = text.indexOf(' ');
    if (index == -1)
        return;

    QBluetoothAddress address (text.left(index));
    if (chosenAction == pairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
    } else if (chosenAction == removePairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Unpaired);
    }
    qDebug()<<"test11 " ;
}

void MainWindow::pairingDone(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
    QList<QListWidgetItem *> items = ui->list->findItems(address.toString(), Qt::MatchContains);

    if (pairing == QBluetoothLocalDevice::Paired || pairing == QBluetoothLocalDevice::AuthorizedPaired ) {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setForeground(QColor(Qt::green));
        }
    } else {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setForeground(QColor(Qt::red));
        }
    }
    qDebug()<<"test12 " ;
}


void MainWindow::itemActivated(QListWidgetItem *item)
{
    QString text = item->text();

    int index = text.indexOf(' ');

    if (index == -1)
        return;

    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index + 1));

    service w(name, address);

    //w.exec();
   // qDebug()<<"test4 " ;
}
