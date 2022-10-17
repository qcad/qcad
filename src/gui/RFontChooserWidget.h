/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#ifndef _RFONTCHOOSERWIDGET_H_
#define _RFONTCHOOSERWIDGET_H_

#include "gui_global.h"

#include <QComboBox>
#include <QFont>
#include <QFontComboBox>

class QLabel;

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RFontChooserWidget: public QWidget {

Q_OBJECT
Q_PROPERTY(QString label READ getLabel WRITE setLabel);
Q_PROPERTY(QFont chosenFont READ getChosenFont WRITE setChosenFont);

public:
    RFontChooserWidget(QWidget* parent = 0);

    QFont getChosenFont() const;
    void setChosenFont(const QFont& font);
    int getSize() const;
    void setSize(int size);
    QString getLabel() const;
    void setLabel(const QString& l);

signals:
    void valueChanged(const QFont& font);

public slots:
    void chosenFontChanged(const QFont& font);
    void sizeChanged(int index);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    void updateSizeCombo();

private:
    QFont chosenFont;
    QComboBox* cbSize;
    QFontComboBox* cbChosenFont;
    QLabel* lbSampleText;
    QLabel* lbLabel;
};

Q_DECLARE_METATYPE(RFontChooserWidget*)

#endif
