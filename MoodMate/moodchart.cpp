#include "moodchart.h"
#include "ui_moodchart.h"
#include <QDate>
#include <QDebug>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QGraphicsPixmapItem>
#include <QMapIterator>
#include <QFileInfo>


MoodChart::MoodChart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoodChart)
{
    ui->setupUi(this);
    setWindowTitle("心情统计");

    if (!moodData.load("data/mood_diary.json")) {
        qDebug() << "加载心情数据失败";
        return;
    }
    drawWeeklyEmojiUsage();
    drawMonthlyEmojiUsage();
    drawWeeklyChart();
    drawMonthlyChart();

    //成就实现
    QFile file("data/achievement_status.json");
    QJsonObject achievementStatus;
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        achievementStatus = doc.object();
    }

    QFile file2("data/achievement_data.json");
    QJsonObject achievementData;
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data2 = file2.readAll();
        file2.close();

        QJsonDocument doc2 = QJsonDocument::fromJson(data2);
        achievementData = doc2.object();
    }

    int tmp = achievementData.value("图表解读者").toInt();
    tmp += 1;
    if(tmp >= 5){
        achievementStatus["图表解读者"] = true;
    }
    if(tmp >= 30){
        achievementStatus["周报收藏家"] = true;
    }
    achievementData["图表解读者"] = tmp;

    QJsonDocument doc(achievementStatus);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }

    QJsonDocument doc2(achievementData);
    if (file2.open(QIODevice::WriteOnly)) {
        file2.write(doc2.toJson());
        file2.close();
    }

}

int MoodChart::getMoodValue(const QString &emojiPath) {
    if (emojiPath.contains("开心") || emojiPath.contains("庆祝")) return 5;
    if (emojiPath.contains("酷帅") || emojiPath.contains("机智") || emojiPath.contains("好吃"))   return 4;
    //if (emojiPath.contains("思考") || emojiPath.contains("平静")) return 3;
    if (emojiPath.contains("伤心") || emojiPath.contains("可怜")) return 2;
    if (emojiPath.contains("生气")) return 1;
    if (emojiPath.trimmed().isEmpty()) return 3; // 无表情计为3
    return 3; // 默认值
}


