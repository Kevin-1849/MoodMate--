// moodtest.cpp
#include "moodtest.h"
#include "ui_moodtest.h"
#include <QMessageBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QJsonObject>

MoodTest::MoodTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoodTest)
{
    ui->setupUi(this);
    loadQuestionnaires();
    setupQuestionnaireSelection();

    //progressTimer = new QTimer(this);
    //connect(progressTimer, &QTimer::timeout, this, &MoodTest::updateProgress);

    ui->stackedWidget->setCurrentWidget(ui->selectionPage);
}

MoodTest::~MoodTest()
{
    delete ui;
}

void MoodTest::loadQuestionnaires()
{
    // 加载快速自测问卷
    Questionnaire quickTest;
    quickTest.name = "情绪快速自测";
    quickTest.description = "快速评估当前情绪状态，约需1分钟";
    quickTest.isQuick = true;

    Question q1;
    q1.text = "今天你的心情如何?";
    q1.options["非常愉快"] = 4;
    q1.options["比较愉快"] = 3;
    q1.options["一般"] = 2;
    q1.options["有点低落"] = 1;
    q1.options["非常低落"] = 0;

    Question q2;
    q2.text = "你感到有压力吗?";
    q2.options["完全没有"] = 4;
    q2.options["有一点"] = 3;
    q2.options["中等程度"] = 2;
    q2.options["比较大"] = 1;
    q2.options["压力极大"] = 0;

    quickTest.questions.append(q1);
    quickTest.questions.append(q2);

    quickTest.resultInterpretations[4] = "你的情绪状态极佳，继续保持!";
    quickTest.resultInterpretations[3] = "你的情绪状态良好，生活愉快!";
    quickTest.resultInterpretations[2] = "你的情绪状态一般，注意调节压力。";
    quickTest.resultInterpretations[1] = "你可能有些压力，建议适当放松。";
    quickTest.resultInterpretations[0] = "你目前情绪状态不佳，建议寻求亲友或专业人士帮助。";

    // 加载全面自测问卷
    Questionnaire fullTest;
    fullTest.name = "心理健康全面评估";
    fullTest.description = "全面评估心理健康状况，约需5分钟";
    fullTest.isQuick = false;

    // 问题1：情绪状态
    Question q3;
    q3.text = "在过去的一周里，你感到情绪低落、沮丧或绝望的频率如何？";
    q3.options["完全没有"] = 4;
    q3.options["偶尔（1-2天）"] = 3;
    q3.options["有时（3-4天）"] = 2;
    q3.options["经常（5-7天）"] = 1;
    q3.options["几乎每天"] = 0;

    // 问题2：兴趣丧失
    Question q4;
    q4.text = "你对平时感兴趣的事情失去兴趣或乐趣的频率如何？";
    q4.options["完全没有"] = 4;
    q4.options["偶尔（1-2天）"] = 3;
    q4.options["有时（3-4天）"] = 2;
    q4.options["经常（5-7天）"] = 1;
    q4.options["几乎每天"] = 0;

    // 问题3：睡眠问题
    Question q5;
    q5.text = "你的睡眠质量如何？";
    q5.options["非常好，睡眠充足且精力充沛"] = 4;
    q5.options["较好，偶尔失眠但不影响白天活动"] = 3;
    q5.options["一般，有时失眠或睡眠浅"] = 2;
    q5.options["较差，经常失眠或早醒"] = 1;
    q5.options["很差，严重失眠影响日常生活"] = 0;

    // 问题4：疲劳感
    Question q6;
    q6.text = "你经常感到疲劳或精力不足吗？";
    q6.options["完全没有"] = 4;
    q6.options["偶尔（1-2天）"] = 3;
    q6.options["有时（3-4天）"] = 2;
    q6.options["经常（5-7天）"] = 1;
    q6.options["几乎每天"] = 0;

    // 问题5：食欲变化
    Question q7;
    q7.text = "你的食欲是否有明显变化？";
    q7.options["没有变化，食欲正常"] = 4;
    q7.options["轻微变化，不影响健康"] = 3;
    q7.options["有些变化，偶尔食欲不振或暴饮暴食"] = 2;
    q7.options["明显变化，经常食欲不振或暴饮暴食"] = 1;
    q7.options["严重变化，食欲大幅波动影响健康"] = 0;

    // 问题6：注意力集中
    Question q8;
    q8.text = "你集中注意力做事情的难度如何？";
    q8.options["完全没有困难"] = 4;
    q8.options["轻微困难，不影响正常活动"] = 3;
    q8.options["有些困难，需要额外努力"] = 2;
    q8.options["明显困难，影响日常工作学习"] = 1;
    q8.options["严重困难，几乎无法集中注意力"] = 0;

    // 问题7：焦虑程度
    Question q9;
    q9.text = "你感到焦虑或紧张的频率如何？";
    q9.options["完全没有"] = 4;
    q9.options["偶尔（1-2天）"] = 3;
    q9.options["有时（3-4天）"] = 2;
    q9.options["经常（5-7天）"] = 1;
    q9.options["几乎每天"] = 0;

    // 问题8：自我价值感
    Question q10;
    q10.text = "你对自己的感觉如何？是否经常感到自卑或自责？";
    q10.options["非常积极，对自己充满信心"] = 4;
    q10.options["比较积极，偶尔有负面想法但很快克服"] = 3;
    q10.options["一般，有时会有负面想法"] = 2;
    q10.options["比较消极，经常感到自卑或自责"] = 1;
    q10.options["非常消极，严重自卑影响生活"] = 0;

    // 问题9：人际关系
    Question q11;
    q11.text = "你与家人、朋友或同事的关系如何？";
    q11.options["非常融洽，关系亲密"] = 4;
    q11.options["比较融洽，偶尔有小矛盾"] = 3;
    q11.options["一般，关系平淡"] = 2;
    q11.options["比较紧张，经常有矛盾"] = 1;
    q11.options["非常紧张，几乎无法维持关系"] = 0;

    // 问题10：生活兴趣
    Question q12;
    q12.text = "你对未来的生活是否充满希望？";
    q12.options["充满希望，对未来有明确规划"] = 4;
    q12.options["比较有希望，对未来有一定期待"] = 3;
    q12.options["一般，对未来没有太多想法"] = 2;
    q12.options["比较迷茫，对未来缺乏信心"] = 1;
    q12.options["非常迷茫，对未来不抱希望"] = 0;

    fullTest.questions.append(q3);
    fullTest.questions.append(q4);
    fullTest.questions.append(q5);
    fullTest.questions.append(q6);
    fullTest.questions.append(q7);
    fullTest.questions.append(q8);
    fullTest.questions.append(q9);
    fullTest.questions.append(q10);
    fullTest.questions.append(q11);
    fullTest.questions.append(q12);

    // 全面评估结果解释（基于总分区间）
    fullTest.resultInterpretations[36] = "你的心理健康状况极佳，情绪稳定，对生活充满积极态度。继续保持良好的生活习惯和心态！";
    fullTest.resultInterpretations[28] = "你的心理健康状况良好，虽然偶尔会有一些情绪波动，但整体状态稳定。建议继续保持健康的生活方式，适当关注压力管理。";
    fullTest.resultInterpretations[20] = "你的心理健康状况一般，可能正在经历一些压力或情绪困扰。建议调整生活节奏，增加放松和自我关怀的时间，必要时可以寻求亲友的支持。";
    fullTest.resultInterpretations[12] = "你的心理健康状况需要关注，可能存在较明显的情绪问题或压力。建议尝试通过运动、兴趣爱好或心理咨询来缓解压力，改善心理状态。";
    fullTest.resultInterpretations[0] = "你的心理健康状况较差，可能存在较严重的情绪困扰或心理压力。建议尽快寻求专业心理咨询师或医生的帮助，以便及时调整和改善。";

    questionnaires[quickTest.name] = quickTest;
    questionnaires[fullTest.name] = fullTest;
}

