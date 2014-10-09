TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

SOURCES += src/main.cpp \
    src/master/Master.cpp \
    src/htmlfile/HtmlFile.cpp \
    src/cssfile/CssFile.cpp

LIBS += -lre2

HEADERS += \
    src/master/Master.hpp \
    src/htmlfile/HtmlFile.hpp \
    src/cssfile/CssFile.hpp