void MoodChart::drawWeeklyEmojiUsage() {
    QMap<QString, int> emojiUsage;

    QDate today = QDate::currentDate();
    for (int i = 0; i < 7; ++i) {
        QDate date = today.addDays(-i);
        QString key = date.toString("yyyy.MM.dd");
        DailyMood mood = moodData.getMoodForDate(date);

        // 统计当天每个表情的使用次数
        for (const TimeSlotMood &tsm : mood.timeSlots.values()) {
            QString emoji = tsm.emoji;
            emojiUsage[emoji]++;
        }
        QString emoji = mood.dailyEmoji;
        emojiUsage[emoji]++;
    }

    if(emojiUsage.isEmpty())return;

    // 找到使用最多的表情
    QStringList emojis = emojiUsage.keys();
    QVector<int> counts;
    /*for (const QString &emoji : emojis) {
        qDebug() << emoji;
        if(emoji == "")continue;
        counts.append(emojiUsage[emoji]);
    }*/

    QString mostUsedEmoji;
    int maxCount = -1;

    for (auto it = emojiUsage.begin(); it != emojiUsage.end(); ++it) {
        if (it.value() > maxCount  && it.key() != "") {
            maxCount = it.value();
            mostUsedEmoji = it.key();
        }
    }

    qDebug() << "最常使用的表情是：" << mostUsedEmoji << "，使用次数：" << maxCount;

    QPixmap pixmap(mostUsedEmoji);
    ui->weekEmojiLabel->setPixmap(pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    /*// 创建柱状图
    QBarSeries *series = new QBarSeries();

    QBarSet *set = new QBarSet("表情使用频率");
    for (int count : counts) {
        *set << count;
    }

    series->append(set);*/

    /*// 设置图表
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("近7天表情使用情况");

    // 设置 X 轴为表情名称
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(emojis);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 设置 Y 轴为次数
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("使用次数");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 显示图表
    QChartView *chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->weeklyEmojiLayout->addWidget(chartView);*/
}

void MoodChart::drawMonthlyEmojiUsage() {
    QMap<QString, int> emojiUsage;

    QDate today = QDate::currentDate();
    for (int i = 0; i < 30; ++i) {
        QDate date = today.addDays(-i);
        QString key = date.toString("yyyy.MM.dd");
        DailyMood mood = moodData.getMoodForDate(date);

        // 统计当天每个表情的使用次数
        for (const TimeSlotMood &tsm : mood.timeSlots.values()) {
            QString emoji = tsm.emoji;
            emojiUsage[emoji]++;
        }
        QString emoji = mood.dailyEmoji;
        emojiUsage[emoji]++;
    }

    if (emojiUsage.isEmpty()) return;

    QList<QPair<QString, int>> sortedEmojiUsage;
    for (auto it = emojiUsage.begin(); it != emojiUsage.end(); ++it) {
        sortedEmojiUsage.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedEmojiUsage.begin(), sortedEmojiUsage.end(),
              [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
                  return a.second > b.second;  // 按照第二个元素（使用次数）降序排序
              });

    // 找到使用最多的表情
    QString mostUsedEmoji;
    int maxCount = -1;

    for (auto it = emojiUsage.begin(); it != emojiUsage.end(); ++it) {
        if (it.value() > maxCount && it.key() != "") {
            maxCount = it.value();
            mostUsedEmoji = it.key();
        }
    }

    qDebug() << "最常使用的表情是：" << mostUsedEmoji << "，使用次数：" << maxCount;

    QPixmap pixmap(mostUsedEmoji);
    ui->monthEmojiLabel->setPixmap(pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // 填充柱状图数据
    QVector<int> values;
    QStringList emojis;
    for (const QPair<QString, int> &emoji : sortedEmojiUsage) {
        // 提取文件名作为 X 轴标签
        if(emoji.first == "")continue;
        QFileInfo fileInfo(emoji.first);
        QString emojiName = fileInfo.baseName();  // 提取文件名（去除路径和扩展名）

        emojis.append(emojiName);  // 使用提取的文件名
        values.append(emoji.second);  // 使用次数
    }

    // 创建柱状图
    QBarSeries *series = new QBarSeries();

    QBarSet *set = new QBarSet("表情使用频率");
    // 将数据添加到柱状图
    for (int i = 0; i < values.size(); ++i) {
        set->append(values[i]);
    }

    series->append(set);  // 把 BarSet 添加到 BarSeries

    // 设置图表
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("近30天表情使用情况");

    // 设置 X 轴为提取的表情名称
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(emojis);  // 设置 X 轴标签为提取的文件名
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // 设置 Y 轴为次数
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("使用次数");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // 显示图表
    QChartView *chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->monthlyEmojiLayout->addWidget(chartView);
}


void MoodChart::drawWeeklyChart() {
    QLineSeries *series = new QLineSeries();
    series->setName("近7天心情变化");

    QDate today = QDate::currentDate();
    double total = 0;
    double count = 0;
    int num = 0;


    for (int i = 0; i < 7; ++i) {
        QDate date = today.addDays(-i);
        QString key = date.toString("yyyy.MM.dd");
        DailyMood mood = moodData.getMoodForDate(date);

        /*int total = 0;
        int count = 0;
        for (const TimeSlotMood &tsm : mood.timeSlots.values()) {
            int val = getMoodValue(tsm.emoji);
            if (val > 0) {
                total += val;
                count++;
            }
        }*/
        //int dailyMood = (count == 0) ? 3 : total / count;
        int dailyMood = getMoodValue(mood.dailyEmoji);
        total += dailyMood;
        count ++;
        if(mood.dailyNote != "")++num;
        series->append(7-i , dailyMood); // X轴是1到7
    }

    weeklyMoodNum = total/count;
    ui->weekIconLabel->setText(QString::number(weeklyMoodNum));
    ui->monthDairyTime->setText(QString::number(num));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("近7天心情变化");
    chart->createDefaultAxes();
    // 设置 X 轴为 1 到 7
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(1, 7);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("日期");
    chart->setAxisX(axisX, series);

    // 设置 Y 轴范围
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 5); // 假设心情值是从0到5的范围
    chart->setAxisY(axisY, series);

    // 显示图表
    QChartView *chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->weeklyChartLayout->addWidget(chartView);
}

void MoodChart::drawMonthlyChart() {
    QLineSeries *series = new QLineSeries();
    series->setName("近30天心情变化");

    QMap<QString, QList<int>> monthlyData;

    QDate today = QDate::currentDate();
    double total = 0;
    double count = 0;
    int num = 0;
    for (int i = 0; i < 30; ++i) {
        QDate date = today.addDays(-i);
        QString key = date.toString("yyyy.MM.dd");
        DailyMood mood = moodData.getMoodForDate(date);


        /*for (const TimeSlotMood &tsm : mood.timeSlots.values()) {
            int val = getMoodValue(tsm.emoji);
            if (val > 0) {
                total += val;
                count++;
            }
        }*/
        int dailyMood = getMoodValue(mood.dailyEmoji);
        total += dailyMood;
        count ++;
        if(mood.dailyNote != "")++num;
        series->append(30-i , dailyMood); // X轴是1到30
        //QString month = date.toString("yyyy-MM");
        //monthlyData[month].append(dailyMood);
    }

    monthlyMoodNum = total/count;
    ui->monthIconLabel->setText(QString::number(monthlyMoodNum));
    ui->monthDairyTime->setText(QString::number(num));
    /*for (const QString &month : monthlyData.keys()) {
        QDate monthDate = QDate::fromString(month + "-01", "yyyy-MM-dd");
        int avg = 0;
        for (int val : monthlyData[month]) {
            avg += val;
        }
        avg /= monthlyData[month].size();
        series->append(monthDate.toJulianDay(), avg);
    }*/


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("近30天心情变化");
    chart->createDefaultAxes();

    // 设置 X 轴为 1 到 30
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(1, 30);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("日期");
    chart->setAxisX(axisX, series);

    // 设置 Y 轴范围
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 5); // 假设心情值是从0到5的范围
    chart->setAxisY(axisY, series);

    // 显示图表
    QChartView *chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->monthlyChartLayout->addWidget(chartView);
}

MoodChart::~MoodChart() {
    delete ui;
}
