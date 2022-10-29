TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -no-pie
QMAKE_CXXFLAGS += -std=c++17
SOURCES += \
        command.cpp \
        cpu.cpp \
        main.cpp \
        memory.cpp

HEADERS += \
    command.h \
    cpu.h \
    memory.h \
    types.h

DISTFILES +=
