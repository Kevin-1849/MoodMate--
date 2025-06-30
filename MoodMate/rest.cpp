#include "rest.h"
#include "ui_rest.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QPainterPath>
#include <QAudioOutput>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QJsonObject>
#include <QJsonArray>

// 呼吸动画组件实现
BreathAnimation::BreathAnimation(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
    setMaximumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void BreathAnimation::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    opt.palette = palette();
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QRectF rect = contentsRect();
    qreal centerX = rect.center().x();
    qreal centerY = rect.center().y();
    qreal diameter = qMin(rect.width(), rect.height()) * 0.8;

    QPainterPath path;
    path.addEllipse(centerX - m_radius, centerY - m_radius,
                    2 * m_radius, 2 * m_radius);

    QPen pen(m_circleColor, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen);
    p.drawPath(path);
}

qreal BreathAnimation::radius() const { return m_radius; }
QColor BreathAnimation::circleColor() const { return m_circleColor; }
void BreathAnimation::setRadius(qreal radius) { m_radius = radius; update(); }
void BreathAnimation::setCircleColor(const QColor &color) { m_circleColor = color; update(); }


// Rest 类实现
Rest::Rest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Rest)
    , musicPlayer(nullptr)
    , guidePlayer(nullptr)
    , musicAudioOutput(nullptr)
    , guideAudioOutput(nullptr)
    , countdownTimer(nullptr)
    , breathAnimation(nullptr)
    , remainingTime(0)
    , breathSpeed(2000)
    , isPlaying(false)
    , isBedtimeMode(false)
{
    ui->setupUi(this);
    qDebug() << ui->musicTypeComboBox_3->metaObject()->className();

    // 初始化组件
    setupAudioPlayers();
    setupBreathAnimation();
    setupCountdown();

    // 连接信号与槽
    connect(ui->musicTypeComboBox_3, SIGNAL(currentIndexChanged(int)),
                             this, SLOT(on_musicTypeComboBox_3_currentIndexChanged(int)));

    connect(ui->playButton, &QPushButton::clicked, this, &Rest::on_playButton_clicked);
    connect(ui->pauseButton, &QPushButton::clicked, this, &Rest::on_pauseButton_clicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &Rest::on_stopButton_clicked);
    connect(ui->countdownSlider, &QSlider::valueChanged,
            this, &Rest::on_countdownSlider_valueChanged);
    connect(ui->breathSpeedSlider, &QSlider::valueChanged,
            this, &Rest::on_breathSpeedSlider_valueChanged);
    connect(ui->bedtimeModeCheckBox, &QCheckBox::toggled,
            this, &Rest::on_bedtimeModeCheckBox_toggled);
}

Rest::~Rest()
{
    delete ui;
    delete musicPlayer;
    delete guidePlayer;
    delete musicAudioOutput;
    delete guideAudioOutput;
    delete countdownTimer;
    delete breathAnimation;
}

void Rest::setupAudioPlayers()
{
    // 创建音频输出对象
    musicPlayer = new QMediaPlayer(this);
    guidePlayer = new QMediaPlayer(this);
    musicAudioOutput = new QAudioOutput(this);
    guideAudioOutput = new QAudioOutput(this);

    // 设置音量（0.0-1.0）
    musicAudioOutput->setVolume(0.5);
    guideAudioOutput->setVolume(0.3);

    // 关联音频输出
    musicPlayer->setAudioOutput(musicAudioOutput);
    guidePlayer->setAudioOutput(guideAudioOutput);
}

void Rest::setupBreathAnimation()
{
    // 创建呼吸动画组件
    BreathAnimation *breathWidget = new BreathAnimation(this);
    breathWidget->setCircleColor(QColor(0, 128, 0)); // 使用一种深绿色，使得颜色与浅绿色背景搭配
    //breathWidget->setCircleFill(true);  // 设置圆为实心

    /*// 添加到UI布局（确保animationLayout存在）
    if (ui->animationLayout) {
        ui->animationLayout->addWidget(breathWidget);
    } else {
        qDebug() << "警告: 未找到animationLayout，使用默认布局";

        // 替代方案：使用QWidget的默认布局（QVBoxLayout）
        QVBoxLayout *defaultLayout = new QVBoxLayout(this);
        defaultLayout->addWidget(breathWidget);
        defaultLayout->setAlignment(breathWidget, Qt::AlignCenter);
    }*/

    ui->layout->addWidget(breathWidget);

    // 创建属性动画
    breathAnimation = new QPropertyAnimation(breathWidget, "radius");
    breathAnimation->setDuration(breathSpeed / 2);
    breathAnimation->setStartValue(30);
    breathAnimation->setEndValue(80);
    breathAnimation->setLoopCount(-1);
}

void Rest::setupCountdown()
{
    // 初始化倒计时
    countdownTimer = new QTimer(this);
    countdownTimer->setInterval(1000);
    connect(countdownTimer, &QTimer::timeout, this, &Rest::updateCountdown);

    // 初始设置为5分钟
    ui->countdownSlider->setValue(5);
    on_countdownSlider_valueChanged(5);

}

