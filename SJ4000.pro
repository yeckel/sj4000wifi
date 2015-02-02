#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T11:01:35
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sj4000wifi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
	cameracontroller.cpp

HEADERS  += mainwindow.h\
	cameracontroller.h

FORMS    += mainwindow.ui
