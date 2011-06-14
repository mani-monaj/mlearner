# -------------------------------------------------
# Project created by QtCreator 2011-01-09T02:45:48
# -------------------------------------------------
include(../mlearner/mlearner.pro)
QT -= gui
TARGET = MountainCarTestBed
CONFIG += console
CONFIG -= app_bundle
UI_DIR = ./src.gen/ui
MOC_DIR = ./src.gen/moc
OBJECTS_DIR = ./src.gen/obj
TEMPLATE = app
SOURCES += main.cpp \
    cmountaincarenv.cpp \
    profiler.cpp
HEADERS += cmountaincarenv.h \
    profiler.h
