#-------------------------------------------------
#
# Project created by QtCreator 2016-06-10T15:00:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

CONFIG += c++11
TARGET = qopengl_vs_qgl_fps
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    FPSCounter.cpp

HEADERS  += MainWindow.h \
    FPSCounter.h
