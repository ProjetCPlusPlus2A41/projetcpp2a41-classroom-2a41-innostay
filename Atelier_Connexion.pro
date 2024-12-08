#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql widgets
QT += svg

TARGET = Atelier_Connexion
TEMPLATE = app

# Warnings for deprecated APIs
DEFINES += QT_DEPRECATED_WARNINGS

# Use C++11
CONFIG += c++11

# Sources
SOURCES += \
    qrcodegeneratordemo.cpp \
    qrcodegeneratorworker.cpp \
    main.cpp \
    mainwindow.cpp \
    connection.cpp \
    qrcode.cpp \
    qrwidget.cpp \
    reservation.cpp

# Headers
HEADERS += \
    mainwindow.h \
    connection.h \
    qrcode.h \
    qrwidget.h \
    reservation.h

# Forms
FORMS += \
    mainwindow.ui

