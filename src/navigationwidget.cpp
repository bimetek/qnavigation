#include "navigationwidget.h"
#include <QFont>
#include <QObjectCleanupHandler>
#include <QStack>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include "slidingstackedwidget.h"

namespace QNavigation
{

const int NavigationBarHeight = 40;

class NavigationWidgetPrivate
{
    Q_DECLARE_PUBLIC(NavigationWidget)
    NavigationWidget * const q_ptr;

public:
    NavigationWidgetPrivate(NavigationWidget *q);
    ~NavigationWidgetPrivate();

    void cleanup();

    QObjectCleanupHandler *cleaner;
    SlidingStackedWidget *stackedWidget;
    QLabel *titleLabel;
    QPushButton *backButton;
    QStack<int> popStack;
};

NavigationWidgetPrivate::NavigationWidgetPrivate(NavigationWidget *q) :
    q_ptr(q), cleaner(new QObjectCleanupHandler()),
    stackedWidget(new SlidingStackedWidget(q)), titleLabel(new QLabel()),
    backButton(new QPushButton(titleLabel))
{
}

NavigationWidgetPrivate::~NavigationWidgetPrivate()
{
    cleaner->deleteLater();
}

void NavigationWidgetPrivate::cleanup()
{
    cleaner->clear();
    backButton->setVisible(!popStack.isEmpty());
}


NavigationWidget::NavigationWidget(QWidget *parent) :
    QWidget(parent), d_ptr(new NavigationWidgetPrivate(this))
{
    Q_D(NavigationWidget);
    connect(d->stackedWidget, SIGNAL(animationEnded()), this, SLOT(cleanup()));

    d->titleLabel->setFont(QFont(d->titleLabel->font().family(),
                                 16, QFont::Bold));
    d->titleLabel->setFixedHeight(NavigationBarHeight);
    d->titleLabel->setAlignment(Qt::AlignCenter);

    d->backButton->setText(tr("< Back"));
    d->backButton->setFixedHeight(NavigationBarHeight);
    d->backButton->setStyleSheet("QPushButton { border: none; outline: none; }"
                                 "QPushButton:hover { color: gray; }");
    d->backButton->hide();

    connect(d->backButton, SIGNAL(clicked()), this, SLOT(pop()));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->addWidget(d->titleLabel, 0);
    mainLayout->addWidget(d->stackedWidget, 1);
    setLayout(mainLayout);
}

NavigationWidget::~NavigationWidget()
{
    delete d_ptr;
}

bool NavigationWidget::level() const
{
    return d_ptr->popStack.count();
}

QLabel *NavigationWidget::titleLabel() const
{
    return d_ptr->titleLabel;
}

QPushButton *NavigationWidget::backButton() const
{
    return d_ptr->backButton;
}

SlidingStackedWidget *NavigationWidget::stackedWidget() const
{
    return d_ptr->stackedWidget;
}

bool NavigationWidget::navigationBarHidden() const
{
    return !(d_ptr->titleLabel->isVisible());
}

void NavigationWidget::setNavigationBarHidden(bool hidden)
{
    d_ptr->titleLabel->setVisible(!hidden);
}

void NavigationWidget::push(QWidget *item)
{
    Q_D(NavigationWidget);

    if (d->stackedWidget->currentIndex() >= 0)
        d->popStack.push(d->stackedWidget->currentIndex());

    int next = d->stackedWidget->addWidget(item);
    d->stackedWidget->navigate(next, SlidingStackedWidget::RightToLeft);
    d->titleLabel->setText(item->windowTitle());
}

void NavigationWidget::pop()
{
    Q_D(NavigationWidget);
    if (d->popStack.isEmpty())
        return;

    d->cleaner->add(d->stackedWidget->currentWidget());
    d->stackedWidget->navigate(d->popStack.pop(),
                               SlidingStackedWidget::LeftToRight);
}

void NavigationWidget::popToTop()
{
    Q_D(NavigationWidget);
    if (d->popStack.isEmpty())
        return;

    int target = d->stackedWidget->currentIndex();
    do {
        d->cleaner->add(d->stackedWidget->widget(target));
        target = d->popStack.pop();
    } while (!d->popStack.isEmpty());
    d->stackedWidget->navigate(target, SlidingStackedWidget::LeftToRight);
}

}   // namespace QNavigation


// Hack to include symbols so that Q_PRIVATE_SLOT works.
// http://qt-project.org/wiki/Binary_Compatibility_Workarounds
#include "moc_navigationwidget.cpp"
