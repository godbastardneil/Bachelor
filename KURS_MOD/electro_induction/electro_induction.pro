QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_LFLAGS += -no-pie

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    dialog.cpp \
    exercise.cpp \
    faradei.cpp \
    main.cpp \
    mainwindow.cpp \
    picturebox.cpp \
    show_text.cpp \
    test.cpp \
    test_comp.cpp \
    theory.cpp

HEADERS += \
    admin.h \
    dialog.h \
    exercise.h \
    exercise_comp.h \
    faradei.h \
    mainwindow.h \
    picturebox.h \
    reader.h \
    show_text.h \
    test.h \
    test_comp.h \
    theory.h

FORMS += \
    admin.ui \
    dialog.ui \
    exercise.ui \
    faradei.ui \
    mainwindow.ui \
    show_text.ui \
    test.ui \
    theory.ui

DISTFILES += \
    class.qmodel
