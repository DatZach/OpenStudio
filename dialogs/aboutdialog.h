/**
* @file  aboutdialog.h
* @brief Header implementing a class for an about dialog.
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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QVBoxLayout>
#include <QDialog>
#include <QTextEdit>

class AboutDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();
    void show(char* path, char* title);
private:
    QTextEdit* browser;
};

#endif // ABOUTDIALOG_H
