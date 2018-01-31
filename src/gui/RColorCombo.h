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

#ifndef RCOLORCOMBO_H_
#define RCOLORCOMBO_H_

#include "gui_global.h"

#include <QComboBox>

#include "RColor.h"

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RColorCombo: public QComboBox {

Q_OBJECT
Q_PROPERTY(bool onlyFixed READ getOnlyFixed WRITE setOnlyFixed);
Q_PROPERTY(bool showAlphaChannel READ getShowAlphaChannel WRITE setShowAlphaChannel);
Q_PROPERTY(QColor color READ getColor WRITE setColor);

public:
    RColorCombo(QWidget *parent = 0);

    RColor getColor();
    void setColor(const RColor& col);
    void init();
    bool getOnlyFixed();
    void setOnlyFixed(bool onlyFixed);
    //bool isBlackWhite();
    //void setBlackWhite(bool blackWhite);
    bool getShowAlphaChannel();
    void setShowAlphaChannel(bool showAlphaChannel);

signals:
    void valueChanged(const RColor& color);
    void dialogRunning(bool isRunning);

public slots:
    void colorChanged(int index);

private:
    RColor currentColor;
    bool onlyFixed;
    bool showAlphaChannel;
};

Q_DECLARE_METATYPE(RColorCombo*)

#endif /* RCOLORCOMBO_H_ */
