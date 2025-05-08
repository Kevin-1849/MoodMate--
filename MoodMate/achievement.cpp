#include "achievement.h"
#include "ui_achievement.h"

Achievement::Achievement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Achievement)
{
    ui->setupUi(this);
}

Achievement::~Achievement()
{
    delete ui;
}
