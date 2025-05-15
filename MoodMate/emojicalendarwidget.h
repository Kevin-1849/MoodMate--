#ifndef EMOJICALENDARWIDGET_H
#define EMOJICALENDARWIDGET_H

#include <QCalendarWidget>
#include <QDate>
#include <QMap>

class EmojiCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit EmojiCalendarWidget(QWidget *parent = nullptr);

    // 设置某天的表情
    void setEmojiForDate(const QDate &date, const QString &emoji);

protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

private:
    QMap<QDate, QString> emojiMap;  // 存储日期到表情的映射
};

#endif // EMOJICALENDARWIDGET_H
