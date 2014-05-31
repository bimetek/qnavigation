#include <QSpinBox>
#include <QToolBar>
#include "mainwindow.h"
#include "scene.h"
#include "navigationwidget.h"
#include "slidingstackedwidget.h"

MainWindow::MainWindow(QNavigation::NavigationWidget *w) :
    QMainWindow(), _toolBar(new QToolBar()), _mainWidget(w), _counter(0)
{
    setCentralWidget(w);
    navigateToNext();

    QSpinBox *durationInput = new QSpinBox();
    durationInput->setRange(100, 1000);
    durationInput->setSingleStep(100);
    durationInput->setValue(_mainWidget->stackedWidget()->duration());
    connect(durationInput, SIGNAL(valueChanged(int)),
            _mainWidget->stackedWidget(), SLOT(setDuration(int)));

    _toolBar->addAction("Toggle Navbar", this, SLOT(toggleNavBar()));
    _toolBar->addWidget(durationInput);
    addToolBar(_toolBar);
}

void MainWindow::navigateToNext()
{
    Scene *scene = addScene();
    _mainWidget->push(scene);
    scene->setPrevButtonEnabled(_mainWidget->level() != 0);
}

void MainWindow::navigateToPrev()
{
    _mainWidget->pop();
}

void MainWindow::toggleNavBar()
{
    _mainWidget->setNavigationBarHidden(!_mainWidget->navigationBarHidden());
}

Scene *MainWindow::addScene()
{
    Scene *s = new Scene(QString("%1").arg(_counter));
    s->setWindowTitle(QString("Scene %1").arg(_counter));

    connect(s, SIGNAL(prevClicked()), this, SLOT(navigateToPrev()));
    connect(s, SIGNAL(nextClicked()), this, SLOT(navigateToNext()));

    _counter++;
    return s;
}
