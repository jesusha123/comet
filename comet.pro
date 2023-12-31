QT       += core gui
QMAKE_LFLAGS += "-lcurl"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contenttypecombobox.cpp \
    curlutils.cpp \
    debuginfoformatter.cpp \
    httpclient.cpp \
    httpmethod.cpp \
    httprequeststorage.cpp \
    main.cpp \
    mainwindow.cpp \
    methodcombobox.cpp \
    propertytablewidget.cpp \
    requestbuilder.cpp

HEADERS += \
    contenttypecombobox.h \
    curlutils.h \
    debuginfoformatter.h \
    httpclient.h \
    httpmethod.h \
    httprequest.h \
    httprequeststorage.h \
    httpresponse.h \
    mainwindow.h \
    methodcombobox.h \
    propertytablewidget.h \
    requestbuilder.h \
    types.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
