#include <QApplication>
#include "navigationwidget.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QNavigation::NavigationWidget w;

    Controller c(&w);
    Q_UNUSED(c);

    w.show();
    return a.exec();
}
