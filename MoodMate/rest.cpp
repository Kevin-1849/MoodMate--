#include "rest.h"
#include "ui_rest.h"

Rest::Rest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Rest)
{
    ui->setupUi(this);
}

Rest::~Rest()
{
    delete ui;
}
