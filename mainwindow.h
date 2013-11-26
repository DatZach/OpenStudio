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
#include <QComboBox>
#include <QTextEdit>
#include <QTableWidget>
#include <QStatusBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDockWidget>

#include "customwidgets/qttoolbar.h"
#include "widgets/toolboxwidget.h"
#include "widgets/codewidget.h"
#include "widgets/welcomewidget.h"
#include "widgets/filetree.h"
#include "dialogs/templatedialog.h"
#include "dialogs/helpviewer.h"
#include "dialogs/aboutdialog.h"
#include "dialogs/findandreplace.h"
#include "dialogs/preferencesdialog.h"

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

    void createScriptTab();
    void outputClear(bool clearLog = true, bool clearMessages = true);
    void outputText(QString text);
    void outputLine(QString text);
    void outputMessage(int type, QString origin, QString location, QString description);
    void addResourceGroup(QString name);
    void addResource(QString name, QIcon icon);

private:
    AboutDialog* aboutDialog;

    QMenuBar* mainMenubar;
    QStatusBar* mainStatusbar;

    QMenu* recentFilesMenu;
    QMenu* recentProjectsMenu;

    QtToolBar* fileToolbar;
    QtToolBar* buildToolbar;
    QtToolBar* debugToolbar;
    QtToolBar* editToolbar;

    QMdiArea* mainMdiArea;

    QDockWidget* propDock;
    QDockWidget* evtDock;
    QDockWidget* treeDock;
    FileTree* treeWidget;
    ToolBoxWidget* toolWidget;
    QDockWidget* toolDock;

    QTextEdit* outputWidget;
    QDockWidget* outputDock;
    QTableWidget* messagesWidget;
    QDockWidget* messagesDock;

    HelpViewer* helpViewer;
    FindAndReplace* fnrDialog;
    PreferencesDialog* preferencesDialog;

    QByteArray defaultState;

public slots:
    void newProject();

    void closeApplication();
    void closeEvent(QCloseEvent *event);
    void readSettings();
    void writeSettings();

    void showOpenDialog();
    void showSaveDialog();
    void showFindAndReplace();
    void showHelpViewer();
    void showLicenseDialog();
    void showAboutDialog();
    void showPreferencesDialog();

    void toggleMdiTabs();
    void restoreLayout();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void selectAll();

    void clearRecentFiles();
    void clearRecentProjects();

private:
    void loadFile(const QString &fileName);
    void saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void updateRecentFileActions();

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];
};

#endif // MAINWINDOW_H
