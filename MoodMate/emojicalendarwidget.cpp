#include "emojicalendarwidget.h"
#include <QPainter>
#include <QFont>
#include <QSysInfo>  // 判断系统平台

EmojiCalendarWidget::EmojiCalendarWidget(QWidget *parent)
    : QCalendarWidget(parent)
{
    //设置日历样式
    this->setStyleSheet(R"(
    QCalendarWidget QWidget {
        background-color: #f5f5f5;
        color: #333;
        font-size: 14px;
    }

    QCalendarWidget QToolButton {
        background-color: #ffffff;
        color: #2e8b57;
        font-weight: bold;
        border: none;
        padding: 5px;
    }

    QCalendarWidget QMenu {
        background-color: #ffffff;
    }

    QCalendarWidget QSpinBox {
        color: #2e8b57;
    }

    QCalendarWidget QAbstractItemView::item:hover {
        background-color: #d8f3dc;
        border-radius: 5px;
    }

    QCalendarWidget QAbstractItemView:enabled {
        font-size: 13px;
        background-color: white;
        selection-background-color: #aed581;
        selection-color: black;
        gridline-color: #ccc;
    }

    QCalendarWidget QAbstractItemView::item {
        padding: 4px;
    }
)");
}

void EmojiCalendarWidget::setEmojiForDate(const QDate &date, const QString &emoji)
{
    emojiMap[date] = emoji;
    updateCell(date); // 只更新这一天
}

void EmojiCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    // 调用父类绘制原始内容
    QCalendarWidget::paintCell(painter, rect, date);

    // 如果这一天有 emoji，就绘制上去
    if (emojiMap.contains(date)) {
        painter->save();

        QFont emojiFont;
#if defined(Q_OS_MAC)
        emojiFont = QFont("Apple Color Emoji", 14);
#elif defined(Q_OS_WIN)
        emojiFont = QFont("Segoe UI Emoji", 14);
#else
        emojiFont = QFont("Noto Color Emoji", 14);
#endif
        painter->setFont(emojiFont);
        painter->drawText(rect, Qt::AlignBottom | Qt::AlignHCenter, emojiMap.value(date));

        painter->restore();
    }
}
