#include <QDebug>
#include "controller.h"
#include "scene.h"
#include "navigationwidget.h"
#include "slidingstackedwidget.h"

Controller::Controller(QNavigation::NavigationWidget *w, QObject *parent) :
    QObject(parent), _mainWidget(w), _counter(0)
{
    navigateToNext();
}

void Controller::navigateToNext()
{
    Scene *scene = addScene();
    _mainWidget->push(scene);
    scene->setPrevButtonEnabled(_mainWidget->level() != 0);
}

void Controller::navigateToPrev()
{
    _mainWidget->pop();
}

Scene *Controller::addScene()
{
    Scene *s = new Scene(QString("%1").arg(_counter));
    s->setWindowTitle(QString("Scene %1").arg(_counter));

    connect(s, SIGNAL(prevClicked()), this, SLOT(navigateToPrev()));
    connect(s, SIGNAL(nextClicked()), this, SLOT(navigateToNext()));

    _counter++;
    return s;
}
