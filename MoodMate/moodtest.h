#ifndef MOODTEST_H
#define MOODTEST_H

#include <QWidget>
#include <QMap>
#include <QVector>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MoodTest; }
QT_END_NAMESPACE

struct Question {
    QString text;
    QMap<QString, int> options; // 选项文本 -> 分值
};

struct Questionnaire {
    QString name;
    QString description;
    bool isQuick; // 是否为快速测试
    QVector<Question> questions;
    QMap<int, QString> resultInterpretations; // 分数区间 -> 解释
};

class MoodTest : public QWidget
{
    Q_OBJECT

public:
    MoodTest(QWidget *parent = nullptr);
    ~MoodTest();

private slots:
    void on_startButton_clicked();
    void on_nextButton_clicked();
    void on_finishButton_clicked();
    void on_questionnaireComboBox_currentIndexChanged(int index);
    //void updateProgress();

    // 添加的槽函数声明
    void on_restartButton_clicked();

private:
    Ui::MoodTest *ui;
    QMap<QString, Questionnaire> questionnaires;
    QString currentQuestionnaire;
    int currentQuestionIndex;
    int totalScore;
    //QTimer *progressTimer;
    int progressValue;

    void loadQuestionnaires();
    void setupQuestionnaireSelection();
    void setupQuestionPage(const Question &question);
    void showResult(int score);
};
#endif // MOODTEST_H
