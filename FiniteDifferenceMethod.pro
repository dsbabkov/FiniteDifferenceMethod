QT       += core gui widgets

TARGET = FiniteDifferenceMethod
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MethodWidget.cpp

HEADERS  += MainWindow.h \
    MethodWidget.h

FORMS    += MainWindow.ui \
    MethodWidget.ui

LIBS += -LC:\Development\armadillo\bin -larmadillo
INCLUDEPATH += C:\Development\armadillo\include
