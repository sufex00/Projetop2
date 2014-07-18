#-------------------------------------------------
#
# Project created by QtCreator 2014-07-17T17:37:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = huffman
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    File.cpp \
    TreeHuffman.cpp \
    Cell.cpp \
    TreatmentHeader.cpp \
    BitVector.cpp \
    huffdecoditication.cpp

HEADERS += \
    File.h \
    TreeHuffman.h \
    Cell.h \
    TreatmentHeader.h \
    BitVector.h \
    huffdecoditication.h
