#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T20:23:44
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuperMario
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameelement.cpp \
    elebackground.cpp \
    elescoreboard.cpp \
    elereadyboard.cpp \
    eleoverboard.cpp \
    eletitleboard.cpp \
    eleflower.cpp \
    eleBrick.cpp \
    eleCloud.cpp \
    eleTurtle.cpp \
    eleMario.cpp \
    eleReadyBrick.cpp \
    MyWidget.cpp

HEADERS  += mainwindow.h \
    gameelement.h \
    elebackground.h \
    elescoreboard.h \
    elereadyboard.h \
    eleoverboard.h \
    eletitleboard.h \
    eleflower.h \
    eleBrick.h \
    eleCloud.h \
    eleTurtle.h \
    eleMario.h \
    eleReadyBrick.h \
    MyWidget.h

RESOURCES += \
    resource/image.qrc \
    resource/sounds.qrc

CONFIG += resources_big

OTHER_FILES +=

RC_ICONS=myico1.ico
