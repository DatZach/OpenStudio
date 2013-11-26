/**
* @file  codewidget.cpp
* @brief Source implementing a class for a code widget.
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

#include "codewidget.h"

CodeWidget::CodeWidget(QWidget *parent) :
    QsciScintilla(parent)
{
    this->setWindowTitle("example.cpp");

    //sciEditor = new QsciScintilla(this);
    BREAK_MARKER_NUM = 8;
    //this->setFrameStyle(QsciScintilla::NoFrame);
    //this->setWrapMode(QsciScintilla::WrapCharacter);

    this->setCaretLineVisible(true);
    this->setCaretLineBackgroundColor(QColor("#ffe4e4"));

    QFont font = QFont("Courier", 8);
    font.setFixedPitch(true);
    //this->setFont(font);
    QsciLexerCPP lexer;
    lexer.setFont(font);
    lexer.setFoldCompact(false);
    this->setLexer(&lexer);

    QFontMetrics fontmetrics = QFontMetrics(font);
    this->setMarginWidth(0, fontmetrics.width("__")+8);
   // this->setMarginWidth(1, 0);
    this->setMarginLineNumbers(0, true);
    this->setMarginsBackgroundColor(QColor("#dddddd"));

    this->setMarginSensitivity(1, true);
    //this->setMarginWidth();
    connect(this,
        SIGNAL(marginClicked(int, int, Qt::KeyboardModifiers)), this,
                       SLOT(on_margin_clicked(int, int, Qt::KeyboardModifiers)));
    this->markerDefine(QImage(":/icons/icons/link_break.png"),
        BREAK_MARKER_NUM);
    this->setBraceMatching(QsciScintilla::SloppyBraceMatch);

    this->setFolding(QsciScintilla::BoxedTreeFoldStyle, 3);
    //this->setFoldMarginColors(QColor("#dddddd"), QColor("#dddddd"));

    this->setMarginsFont(font);
    this->setMarginsForegroundColor(QColor("#bbbbbb"));

   //QVBoxLayout* layout = new QVBoxLayout();
    //layout->addWidget(sciEditor);
   //layout->setContentsMargins(3, 3, 3, 3);
    //this->setLayout(layout);

    QAction* cutAction = new QAction(QIcon(":icons/icons/cut.png"), "&Cut", this);
    cutAction->setShortcuts(QKeySequence::Cut);
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));
    QAction* copyAction = new QAction(QIcon(":icons/icons/page_white_copy.png"), "&Copy", this);
    copyAction->setShortcuts(QKeySequence::Copy);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));
    QAction* pasteAction = new QAction(QIcon(":icons/icons/paste_plain.png"), "&Paste", this);
    pasteAction->setShortcuts(QKeySequence::Paste);
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));
    QAction* undoAction = new QAction(QIcon(":icons/icons/undo.png"), "&Undo", this);
    undoAction->setShortcuts(QKeySequence::Undo);
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    QAction* redoAction = new QAction(QIcon(":icons/icons/redo.png"), "&Redo", this);
    redoAction->setShortcuts(QKeySequence::Redo);
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));
    QAction* selectallAction = new QAction("Select &All", this);
    selectallAction->setShortcuts(QKeySequence::SelectAll);
    connect(selectallAction, SIGNAL(triggered()), this, SLOT(selectAll()));

    editMenu = new QMenu("&Edit");
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(selectallAction);
}

CodeWidget::~CodeWidget()
{

}

void CodeWidget::contextMenuEvent(QContextMenuEvent* e) {
    editMenu->move(this->mapFromParent(QCursor::pos()));
   editMenu->show();
}

void CodeWidget::on_margin_clicked(int nmargin, int nline, Qt::KeyboardModifiers modifiers) {
    // Toggle marker for the line the margin was clicked on
    if (this->markersAtLine(nline) != 0) {
        this->markerDelete(nline, BREAK_MARKER_NUM);
    } else {
        this->markerAdd(nline, BREAK_MARKER_NUM);
    }
}
