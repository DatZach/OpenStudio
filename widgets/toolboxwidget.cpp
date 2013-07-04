/**
* @file  toolboxwidget.cpp
* @brief Source implementing a class for a tool box widget.
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


#include "toolboxwidget.h"

ToolBoxWidget::ToolBoxWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout();
    QLineEdit* searchEdit = new QLineEdit();
    searchEdit->setText("Filter...");
    searchEdit->setFont(QFont("Ubuntu", -1, -1, true));
    QListWidget* toolList = new QListWidget();
    layout->addWidget(searchEdit);
    layout->addWidget(toolList);
    layout->setContentsMargins(3, 3, 3, 3);
    this->setLayout(layout);
}

ToolBoxWidget::~ToolBoxWidget()
{

}
