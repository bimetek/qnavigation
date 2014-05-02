#ifndef QNAVIGATION_SLIDINGSTACKEDWIDGET_H
#define QNAVIGATION_SLIDINGSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QEasingCurve>
#include "qnavigation_global.h"

namespace QNavigation
{

class SlidingStackedWidgetPrivate;

class QNAVIGATION_SHARED_EXPORT SlidingStackedWidget : public QStackedWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(SlidingStackedWidget)
    SlidingStackedWidgetPrivate * const d_ptr;

    Q_PRIVATE_SLOT(d_func(), void animationDidFinish())

public:

    enum Direction
    {
        Automatic = -1,
        LeftToRight = 0,
        RightToLeft
    };

    explicit SlidingStackedWidget(QWidget *parent = 0);
    virtual ~SlidingStackedWidget();

    int duration() const;
    QEasingCurve::Type easingType() const;

public slots:
    void setDuration(int duration);
    void setEasingType(QEasingCurve::Type type);

    void navigate(int to, Direction direction = Automatic, int duration = -1);
    void navigate(QWidget *to, Direction direction = Automatic,
                  int duration = -1);

signals:
    void animationStarting();
    void animationEnded();
};

}   // namespace QNavigation

#endif // QNAVIGATION_SLIDINGSTACKEDWIDGET_H
