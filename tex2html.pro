TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

SOURCES += src/main.cpp \
    src/master/Master.cpp

LIBS += -lre2

HEADERS += \
    src/master/Master.hpp
