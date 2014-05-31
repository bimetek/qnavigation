#include "slidingstackedwidget.h"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

namespace QNavigation
{

static const char *SlidingStackedWidgetCurrOriginrKey =
        "SlidingStackedWidget_currOrigin";
static const char *SlidingStackedWidgetCurrIndexKey =
        "SlidingStackedWidget_currIndex";
static const char *SlidingStackedWidgetNextIndexKey =
        "SlidingStackedWidget_nextIndex";

class SlidingStackedWidgetPrivate
{
    Q_DECLARE_PUBLIC(SlidingStackedWidget)
    SlidingStackedWidget * const q_ptr;

public:
    SlidingStackedWidgetPrivate(SlidingStackedWidget *q) :
        q_ptr(q), active(false), duration(500),
        easingType(QEasingCurve::InOutQuad) {}

    void animationDidFinish();

    bool active;
    int duration;
    QEasingCurve::Type easingType;
};

void SlidingStackedWidgetPrivate::animationDidFinish()
{
    Q_Q(SlidingStackedWidget);

    QObject *ani = q->sender();
    bool ok = false;

    // Extract context.
    int next = ani->property(SlidingStackedWidgetNextIndexKey).toInt(&ok);
    Q_ASSERT(ok);
    int curr = ani->property(SlidingStackedWidgetCurrIndexKey).toInt(&ok);
    Q_ASSERT(ok);
    QPoint origin = ani->property(SlidingStackedWidgetCurrOriginrKey).toPoint();

    // Update states.
    q->setCurrentIndex(next);
    QWidget *currw = q->widget(curr);
    currw->hide();
    currw->move(origin);

    // Cleanup.
    active = false;
    q->setEnabled(true);

    emit q->animationEnded();
}


SlidingStackedWidget::SlidingStackedWidget(QWidget *parent) :
    QStackedWidget(parent), d_ptr(new SlidingStackedWidgetPrivate(this))
{
}

SlidingStackedWidget::~SlidingStackedWidget()
{
    delete d_ptr;
}

int SlidingStackedWidget::duration() const
{
    return d_ptr->duration;
}

void SlidingStackedWidget::setDuration(int duration)
{
    d_ptr->duration = duration;
}

QEasingCurve::Type SlidingStackedWidget::easingType() const
{
    return d_ptr->easingType;
}

void SlidingStackedWidget::setEasingType(QEasingCurve::Type type)
{
    d_ptr->easingType = type;
}

void SlidingStackedWidget::navigate(
        int to, SlidingStackedWidget::Direction direction, int duration)
{
    Q_D(SlidingStackedWidget);

    Q_ASSERT(to >= 0 && to < count());

    if (d->active)
        return;

    int from = currentIndex();
    if (to == from)
        return;

    int offsetx = width();
    int offsety = height();
    QWidget *currw = currentWidget();
    QWidget *nextw = widget(to);

    // Resize the next widget.
    nextw->setGeometry(0, 0, offsetx, offsety);

    // Calculate values for animation.
    if (duration < 0)
        duration = d->duration;
    if (direction == Automatic)
        direction = (to > from) ? RightToLeft : LeftToRight;
    switch (direction)
    {
    case RightToLeft:
        offsetx = 0 - offsetx;
        offsety = 0;
        break;
    case LeftToRight:
        offsety = 0;
        break;
    default:
        qWarning("SlidingStackedWidget::navigate() - Animation direction %d "
                 "not handled.", direction);
        break;
    }

    QPoint pnext = nextw->pos();
    QPoint pcurr = currw->pos();

    // Prepare to the next widget.
    nextw->move(pnext.x() - offsetx, pnext.y() - offsety);
    nextw->show();
    nextw->raise();

    QPropertyAnimation *animcurr = new QPropertyAnimation(currw, "pos");
    animcurr->setDuration(duration);
    animcurr->setEasingCurve(d->easingType);
    animcurr->setStartValue(QPoint(pcurr.x(), pcurr.y()));
    animcurr->setEndValue(QPoint(offsetx + pcurr.x(), offsety + pcurr.y()));

    QPropertyAnimation *animnext = new QPropertyAnimation(nextw, "pos");
    animnext->setDuration(duration);
    animnext->setEasingCurve(d->easingType);
    animnext->setStartValue(QPoint(0 - offsetx+pnext.x(), offsety+pnext.y()));
    animnext->setEndValue(QPoint(pnext.x(), pnext.y()));

    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup();
    animgroup->addAnimation(animcurr);
    animgroup->addAnimation(animnext);

    animgroup->setProperty(SlidingStackedWidgetCurrOriginrKey, pcurr);
    animgroup->setProperty(SlidingStackedWidgetCurrIndexKey, from);
    animgroup->setProperty(SlidingStackedWidgetNextIndexKey, to);
    connect(animgroup, SIGNAL(finished()), this, SLOT(animationDidFinish()),
            Qt::QueuedConnection);
    setEnabled(false);

    emit animationStarting();
    animgroup->start();
    // The rest is at SlidingStackedWidgetPrivate::animationDidFinish()
}

void SlidingStackedWidget::navigate(
        QWidget *to, SlidingStackedWidget::Direction direction, int duration)
{
    int index = indexOf(to);
    navigate(index, direction, duration);
}

}   // namespace QNavigation


// Hack to include symbols so that Q_PRIVATE_SLOT works.
// http://qt-project.org/wiki/Binary_Compatibility_Workarounds
#include "moc_slidingstackedwidget.cpp"
