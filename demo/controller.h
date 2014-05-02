#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

namespace QNavigation
{
class NavigationWidget;
}

class Scene;

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QNavigation::NavigationWidget *w,
                        QObject *parent = 0);

private slots:
    void navigateToNext();
    void navigateToPrev();

private:
    Scene *addScene();

    QNavigation::NavigationWidget *_mainWidget;
    int _counter;
};

#endif // CONTROLLER_H
