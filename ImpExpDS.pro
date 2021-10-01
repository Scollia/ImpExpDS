VERSION = 0.0.1.0
QMAKE_TARGET_COMPANY = TIV Studio
QMAKE_TARGET_PRODUCT = Import, export DS
QMAKE_TARGET_DESCRIPTION = Import, export digital signatures
QMAKE_TARGET_COPYRIGHT = (c) Ivan Tararykov

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/cmaindata.cpp \
    src/cprogrammoptions.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    include/cmaindata.h \
    include/cprogrammoptions.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    ImpExpDS_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
