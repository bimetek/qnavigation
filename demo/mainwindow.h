#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QToolBar;

namespace QNavigation
{
class NavigationWidget;
}

class Scene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QNavigation::NavigationWidget *w);

private slots:
    void navigateToNext();
    void navigateToPrev();
    void toggleNavBar();

private:
    Scene *addScene();

    QToolBar *_toolBar;
    QNavigation::NavigationWidget *_mainWidget;
    int _counter;
};

#endif // MAINWINDOW_H
