#include "mooddiary.h"
#include "ui_mooddiary.h"
#include "emojicalendarwidget.h"
#include <QGroupBox>
#include <QVBoxLayout>


MoodDiary::MoodDiary(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoodDiary)
{
    ui->setupUi(this);


}

MoodDiary::~MoodDiary()
{
    delete ui;
}

void MoodDiary::onDateSelected(const QDate &date) {
    selectedDate = date;
    updateMoodPreview();
}

void MoodDiary::updateMoodPreview() {
    /*if (moodData.moodMap.contains(selectedDate)) {
        auto mood = moodData.moodMap[selectedDate];
        moodLabel->setText(mood.emoji + " 表情：" + mood.emoji);
        notePreview->setPlainText(mood.note);
    } else {
        moodLabel->setText("🙂 表情：暂无记录");
        notePreview->setPlainText("暂无心情笔记");
    }*/
}

void MoodDiary::onEditButtonClicked() {
    //editPage->loadDate(selectedDate, &moodData);
    stack->setCurrentWidget(editPage);
}
