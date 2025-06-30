#ifndef AICHAT_H
#define AICHAT_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QThread>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include <QWidget>

class WorkerThread : public QThread {
    Q_OBJECT
public:
    explicit WorkerThread(const QJsonArray& history,
                          const QString& apiKey,
                          const QString& model,
                          double temperature,
                          int maxTokens,
                          QObject* parent = nullptr);
    void run() override;

signals:
    void responseReceived(const QString& response);

private:
    QJsonArray m_history;
    QString m_apiKey;
    QString m_model;
    double m_temperature;
    int m_maxTokens;
};

namespace Ui {
    class AIChat;
}

class AIChat : public QWidget{
    Q_OBJECT

public:
    explicit AIChat(QWidget *parent = nullptr);
    ~AIChat();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void sendMessage();
    void handleResponse(const QString& response);
    void updateAssistantSettings();

private:
    void createUI();
    void loadConfig();
    void loadChatHistory();
    void saveChatHistory();
    QString getProjectRoot();
    QString findConfigFile();
    void applyStyle();

    /*// UI控件
    QTextEdit *m_chatDisplay;
    QLineEdit *m_inputBox;
    QPushButton *m_sendButton;
    QPushButton *m_settingsButton;
    QLabel *m_loadingLabel;
    QLabel *m_cartoonLabel;
    QLabel *m_assistantNameLabel;*/

    // 头像相关
    QLabel *m_userAvatar;
    QLabel *m_assistantAvatar;

    // 网络管理
    QNetworkAccessManager *m_networkManager;

    // 数据
    QJsonArray m_history;
    QString m_apiKey;
    QString m_model;
    double m_temperature;
    int m_maxTokens;
    QString m_assistantName;
    QString m_assistantAvatarPath;
    QString m_cartoonPath;
    Ui::AIChat *ui;

};

#endif // AICHAT_H
