#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <QWidget>

namespace Ui {
class Achievement;
}

class Achievement : public QWidget
{
    Q_OBJECT

public:
    explicit Achievement(QWidget *parent = nullptr);
    ~Achievement();

private:
    Ui::Achievement *ui;
};

#endif // ACHIEVEMENT_H
