#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("FDM");
    a.setOrganizationName("VNICTT");

    MainWindow w;
    w.show();

    return a.exec();
}
