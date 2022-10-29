TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -no-pie
QMAKE_CXXFLAGS += -std=c++17
SOURCES += main.cpp \
        command.cpp \
        memory.cpp \
        processor.cpp

HEADERS += \
    command.h \
    memory.h \
    processor.h \
    structure.h

DISTFILES +=
