#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include "qnavigation_global.h"

class QLabel;
class QPushButton;

namespace QNavigation
{

class SlidingStackedWidget;
class NavigationWidgetPrivate;

class NavigationWidget : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(NavigationWidget)
    NavigationWidgetPrivate * const d_ptr;

    Q_PRIVATE_SLOT(d_func(), void cleanup())

public:
    explicit NavigationWidget(QWidget *parent = 0);
    virtual ~NavigationWidget();

    bool level() const;
    QLabel *titleLabel() const;
    QPushButton *backButton() const;
    SlidingStackedWidget *stackedWidget() const;

    bool navigationBarHidden() const;
    void setNavigationBarHidden(bool hidden);

public slots:
    void push(QWidget *item);
    void pop();
    void popToTop();
};

}   // namespace QNavigation

#endif // NAVIGATIONWIDGET_H
