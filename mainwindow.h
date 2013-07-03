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
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>

#include "customwidgets/qttoolbar.h"
#include "dialogs/templatedialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMenuBar* mainMenubar;
    QtToolBar* mainToolbar;
    QStatusBar* mainStatusbar;

    QMdiArea* mainMdiArea;

    QDockWidget* treeDock;
    QTreeWidget* treeWidget;

    QTextEdit* outputWidget;
    QDockWidget* outputDock;
    QTableWidget* messagesWidget;
    QDockWidget* messagesDock;

    void CreateScriptTab();

public slots:
    void newProject();
    void closeApplication();
};

#endif // MAINWINDOW_H
