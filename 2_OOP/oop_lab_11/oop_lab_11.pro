TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        array.cpp \
        bitstring.cpp \
        main.cpp \
        reference.cpp \
        test.cpp \
        twelve.cpp

HEADERS += \
    array.h \
    bitstring.h \
    catch.hpp \
    reference.h \
    twelve.h
