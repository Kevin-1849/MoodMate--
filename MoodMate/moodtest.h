#ifndef MOODTEST_H
#define MOODTEST_H

#include <QWidget>

namespace Ui {
class MoodTest;
}

class MoodTest : public QWidget
{
    Q_OBJECT

public:
    explicit MoodTest(QWidget *parent = nullptr);
    ~MoodTest();

private:
    Ui::MoodTest *ui;
};

#endif // MOODTEST_H
