#-------------------------------------------------
#
# Project created by QtCreator 2017-09-20T16:39:58
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A1_v2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    glcamera.cpp \
    globject.cpp \
    glpointmarker.cpp \
    glbasicshapes.cpp \
    pointmass.cpp \
    linearspring.cpp \
    constantforcefield.cpp \
    constraintfixedpos.cpp \
    constraintorbit.cpp \
    angularspring.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glcamera.h \
    globject.h \
    glpointmarker.h \
    glbasicshapes.h \
    pointmass.h \
    linearspring.h \
    forceapplier.h \
    constantforcefield.h \
    constraint.h \
    constraintfixedpos.h \
    constraintorbit.h \
    angularspring.h

FORMS    += mainwindow.ui
