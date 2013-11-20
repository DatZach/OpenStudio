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
#include <QFileDialog>
#include <QSettings>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("Open Studio");
    this->resize(1000, 600);

    // this helps with the layout to keep the output window
    // from stretching the entire bottom of the main window
    setCorner( Qt::TopLeftCorner, Qt::LeftDockWidgetArea );
    setCorner( Qt::TopRightCorner, Qt::RightDockWidgetArea );
    setCorner( Qt::BottomLeftCorner, Qt::LeftDockWidgetArea );
    setCorner( Qt::BottomRightCorner, Qt::RightDockWidgetArea );

    QAction* newAction = new QAction(QIcon(":icons/icons/page_white_add.png"), "&New file or project", this);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newProject()));
    QAction* openAction = new QAction(QIcon(":icons/icons/folder.png"), "&Open existing file or project", this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(showOpenDialog()));
    QAction* saveAction = new QAction(QIcon(":icons/icons/save.png"), "&Save the current file", this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(showSaveDialog()));
    QAction* saveasAction = new QAction(QIcon(":icons/icons/save-as.png"), "Open existing file or project", this);
     connect(saveasAction, SIGNAL(triggered()), this, SLOT(showSaveDialog()));
    QAction* saveallAction = new QAction(QIcon(":icons/icons/save-all.png"), "Save &All open files", this);
    QAction* exitAction = new QAction(QIcon(":icons/icons/exit.png"), "&Exit", this);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(closeApplication()));

    QAction* prefsAction = new QAction(QIcon(":icons/icons/preferences.png"), "&Preferences", this);
    connect(prefsAction, SIGNAL(triggered()), this, SLOT(showPreferencesDialog()));

    QAction* stopAction = new QAction(QIcon(":icons/icons/stop.png"), "&Stop", this);
    connect(stopAction, SIGNAL(triggered()), this, SLOT(cut()));
    QAction* pauseAction = new QAction(QIcon(":icons/icons/pause.png"), "&Pause", this);
    connect(pauseAction, SIGNAL(triggered()), this, SLOT(cut()));
    QAction* executeAction = new QAction(QIcon(":icons/icons/execute.png"), "&Execute", this);
    connect(executeAction, SIGNAL(triggered()), this, SLOT(cut()));

    QAction* stepoverAction = new QAction(QIcon(":icons/icons/stepover.png"), "&Step Over", this);
    connect(stepoverAction, SIGNAL(triggered()), this, SLOT(cut()));
    QAction* stepintoAction = new QAction(QIcon(":icons/icons/stepinto.png"), "&Step Into", this);
    connect(stepintoAction, SIGNAL(triggered()), this, SLOT(cut()));
    QAction* stepoutofAction = new QAction(QIcon(":icons/icons/stepout.png"), "&Step Out Of", this);
    connect(stepoutofAction, SIGNAL(triggered()), this, SLOT(cut()));
    QAction* runtolineAction = new QAction(QIcon(":icons/icons/debugruntoline.png"), "&Run to Line", this);
    connect(runtolineAction, SIGNAL(triggered()), this, SLOT(cut()));
    QAction* debugstepoverAction = new QAction(QIcon(":icons/icons/debugstepover.png"), "&Debug Step Over", this);
    connect(debugstepoverAction, SIGNAL(triggered()), this, SLOT(cut()));
    QAction* debugstepintoAction = new QAction(QIcon(":icons/icons/debugstepinto.png"), "&Debug Step Into", this);
    connect(debugstepintoAction, SIGNAL(triggered()), this, SLOT(cut()));

    QAction* cutAction = new QAction(QIcon(":icons/icons/cut.png"), "&Cut", this);
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));
    QAction* copyAction = new QAction(QIcon(":icons/icons/page_white_copy.png"), "&Copy", this);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    QAction* pasteAction = new QAction(QIcon(":icons/icons/paste_plain.png"), "&Paste", this);
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
    QAction* undoAction = new QAction(QIcon(":icons/icons/undo.png"), "&Undo", this);
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    QAction* redoAction = new QAction(QIcon(":icons/icons/redo.png"), "&Redo", this);
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));
    QAction* selectallAction = new QAction("Select &All", this);
    connect(selectallAction, SIGNAL(triggered()), this, SLOT(selectAll()));
    QAction* fnrAction = new QAction(QIcon(":icons/icons/find.png"), "&Find and Replace", this);
    connect(fnrAction, SIGNAL(triggered()), this, SLOT(showFindAndReplace()));

    QAction* mdiAction = new QAction("&Multiple Document Interface", this);
    connect(mdiAction, SIGNAL(triggered()), this, SLOT(toggleMdiTabs()));
    QAction* restoreAction = new QAction("&Restore Layout", this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(restoreLayout()));

    QAction* manualAction = new QAction(QIcon(":icons/icons/manual.png"), "&Documentation", this);
    connect(manualAction, SIGNAL(triggered()), this, SLOT(showHelpViewer()));
    QAction* licenseAction = new QAction("&License", this);
    connect(licenseAction, SIGNAL(triggered()), this, SLOT(showLicenseDialog()));
    QAction* aboutAction = new QAction(QIcon(":icons/icons/help.png"), "&About", this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutDialog()));

    fileToolbar = new QtToolBar();
    fileToolbar->setObjectName("fileToolbar");
    fileToolbar->addAction(newAction);
    fileToolbar->addAction(openAction);
    fileToolbar->addAction(saveAction);
    fileToolbar->addAction(saveallAction);
    fileToolbar->setActionWidgetSize(26, 26);
    this->addToolBar(fileToolbar);
    buildToolbar = new QtToolBar();
    buildToolbar->setObjectName("buildToolbar");
    buildToolbar->addAction(stopAction);
    buildToolbar->addAction(pauseAction);
    buildToolbar->addAction(executeAction);
    QStringList options;
    options << "Release";
    options << "Debug";
    QComboBox* buildmodeCombo = new QComboBox();
    buildmodeCombo->addItems(options);
    buildToolbar->setActionWidgetSize(26, 26);
    buildToolbar->addWidget(buildmodeCombo);
    this->addToolBar(buildToolbar);
    debugToolbar = new QtToolBar();
    debugToolbar->setObjectName("debugToolbar");
    debugToolbar->addAction(stepoverAction);
    debugToolbar->addAction(stepintoAction);
    debugToolbar->addAction(stepoutofAction);
    debugToolbar->addAction(runtolineAction);
    debugToolbar->addAction(debugstepoverAction);
    debugToolbar->addAction(debugstepintoAction);
    debugToolbar->setActionWidgetSize(26, 26);
    this->addToolBar(debugToolbar);
    editToolbar = new QtToolBar();
    editToolbar->setObjectName("editToolbar");
    editToolbar->addAction(undoAction);
    editToolbar->addAction(redoAction);
    editToolbar->addAction(cutAction);
    editToolbar->addAction(copyAction);
    editToolbar->addAction(pasteAction);
    editToolbar->addAction(fnrAction);
    editToolbar->setActionWidgetSize(26, 26);
    this->addToolBar(editToolbar);
    mainStatusbar = new QStatusBar();
    QLabel* statusLabel = new QLabel("Ready");
    mainStatusbar->setStyleSheet("QStatusBar { background-color: #1B91E0; }  QStatusBar::item { border: 0px solid red; border-radius: 3px; }");
    statusLabel->setStyleSheet("QLabel { background-color: #1B91E0; color: white; }");
    //this->setStyleSheet("QMainWindow { background-color: white; }");
    mainStatusbar->addWidget(statusLabel);
    this->setStatusBar(mainStatusbar);
    mainMenubar = new QMenuBar();
    QMenu* fileMenu = new QMenu("&File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveallAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    mainMenubar->addMenu(fileMenu);
    QMenu* viewMenu = new QMenu("&View");
    viewMenu->addAction(mdiAction);
    viewMenu->addAction(restoreAction);
    mainMenubar->addMenu(viewMenu);
    QMenu* editMenu = new QMenu("&Edit");
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(selectallAction);
    mainMenubar->addMenu(editMenu);
    mainMenubar->addMenu("&Build");
    mainMenubar->addMenu("&Project");
    QMenu* toolsMenu = new QMenu("&Tools");
    toolsMenu->addAction(prefsAction);
    mainMenubar->addMenu(toolsMenu);
    QMenu* helpMenu = new QMenu("&Help");
    helpMenu->addAction(manualAction);
    helpMenu->addAction(licenseAction);
    helpMenu->addAction(aboutAction);
    mainMenubar->addMenu(helpMenu);
    this->setMenuBar(mainMenubar);

    treeWidget = new QTreeWidget();
    treeWidget->setHeaderHidden(true);
    treeDock = new QDockWidget("Project");
    treeDock->setObjectName("treeDock");
    treeDock->setWidget(treeWidget);
    this->addDockWidget(Qt::RightDockWidgetArea, treeDock);
    ToolBoxWidget* toolWidget = new ToolBoxWidget();
    toolDock = new QDockWidget("Toolbox");
    toolDock->setObjectName("toolDock");
    toolDock->setWidget(toolWidget);
    this->addDockWidget(Qt::LeftDockWidgetArea, toolDock);
    propDock = new QDockWidget("Properties");
    propDock->setObjectName("propDock");
    this->addDockWidget(Qt::LeftDockWidgetArea, propDock);
    evtDock = new QDockWidget("Events");
    evtDock->setObjectName("evtDock");
    this->addDockWidget(Qt::RightDockWidgetArea, evtDock);
    tabifyDockWidget(treeDock, propDock);
    tabifyDockWidget(treeDock, evtDock);
    treeDock->raise();
    // this will make the tabs ontop of the right dock widget area instead of on bottom
    // they look better on bottom
    //this->setTabPosition(Qt::RightDockWidgetArea, QTabWidget::North);

    outputDock = new QDockWidget("Output");
    outputDock->setObjectName("outputDock");
    outputWidget = new QTextEdit();
    outputWidget->setText("This will be ouput displayed by a compiler...");
    outputWidget->setReadOnly(true);
    outputDock->setWidget(outputWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, outputDock);
    messagesDock = new QDockWidget("Messages");
    messagesDock->setObjectName("messagesDock");
    messagesWidget = new QTableWidget();
    messagesWidget->setColumnCount(4);
    QStringList headers;
    headers.append("Type");
    headers.append("File");
    headers.append("Location");
    headers.append("Description");
    messagesWidget->setHorizontalHeaderLabels(headers);
    messagesWidget->verticalHeader()->setVisible(false);
    messagesDock->setWidget(messagesWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, messagesDock);
    tabifyDockWidget(outputDock, messagesDock);
    outputDock->raise();

    mainMdiArea = new QMdiArea();
    mainMdiArea->setTabsClosable(true);
    mainMdiArea->setTabsMovable(true);
   // mainMdiArea->setStyleSheet("QWidget{ background-color: white; }");
    //self.brush = QtGui.QBrush(QtGui.QPixmap("view.jpg"))

    WelcomeWidget* welcomeTab = new WelcomeWidget();
    mainMdiArea->addSubWindow(welcomeTab, Qt::WindowTitleHint);
    //mainMdiArea->setStyleSheet("QTabBar::tab { height: 24px; width: 100px; }");
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
    outputMessage(MSG_ERROR, "example.cpp", "Line 552", "Lorem ipsum dolor sit amet...");
    outputMessage(MSG_WARNING, "example.cpp", "Line 553", "Lorem ipsum dolor sit amet...");
    outputMessage(MSG_NOTICE, "example.cpp", "Line 554", "Lorem ipsum dolor sit amet...");

    preferencesDialog = NULL;
    aboutDialog = NULL;
    helpViewer = NULL;
    fnrDialog = NULL;

    CreateScriptTab();

    treeDock->setVisible(false);
    evtDock->setVisible(false);
    toolDock->setVisible(false);
    outputDock->setVisible(false);
    messagesDock->setVisible(false);
    propDock->setVisible(false);

    this->setObjectName("mainWindow");
    defaultState = this->saveState();
    this->readSettings();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeApplication() {
    this->writeSettings();
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event) {

}

void MainWindow::readSettings()
{
    QSettings settings("LateralGMTeam", "LateralGM");
    restoreGeometry(settings.value("mainWindow/geometry").toByteArray());
    restoreState(settings.value("mainWindowState").toByteArray());
}

void MainWindow::writeSettings()
{
    QSettings settings("LateralGMTeam", "LateralGM");
   settings.setValue("mainWindow/geometry", saveGeometry());
    settings.setValue("mainWindowState", saveState());
}

void MainWindow::restoreLayout() {
    this->restoreState(defaultState);
}

void MainWindow::newProject() {
    TemplateDialog* newSelector = new TemplateDialog();
    newSelector->show();

    treeDock->setVisible(true);
    evtDock->setVisible(true);
    toolDock->setVisible(true);
    outputDock->setVisible(true);
    messagesDock->setVisible(true);
    propDock->setVisible(true);
   // CreateScriptTab();
}

void MainWindow::showOpenDialog() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "", tr("All Files (*.*);;Visual Studio Solution (*.sln);;Code::Blocks Project (*.cbp)"));
}

