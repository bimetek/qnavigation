#ifndef SCENE_H
#define SCENE_H

#include <QWidget>

namespace Ui {
class Scene;
}

class Scene : public QWidget
{
    Q_OBJECT

public:
    explicit Scene(const QString &title, QWidget *parent = 0);
    ~Scene();

signals:
    void prevClicked();
    void nextClicked();

private:
    Ui::Scene *_ui;
    QString _title;
};

#endif // SCENE_H
