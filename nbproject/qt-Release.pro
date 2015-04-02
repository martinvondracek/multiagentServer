# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = DP_server
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += DbConnector.cpp KoordinacnaSur.cpp Poloha.cpp Prekazka.cpp PreskumanaBunka.cpp PreskumaneOblasti.cpp Server.cpp SocketConnector.cpp SocketUtil.cpp main.cpp serverForm.cpp
HEADERS += DbConnector.h KoordinacnaSur.h Poloha.h Prekazka.h PreskumanaBunka.h PreskumaneOblasti.h Server.h SocketConnector.h SocketUtil.h serverForm.h
FORMS += serverForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += . 
LIBS += 
