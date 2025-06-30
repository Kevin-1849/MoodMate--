#ifndef MOODCHART_H
#define MOODCHART_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include "mooddata.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MoodChart; }
QT_END_NAMESPACE

class MoodChart : public QWidget
{
    Q_OBJECT

public:
    MoodChart(QWidget *parent = nullptr);
    ~MoodChart();

private:
    Ui::MoodChart *ui;
    MoodData moodData;

    double weeklyMoodNum;
    double monthlyMoodNum;
    QString weeklyMood;
    int weeklyNum = 0;
    QString monthlyMood;
    int monthlyNum = 0;
    void drawWeeklyChart();
    void drawMonthlyChart();
    int getMoodValue(const QString &emojiPath); // 根据图片路径转换心情值
    void drawWeeklyEmojiUsage();
    void drawMonthlyEmojiUsage();

};

#endif // MOODCHART_H