//设置问卷选项
void MoodTest::setupQuestionnaireSelection()
{
    ui->questionnaireComboBox->clear();
    for (const QString &name : questionnaires.keys()) {
        ui->questionnaireComboBox->addItem(name);
    }
}

void MoodTest::on_startButton_clicked()
{
    currentQuestionnaire = ui->questionnaireComboBox->currentText();
    if (!questionnaires.contains(currentQuestionnaire)) {
        QMessageBox::warning(this, "错误", "请选择有效问卷");
        return;
    }

    currentQuestionIndex = 0;
    totalScore = 0;

    // 初始化进度条
    int totalQuestions = questionnaires[currentQuestionnaire].questions.size();
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    setupQuestionPage(questionnaires[currentQuestionnaire].questions[0]);
    ui->stackedWidget->setCurrentWidget(ui->questionPage);
}

void MoodTest::setupQuestionPage(const Question &question)
{
    // 清空现有选项
    QLayoutItem *child;
    while ((child = ui->optionsLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    ui->questionLabel->setText(question.text);
    ui->questionLabel->setStyleSheet(R"(
        background-color:rgba(0,0,0,0)
)");
    ui->questionLabel->setAlignment(Qt::AlignCenter);

    // 添加选项按钮
    for (const QString &option : question.options.keys()) {
        QRadioButton *radioButton = new QRadioButton(option, this);
        radioButton->setStyleSheet(R"(
            QRadioButton {
                text-align: center;
                background-color:rgba(0,0,0,0);
                font-size: 18px;
                font: 700 18pt "Songti SC";
        })");
        ui->optionsLayout->addWidget(radioButton);
    }

    // 更新导航按钮状态
    ui->nextButton->setEnabled(true);
    ui->finishButton->setEnabled(currentQuestionIndex == questionnaires[currentQuestionnaire].questions.size() - 1);

    // 更新进度显示
    int totalQuestions = questionnaires[currentQuestionnaire].questions.size();
    int progress = (currentQuestionIndex * 100) / totalQuestions;
    ui->questionCountLabel->setText(
        QString("问题 %1/%2 (进度: %3%)").arg(currentQuestionIndex + 1)
            .arg(totalQuestions)
            .arg(progress)
        );
}

void MoodTest::on_nextButton_clicked()
{
    // 获取选中的选项
    int selectedScore = -1;
    const Question &currentQuestion = questionnaires[currentQuestionnaire].questions[currentQuestionIndex];

    for (int i = 0; i < ui->optionsLayout->count(); ++i) {
        QRadioButton *radioButton = qobject_cast<QRadioButton*>(ui->optionsLayout->itemAt(i)->widget());
        if (radioButton && radioButton->isChecked()) {
            selectedScore = currentQuestion.options[radioButton->text()];
            break;
        }
    }

    if (selectedScore == -1) {
        QMessageBox::information(this, "提示", "请选择一个选项");
        return;
    }

    totalScore += selectedScore;
    ++currentQuestionIndex;

    if (currentQuestionIndex < questionnaires[currentQuestionnaire].questions.size()) {
        setupQuestionPage(questionnaires[currentQuestionnaire].questions[currentQuestionIndex]);

        // 根据题目数量更新进度条
        int totalQuestions = questionnaires[currentQuestionnaire].questions.size();
        int progress = (currentQuestionIndex * 100) / totalQuestions;
        ui->progressBar->setValue(progress);
    } else {
        // 完成所有问题
        showResult(totalScore);
    }
}

void MoodTest::on_finishButton_clicked()
{
    on_nextButton_clicked();
}

void MoodTest::showResult(int score)
{
    // 计算最终得分百分比
    int maxScore = 0;
    for (const Question &q : questionnaires[currentQuestionnaire].questions) {
        // 使用 qMax 和 foreach 遍历找到最大值
        int questionMax = 0;
        foreach (int value, q.options.values()) {
            questionMax = qMax(questionMax, value);
        }
        maxScore += questionMax;
    }

    double percentage = (double)score / maxScore * 100;

    // 查找最接近的结果解释
    QString interpretation;
    int closestScore = -1;
    int minDiff = INT_MAX;

    for (int key : questionnaires[currentQuestionnaire].resultInterpretations.keys()) {
        int diff = qAbs(key - score);
        if (diff < minDiff) {
            minDiff = diff;
            closestScore = key;
        }
    }

    if (closestScore != -1) {
        interpretation = questionnaires[currentQuestionnaire].resultInterpretations[closestScore];
    } else {
        interpretation = "测试完成，感谢参与！";
    }

    // 显示结果
    ui->resultScoreLabel->setText(QString("你的得分: %1/%2 (%3%)").arg(score).arg(maxScore).arg(percentage, 0, 'f', 1));
    ui->resultInterpretationLabel->setText(interpretation);

    // 显示建议
    QString advice;
    if (percentage >= 75) {
        advice = "你的心理状态非常健康，请继续保持规律的作息、均衡的饮食和适度的运动，同时维持良好的社交关系。";
    } else if (percentage >= 50) {
        advice = "你的心理状态良好，但可以通过一些方法进一步提升：每天留出10分钟进行冥想或深呼吸练习，培养一个能让你专注的兴趣爱好。";
    } else if (percentage >= 25) {
        advice = "你可能正在经历一定的压力或情绪波动，建议：\n1. 每天进行30分钟有氧运动\n2. 记录情绪日记，了解情绪触发因素\n3. 与信任的人分享感受";
    } else {
        advice = "你的心理状态需要特别关注，建议采取以下措施：\n1. 尽快联系专业心理咨询师进行评估\n2. 保证每天7-8小时的睡眠\n3. 避免独自承受压力，主动寻求亲友帮助";
    }

    // 修正：将建议文本设置到正确的标签
    ui->resultAdviceLabel->setText(advice);
    ui->stackedWidget->setCurrentWidget(ui->resultPage);

    //成就实现
    QFile file("data/achievement_status.json");
    QJsonObject achievementStatus;
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        achievementStatus = doc.object();
    }

    QFile file2("data/achievement_data.json");
    QJsonObject achievementData;
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data2 = file2.readAll();
        file2.close();

        QJsonDocument doc2 = QJsonDocument::fromJson(data2);
        achievementData = doc2.object();
    }

    int tmp = achievementData.value("心灵初探秘").toInt();
    tmp += 1;
    if(tmp >= 5){
        achievementStatus["心灵初探秘"] = true;
    }
    if(tmp >= 30){
        achievementStatus["心灵分析师"] = true;
    }
    achievementData["心灵初探秘"] = tmp;

    QJsonDocument doc(achievementStatus);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }

    QJsonDocument doc2(achievementData);
    if (file2.open(QIODevice::WriteOnly)) {
        file2.write(doc2.toJson());
        file2.close();
    }

}

// 添加重启按钮的点击事件处理函数
void MoodTest::on_restartButton_clicked()
{
    // 重置状态
    currentQuestionIndex = 0;
    totalScore = 0;

    // 重置进度条
    ui->progressBar->setValue(0);

    // 回到选择页面
    ui->stackedWidget->setCurrentWidget(ui->selectionPage);
}
/*void MoodTest::updateProgress()
{
    progressValue += 1;
    ui->progressBar->setValue(progressValue);

    if (progressValue >= 100) {
        progressTimer->stop();
    }
}*/

void MoodTest::on_questionnaireComboBox_currentIndexChanged(int index)
{
    QString selectedName = ui->questionnaireComboBox->itemText(index);
    if (questionnaires.contains(selectedName)) {
        ui->questionnaireDescLabel->setText(questionnaires[selectedName].description);
    }
}
