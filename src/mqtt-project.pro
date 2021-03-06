QT       += core gui
QT       += mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    dashboard.cpp \
    dashboardcard.cpp \
    dashboardcardsetter.cpp \
    dashboardcardswitch.cpp \
    dialogadditem.cpp \
    dialogaddtopic.cpp \
    dialogconnect.cpp \
    dialogdata.cpp \
    dialogsend.cpp \
    main.cpp \
    mainwindow.cpp \
    simulator.cpp

HEADERS += \
    dashboard.h \
    dashboardcard.h \
    dashboardcardsetter.h \
    dashboardcardswitch.h \
    dialogadditem.h \
    dialogaddtopic.h \
    dialogconnect.h \
    dialogdata.h \
    dialogsend.h \
    mainwindow.h \
    simulator.h

FORMS += \
    dashboard.ui \
    dashboardcard.ui \
    dashboardcardsetter.ui \
    dashboardcardswitch.ui \
    dialogadditem.ui \
    dialogaddtopic.ui \
    dialogconnect.ui \
    dialogdata.ui \
    dialogsend.ui \
    mainwindow.ui \
    simulator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
