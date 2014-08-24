#-------------------------------------------------
#
# Project created by QtCreator 2014-01-09T13:39:13
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PassWordManager
TEMPLATE = app


SOURCES += main.cpp\
        datamanager.cpp\
        accountinfo.cpp\
        user.cpp\
        mainwindow.cpp\
        addacountdialog.cpp \
    utils.cpp \
    aboutdialog.cpp


HEADERS  += mainwindow.h\
    addacountdialog.h\
    datamanager.h\
    accountinfo.h\
    user.h \
    utils.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    addacountdialog.ui \
    aboutdialog.ui

RC_FILE += caikewen.rc
