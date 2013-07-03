#-------------------------------------------------
#
# Project created by QtCreator 2013-07-02T17:13:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS	+= -L$$[QT_INSTALL_LIBS] -lqscintilla2

TARGET = OpenStudio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customwidgets/qttoolbar.cpp \
    dialogs/templatedialog.cpp

HEADERS  += mainwindow.h \
    customwidgets/qttoolbar.h \
    dialogs/templatedialog.h

FORMS    +=

RESOURCES += \
    iconsres.qrc
