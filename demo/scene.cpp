#include <iostream>
#include "scene.h"
#include "ui_scene.h"

Scene::Scene(const QString &title, QWidget *parent) :
    QWidget(parent), _ui(new Ui::Scene)
{
    _ui->setupUi(this);
    _ui->label->setText(title);
    connect(_ui->prevButton, SIGNAL(clicked()), this, SIGNAL(prevClicked()));
    connect(_ui->nextButton, SIGNAL(clicked()), this, SIGNAL(nextClicked()));

    std::cout << "Allocated " <<
                 title.toLocal8Bit().constData() <<
                 std::endl;
}

Scene::~Scene()
{
    std::cout << "Deallocating " <<
                 _ui->label->text.toLocal8Bit().constData() <<
                 std::endl;
    delete _ui;
}

void Scene::setPrevButtonEnabled(bool enabled)
{
    _ui->prevButton->setEnabled(enabled);
}
