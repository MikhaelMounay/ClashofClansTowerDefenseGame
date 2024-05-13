QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apiclient.cpp \
    astar.cpp \
    bullet.cpp \
    buttonclickaudio.cpp \
    cannon.cpp \
    castle.cpp \
    enemy.cpp \
    fence.cpp \
    game.cpp \
    healthbar.cpp \
    itemshopwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    shopitem.cpp \
    worker.cpp

HEADERS += \
    apiclient.h \
    astar.h \
    bullet.h \
    buttonclickaudio.h \
    cannon.h \
    castle.h \
    enemy.h \
    fence.h \
    game.h \
    healthbar.h \
    itemshopwindow.h \
    loginwindow.h \
    mainwindow.h \
    player.h \
    shopitem.h \
    worker.h

FORMS += \
    itemshopwindow.ui \
    loginwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = assets/icon.ico
