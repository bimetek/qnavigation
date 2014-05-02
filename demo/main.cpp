#include <QApplication>
#include "slidingstackedwidget.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QNavigation::SlidingStackedWidget w;

    Controller c(&w);
    Q_UNUSED(c);

    w.show();
    return a.exec();
}
