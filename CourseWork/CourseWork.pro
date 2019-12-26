#-------------------------------------------------
#
# Project created by QtCreator 2019-12-18T19:47:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseWork
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        binaryrandomtreap.cpp \
        controller.cpp \
        generationwindow.cpp \
        generationwindowcontroller.cpp \
        generationwindowmaincontroller.cpp \
        generationwindowmainview.cpp \
        main.cpp \
        maincontroller.cpp \
        mainview.cpp \
        mainwindow.cpp \
        randomgenerator.cpp \
        syntaxerrorexception.cpp \
        taskgenerator.cpp \
        validator.cpp

HEADERS += \
        binaryrandomtreap.h \
        controller.h \
        generationwindow.h \
        generationwindowcontroller.h \
        generationwindowmaincontroller.h \
        generationwindowmainview.h \
        maincontroller.h \
        mainview.h \
        mainwindow.h \
        queue.h \
        randomgenerator.h \
        syntaxerrorexception.h \
        taskgenerator.h \
        validator.h

FORMS += \
        generationwindow.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
