QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += widgets sql

INCLUDEPATH += $$PWD/lib/include
LIBS += -L$$PWD/lib -lnavlib


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    iconcombobox.cpp \
    login_register.cpp \
    main.cpp \
    mainwindow.cpp \
    perfil.cpp \
    preguntas.cpp \
    utils.cpp

HEADERS += \
    iconcombobox.h \
    login_register.h \
    mainwindow.h \
    perfil.h \
    preguntas.h \
    utils.h

FORMS += \
    login_register.ui \
    mainwindow.ui \
    perfil.ui \
    preguntas.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
