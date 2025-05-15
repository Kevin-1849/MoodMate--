#ifndef MOODDIARY_H
#define MOODDIARY_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QStackedWidget>
#include <QPushButton>

#include "editpage.h"
#include "emojicalendarwidget.h"

namespace Ui {
class MoodDiary;
}

class MoodDiary : public QWidget
{
    Q_OBJECT

public:
    explicit MoodDiary(QWidget *parent = nullptr);
    ~MoodDiary();

private slots:
    void onDateSelected(const QDate &date);
    void onEditButtonClicked();

private:
    Ui::MoodDiary *ui;
    QDate selectedDate;
    //MoodData moodData;

    EmojiCalendarWidget *calendar;
    QLabel *moodLabel;
    QTextEdit *notePreview;
    QPushButton *editButton;

    QStackedWidget *stack; // 当前 page 内部切换：日历视图 <-> 编辑界面
    EditPage *editPage;

    void updateMoodPreview();
};

#endif // MOODDIARY_H
