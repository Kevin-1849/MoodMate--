#include "emojicalendarwidget.h"
#include <QPainter>
#include <QFont>
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
        selection-color: black;
        selection-background-color: #aed581;
        gridline-color: #ccc;
    }

    QCalendarWidget QAbstractItemView::item {
        color: black;
        padding: 4px;
    }
)");
}

/*void EmojiCalendarWidget::setEmojiForDate(const QDate &date, const QString &emoji)
{
    //emojiMap[date] = emoji;
    updateCell(date); // 只更新这一天
}*/
void EmojiCalendarWidget::paintCell(QPainter *painter, const QRect &rect, QDate date) const
{
    // 调用父类绘制原始内容
    QCalendarWidget::paintCell(painter, rect, date);
    auto mood = moodData.getMoodForDate(date);
    // 如果这一天有 emoji，就绘制上去
    //qDebug() << date;
    //qDebug() << mood.dailyEmoji;

    if (mood.dailyEmoji != "") {

        painter->save();  // 保存状态
        // 覆盖数字区域（上半部分）白色块
        QRect topRect = QRect(rect.left(), rect.top(), rect.width(), rect.height()/2);

        // 判断是否是选中日期
        bool isSelected = (date == this->selectedDate());
        if (isSelected) {
            // 画选中背景色（保持绿色）
            painter->fillRect(rect, QColor("#aed581"));  // 绿色背景
        } else {
            // 画正常背景
            painter->fillRect(rect, Qt::white);
        }

        // 重画数字，字体大点，向上
        // 判断是否周末
        bool isWeekend = (date.dayOfWeek() == 6 || date.dayOfWeek() == 7);  // 6=周六，7=周日
        QColor textColor = isWeekend ? QColor(Qt::red) : QColor(Qt::black);
        painter->setPen(textColor);
        QFont font = painter->font();
        font.setBold(true);
        font.setPointSize(14);
        painter->setFont(font);
        QRect numberRect = QRect(rect.left(), rect.top() + 2, rect.width(), rect.height()/2);
        painter->drawText(numberRect, Qt::AlignHCenter | Qt::AlignTop, QString::number(date.day()));

        QIcon icon = QIcon(mood.dailyEmoji);
        int iconHeight = rect.height() / 2;
        int iconWidth = iconHeight;
        QRect iconRect(rect.left() + (rect.width() - iconWidth) / 2,
                       rect.bottom() - iconHeight - 5,
                       iconWidth,
                       iconHeight);
        icon.paint(painter, iconRect, Qt::AlignCenter);
    }
}

void EmojiCalendarWidget::refreshCalendar(){
    updateCells();
}
