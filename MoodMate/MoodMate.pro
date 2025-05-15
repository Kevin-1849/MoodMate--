QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achievement.cpp \
    aichat.cpp \
    editpage.cpp \
    emojicalendarwidget.cpp \
    homepage.cpp \
    main.cpp \
    mainwindow.cpp \
    moodchart.cpp \
    mooddiary.cpp \
    moodtest.cpp \
    rest.cpp

HEADERS += \
    achievement.h \
    aichat.h \
    editpage.h \
    emojicalendarwidget.h \
    homepage.h \
    mainwindow.h \
    moodchart.h \
    mooddiary.h \
    moodtest.h \
    rest.h

FORMS += \
    achievement.ui \
    aichat.ui \
    editpage.ui \
    homepage.ui \
    mainwindow.ui \
    moodchart.ui \
    mooddiary.ui \
    moodtest.ui \
    rest.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
