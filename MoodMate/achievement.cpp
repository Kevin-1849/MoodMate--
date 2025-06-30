#include "achievement.h"
#include "ui_achievement.h"
#include "achievementitem.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>

Achievement::Achievement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Achievement)
{
    ui->setupUi(this);
    QFile file("data/achievement_status.json");
    QJsonObject achievementStatus;

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        achievementStatus = doc.object();
    }
    ui->achievementList->setSpacing(10);
    addAchItem(new AchievementItem(":/icon/心情日记图标", "<b>日记达人</b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;连续记录心情日记7天", achievementStatus["日记达人"].toBool()));
    addAchItem(new AchievementItem(":/icon/成就图标", "<b>日记超人</b>&nbsp;&nbsp;&nbsp;&nbsp;连续记录心情日记30天", achievementStatus["日记达人（进阶）"].toBool()));
    addAchItem(new AchievementItem(":/icon/聊天图标", "<b>心语初相识</b>&nbsp;&nbsp;&nbsp;&nbsp;与 “心语 AI” 完成5次聊天", achievementStatus["心语初相识"].toBool()));
    addAchItem(new AchievementItem(":/icon/chat", "<b>心灵树洞王</b>&nbsp;&nbsp;&nbsp;&nbsp;与AI完成30次聊天", achievementStatus["心灵树洞王"].toBool()));
    addAchItem(new AchievementItem(":/icon/心理测试图标", "<b>心灵初探秘</b>&nbsp;&nbsp;&nbsp;&nbsp;完成 5 次心理测试", achievementStatus["心灵初探秘"].toBool()));
    addAchItem(new AchievementItem(":/icon/fenxi", "<b>心灵分析师</b>&nbsp;&nbsp;&nbsp;&nbsp;完成30次心理测试", achievementStatus["心灵分析师"].toBool()));
    addAchItem(new AchievementItem(":/icon/冥想图标", "<b>冥想初体验</b>&nbsp;&nbsp;&nbsp;&nbsp;完成 1 次 5 分钟冥想", achievementStatus["冥想初体验"].toBool()));
    addAchItem(new AchievementItem(":/icon/whitenoise", "<b>白噪音收藏家</b>&nbsp;&nbsp;&nbsp;&nbsp;尝试 4 种不同类型的白噪音", achievementStatus["白噪音收藏家"].toBool()));
    addAchItem(new AchievementItem(":/icon/图表图标", "<b>图表解读者</b>&nbsp;&nbsp;&nbsp;&nbsp;累计查看情绪图表 5 次", achievementStatus["图表解读者"].toBool()));
    addAchItem(new AchievementItem(":/icon/tubiao", "<b>周报收藏家</b>&nbsp;&nbsp;&nbsp;&nbsp;累计查看情绪图表 30 次", achievementStatus["周报收藏家"].toBool()));
}

Achievement::~Achievement()
{
    delete ui;
}

void Achievement::addAchItem(AchievementItem* item){
    ui->achievementList->addWidget(item);
    //ui->achievementList->setAlignment(item, Qt::AlignTop);
}
