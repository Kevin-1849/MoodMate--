#include "achievementitem.h"
#include "ui_achievementitem.h"


AchievementItem::AchievementItem(const QString& path, const QString& text, bool yes, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AchievementItem)
{
    ui->setupUi(this);
    //设置图标、文字和完成情况
    setIcon(path);
    setText(text);
    setAchieved(yes);
}

AchievementItem::~AchievementItem()
{
    delete ui;
}

void AchievementItem::setIcon(const QString& path) {
    ui->iconLabel->setPixmap(QPixmap(path).scaled(64, 64, Qt::KeepAspectRatio));
}
void AchievementItem::setText(const QString& text) {
    ui->textLabel->setText(text);
}
void AchievementItem::setAchieved(bool yes) {
    if (yes)
        ui->checkLabel->setPixmap(QPixmap(":/icon/check.png").scaled(60, 60));
    else
        ui->checkLabel->clear();
}