void Rest::on_musicTypeComboBox_3_currentIndexChanged(int index)
{
    if (!isPlaying) return;


    // 停止当前播放
    musicPlayer->stop();

    // 加载新音频
    QString musicPath;
    switch (index) {
    case 0: musicPath = "/Users/yukaiwen/Desktop/ocean.mp3"; break;
    case 1: musicPath = "/Users/yukaiwen/Desktop/rain.mp3"; break;
    case 2: musicPath = "/Users/yukaiwen/Desktop/windbell.mp3"; break;
    case 3: musicPath = "/Users/yukaiwen/Desktop/soft_bgm.mp3"; break;
    default: musicPath = "/Users/yukaiwen/Desktop/ocean.mp3";
    }

    musicPlayer->setSource(QUrl::fromLocalFile(musicPath));

    musicPlayer->play();
}

void Rest::on_playButton_clicked()
{
    isPlaying = true;

    // 加载并播放音乐
    int index = ui->musicTypeComboBox_3->currentIndex();
    QString musicPath;
    switch (index) {
    case 0: musicPath = "/Users/yukaiwen/Desktop/ocean.mp3"; break;
    case 1: musicPath = "/Users/yukaiwen/Desktop/rain.mp3"; break;
    case 2: musicPath = "/Users/yukaiwen/Desktop/windbell.mp3"; break;
    case 3: musicPath = "/Users/yukaiwen/Desktop/soft_bgm.mp3"; break;
    default: musicPath = "/Users/yukaiwen/Desktop/ocean.mp3";
    }

    musicPlayer->setSource(QUrl::fromLocalFile(musicPath));
    musicPlayer->play();

    //QMediaPlayer::State state = musicPlayer->state();
    //qDebug() << "Player state:" << state;

    // 播放引导语音
    /*if (ui->guideVoiceCheckBox->isChecked()) {
        guidePlayer->setSource(QUrl(":/sounds/guide_voice.wav"));
        guidePlayer->play();
    }*/

    // 启动动画和倒计时
    startBreathAnimation();
    remainingTime = ui->countdownSlider->value() * 60;
    countdownTimer->start();

    // 更新按钮状态
    ui->playButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    ui->stopButton->setEnabled(true);

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

    QJsonArray favoriteArray = achievementData.value("白噪音收藏夹").toArray();
    favoriteArray[index] = 1;
    int tmp = 0;

    for(int i = 0; i < 4; ++i){
        tmp += favoriteArray[i].toInt();
    }

    if(tmp == 4){
        achievementStatus["白噪音收藏夹"] = true;
    }
    achievementData["白噪音收藏夹"] = favoriteArray;

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

void Rest::on_pauseButton_clicked()
{
    isPlaying = false;

    // 暂停播放
    musicPlayer->pause();
    guidePlayer->pause();

    // 暂停动画和倒计时
    breathAnimation->pause();
    countdownTimer->stop();

    // 更新按钮状态
    ui->playButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void Rest::on_stopButton_clicked()
{
    isPlaying = false;

    // 停止播放
    musicPlayer->stop();
    guidePlayer->stop();

    // 停止动画和倒计时
    stopBreathAnimation();
    countdownTimer->stop();

    // 重置时间
    ui->timeLabel->setText("00:00");

    // 更新按钮状态
    ui->playButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    // 睡前模式处理
    /*if (isBedtimeMode) {
        close();
    }*/
}

void Rest::on_countdownSlider_valueChanged(int value)
{
    ui->countdownLabel->setText(QString("倒计时: %1 分钟").arg(value));
    if (isPlaying) {
        remainingTime = value * 60;
    }
}

void Rest::updateCountdown()
{
    remainingTime--;
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    ui->timeLabel->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0'))
                               .arg(seconds, 2, 10, QChar('0')));

    // 倒计时结束
    if (remainingTime <= 0) {
        //on_stopButton_clicked();
        //QMessageBox::information(this, "休息完成", "你的休息时间到了！");

        // 睡前模式延迟关闭
        if (isBedtimeMode) {
            on_stopButton_clicked();
            //QTimer::singleShot(5000, this, &Rest::close);
        }
        else{
            on_stopButton_clicked();
            QMessageBox::information(this, "休息完成", "你的休息时间到了！");
        }
    }
}

void Rest::on_breathSpeedSlider_valueChanged(int value)
{
    breathSpeed = 1000 + value * 1000;
    breathAnimation->setDuration(breathSpeed / 2);

    if (isPlaying) {
        startBreathAnimation();
    }
}

void Rest::on_bedtimeModeCheckBox_toggled(bool checked)
{
    isBedtimeMode = checked;
    if (checked) {
        ui->countdownSlider->setValue(15);
        on_countdownSlider_valueChanged(15);
    }
}

void Rest::startBreathAnimation()
{
    breathAnimation->start();

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

    if(remainingTime >= 300){
        achievementStatus["冥想初体验"] = true;
    }

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

void Rest::stopBreathAnimation()
{
    breathAnimation->stop();
    /*if (BreathAnimation *breathWidget = qobject_cast<BreathAnimation*>(ui->animationLayout->itemAt(0)->widget())) {
        breathWidget->setRadius(30);
    }*/
}
