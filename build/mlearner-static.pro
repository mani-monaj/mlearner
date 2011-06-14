QT -= gui
CONFIG += staticlib \
    release
MOC_DIR = ./src.gen/moc
OBJECTS_DIR = ./src.gen/obj
TEMPLATE = lib
DESTDIR = ./
TARGET = mlearner

include(../mlearner/mlearner.pro)

