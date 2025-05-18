#ifndef MOODDIARY_H
#define MOODDIARY_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QStackedWidget>
#include <QPushButton>

#include "emojicalendarwidget.h"
#include "mooddata.h"

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
    //void onDateSelected(const QDate &date);
    //void onEditButtonClicked();

    void on_editButton_clicked();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MoodDiary *ui;
    QDate selectedDate;
    MoodData moodData;

    void updateMoodPreview();
};

#endif // MOODDIARY_H
