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
    QWidget(parent)
{
    this->setWindowTitle("example.cpp");

    sciEditor = new QsciScintilla(this);
    BREAK_MARKER_NUM = 8;
    //sciEditor->setFrameStyle(QsciScintilla::NoFrame);
    //sciEditor->setWrapMode(QsciScintilla::WrapCharacter);

    sciEditor->setCaretLineVisible(true);
    sciEditor->setCaretLineBackgroundColor(QColor("#ffe4e4"));

    QFont font = QFont("Courier 10 Pitch", 10);
    font.setFixedPitch(true);
    sciEditor->setFont(font);
    QsciLexerCPP lexer;
    lexer.setFont(font);
    sciEditor->setLexer(&lexer);

    QFontMetrics fontmetrics = QFontMetrics(font);
    sciEditor->setMarginWidth(0, fontmetrics.width("__")+8);
   // sciEditor->setMarginWidth(1, 0);
    sciEditor->setMarginLineNumbers(0, true);
    sciEditor->setMarginsBackgroundColor(QColor("#dddddd"));

    sciEditor->setMarginSensitivity(1, true);
    //sciEditor->setMarginWidth();
    connect(sciEditor,
        SIGNAL(marginClicked(int, int, Qt::KeyboardModifiers)), this,
                       SLOT(on_margin_clicked(int, int, Qt::KeyboardModifiers)));
    sciEditor->markerDefine(QImage(":/icons/icons/link_break.png"),
        BREAK_MARKER_NUM);
    sciEditor->setBraceMatching(QsciScintilla::SloppyBraceMatch);

    sciEditor->setFolding(QsciScintilla::BoxedTreeFoldStyle, 3);
    //sciEditor->setFoldMarginColors(QColor("#dddddd"), QColor("#dddddd"));

    sciEditor->setMarginsFont(font);
    sciEditor->setMarginsForegroundColor(QColor("#bbbbbb"));

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(sciEditor);
    layout->setContentsMargins(3, 3, 3, 3);
    this->setLayout(layout);
}

CodeWidget::~CodeWidget()
{

}

void CodeWidget::on_margin_clicked(int nmargin, int nline, Qt::KeyboardModifiers modifiers) {
    // Toggle marker for the line the margin was clicked on
    if (sciEditor->markersAtLine(nline) != 0) {
        sciEditor->markerDelete(nline, BREAK_MARKER_NUM);
    } else {
        sciEditor->markerAdd(nline, BREAK_MARKER_NUM);
    }
}
