/**
* @file  qttoolbar.h
* @brief Header implementing a class for the applications main window.
*
* @section License
*
* Copyright (C) 2013 Robert B. Colton
* This file is a part of the Open Studio IDE.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QTextEdit>
#include <QTableWidget>
#include <QStatusBar>
#include <QMdiArea>
#include <QDockWidget>
#include <QTreeWidget>

#include "customwidgets/qttoolbar.h"
#include "widgets/toolboxwidget.h"
#include "widgets/codewidget.h"
#include "widgets/welcomewidget.h"
#include "dialogs/templatedialog.h"
#include "dialogs/aboutdialog.h"

enum {
    MSG_ERROR,
    MSG_WARNING,
    MSG_NOTICE
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void CreateScriptTab();
    void outputClear(bool clearLog = true, bool clearMessages = true);
    void outputText(QString text);
    void outputLine(QString text);
    void outputMessage(int type, QString origin, QString location, QString description);
    void addResourceGroup(QString name);
    void addResource(QString name, QIcon icon);

private:
    QMenuBar* mainMenubar;
    QtToolBar* mainToolbar;
    QStatusBar* mainStatusbar;

    QMdiArea* mainMdiArea;

    QDockWidget* propDock;
    QDockWidget* evtDock;
    QDockWidget* treeDock;
    QTreeWidget* treeWidget;
    ToolBoxWidget* toolWidget;
    QDockWidget* toolDock;

    QTextEdit* outputWidget;
    QDockWidget* outputDock;
    QTableWidget* messagesWidget;
    QDockWidget* messagesDock;

public slots:
    void newProject();
    void closeApplication();
    void showAboutDialog();
};

#endif // MAINWINDOW_H
