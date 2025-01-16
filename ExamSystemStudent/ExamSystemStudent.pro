QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientsocket.cpp \
    dbhelper.cpp \
    examcontorller.cpp \
    examdlg.cpp \
    exammodel.cpp \
    infomationdlg.cpp \
    joinclassdlg.cpp \
    logincontorller.cpp \
    loginmodel.cpp \
    main.cpp \
    mainmenuecontorller.cpp \
    mainmenuedlg.cpp \
    mainmenuemodel.cpp \
    namechangedlg.cpp \
    phonenumberchangedlg.cpp \
    registercontorller.cpp \
    registerdlg.cpp \
    registermodel.cpp \
    widget.cpp

HEADERS += \
    DBHelper.h \
    clientsocket.h \
    examcontorller.h \
    examdlg.h \
    exammodel.h \
    infomationdlg.h \
    joinclassdlg.h \
    logincontorller.h \
    loginmodel.h \
    mainmenuecontorller.h \
    mainmenuedlg.h \
    mainmenuemodel.h \
    namechangedlg.h \
    phonenumberchangedlg.h \
    registercontorller.h \
    registerdlg.h \
    registermodel.h \
    widget.h

FORMS += \
    examdlg.ui \
    infomationdlg.ui \
    joinclassdlg.ui \
    mainmenuedlg.ui \
    namechangedlg.ui \
    phonenumberchangedlg.ui \
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


LIBS += -lws2_32
