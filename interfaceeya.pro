# Ajout des modules nécessaires
QT += core gui sql
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# Configuration pour les en-têtes, sources et ressources
DEFINES += QT_DEPRECATED_WARNINGS
TARGET = interfaceeya
TEMPLATE = app

# Fichiers sources
SOURCES += main.cpp \
           connection.cpp \
           mainwindow.cpp \
           plat.cpp  # Ajoutez vos autres fichiers sources ici

# Fichiers d'en-tête
HEADERS += mainwindow.h \
           connection.h \
           plat.h  # Ajoutez vos fichiers d'en-tête ici

# Fichiers d'interface utilisateur
FORMS += mainwindow.ui


# Ajout des bibliothèques MySQL (version 64 bits)
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
