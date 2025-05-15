#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QStringList>
#include <QString>

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private slots:
    void on_DiaryButton_clicked();

//切换页面
    void on_TestButton_clicked();

    void on_RestButton_clicked();

    void on_ChatPage_clicked();

signals:
    void requestSwitchToDiaryPage();
    void requestSwitchToTestPage();
    void requestSwitchToChatPage();
    void requestSwitchToRestPage();

private:
    Ui::HomePage *ui;
    QStringList sentenceSet = {
        "每一个不曾起舞的日子都是对生命的辜负  ——尼采",
        "我的热情，一如盲者，不惧黑暗  ——与谢野晶子",
        "我会继续探寻，尽管漫天星辰让我迷失方向，即使我将单枪匹马 ——艾萨克.阿西莫夫",
        "我所热切渴望的，不过是活一次，将那自发的自我抛向世界，与之相联，或与之抗争 ——黑塞",
        "信念是鸟，它在黎明仍然黑暗之际，感觉到了光明，唱出了歌。——泰戈尔《飞鸟集》",
        "有些鸟儿注定是关不住的，它们的每一片羽毛都闪耀着自由的光辉。——肖申克的救赎",
        "强者自救，圣者渡人。——肖申克的救赎",
        "让灵魂从婴儿做起，像童年那样，咬着铅笔，对世界报以纯真，好奇和汹涌的爱意 ——王开岭",
        "只有流过血的手指，才能弹出世间的绝唱。——泰戈尔",
        "我将不停地行走，这是我自己的歌吟与诗篇 ——叶芝",
        "诗不求工字不奇，天真烂漫是吾师。——苏轼",
        "只有用水将心上的雾气淘洗干净，荣光才会照亮最初的梦想 ——马尔克斯",
        "如果你独处时感到寂寞，这说明你没有和自己成为好朋友 ——萨特",
        "怕什么真理无穷，进一寸有进一寸的欢喜 ——胡适",
        "人生的意义也许永远没有答案，但也要尽情享受没有答案的人生 ——伍尔芙",
        "人不是插在花瓶中的静物，而是草原上飞扬的韵律 ——伍尔芙",
        "世界上只有一种英雄主义，那就是看清生活的真相之后，依然热爱生活。——罗曼罗兰",
        "无论风暴将我带到什么岸边，我都将以主人的身份上岸——贺拉斯"
    };//每日一句集
};

#endif // HOMEPAGE_H
