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
    QAction* exitAction = new QAction(QIcon(":icons/icons/exit.png"), "Exit", this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(closeApplication()));

    mainToolbar = new QtToolBar();
    mainToolbar->addAction(newAction);
    mainToolbar->addAction(openAction);
    mainToolbar->setActionWidgetSize(24, 24);
    this->addToolBar(mainToolbar);
    mainStatusbar = new QStatusBar();
    this->setStatusBar(mainStatusbar);
    mainMenubar = new QMenuBar();
    QMenu* fileMenu = new QMenu("File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
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
    treeDock = new QDockWidget("Hierarchy");
    treeDock->setWidget(treeWidget);
    this->addDockWidget(Qt::RightDockWidgetArea, treeDock);

    outputDock = new QDockWidget("Output");
    outputWidget = new QTextEdit();
    outputWidget->setText("This will be ouput displayed by a compiler...");
    outputDock->setWidget(outputWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, outputDock);
    messagesDock = new QDockWidget("Messages");
    messagesWidget = new QTableWidget();
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
