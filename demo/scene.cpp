#include "scene.h"
#include "ui_scene.h"

Scene::Scene(const QString &title, QWidget *parent) :
    QWidget(parent), _ui(new Ui::Scene)
{
    _ui->setupUi(this);
    _ui->label->setText(title);
    connect(_ui->prevButton, SIGNAL(clicked()), this, SIGNAL(prevClicked()));
    connect(_ui->nextButton, SIGNAL(clicked()), this, SIGNAL(nextClicked()));
}

Scene::~Scene()
{
    delete _ui;
}
