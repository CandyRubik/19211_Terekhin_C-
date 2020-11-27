QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game.cpp \
    gamefield.cpp \
    gameroptimal.cpp \
    gamerrandom.cpp \
    gameruser.cpp \
    gamewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mapmaker.cpp \
    mapmakerwidget.cpp \
    settingswindow.cpp

HEADERS += \
    game.h \
    gamefield.h \
    gameri.h \
    gameroptimal.h \
    gamerrandom.h \
    gameruser.h \
    gamewindow.h \
    mainwindow.h \
    mapmaker.h \
    mapmakerwidget.h \
    settingswindow.h

FORMS += \
    gamewindow.ui \
    mainwindow.ui \
    mapmaker.ui \
    settingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    info/MapF.txt \
    info/MapS.txt
