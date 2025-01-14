QT       += core gui
QT       += charts
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QTPLUGIN += dsengine qtmedia_audioengine

CONFIG += resources_big

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
    addsuccess.cpp \
    alert.cpp \
    customcalendarwidget.cpp \
    customerLineEdit.cpp \
    customlabel.cpp \
    deletewindow.cpp \
    extrainfowindow.cpp \
    main.cpp \
    mymemo.cpp \
    mythings.cpp \
    readlist.cpp \
    records.cpp \
    secdialog.cpp \
    settimerrem.cpp \
    settings.cpp \
    timeremainder.cpp

HEADERS += \
    Records.h \
    addsuccess.h \
    alert.h \
    customcalendarwidget.h \
    customerLineEdit.h \
    customlabel.h \
    deletewindow.h \
    extrainfowindow.h \
    mymemo.h \
    mythings.h \
    readlist.h \
    secdialog.h \
    settimerrem.h \
    settings.h \
    timeremainder.h

FORMS += \
    addsuccess.ui \
    alert.ui \
    deletewindow.ui \
    extrainfowindow.ui \
    mymemo.ui \
    mythings.ui \
    secdialog.ui \
    settimerrem.ui \
    settings.ui
RC_FILE += setIcon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    _src.qrc

DISTFILES += \
    notes/record.txt \
    setIcon.rc
