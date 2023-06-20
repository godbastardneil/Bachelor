TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        admin.cpp \
        list.cpp \
        main.cpp \
        print.cpp \
        stat.cpp \
        test.cpp \
        theory.cpp

DISTFILES += \
    all_stat.dat \
    all_test.dat \
    all_text.dat

HEADERS += \
    admin.h \
    list.h \
    print.h \
    stat.h \
    struct.h \
    test.h \
    theory.h
