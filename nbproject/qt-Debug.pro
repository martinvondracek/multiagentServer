# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = DP_server
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += CoordinationPosition.cpp CoveredArea.cpp CoveredAreas.cpp DbConnector.cpp NavigaciaUtil.cpp Obstacle.cpp Position.cpp Server.cpp SocketConnector.cpp SocketUtil.cpp main.cpp serverForm.cpp
HEADERS += CoordinationPosition.h CoveredArea.h CoveredAreas.h DbConnector.h NavigationUtil.h Obstacle.h Position.h Server.h SocketConnector.h SocketUtil.h serverForm.h
FORMS += serverForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += . 
LIBS += -lmysqlcppconn -lpthread  -lpthread  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
