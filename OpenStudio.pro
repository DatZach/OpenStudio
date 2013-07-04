#-------------------------------------------------
#
# Project created by QtCreator 2013-07-02T17:13:51
#
#-------------------------------------------------

QT       += webkitwidgets network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS	+= -L$$[QT_INSTALL_LIBS] -lqscintilla2

TARGET = OpenStudio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customwidgets/qttoolbar.cpp \
    dialogs/templatedialog.cpp \
    widgets/toolboxwidget.cpp \
    widgets/codewidget.cpp \
    widgets/welcomewidget.cpp \
    dialogs/aboutdialog.cpp \
    dialogs/helpviewer.cpp \
    dialogs/findandreplace.cpp

HEADERS  += mainwindow.h \
    customwidgets/qttoolbar.h \
    dialogs/templatedialog.h \
    widgets/toolboxwidget.h \
    widgets/codewidget.h \
    widgets/welcomewidget.h \
    dialogs/aboutdialog.h \
    dialogs/helpviewer.h \
    dialogs/findandreplace.h

FORMS    += \
    widgets/welcomewidget.ui \
    dialogs/helpviewer.ui \
    dialogs/findandreplace.ui

RESOURCES += \
    iconsres.qrc
