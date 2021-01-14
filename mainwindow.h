#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include "service.h"
#include <QDialog>

#include <qbluetoothlocaldevice.h>


QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

//QT_BEGIN_NAMESPACE


//namespace Ui { class MainWindow; }

//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void displayPairingMenu(const QPoint &pos);
     void pairingDone(const QBluetoothAddress&, QBluetoothLocalDevice::Pairing);



private slots:

    void start_scan();
    void finished_scan();
    void itemActivated(QListWidgetItem *item);


private:
    Ui::MainWindow *ui;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;




};
#endif // MAINWINDOW_H
