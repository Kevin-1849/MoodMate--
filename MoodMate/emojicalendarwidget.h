#ifndef EMOJICALENDARWIDGET_H
#define EMOJICALENDARWIDGET_H

#include <QCalendarWidget>
#include <QDate>
#include <QMap>

#include "mooddata.h"

class EmojiCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    MoodData moodData;
    explicit EmojiCalendarWidget(QWidget *parent = nullptr);
    void refreshCalendar();

    // 设置某天的表情
    //void setEmojiForDate(const QDate &date, const QString &emoji);

protected:
    void paintCell(QPainter *painter, const QRect &rect, QDate date) const override;


};

#endif // EMOJICALENDARWIDGET_H
