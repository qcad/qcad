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

#ifndef RLINEWEIGHTCOMBO_H_
#define RLINEWEIGHTCOMBO_H_

#include "gui_global.h"

#include <QComboBox>

#include "RGlobal.h"
#include "RLineweight.h"

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RLineweightCombo: public QComboBox {

Q_OBJECT
Q_PROPERTY(bool onlyFixed READ getOnlyFixed WRITE setOnlyFixed);
Q_PROPERTY(bool noDefault READ getNoDefault WRITE setNoDefault);

public:
    RLineweightCombo(QWidget *parent = 0);

    void init();

    RLineweight::Lineweight getLineweight();
    void setLineweight(RLineweight::Lineweight lw);

    bool getOnlyFixed();
    void setOnlyFixed(bool onlyFixed);

    bool getNoDefault();
    void setNoDefault(bool noDefault);

signals:
    void valueChanged(RLineweight::Lineweight lw);

public slots:
    void lineweightChanged(int index);

private:
    RLineweight::Lineweight currentLineweight;
    bool onlyFixed;
    bool noDefault;
};

Q_DECLARE_METATYPE(RLineweightCombo*)

#endif
