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
    pointmass.cpp \
    ForceAppliers/linearspring.cpp \
    ForceAppliers/constantforcefield.cpp \
    ForceAppliers/angularspring.cpp \
    Constraints/constraintfixedpos.cpp \
    Constraints/constraintorbit.cpp \
    glutility.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glcamera.h \
    pointmass.h \
    ForceAppliers/forceapplier.h \
    ForceAppliers/linearspring.h \
    ForceAppliers/angularspring.h \
    ForceAppliers/constantforcefield.h \
    Constraints/constraint.h \
    Constraints/constraintfixedpos.h \
    Constraints/constraintorbit.h \
    glutility.h

FORMS    += mainwindow.ui
