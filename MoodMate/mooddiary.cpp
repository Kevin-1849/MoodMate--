#include "mooddiary.h"
#include "ui_mooddiary.h"
#include "emojicalendarwidget.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDebug>


MoodDiary::MoodDiary(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoodDiary)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->calendarPage);

}

MoodDiary::~MoodDiary()
{
    delete ui;
}

//日期被选择时触发事件
void MoodDiary::on_calendarWidget_clicked(const QDate &date)
{
    selectedDate = date;
    updateMoodPreview();
}

//更新当天心情情况概览
void MoodDiary::updateMoodPreview() {
    ui->timeRecordList->clear();
    auto mood = moodData.getMoodForDate(selectedDate);
    if(mood.timeSlots.isEmpty() && mood.dailyNote.isEmpty() && mood.dailyEmoji.isEmpty()){
        ui->dateLabel->setText(selectedDate.toString("yyyy.MM.dd"));
        ui->moodLabel->setText("暂无记录");
        ui->timeRecordList->addItem("暂无数据");
        ui->diaryBrowser->setText("暂无心情笔记");
    }
    else{
        ui->dateLabel->setText(selectedDate.toString("yyyy.MM.dd"));
        ui->moodLabel->setText(mood.dailyEmoji.isEmpty()? "暂无记录" : mood.dailyEmoji);
        ui->timeRecordList->addItem("早上：" + (mood.timeSlots["morning"].emoji.isEmpty()? "暂无数据" : mood.timeSlots["morning"].emoji) + " " + mood.timeSlots["morning"].note);
        ui->timeRecordList->addItem("下午：" + (mood.timeSlots["afternoon"].emoji.isEmpty()? "暂无数据" : mood.timeSlots["afternoon"].emoji) + " " + mood.timeSlots["afternoon"].note);
        ui->timeRecordList->addItem("晚上：" + (mood.timeSlots["evening"].emoji.isEmpty()? "暂无数据" : mood.timeSlots["evening"].emoji) + " " + mood.timeSlots["evening"].note);
        ui->diaryBrowser->setText(mood.dailyNote.isEmpty()? "暂无心情笔记" : mood.dailyNote);
    }
}

void MoodDiary::on_editButton_clicked()
{
    qDebug("1");
    ui->stackedWidget->setCurrentWidget(ui->editPage);
}




