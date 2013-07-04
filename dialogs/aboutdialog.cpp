/**
* @file  aboutdialog.cpp
* @brief Source implementing a class for an about dialog.
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

#include "aboutdialog.h"
#include <QFile>
#include <QTextStream>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("About");
    this->resize(500, 300);

    QVBoxLayout* layout = new QVBoxLayout();
    browser = new QTextEdit();
    browser->setReadOnly(true);

    layout->setContentsMargins(3, 3, 3, 3);
    layout->addWidget(browser);
    this->setLayout(layout);
}

AboutDialog::~AboutDialog()
{

}

void AboutDialog::show(char* path, char* title) {
    QFile file(path);

    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream ReadFile(&file);
    browser->setHtml(ReadFile.readAll());
    this->setVisible(true);
    this->setWindowTitle(title);
}
