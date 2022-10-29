TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        array.cpp \
        bitstring.cpp \
        main.cpp \
        octal.cpp \
        test.cpp

HEADERS += \
    array.h \
    bitstring.h \
    catch.hpp \
    octal.h
