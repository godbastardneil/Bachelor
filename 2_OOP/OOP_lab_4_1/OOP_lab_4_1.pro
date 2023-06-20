TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        money.cpp \
        payment.cpp \
        test.cpp

HEADERS += \
    catch.hpp \
    money.h \
    payment.h
