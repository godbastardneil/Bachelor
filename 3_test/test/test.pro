GOOGLETEST_DIR = /home/gbn_neil/projects/googletest-master

include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../../3_spo/lab2/VirtualMachine/assembler.h \
        ../../3_spo/lab2/VirtualMachine/client.h \
        ../../3_spo/lab2/VirtualMachine/command.h \
        ../../3_spo/lab2/VirtualMachine/cpu.h \
        ../../3_spo/lab2/VirtualMachine/expression.h \
        ../../3_spo/lab2/VirtualMachine/memory.h \
        ../../3_spo/lab2/VirtualMachine/parser.h \
        ../../3_spo/lab2/VirtualMachine/types.h \
        tst_assem_test.h \
        tst_client_test.h \
        tst_cmd_test.h \
        tst_comp_test.h \
        tst_mem_test.h \
        tst_par_test.h \
        types.h

SOURCES += \
        ../../3_spo/lab2/VirtualMachine/assembler.cpp \
        ../../3_spo/lab2/VirtualMachine/client.cpp \
        ../../3_spo/lab2/VirtualMachine/command.cpp \
        ../../3_spo/lab2/VirtualMachine/cpu.cpp \
        ../../3_spo/lab2/VirtualMachine/memory.cpp \
        ../../3_spo/lab2/VirtualMachine/parser.cpp \
        main.cpp
