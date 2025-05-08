#include "moodchart.h"
#include "ui_moodchart.h"

MoodChart::MoodChart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoodChart)
{
    ui->setupUi(this);
    setWindowTitle("心情图表");
}

MoodChart::~MoodChart()
{
    delete ui;
}
