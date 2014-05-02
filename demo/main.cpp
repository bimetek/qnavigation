#include <QApplication>
#include "navigationwidget.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw(new QNavigation::NavigationWidget());
    mw.show();
    return a.exec();
}
