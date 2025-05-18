#ifndef MOODDATA_H
#define MOODDATA_H

#include <QJsonObject>
#include <QDate>
#include <QString>

/* moodData的存储结构大致如下：
 * moodMap 一个date对应一个DailyMood结构
 * DailyMood 包含三部分，dailyEmoji，dailyNote（当天心情与当天笔记），timeSlots（记录每个时段的心情情况）
 * timeSlots 一个时段（"morning", "afternoon" 和 "evening"）对应 一个 TimeSlotMood
 * TimeSlotMood 包含两部分，该时段的心情emoji和该时段的笔记note
*/

struct TimeSlotMood {
    QString emoji;
    QString note;
};

struct DailyMood {
    QMap<QString, TimeSlotMood> timeSlots; // "morning", "afternoon" 和 "evening"
    QString dailyNote;
    QString dailyEmoji;
};

class MoodData {
public:
    MoodData();

    bool load(const QString &filename);
    bool save(const QString &filename);

    // 获取某一天的MoodDiary
    DailyMood getMoodForDate(const QDate &date) const;
    //设置某一天的MoodDiary
    void setMoodForDate(const QDate &date, const DailyMood &mood);

private:
    QMap<QString, DailyMood> moodMap; // key: date.toString("yyyy-MM-dd")
};

#endif // MOODDATA_H
