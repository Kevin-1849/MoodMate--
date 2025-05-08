#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);
    setWindowTitle("首页");
}

HomePage::~HomePage()
{
    delete ui;
}
