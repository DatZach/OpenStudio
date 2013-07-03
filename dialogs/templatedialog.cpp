/**
* @file  templatedialog.cpp
* @brief Source implementing a class for a template selection dialog.
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


#include "templatedialog.h"

TemplateDialog::TemplateDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Template Selection Dialog");
    this->resize(600, 400);
    QVBoxLayout* verticalLayout = new QVBoxLayout();

    typeTree = new QTreeWidget();
    QTreeWidgetItem* vsItem = new QTreeWidgetItem(QStringList("Visual Studio"), 0);
    vsItem->addChild(new QTreeWidgetItem(QStringList("Visual Basic"), 0));
    vsItem->addChild(new QTreeWidgetItem(QStringList("Visual C#"), 0));
    vsItem->addChild(new QTreeWidgetItem(QStringList("Visual C++"), 0));
    typeTree->addTopLevelItem(vsItem);
    typeTree->addTopLevelItem(new QTreeWidgetItem(QStringList("Code::Blocks"), 0));
    typeTree->addTopLevelItem(new QTreeWidgetItem(QStringList("OGRE"), 0));
    typeTree->setHeaderLabel("Project Types");
    templateTree = new QTreeWidget();
    templateTree->setColumnCount(2);

    QStringList emptyAppDesc;
    emptyAppDesc.append("Empty Project");
    emptyAppDesc.append("Project without only a main manifest and entry point generated.");
    QTreeWidgetItem* emptyAppItem = new QTreeWidgetItem(emptyAppDesc, 0);
    emptyAppItem->setIcon(0, QIcon(":/icons/icons/application.png"));

    QStringList consoleAppDesc;
    consoleAppDesc.append("Console Application");
    consoleAppDesc.append("Basic input and ouput terminal program.");
    QTreeWidgetItem* consoleAppItem = new QTreeWidgetItem(consoleAppDesc, 0);
    consoleAppItem->setIcon(0, QIcon(":/icons/icons/application_xp_terminal.png"));

    QStringList formsAppDesc;
    formsAppDesc.append("Forms Application");
    formsAppDesc.append("Graphical user interface application using Windows Forms.");
    QTreeWidgetItem* formsAppItem = new QTreeWidgetItem(formsAppDesc, 0);
    formsAppItem->setIcon(0, QIcon(":/icons/icons/application_form.png"));

    QStringList sourceDesc;
    sourceDesc.append("Source");
    sourceDesc.append("Visual C++ source code file");
    QTreeWidgetItem* sourceItem = new QTreeWidgetItem(sourceDesc, 0);
    sourceItem->setIcon(0, QIcon(":/icons/icons/page_white_cplusplus.png"));

    QStringList headerDesc;
    headerDesc.append("Header");
    headerDesc.append("Visual C++ header file.");
    QTreeWidgetItem* headerItem = new QTreeWidgetItem(headerDesc, 0);
    headerItem->setIcon(0, QIcon(":/icons/icons/page_white_h.png"));

    templateTree->addTopLevelItem(emptyAppItem);
    templateTree->addTopLevelItem(formsAppItem);
    templateTree->addTopLevelItem(consoleAppItem);
    templateTree->addTopLevelItem(sourceItem);
    templateTree->addTopLevelItem(headerItem);
    QStringList headers;
    headers.append("Template");
    headers.append("Description");
    templateTree->setHeaderLabels(headers);
    QSplitter* treesSplitter = new QSplitter();
    treesSplitter->addWidget(typeTree);
    treesSplitter->addWidget(templateTree);
    verticalLayout->addWidget(treesSplitter);

    QGridLayout* fileLayout = new QGridLayout();
    fileLayout->addWidget(new QLabel("Name:"), 0, 0);
    QLineEdit* nameEdit = new QLineEdit();
    fileLayout->addWidget(nameEdit, 0, 1);
    fileLayout->addWidget(new QLabel("Location:"), 1, 0);
    QLineEdit* locEdit = new QLineEdit();
    fileLayout->addWidget(locEdit, 1, 1);
    QPushButton* browseButton = new QPushButton("Browse");
    fileLayout->addWidget(browseButton, 1, 2);
    fileLayout->addWidget(new QLabel("Project Name:"), 2, 0);
    QLineEdit* projEdit = new QLineEdit();
    fileLayout->addWidget(projEdit, 2, 1);
    QCheckBox* dirCheckbox = new QCheckBox("Create directory");
    fileLayout->addWidget(dirCheckbox, 2, 2);
    verticalLayout->addLayout(fileLayout);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    verticalLayout->addWidget(buttonBox);

    verticalLayout->setContentsMargins(3, 3, 3, 3);
    this->setLayout(verticalLayout);
}

TemplateDialog::~TemplateDialog()
{

}
