QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbhelper.cpp \
    logincontorller.cpp \
    loginmodel.cpp \
    main.cpp \
    registercontorller.cpp \
    registerdlg.cpp \
    registermodel.cpp \
    widget.cpp

HEADERS += \
    DBHelper.h \
    logincontorller.h \
    loginmodel.h \
    registercontorller.h \
    registerdlg.h \
    registermodel.h \
    widget.h

FORMS += \
    registerdlg.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

win32: LIBS += -L$$PWD/./ -llibmysql

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./libmysql.lib

INCLUDEPATH += .\include
