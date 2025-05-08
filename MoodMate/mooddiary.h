#ifndef MOODDIARY_H
#define MOODDIARY_H

#include <QWidget>

namespace Ui {
class MoodDiary;
}

class MoodDiary : public QWidget
{
    Q_OBJECT

public:
    explicit MoodDiary(QWidget *parent = nullptr);
    ~MoodDiary();

private:
    Ui::MoodDiary *ui;
};

#endif // MOODDIARY_H
