QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../common/behavior.c \
    ../../common/sm1.c \
    ../../common/sm2.c \
    ../../common/sm3.c \
    ../../common/sm4.c \
    behaviorthread.cpp \
    cedatank.cpp \
    defaults.c \
    hal.c \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../common/behavior.h \
    ../../common/defaults.h \
    ../../common/hal.h \
    ../../common/sm.h \
    ../../common/sm1.h \
    ../../common/sm2.h \
    ../../common/sm3.h \
    ../../common/sm4.h \
    behaviorthread.h \
    cedatank.h \
    led.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
