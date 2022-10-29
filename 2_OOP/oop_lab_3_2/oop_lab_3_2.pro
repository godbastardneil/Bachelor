TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        money.cpp \
        test.cpp

HEADERS += \
    Catch2-master/single_include/catch2/catch_reporter_automake.hpp \
    Catch2-master/single_include/catch2/catch_reporter_tap.hpp \
    Catch2-master/single_include/catch2/catch_reporter_teamcity.hpp \
    catch.hpp \
    money.h
