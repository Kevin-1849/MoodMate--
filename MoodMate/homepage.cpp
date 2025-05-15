#include "homepage.h"
#include "ui_homepage.h"
#include <QStringList>
#include <QString>
#include <QRandomGenerator>
#include <QDate>

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);
    setWindowTitle("首页");
    //设置日期
    QDate date = QDate::currentDate();
    QString dateStr = date.toString("MMM.dd");
    ui->dateLabel->setText(dateStr);

    // 自动选句
    int index = QRandomGenerator::global()->bounded(sentenceSet.size());
    QString quote = sentenceSet[index];
    ui->quoteLabel->setText(quote);

    // 允许自动换行
    ui->quoteLabel->setWordWrap(true);
    ui->quoteLabel->setMinimumWidth(300);  // 控制宽度来影响换行

    // 设置自动调整字体大小
    ui->quoteLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // 居中对齐
    ui->quoteLabel->setAlignment(Qt::AlignCenter);
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::on_DiaryButton_clicked()
{
    emit requestSwitchToDiaryPage();  // 进入日记页面
}


void HomePage::on_TestButton_clicked()
{
    emit requestSwitchToTestPage(); // 进入测试界面
}


void HomePage::on_RestButton_clicked()
{
    emit requestSwitchToRestPage(); //进入休息界面
}


void HomePage::on_ChatPage_clicked()
{
    emit requestSwitchToChatPage(); //进入聊天界面
}

