#include "service.h"
#include "ui_service.h"

#include <qbluetoothaddress.h>
#include <qbluetoothservicediscoveryagent.h>
#include <qbluetoothserviceinfo.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothuuid.h>
#include <QApplication>

service::service(const QString &name,
                 const QBluetoothAddress &address, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::service)
{
    ui->setupUi(this);
    QBluetoothLocalDevice localDevice;
    QBluetoothAddress adapterAddress = localDevice.address();


    discoveryAgent = new QBluetoothServiceDiscoveryAgent(adapterAddress);

    discoveryAgent->setRemoteAddress(address);

    setWindowTitle(name);

    connect(discoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(addService(QBluetoothServiceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), ui->status, SLOT(hide()));


    discoveryAgent->start();
}

service::~service()
{
    delete discoveryAgent;
    delete ui;
}

void service::addService(const QBluetoothServiceInfo &info)
{
    if (info.serviceName().isEmpty())
        return;

    QString line = info.serviceName();
    if (!info.serviceDescription().isEmpty())
        line.append("\n\t" + info.serviceDescription());
    if (!info.serviceProvider().isEmpty())
        line.append("\n\t" + info.serviceProvider());

    ui->list->addItem(line);

}
