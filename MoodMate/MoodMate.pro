QT += core gui network
QT += multimedia
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achievement.cpp \
    achievementitem.cpp \
    aichat.cpp \
    emojicalendarwidget.cpp \
    homepage.cpp \
    main.cpp \
    mainwindow.cpp \
    moodchart.cpp \
    mooddata.cpp \
    mooddiary.cpp \
    moodtest.cpp \
    rest.cpp

HEADERS += \
    achievement.h \
    achievementitem.h \
    aichat.h \
    emojicalendarwidget.h \
    homepage.h \
    mainwindow.h \
    moodchart.h \
    mooddata.h \
    mooddiary.h \
    moodtest.h \
    rest.h

FORMS += \
    achievement.ui \
    achievementitem.ui \
    aichat.ui \
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
    emoji.qrc \
    icon.qrc \
    sounds.qrc

DISTFILES += \
    chat_history.json \
    config.ini \
    data/achievement_data.json \
    data/achievement_status.json \
    data/mood_diary.json \
    mood_diary.json
