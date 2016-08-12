QT       += core gui widgets

TARGET = FiniteDifferenceMethod
TEMPLATE = app

CONFIG += c++14


SOURCES += main.cpp\
        MainWindow.cpp \
    MethodWidget.cpp \
    InputParameters.cpp \
    ISolver.cpp \
    ImplicitSolver.cpp \
    AbstractSolver.cpp \
    ExplicitSolver.cpp

HEADERS  += MainWindow.h \
    MethodWidget.h \
    InputParameters.h \
    ISolver.h \
    ImplicitSolver.h \
    AbstractSolver.h \
    ExplicitSolver.h

FORMS    += MainWindow.ui \
    MethodWidget.ui

LIBS += -LC:\Development\armadillo\bin -larmadillo -gfortran -LC:\Development\OpenBLAS\lib -lopenblas
INCLUDEPATH += C:\Development\armadillo\include
