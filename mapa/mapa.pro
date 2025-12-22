QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += widgets sql

INCLUDEPATH += $$PWD/lib/include
LIBS += -L$$PWD/lib -lnavlib

QT += svgwidgets




CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login_register.cpp \
    main.cpp \
    mainwindow.cpp \
    perfil.cpp \
    stats.cpp \
    textitem.cpp \
    utils.cpp

HEADERS += \
    login_register.h \
    mainwindow.h \
    perfil.h \
    stats.h \
    textitem.h \
    utils.h

FORMS += \
    login_register.ui \
    mainwindow.ui \
    perfil.ui \
    stats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
