#-------------------------------------------------
#
# Project created by QtCreator 2022-06-16T13:58:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StatisticWord
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    hashmap.cpp \
    bisorttree.cpp \
    linklist.cpp

HEADERS  += mainwindow.h \
    total.h \
    hashmap.h \
    linklist.h \
    dialog.h \
    bisorttree.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    img.qrc

DISTFILES += \
    img/28_painter_4k.png \
    img/103101.png
