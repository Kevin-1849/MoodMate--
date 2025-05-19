#include "mooddiary.h"
#include "ui_mooddiary.h"
#include "emojicalendarwidget.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDebug>
#include <QFont>
#include <QSysInfo>
#include <QFontDatabase>
#include <QScrollBar>
#include <QIcon>
#include <QString>
#include <QDir>
#include <QProxyStyle>
#include <QMessageBox>

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

//增添心情记录函数
void MoodDiary::addMoodRecord(QListWidget *listWidget, const QString &timeLabelText,
                   const QString &iconPath, const QString &noteText)
{
    QWidget *itemWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(itemWidget);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(5);  // 控制间距

    QLabel *timeLabel = new QLabel(timeLabelText);
    QLabel *iconLabel = new QLabel;
    QLabel *noteLabel = new QLabel(noteText.isEmpty() ? "" : noteText);

    if (!iconPath.isEmpty()) {
        QPixmap pixmap(iconPath);
        if (!pixmap.isNull()) {
            iconLabel->setPixmap(pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

    layout->addWidget(timeLabel);
    layout->addWidget(iconLabel);
    layout->addWidget(noteLabel);
    layout->addStretch();  // 右边留白

    QListWidgetItem *listItem = new QListWidgetItem(listWidget);
    listItem->setSizeHint(itemWidget->sizeHint());

    listWidget->addItem(listItem);
    listWidget->setItemWidget(listItem, itemWidget);
}

//更新当天心情情况概览
void MoodDiary::updateMoodPreview() {
    ui->timeRecordList->clear();
    moodData.load("data/mood_diary.json");

    auto mood = moodData.getMoodForDate(selectedDate);
    ui->dateLabel->setText(selectedDate.toString("yyyy.MM.dd"));
    if(mood.dailyEmoji.isEmpty()) ui->moodLabel->setText("暂无记录");
    else{
        QPixmap pixmap(mood.dailyEmoji);
        ui->moodLabel->setPixmap(pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    qDebug() << mood.dailyNote;
    ui->diaryBrowser->setText(mood.dailyNote.isEmpty()? "暂无心情笔记" : mood.dailyNote);

    addMoodRecord(ui->timeRecordList, "早上：", mood.timeSlots["morning"].emoji, mood.timeSlots["morning"].note);
    addMoodRecord(ui->timeRecordList, "下午：", mood.timeSlots["afternoon"].emoji, mood.timeSlots["afternoon"].note);
    addMoodRecord(ui->timeRecordList, "晚上：", mood.timeSlots["evening"].emoji, mood.timeSlots["evening"].note);
}

void MoodDiary::on_editButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->editPage);
    show_editPage();
}

void MoodDiary::show_editPage(){
    ui->scrollArea->verticalScrollBar()->setValue(0);
    ui->dateLabel_2->setText(selectedDate.toString("yyyy.MM.dd"));

    //设置combo选择框
    QComboBox* boxes[] = {ui->dailyEmojiBox, ui->morningEmojiBox, ui->afternoonEmojiBox, ui->eveningEmojiBox};
    for (QComboBox* box : boxes) {
        box->setStyle(new QProxyStyle("Fusion"));
        box->addItem("");
        for(auto emoji: emojiList){
            QString label = emoji;
            QString path = QString(":/emoji/%1.jpeg").arg(label);
            box->setIconSize(QSize(28, 28));
            box->addItem(QIcon(path),label,path);
        }
    }
    auto mood = moodData.getMoodForDate(selectedDate);
    set_default(ui->dailyEmojiBox, mood.dailyEmoji);
    set_default(ui->morningEmojiBox, mood.timeSlots["morning"].emoji);
    set_default(ui->afternoonEmojiBox, mood.timeSlots["afternoon"].emoji);
    set_default(ui->eveningEmojiBox, mood.timeSlots["evening"].emoji);
    set_default(ui->morningEdit, mood.timeSlots["morning"].note);
    set_default(ui->afternoonEdit, mood.timeSlots["afternoon"].note);
    set_default(ui->eveningEdit, mood.timeSlots["evening"].note);
    set_default(ui->diaryEdit, mood.dailyNote);
}

//设置初始选项
void MoodDiary::set_default(QComboBox* box, QString text){
    for (int i = 0; i < box->count(); ++i) {
        if (box->itemData(i).toString() == text) {
            box->setCurrentIndex(i);
            return;
        }
    }
    qDebug() << "Emoji path not found:" << text;
}

void MoodDiary::set_default(QTextEdit* edit, QString text){
    edit->setText(text);
}

void MoodDiary::on_returnButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->calendarPage);
}


void MoodDiary::on_saveButton_clicked()
{
    //保存心情日记
    DailyMood mood;
    mood.dailyEmoji = ui->dailyEmojiBox->itemData(ui->dailyEmojiBox->currentIndex()).toString();
    mood.dailyNote = ui->diaryEdit->toPlainText();
    mood.timeSlots["morning"].emoji = ui->morningEmojiBox->itemData(ui->morningEmojiBox->currentIndex()).toString();
    mood.timeSlots["afternoon"].emoji = ui->afternoonEmojiBox->itemData(ui->afternoonEmojiBox->currentIndex()).toString();
    mood.timeSlots["evening"].emoji = ui->eveningEmojiBox->itemData(ui->eveningEmojiBox->currentIndex()).toString();

    mood.timeSlots["morning"].note = ui->morningEdit->toPlainText();
    mood.timeSlots["afternoon"].note = ui->afternoonEdit->toPlainText();
    mood.timeSlots["evening"].note = ui->eveningEdit->toPlainText();

    moodData.setMoodForDate(selectedDate, mood);
    //qDebug() << "Current working directory:" << QDir::currentPath();
    moodData.save("data/mood_diary.json");
    QMessageBox::information(this, "保存成功", "你的心情记录已保存", QMessageBox::Ok);
}

