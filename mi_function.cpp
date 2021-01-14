#include "mi_function.h"

#include <qbluetoothaddress.h>
#include <qbluetoothservicediscoveryagent.h>
#include <qbluetoothserviceinfo.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothuuid.h>


mi_function::mi_function(const QString &name,
                         const QBluetoothAddress &address, QWidget *parent)
:   QDialog(parent), ui(new Ui_ServiceDiscovery)
{

}
