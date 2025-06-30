#ifndef ACHIEVEMENTITEM_H
#define ACHIEVEMENTITEM_H

#include <QWidget>
#include <QVector>

namespace Ui {
class AchievementItem;
}

class AchievementItem : public QWidget
{
    Q_OBJECT

public:
    explicit AchievementItem(const QString& path, const QString& text, bool yes = false, QWidget* parent = nullptr);
    ~AchievementItem();
    void setIcon(const QString& path);
    void setText(const QString& text);
    void setAchieved(bool yes);

private:
    Ui::AchievementItem *ui;

};

#endif // ACHIEVEMENTITEM_H
