#include "mooddiary.h"
#include "ui_mooddiary.h"

MoodDiary::MoodDiary(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoodDiary)
{
    ui->setupUi(this);
    setWindowTitle("心情日记");
}

MoodDiary::~MoodDiary()
{
    delete ui;
}
