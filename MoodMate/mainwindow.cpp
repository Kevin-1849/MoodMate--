#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>

#include "homepage.h"
#include "achievement.h"
#include "aichat.h"
#include "moodchart.h"
#include "moodtest.h"
#include "mooddiary.h"
#include "rest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //窗口标题
    setWindowTitle("MoodMate");

    // 导航栏
    ui->navigationBar->setIconSize(QSize(40, 40));       // 图标尺寸
    ui->navigationBar->setGridSize(QSize(80, 80));      // 每个 item 所占区域大小

    QListWidgetItem* homeItem = new QListWidgetItem(QIcon(":/icon/主界面图标2.png"), "主页");
    QListWidgetItem* diaryItem = new QListWidgetItem(QIcon(":/icon/心情日记图标.png"), "心情日记");
    QListWidgetItem* testItem = new QListWidgetItem(QIcon(":/icon/心理测试图标.png"), "心理测试");
    QListWidgetItem* chatItem = new QListWidgetItem(QIcon(":/icon/聊天图标.png"), "心理助手");
    QListWidgetItem* restItem = new QListWidgetItem(QIcon(":/icon/冥想图标.png"), "冥想休息");
    QListWidgetItem* chartItem = new QListWidgetItem(QIcon(":/icon/图表图标.png"), "统计");
    QListWidgetItem* achievementItem = new QListWidgetItem(QIcon(":/icon/成就图标.png"), "成就");

    ui->navigationBar->addItem(homeItem);
    ui->navigationBar->addItem(diaryItem);
    ui->navigationBar->addItem(testItem);
    ui->navigationBar->addItem(chatItem);
    ui->navigationBar->addItem(restItem);
    ui->navigationBar->addItem(chartItem);
    ui->navigationBar->addItem(achievementItem);

    //页面
    homePage = new HomePage(this);
    diaryPage = new MoodDiary(this);
    testPage = new MoodTest(this);
    chatPage = new AIChat(this);
    restPage = new Rest(this);
    chartPage = new MoodChart(this);
    achievementPage = new Achievement(this);

    // 页面容器
    stackWidget = new QStackedWidget(this);
    ui->stackWidgetLayout->addWidget(stackWidget);
    stackWidget->addWidget(homePage);
    stackWidget->addWidget(diaryPage);
    stackWidget->addWidget(testPage);
    stackWidget->addWidget(chatPage);
    stackWidget->addWidget(restPage);
    stackWidget->addWidget(chartPage);
    stackWidget->addWidget(achievementPage);

    //连接导航栏与页面容器
    connect(ui->navigationBar, &QListWidget::currentRowChanged,
            stackWidget, &QStackedWidget::setCurrentIndex);

    //连接导航栏与页面容器
    /*connect(ui->navigationBar, &QListWidget::currentRowChanged, [this](int index) {
        // 如果不是"心理助手"项，切换页面
        if (index != 3) {
            stackWidget->setCurrentIndex(index);
        }
    });*/


    /*// 单独处理"心理助手"点击
    connect(ui->navigationBar, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        if (item->text() == "心理助手") {
            qDebug() << 10086;
            openChatDialog();
        }
    });*/

    //接收信号
    connect(homePage, &HomePage::requestSwitchToDiaryPage, this, [=]() {
        ui->navigationBar->setCurrentRow(1);
    });

    connect(homePage, &HomePage::requestSwitchToTestPage, this, [=]() {
        ui->navigationBar->setCurrentRow(2);
    });

    connect(homePage, &HomePage::requestSwitchToRestPage, this, [=]() {
        ui->navigationBar->setCurrentRow(4);
    });

    connect(homePage, &HomePage::requestSwitchToChatPage, this, [=]() {
        ui->navigationBar->setCurrentRow(3);
    });


    // 主界面直接打开聊天窗口
    //connect(homePage, &HomePage::requestOpenChat, this, &MainWindow::openChatDialog);
}



MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::openChatDialog() {
    if (!chatDialog) {
        // 创建新的聊天对话框
        chatDialog = new AIChat(this);
        chatDialog->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除
        connect(chatDialog, &QDialog::finished, this, [this]() {
            chatDialog = nullptr; // 对话框关闭后重置指针
        });
    }
    qDebug() << 10096;
    chatDialog->show(); // 显示对话框
    qDebug() << 10100;
    chatDialog->activateWindow(); // 激活窗口
    qDebug() << 11100;
    chatDialog->raise(); // 置于顶层
    qDebug() << 11111;
}*/
