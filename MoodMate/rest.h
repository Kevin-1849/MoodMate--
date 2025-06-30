#ifndef REST_H
#define REST_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QSlider>
#include <QStyleOption>
#include <QPainter>
#include <QTime>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Rest; }
QT_END_NAMESPACE

// 呼吸动画组件
class BreathAnimation : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius WRITE setRadius)
    Q_PROPERTY(QColor circleColor READ circleColor WRITE setCircleColor)

public:
    BreathAnimation(QWidget *parent = nullptr);
    qreal radius() const;
    QColor circleColor() const;
    void setRadius(qreal radius);
    void setCircleColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal m_radius = 50;
    QColor m_circleColor = Qt::lightGray;
};

class Rest : public QWidget
{
    Q_OBJECT

public:
    Rest(QWidget *parent = nullptr);
    ~Rest();

private slots:
    void on_musicTypeComboBox_3_currentIndexChanged(int index);
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();
    void on_countdownSlider_valueChanged(int value);
    void updateCountdown();
    void on_breathSpeedSlider_valueChanged(int value);
    void on_bedtimeModeCheckBox_toggled(bool checked);

private:
    Ui::Rest *ui;
    QMediaPlayer *musicPlayer;
    QMediaPlayer *guidePlayer;//未使用
    QAudioOutput *musicAudioOutput;
    QAudioOutput *guideAudioOutput;//未使用
    QTimer *countdownTimer;
    QPropertyAnimation *breathAnimation;
    int remainingTime;
    int breathSpeed;
    bool isPlaying;
    bool isBedtimeMode;

    void setupAudioPlayers();
    void setupBreathAnimation();
    void setupCountdown();
    void startBreathAnimation();
    void stopBreathAnimation();
};

#endif // REST_H
