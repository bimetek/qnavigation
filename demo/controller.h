#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

namespace QNavigation
{
class SlidingStackedWidget;
}

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QNavigation::SlidingStackedWidget *w,
                        QObject *parent = 0);

private slots:
    void navigateToNext();
    void navigateToPrev();
    void navigationDidEnd();

private:
    QNavigation::SlidingStackedWidget *_mainWidget;
};

#endif // CONTROLLER_H
