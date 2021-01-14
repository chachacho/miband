#ifndef SERVICE_H
#define SERVICE_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QDialog>



QT_FORWARD_DECLARE_CLASS(QBluetoothAddress)
QT_FORWARD_DECLARE_CLASS(QBluetoothServiceInfo)
QT_FORWARD_DECLARE_CLASS(QBluetoothServiceDiscoveryAgent)

QT_USE_NAMESPACE

namespace Ui {
class service;
}

class service : public QMainWindow
{
    Q_OBJECT

public:
    service(const QString &name, const QBluetoothAddress &address, QWidget *parent = 0);
    ~service();

    //     service(QWidget *parent = nullptr);  original
//    ~service();

public slots:
    void addService(const QBluetoothServiceInfo&);


private:
    QBluetoothServiceDiscoveryAgent *discoveryAgent;
    //Ui_MainWindow *ui;

    //Ui_ServiceDiscovery *ui;
     Ui::service *ui; // original
};

#endif // SERVICE_H
