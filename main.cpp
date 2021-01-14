#include "mainwindow.h"
#include <QDialog>



#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QObject::connect(&w, SIGNAL(accpetd()), &a, SLOT(quit()));
    w.show();

    return a.exec();
}