void MainWindow::showSaveDialog() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Project"), "", tr("All Files (*.*);;Visual Studio Solution (*.sln);;Code::Blocks Project (*.cbp)"));
}

void MainWindow::showFindAndReplace() {
    if (fnrDialog == NULL) {
        fnrDialog = new FindAndReplace(this);
    }
    fnrDialog->show();
}

void MainWindow::showHelpViewer() {
    if (helpViewer == NULL) {
        helpViewer = new HelpViewer(this);
    }
    helpViewer->show();
}

void MainWindow::showLicenseDialog() {
    if (aboutDialog == NULL) {
        aboutDialog = new AboutDialog(this);
    }
    aboutDialog->show(":/license.html", "License");
}

void MainWindow::showAboutDialog() {
    if (aboutDialog == NULL) {
        aboutDialog = new AboutDialog(this);
    }
    aboutDialog->show(":/about.html", "About");
}

void MainWindow::showPreferencesDialog() {
    if (preferencesDialog == NULL) {
        preferencesDialog = new PreferencesDialog(this);
    }
    preferencesDialog->show();
}


void MainWindow::toggleMdiTabs() {

    mainMdiArea->setDocumentMode(true);
    switch (mainMdiArea->viewMode()) {
    case QMdiArea::TabbedView:
         mainMdiArea->setViewMode(QMdiArea::SubWindowView);
        break;
    case QMdiArea::SubWindowView:
         mainMdiArea->setViewMode(QMdiArea::TabbedView);
        break;
    }
}

void MainWindow::undo() {

}

void MainWindow::redo() {

}

void MainWindow::cut() {

}

void MainWindow::copy() {

}

void MainWindow::paste() {

}

void MainWindow::selectAll() {

}

void MainWindow::CreateScriptTab() {
    CodeWidget* codeWidget = new CodeWidget();
    mainMdiArea->addSubWindow(codeWidget, Qt::WindowTitleHint);
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
