#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>

#include "homepage.h"
#include "achievement.h"
#include "aichat.h"
#include "moodchart.h"
#include "moodtest.h"
#include "mooddiary.h"
#include "rest.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget* stackWidget;//页面容器
    HomePage* homePage;//主页面
    MoodDiary* diaryPage;//心情日记界面
    MoodChart* chartPage;//统计界面
    MoodTest* testPage;//心理测试界面
    AIChat* chatPage;//AI聊天界面
    Rest* restPage;//冥想休息界面
    Achievement* achievementPage;//成就界面
    void openChatDialog();
    AIChat* chatDialog = nullptr; // 对话框指针


};
#endif // MAINWINDOW_H
