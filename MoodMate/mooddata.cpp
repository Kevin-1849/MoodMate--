#include "mooddata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

MoodData::MoodData() {}

//加载 MoodData 到 moodMap
bool MoodData::load(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << filename;
        return false;
    }

    //将文件的数据读取，保存到doc文件
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return false;

    //从doc中获取JsonObject
    QJsonObject root = doc.object();
    moodMap.clear();

    //获取并保存数据进moodMap
    for (const QString &dateStr : root.keys()) {
        QJsonObject moodObj = root.value(dateStr).toObject();
        DailyMood mood;

        QJsonObject slotsObj = moodObj.value("timeSlots").toObject();
        for (const QString &slot : slotsObj.keys()) {
            QJsonObject slotObj = slotsObj.value(slot).toObject();
            TimeSlotMood tsm;
            tsm.emoji = slotObj.value("emoji").toString();
            tsm.note = slotObj.value("note").toString();
            mood.timeSlots[slot] = tsm;
        }

        mood.dailyNote = moodObj.value("dailyNote").toString();
        mood.dailyEmoji = moodObj.value("dailyEmoji").toString();
        moodMap[dateStr] = mood;
    }
    return true;
}

//保存 MoodData 到 json 文件
bool MoodData::save(const QString &filename) {
    QJsonObject root;

    for (const QString &dateStr : moodMap.keys()) {
        const DailyMood &mood = moodMap[dateStr];
        QJsonObject moodObj;

        QJsonObject slotsObj;
        for (const QString &slot : mood.timeSlots.keys()) {
            const TimeSlotMood &tsm = mood.timeSlots[slot];
            QJsonObject slotObj;
            slotObj["emoji"] = tsm.emoji;
            slotObj["note"] = tsm.note;
            slotsObj[slot] = slotObj;
        }

        moodObj["timeSlots"] = slotsObj;
        moodObj["dailyNote"] = mood.dailyNote;
        moodObj["dailyEmoji"] = mood.dailyEmoji;
        root[dateStr] = moodObj;
    }

    //写入json文件
    QJsonDocument doc(root);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << filename;
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

//获取某天的Mood
DailyMood MoodData::getMoodForDate(const QDate &date) const {
    QString key = date.toString("yyyy.MM.dd");
    DailyMood mood = moodMap.value(key);  // 如果存在返回值，否则返回默认构造值
    return mood;
}

//设置某天的Mood
void MoodData::setMoodForDate(const QDate &date, const DailyMood &mood) {
    QString key = date.toString("yyyy.MM.dd");
    moodMap[key] = mood;
}
