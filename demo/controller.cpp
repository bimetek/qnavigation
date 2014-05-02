#include <QDebug>
#include "controller.h"
#include "scene.h"
#include "slidingstackedwidget.h"

Controller::Controller(QNavigation::SlidingStackedWidget *w, QObject *parent) :
    QObject(parent), _mainWidget(w)
{
    for (int i = 0; i < 3; i++)
    {
        Scene *s = new Scene(QString("%1").arg(i));
        _mainWidget->addWidget(s);
        connect(s, SIGNAL(prevClicked()), this, SLOT(navigateToPrev()));
        connect(s, SIGNAL(nextClicked()), this, SLOT(navigateToNext()));
    }
    connect(w, SIGNAL(animationEnded()), this, SLOT(navigationDidEnd()));
}

void Controller::navigateToNext()
{
    int i = (_mainWidget->currentIndex() + 1) % (_mainWidget->count());
    _mainWidget->navigate(i);
}

void Controller::navigateToPrev()
{
    int i = _mainWidget->currentIndex() - 1;
    if (i < 0)
        i += _mainWidget->count();
    _mainWidget->navigate(i);
}

void Controller::navigationDidEnd()
{
    qDebug() << "Switched to" << _mainWidget->currentIndex();
}
