#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <QWidget>
#include <QVector>
#include "achievementitem.h"

namespace Ui {
class Achievement;
}

class Achievement : public QWidget
{
    Q_OBJECT

public:
    explicit Achievement(QWidget *parent = nullptr);
    ~Achievement();
    QVector<AchievementItem*> achieveList;//成就集
    void addAchItem(AchievementItem* item);


private:
    Ui::Achievement *ui;
};

#endif // ACHIEVEMENT_H
