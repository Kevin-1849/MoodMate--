#include "aichat.h"
#include "ui_aichat.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QTimer>
#include <QScrollBar>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <QKeyEvent>
#include <QInputDialog>
#include <QFileDialog>

/*AIChat::AIChat(QWidget *parent) :
    QDialog(parent),
    m_networkManager(new QNetworkAccessManager(this))
{
    // 设置对话框属性
    setWindowTitle("AI心理助手");
    setMinimumSize(900, 650);

    // 创建UI
    createUI();
    qDebug() << 1;
    // 加载配置
    loadConfig();
    qDebug() << 2;
    // 应用样式
    applyStyle();
    qDebug() << 3;
    // 连接信号槽
    connect(m_sendButton, &QPushButton::clicked, this, &AIChat::sendMessage);
    connect(m_inputBox, &QLineEdit::returnPressed, this, &AIChat::sendMessage);
    connect(m_settingsButton, &QPushButton::clicked, this, &AIChat::updateAssistantSettings);
    qDebug() << 4;
    // 加载历史记录
    loadChatHistory();
    qDebug() << 5;
}*/

AIChat::AIChat(QWidget *parent)
    : QWidget(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , ui(new Ui::AIChat)
{
    ui->setupUi(this);
    loadConfig();
    connect(ui->m_sendButton, &QPushButton::clicked, this, &AIChat::sendMessage);
    connect(ui->m_inputBox, &QLineEdit::returnPressed, this, &AIChat::sendMessage);
    //connect(uim_settingsButton, &QPushButton::clicked, this, &AIChat::updateAssistantSettings);
    //loadChatHistory();
}

/*AIChat::~AIChat()
{
    delete ui;
}*/

/*void AIChat::createUI() {
    // 主布局 - 水平布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // ============ 左侧卡通形象区域 ============
    QFrame *leftPanel = new QFrame(this);
    leftPanel->setFixedWidth(180);
    leftPanel->setObjectName("leftPanel");

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    leftLayout->setSpacing(20);
    leftLayout->setContentsMargins(10, 20, 10, 20);

    // 卡通形象标签
    //m_cartoonLabel = new QLabel(this);
    //m_cartoonLabel->setFixedSize(150, 150);
    m_cartoonLabel->setAlignment(Qt::AlignCenter);
    m_cartoonLabel->setObjectName("cartoonLabel");
    leftLayout->addWidget(m_cartoonLabel);

    // 助手名称标签
    m_assistantNameLabel = new QLabel(this);
    m_assistantNameLabel->setAlignment(Qt::AlignCenter);
    m_assistantNameLabel->setObjectName("assistantName");
    leftLayout->addWidget(m_assistantNameLabel);

    // 状态标签
    QLabel *statusLabel = new QLabel("在线", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setObjectName("statusLabel");
    leftLayout->addWidget(statusLabel);

    // 设置按钮
    m_settingsButton = new QPushButton("设置助手", this);
    m_settingsButton->setObjectName("settingsButton");
    leftLayout->addWidget(m_settingsButton);

    leftLayout->addStretch();
    mainLayout->addWidget(leftPanel);

    // ============ 右侧聊天区域 ============
    QFrame *chatFrame = new QFrame(this);
    chatFrame->setObjectName("chatFrame");

    QVBoxLayout *chatLayout = new QVBoxLayout(chatFrame);
    chatLayout->setSpacing(15);
    chatLayout->setContentsMargins(15, 15, 15, 15);

    // 聊天显示区域
    m_chatDisplay = new QTextEdit(this);
    m_chatDisplay->setReadOnly(true);
    m_chatDisplay->setObjectName("chatDisplay");
    chatLayout->addWidget(m_chatDisplay, 1);

    // 输入区域布局
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->setSpacing(10);

    // 用户头像
    m_userAvatar = new QLabel(this);
    m_userAvatar->setFixedSize(40, 40);
    m_userAvatar->setObjectName("userAvatar");
    inputLayout->addWidget(m_userAvatar);

    // 输入框
    m_inputBox = new QLineEdit(this);
    m_inputBox->setPlaceholderText("输入消息...");
    m_inputBox->setObjectName("inputBox");
    inputLayout->addWidget(m_inputBox, 1);

    // 发送按钮
    m_sendButton = new QPushButton("发送", this);
    m_sendButton->setObjectName("sendButton");
    inputLayout->addWidget(m_sendButton);

    chatLayout->addLayout(inputLayout);

    // 助手头像（用于消息显示）
    m_assistantAvatar = new QLabel(this);
    m_assistantAvatar->setFixedSize(40, 40);
    m_assistantAvatar->setObjectName("assistantAvatar");

    // 已移除加载动画标签

    mainLayout->addWidget(chatFrame, 1);

    // 设置布局
    setLayout(mainLayout);
}*/

/*void AIChat::applyStyle() {
    // 使用内置样式表
    setStyleSheet(R"(
        /* 主窗口样式
        QDialog {
            background-color: #f5f7fa;
            font-family: 'Microsoft YaHei', 'Segoe UI', sans-serif;
        }

        /* 左侧面板 *
        #leftPanel {
            background: linear-gradient(135deg, #e3f2fd, #bbdefb);
            border-radius: 20px;
            //box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
        }

        /* 卡通形象标签
        #cartoonLabel {
            border: 3px solid #90caf9;
            border-radius: 50%;
            background-color: white;
            padding: 10px;
            //box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
        }

        /* 助手名称
        #assistantName {
            font-size: 20px;
            font-weight: bold;
            color: #1565c0;
            //text-shadow: 0 1px 2px rgba(0, 0, 0, 0.1);
        }

        /* 状态标签
        #statusLabel {
            font-size: 14px;
            font-weight: bold;
            color: #43a047;
            background-color: #e8f5e9;
            border-radius: 15px;
            padding: 5px 15px;
            //box-shadow: 0 2px 4px rgba(0, 0, 0, 0.05);
        }

        /* 设置按钮
        #settingsButton {
            background: linear-gradient(to right, #64b5f6, #42a5f5);
            color: white;
            border-radius: 20px;
            padding: 10px;
            font-size: 16px;
            font-weight: bold;
            border: none;
            //box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }

        #settingsButton:hover {
            background: linear-gradient(to right, #42a5f5, #2196f3);
        }

        #settingsButton:disabled {
            background: linear-gradient(to right, #a0aec0, #718096);
        }

        /* 聊天区域
        #chatFrame {
            background-color: white;
            border-radius: 20px;
            //box-shadow: 0 4px 12px rgba(0, 0, 0, 0.08);
        }

        /* 聊天显示区域
        #chatDisplay {
            background-color: #f8f9fa;
            border-radius: 15px;
            padding: 15px;
            font-size: 14px;
            border: 1px solid #e0e7ff;
            line-height: 1.6;
        }

        /* 输入框
        #inputBox {
            background-color: #f0f4f8;
            border: 2px solid #c5d9f1;
            border-radius: 25px;
            padding: 12px 20px;
            font-size: 14px;
            color: #2d3748;
        }

        #inputBox:focus {
            border: 2px solid #64b5f6;
            //box-shadow: 0 0 0 3px rgba(100, 181, 246, 0.2);
        }

        /* 发送按钮
        #sendButton {
            background: linear-gradient(to right, #4e73df, #2e59d9);
            color: white;
            border-radius: 25px;
            padding: 12px 25px;
            font-size: 16px;
            font-weight: bold;
            border: none;
            //box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }

        #sendButton:hover {
            background: linear-gradient(to right, #2e59d9, #1a3faa);
        }

        #sendButton:disabled {
            background: linear-gradient(to right, #a0aec0, #718096);
        }

        /* 头像样式
        #userAvatar, #assistantAvatar {
            border-radius: 50%;
            border: 2px solid #bbdefb;
            background-color: white;
            padding: 2px;
            //box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }
    )");
}*/

void AIChat::loadConfig() {
    QString configPath = findConfigFile();
    qDebug() << "Using config file:" << configPath;

    QSettings settings(configPath, QSettings::IniFormat);

    // API 配置
    settings.beginGroup("API");
    m_apiKey = settings.value("KEY").toString();
    m_model = settings.value("MODEL", "deepseek-chat").toString();
    m_temperature = settings.value("TEMPERATURE", 0.7).toDouble();
    m_maxTokens = settings.value("MAX_TOKENS", 500).toInt();
    settings.endGroup();

    // 助手配置
    settings.beginGroup("Assistant");
    m_assistantName = settings.value("NAME", "小安助手").toString();
    m_assistantAvatarPath = settings.value("AVATAR", ":/icon/assistant_avatar.png").toString();
    m_cartoonPath = settings.value("CARTOON", ":/icon/assistant_cartoon.jpg").toString(); // 改为静态图片
    settings.endGroup();

    // 更新UI
    ui->m_assistantNameLabel->setText(m_assistantName);

    // 加载卡通形象（使用静态图片）
    QPixmap pixmap(m_cartoonPath);
    if (!pixmap.isNull()) {
        ui->m_cartoonLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // 加载头像
    QPixmap assistantPixmap(m_assistantAvatarPath);
    if (!assistantPixmap.isNull()) {
        m_assistantAvatar->setPixmap(assistantPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // 加载用户头像（固定）
    QPixmap userPixmap(":/icon/user_avatar.jpg");
    if (!userPixmap.isNull()) {
        ui->m_userAvatar->setPixmap(userPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // 已移除加载动画初始化
}

void AIChat::updateAssistantSettings() {
    // 输入助手新名字
    bool ok;
    QString newName = QInputDialog::getText(this, "修改助手名称",
                                            "请输入新的助手名称:",
                                            QLineEdit::Normal,
                                            m_assistantName,
                                            &ok);

    if (ok && !newName.isEmpty()) {
        m_assistantName = newName;
        ui->m_assistantNameLabel->setText(newName);

        // 保存到配置文件
        QString configPath = findConfigFile();
        QSettings settings(configPath, QSettings::IniFormat);
        settings.beginGroup("Assistant");
        settings.setValue("NAME", newName);
        settings.endGroup();
    }

    // 选择新头像
    QString newAvatar = QFileDialog::getOpenFileName(this, "选择助手头像",
                                                     "",
                                                     "图像文件 (*.png *.jpg *.jpeg)");
    if (!newAvatar.isEmpty()) {
        m_assistantAvatarPath = newAvatar;
        QPixmap pixmap(newAvatar);
        if (!pixmap.isNull()) {
            m_assistantAvatar->setPixmap(pixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

            // 保存到配置文件
            QString configPath = findConfigFile();
            QSettings settings(configPath, QSettings::IniFormat);
            settings.beginGroup("Assistant");
            settings.setValue("AVATAR", newAvatar);
            settings.endGroup();
        }
    }
}

QString AIChat::getProjectRoot() {
    // 获取应用程序目录
    QString appDir = QCoreApplication::applicationDirPath();

    // 向上查找项目根目录
    QDir dir(appDir);
    while (!dir.isRoot()) {
        if (dir.exists("CMakeLists.txt") ||
            dir.exists("MoodMate.pro") ||
            dir.exists("README.md")) {
            return dir.absolutePath();
        }
        if (!dir.cdUp()) break;
    }

    return appDir;
}

QString AIChat::findConfigFile() {
    QString projectRoot = getProjectRoot();
    QStringList possiblePaths;

    // 可能的配置文件位置
    possiblePaths << projectRoot + "/config.ini"
                  << QCoreApplication::applicationDirPath() + "/config.ini"
                  << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/MoodMate/config.ini"
                  << QDir::currentPath() + "/config.ini"
                  << QDir::homePath() + "/MoodMate/config.ini";

    // 检查每个路径是否存在
    for (const QString &path : possiblePaths) {
        if (QFile::exists(path)) {
            return path;
        }
    }

    // 如果都找不到，在项目根目录创建默认配置文件
    QString defaultPath = projectRoot + "/config.ini";
    QDir().mkpath(QFileInfo(defaultPath).absolutePath());

    QSettings settings(defaultPath, QSettings::IniFormat);
    settings.beginGroup("API");
    settings.setValue("KEY", "your-api-key-here");
    settings.setValue("MODEL", "deepseek-chat");
    settings.setValue("TEMPERATURE", 0.7);
    settings.setValue("MAX_TOKENS", 500);
    settings.endGroup();

    settings.beginGroup("Assistant");
    settings.setValue("NAME", "小安助手");
    settings.setValue("AVATAR", ":/icon/assistant_avatar.png");
    settings.setValue("CARTOON", ":/icon/assistant_cartoon.png"); // 改为静态图片
    settings.endGroup();

    return defaultPath;
}

void AIChat::loadChatHistory() {
    QFile file("chat_history.json");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isArray()) {
            m_history = doc.array();

            // 在UI中显示历史消息
            for (const QJsonValue &value : m_history) {
                QJsonObject obj = value.toObject();
                QString role = obj["role"].toString();
                QString content = obj["content"].toString();
                QString timestamp = QDateTime::fromString(obj["timestamp"].toString(), Qt::ISODate).toString("hh:mm");

                if (role == "user") {
                    QString userMsgHtml = QString(
                                              "<div style='margin:15px 0;'>"
                                              "   <div style='display:flex; justify-content:flex-end; align-items:flex-end;'>"
                                              "       <div style='max-width:80%%; background-color:#e3f2fd; border-radius:15px 15px 0 15px; padding:10px 15px;'>"
                                              "           <div style='font-size:14px;'>%2</div>"
                                              "           <div style='font-size:10px; color:#78909c; text-align:right; margin-top:5px;'>%1</div>"
                                              "       </div>"
                                              "       <img src=':/icons/user_avatar.png' style='width:32px; height:32px; border-radius:50%%; margin-left:10px;'/>"
                                              "   </div>"
                                              "</div>"
                                              ).arg(timestamp, content);

                    ui->m_chatDisplay->append(userMsgHtml);
                } else if (role == "assistant") {
                    QString aiMsgHtml = QString(
                                            "<div style='margin:15px 0;'>"
                                            "   <div style='display:flex; justify-content:flex-start; align-items:flex-end;'>"
                                            "       <img src='%3' style='width:32px; height:32px; border-radius:50%%; margin-right:10px;'/>"
                                            "       <div style='max-width:80%%; background-color:#f5f5f5; border-radius:15px 15px 15px 0; padding:10px 15px;'>"
                                            "           <div style='font-size:14px;'>%2</div>"
                                            "           <div style='font-size:10px; color:#78909c; text-align:left; margin-top:5px;'>%4 · %1</div>"
                                            "       </div>"
                                            "   </div>"
                                            "</div>"
                                            ).arg(timestamp, content, m_assistantAvatarPath, m_assistantName);

                    ui->m_chatDisplay->append(aiMsgHtml);
                }
            }

            // 滚动到底部
            ui->m_chatDisplay->verticalScrollBar()->setValue(ui->m_chatDisplay->verticalScrollBar()->maximum());
            //scrollbar->setValue(scrollbar->maximum());
        }
        file.close();
    }
}

void AIChat::sendMessage() {
    QString userInput = ui->m_inputBox->text().trimmed();
    if (userInput.isEmpty()) return;

    // 获取当前时间
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm");

    // 显示用户消息
    QString userMsgHtml = QString(
                              "<div style='margin:15px 0;'>"
                              "   <div style='display:flex; justify-content:flex-end; align-items:flex-end;'>"
                              "       <div style='max-width:80%%; background-color:#e3f2fd; border-radius:15px 15px 0 15px; padding:10px 15px;'>"
                              "           <div style='font-size:14px;'>%2</div>"
                              "           <div style='font-size:10px; color:#78909c; text-align:right; margin-top:5px;'>%1</div>"
                              "       </div>"
                              "       <img src=':/icons/user_avatar.png' style='width:32px; height:32px; border-radius:50%%; margin-left:10px;'/>"
                              "   </div>"
                              "</div>"
                              ).arg(timestamp, userInput);

    ui->m_chatDisplay->append(userMsgHtml);
    ui->m_inputBox->clear();

    // 添加到历史
    QJsonObject userMsg;
    userMsg["role"] = "user";
    userMsg["content"] = userInput;
    userMsg["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    m_history.append(userMsg);

    // 禁用控件（不再显示加载动画）
    ui->m_sendButton->setEnabled(false);
    ui->m_inputBox->setEnabled(false);
    //qDebug() << "?";
    // 启动工作线程
    WorkerThread *worker = new WorkerThread(m_history, m_apiKey, m_model, m_temperature, m_maxTokens);
    connect(worker, &WorkerThread::responseReceived, this, &AIChat::handleResponse);
    connect(worker, &WorkerThread::finished, worker, &QObject::deleteLater);
    worker->start();
}

void AIChat::handleResponse(const QString& response) {
    // 获取当前时间
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm");

    // 显示AI回复
    QString aiMsgHtml = QString(
                            "<div style='margin:15px 0;'>"
                            "   <div style='display:flex; justify-content:flex-start; align-items:flex-end;'>"
                            "       <img src='%3' style='width:32px; height:32px; border-radius:50%%; margin-right:10px;'/>"
                            "       <div style='max-width:80%%; background-color:#f5f5f5; border-radius:15px 15px 15px 0; padding:10px 15px;'>"
                            "           <div style='font-size:14px;'>%2</div>"
                            "           <div style='font-size:10px; color:#78909c; text-align:left; margin-top:5px;'>%4 · %1</div>"
                            "       </div>"
                            "   </div>"
                            "</div>"
                            ).arg(timestamp, response, m_assistantAvatarPath, m_assistantName);

    ui->m_chatDisplay->append(aiMsgHtml);

    // 添加到历史
    if (!response.startsWith("错误：")) {
        QJsonObject aiMsg;
        aiMsg["role"] = "assistant";
        aiMsg["content"] = response;
        aiMsg["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
        m_history.append(aiMsg);
    }

    // 启用控件
    ui->m_sendButton->setEnabled(true);
    ui->m_inputBox->setEnabled(true);
    ui->m_inputBox->setFocus();

    // 自动滚动到底部
    QScrollBar *scrollbar = ui->m_chatDisplay->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());

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

    int tmp = achievementData.value("心语初相识").toInt();
    tmp += 1;
    if(tmp >= 5){
        achievementStatus["心语初相识"] = true;
    }
    if(tmp >= 30){
        achievementStatus["心灵树洞王"] = true;
    }
    achievementData["图表解读者"] = tmp;

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

    // 保存历史记录
    //saveChatHistory();
}

void AIChat::saveChatHistory() {
    // 限制历史记录长度（保留最近20条）
    if (m_history.size() > 20) {
        QJsonArray recentHistory;
        for (int i = m_history.size() - 20; i < m_history.size(); i++) {
            recentHistory.append(m_history.at(i));
        }
        m_history = recentHistory;
    }

    QFile file("chat_history.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(m_history).toJson());
        file.close();
    }
}

void AIChat::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // 检查焦点是否在输入框上
        if (ui->m_inputBox->hasFocus()) {
            sendMessage(); // 发送消息
            event->accept(); // 标记事件已处理
            return;
        }
    }

    // 其他按键事件交给基类处理
    QWidget::keyPressEvent(event);
}

void AIChat::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
}

AIChat::~AIChat() {
    saveChatHistory();
}

// WorkerThread 实现
WorkerThread::WorkerThread(const QJsonArray& history,
                           const QString& apiKey,
                           const QString& model,
                           double temperature,
                           int maxTokens,
                           QObject* parent)
    : QThread(parent),
    m_history(history),
    m_apiKey(apiKey),
    m_model(model),
    m_temperature(temperature),
    m_maxTokens(maxTokens) {}

void WorkerThread::run() {
    QNetworkAccessManager manager;
    QEventLoop loop;

    QNetworkRequest request(QUrl("https://api.deepseek.com/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_apiKey).toUtf8());

    QJsonObject body;
    body["model"] = m_model;
    body["temperature"] = m_temperature;
    body["max_tokens"] = m_maxTokens;
    body["messages"] = m_history;

    QByteArray requestData = QJsonDocument(body).toJson();
    QNetworkReply *reply = manager.post(request, requestData);

    qDebug() << "Request URL:" << request.url().toString();
    qDebug() << "Request body:" << QString(requestData);

    // 超时处理
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start(60000);

    //loop.exec();

    QString result;
    if (timer.isActive()) {
        timer.stop();
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray replyData = reply->readAll();
            qDebug() << "API Response:" << replyData;  // 打印响应内容
            qDebug() << "HTTP status code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            QJsonDocument doc = QJsonDocument::fromJson(replyData);
            if (doc.isObject()) {
                QJsonObject obj = doc.object();

                if (obj.contains("error")) {
                    QJsonObject error = obj["error"].toObject();
                    result = "API错误：" + error["message"].toString();
                }
                else if (obj.contains("choices")) {
                    QJsonArray choices = obj["choices"].toArray();
                    if (!choices.isEmpty()) {
                        result = choices[0].toObject()["message"].toObject()["content"].toString();
                    } else {
                        result = "错误：API返回空响应";
                    }
                } else {
                    result = "错误：API返回格式异常";
                }
            } else {
                result = "错误：无法解析API响应";
            }
        } else {
            if (reply->error() == QNetworkReply::AuthenticationRequiredError) {
               result = "错误：API密钥无效";
            } else {
                result = "网络错误：" + reply->errorString();
            }
        }
    } else {
        reply->abort();
        result = "错误：请求超时，请检查网络连接";
    }
    emit responseReceived(result);

}
