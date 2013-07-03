/**
* @file  main.cpp
* @brief Source implementing a class for the applications main window.
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

#include <QHeaderView>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("Open Studio");

    // this helps with the layout to keep the output window
    // from stretching the entire bottom of the main window
    setCorner( Qt::TopLeftCorner, Qt::LeftDockWidgetArea );
    setCorner( Qt::TopRightCorner, Qt::RightDockWidgetArea );
    setCorner( Qt::BottomLeftCorner, Qt::LeftDockWidgetArea );
    setCorner( Qt::BottomRightCorner, Qt::RightDockWidgetArea );

    QAction* newAction = new QAction(QIcon(":icons/icons/page_white_add.png"), "New file or project", this);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newProject()));
    QAction* openAction = new QAction(QIcon(":icons/icons/folder.png"), "Open existing file or project", this);
    QAction* saveAction = new QAction(QIcon(":icons/icons/save.png"), "Save the current file", this);
    QAction* saveasAction = new QAction(QIcon(":icons/icons/save-as.png"), "Open existing file or project", this);
    QAction* saveallAction = new QAction(QIcon(":icons/icons/save-all.png"), "Save all open files", this);
    QAction* exitAction = new QAction(QIcon(":icons/icons/exit.png"), "Exit", this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(closeApplication()));

    mainToolbar = new QtToolBar();
    mainToolbar->addAction(newAction);
    mainToolbar->addAction(openAction);
    mainToolbar->addAction(saveAction);
    mainToolbar->addAction(saveallAction);
    mainToolbar->setActionWidgetSize(24, 24);
    this->addToolBar(mainToolbar);
    mainStatusbar = new QStatusBar();
    mainStatusbar->addWidget(new QLabel("Ready"));
    this->setStatusBar(mainStatusbar);
    mainMenubar = new QMenuBar();
    QMenu* fileMenu = new QMenu("File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveallAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    mainMenubar->addMenu(fileMenu);
    mainMenubar->addMenu("Edit");
    mainMenubar->addMenu("Build");
    mainMenubar->addMenu("Project");
    mainMenubar->addMenu("Compilers");
    mainMenubar->addMenu("Help");
    this->setMenuBar(mainMenubar);

    treeWidget = new QTreeWidget();
    treeWidget->setHeaderHidden(true);
    treeDock = new QDockWidget("Project");
    treeDock->setWidget(treeWidget);
    this->addDockWidget(Qt::RightDockWidgetArea, treeDock);
    propDock = new QDockWidget("Properties");
    this->addDockWidget(Qt::RightDockWidgetArea, propDock);
    evtDock = new QDockWidget("Events");
    this->addDockWidget(Qt::RightDockWidgetArea, evtDock);
    tabifyDockWidget(treeDock, propDock);
    tabifyDockWidget(propDock, evtDock);
    treeDock->raise();
    // this will make the tabs ontop of the right dock widget area instead of on bottom
    // they look better on bottom
    //this->setTabPosition(Qt::RightDockWidgetArea, QTabWidget::North);

    outputDock = new QDockWidget("Output");
    outputWidget = new QTextEdit();
    outputWidget->setText("This will be ouput displayed by a compiler...");
    outputDock->setWidget(outputWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, outputDock);
    messagesDock = new QDockWidget("Messages");
    messagesWidget = new QTableWidget();
    messagesWidget->setColumnCount(4);
    messagesWidget->verticalHeader()->setVisible(false);
    messagesDock->setWidget(messagesWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, messagesDock);

    mainMdiArea = new QMdiArea();
    QWidget* welcomeTab = new QWidget();
    welcomeTab->setWindowTitle("Welcome");

    mainMdiArea->addSubWindow(welcomeTab, Qt::WindowTitleHint);
    CreateScriptTab();
    // MDIArea's can bet set to tabs, interesting...
    mainMdiArea->setDocumentMode(true);
    mainMdiArea->setViewMode(QMdiArea::TabbedView);
    this->setCentralWidget(mainMdiArea);

    addResourceGroup("Forms");
    addResourceGroup("Dialogs");
    addResource("main.cpp", QIcon(":/icons/icons/page_white_cplusplus"));
    addResource("EmptyApplication.vcproj", QIcon(":/icons/icons/page_white_visualstudio.png"));

    outputLine("test");
    outputLine("test2");
    outputMessage(MSG_ERROR, "example.cpp", "Line 552", "Lorem ipsum dollar sit amit...");
    outputMessage(MSG_WARNING, "example.cpp", "Line 553", "Lorem ipsum dollar sit amit...");
    outputMessage(MSG_NOTICE, "example.cpp", "Line 554", "Lorem ipsum dollar sit amit...");
}

MainWindow::~MainWindow()
{

}


void MainWindow::newProject() {
    TemplateDialog* newSelector = new TemplateDialog();
    newSelector->show();
}

void MainWindow::closeApplication() {
    this->close();
}

void MainWindow::CreateScriptTab() {
    QsciScintilla* sciEditor = new QsciScintilla(this);
    sciEditor->setWindowTitle("example.cpp");
    sciEditor->setFrameStyle(QsciScintilla::NoFrame);
    //sciEditor->setWrapMode(QsciScintilla::WrapCharacter);

    sciEditor->setCaretLineVisible(true);
    sciEditor->setCaretLineBackgroundColor(QColor("#ffe4e4"));

    QFont font = QFont("Courier 10 Pitch", 10);
    font.setFixedPitch(true);
    sciEditor->setFont(font);
    QsciLexerCPP lexer;
    lexer.setFont(font);
    sciEditor->setLexer(&lexer);
    sciEditor->setMarginsFont(font);
    QFontMetrics fontmetrics = QFontMetrics(font);
    sciEditor->setMarginWidth(0, fontmetrics.width("__")+8);
    sciEditor->setMarginWidth(1, 0);
    sciEditor->setMarginLineNumbers(0, true);
    sciEditor->setMarginsForegroundColor(QColor("#bbbbbb"));
    //sciEditor->setMarginsBackgroundColor(QColor("#cccccc"));

    mainMdiArea->addSubWindow(sciEditor, Qt::WindowTitleHint);
}

void MainWindow::outputClear(bool clearLog, bool clearMessages)
{
    if (clearLog) {
        this->outputWidget->clear();
    }
    if (clearMessages) {
        this->messagesWidget->clearContents();
        this->messagesWidget->setRowCount(0);
    }
}

void MainWindow::outputText(QString text)
{
    this->outputWidget->insertPlainText(text);
}

void MainWindow::outputLine(QString text)
{
    this->outputWidget->append(text);
}

void MainWindow::outputMessage(int type, QString origin, QString location, QString description)
{
    int ind = messagesWidget->rowCount();
    messagesWidget->insertRow(ind);
    QTableWidgetItem* typeItem = new QTableWidgetItem();
    switch (type) {
    case MSG_ERROR:
        typeItem->setText("Error");
        typeItem->setIcon(QIcon(":/icons/icons/error.png"));
        break;
    case MSG_WARNING:
        typeItem->setText("Warning");
        typeItem->setIcon(QIcon(":/icons/icons/warning.png"));
        break;
    case MSG_NOTICE:
        typeItem->setText("Notice");
        typeItem->setIcon(QIcon(":/icons/icons/notice.png"));
        break;
    }

    messagesWidget->setItem(ind, 0, typeItem);
    messagesWidget->setItem(ind, 1, new QTableWidgetItem(origin));
    messagesWidget->setItem(ind, 2, new QTableWidgetItem(location));
    messagesWidget->setItem(ind, 3, new QTableWidgetItem(description));
}

void MainWindow::addResourceGroup(QString name)
{
    QTreeWidgetItem* treeItem = new QTreeWidgetItem();
    treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setIcon(0, QIcon(":/icons/icons/folder.png"));
    treeWidget->addTopLevelItem(treeItem);
}

void MainWindow::addResource(QString name, QIcon icon)
{
    QTreeWidgetItem* treeItem = new QTreeWidgetItem();
    treeItem = new QTreeWidgetItem();
    treeItem->setText(0, name);
    treeItem->setIcon(0, icon);
    treeWidget->addTopLevelItem(treeItem);
}
