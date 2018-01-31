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

#ifndef RLINETYPECOMBO_H_
#define RLINETYPECOMBO_H_

#include "gui_global.h"

#include <QComboBox>

#include "RDocument.h"
#include "RLinetypePattern.h"

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RLinetypeCombo: public QComboBox {

Q_OBJECT
Q_PROPERTY(bool onlyFixed READ getOnlyFixed WRITE setOnlyFixed);

public:
    RLinetypeCombo(QWidget* parent = 0);

    void init(RDocument* doc);
    void reinit();

    RLinetypePattern getLinetypePattern();
    RLinetypePattern getLinetypePatternAt(int i);
    void setLinetypePattern(const QString& name);
    void setLinetypePattern(const RLinetypePattern& linetypePattern);
    bool getOnlyFixed();
    void setOnlyFixed(bool onlyFixed);

signals:
    void valueChanged(const RLinetypePattern& linetypePattern);

public slots:
    void linetypePatternChanged(int index);

private:
    bool onlyFixed;
    QList<RLinetypePattern> patterns;
};

Q_DECLARE_METATYPE(RLinetypeCombo*)

#endif
