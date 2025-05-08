#include "moodtest.h"
#include "ui_moodtest.h"

MoodTest::MoodTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoodTest)
{
    ui->setupUi(this);
}

MoodTest::~MoodTest()
{
    delete ui;
}
