#ifndef MOODDIARY_H
#define MOODDIARY_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QStackedWidget>
#include <QPushButton>
#include <QList>
#include <QString>
#include <QListWidget>
#include <QComboBox>

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

    void on_returnButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::MoodDiary *ui;
    QDate selectedDate = QDate::currentDate();
    MoodData moodData;
    QList<QString> emojiList = {"开心","庆祝","机智","酷帅","好吃","惊讶","平静","伤心","生气","尴尬","可怜","疲倦","思考"};

    void updateMoodPreview();
    void show_editPage();
    void addMoodRecord(QListWidget *listWidget, const QString &timeLabelText, const QString &iconPath, const QString &noteText);
    void set_default(QComboBox* box, QString text);
    void set_default(QTextEdit* edit, QString text);
};


#endif // MOODDIARY_H
