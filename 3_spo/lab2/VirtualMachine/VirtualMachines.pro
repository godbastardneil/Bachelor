TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -no-pie
QMAKE_CXXFLAGS += -std=c++17
SOURCES += \
        assembler.cpp \
        client.cpp \
        command.cpp \
        cpu.cpp \
        main.cpp \
        memory.cpp \
        parser.cpp

HEADERS += \
    assembler.h \
    client.h \
    command.h \
    cpu.h \
    expression.h \
    memory.h \
    parser.h \
    types.h

DISTFILES +=
