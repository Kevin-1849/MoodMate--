#include "mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 切换到上上上级目录（即项目目录）
    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp(); // Contents
    dir.cdUp(); // MoodMate.app
    dir.cdUp(); // Debug
    dir.cdUp(); // build
    dir.cdUp(); // MoodMate ← 项目目录
    QDir::setCurrent(dir.absolutePath());

    // 测试输出
    //qDebug() << "Working directory manually set to:" << QDir::currentPath();

    MainWindow w;
    w.show();

    return a.exec();

}
