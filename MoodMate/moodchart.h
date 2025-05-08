#ifndef MOODCHART_H
#define MOODCHART_H

#include <QWidget>

namespace Ui {
class MoodChart;
}

class MoodChart : public QWidget
{
    Q_OBJECT

public:
    explicit MoodChart(QWidget *parent = nullptr);
    ~MoodChart();

private:
    Ui::MoodChart *ui;
};

#endif // MOODCHART_H
