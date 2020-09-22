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

#ifndef RRULERQT_H
#define RRULERQT_H

#include "gui_global.h"

#include <QFrame>
#include <QMetaType>
#include <QPainterPath>

#include "RCoordinateListener.h"
#include "RPaletteListener.h"
#include "RRuler.h"
#include "RVector.h"

class RGraphicsView;
class RDocumentInterface;

/**
 * Widget that displays the current mouse position.
 * Usually shown in the status bar of an application.
 *
 * \ingroup gui
 * \scriptable
 */
class QCADGUI_EXPORT RRulerQt: public QFrame, public RRuler, public RCoordinateListener, public RPaletteListener {

Q_OBJECT
Q_PROPERTY(Qt::Orientation orientation READ getOrientation WRITE setOrientation);

public:
    RRulerQt(QWidget* parent=0);
    virtual ~RRulerQt();

    virtual void setOrientation(Qt::Orientation orientation);

    virtual QSize sizeHint() const;

    virtual void paintTick(int pos, bool major, const QString& label);

    virtual QFont getFont() const;

    virtual void updateViewport();

    virtual void updateCoordinate(RDocumentInterface* documentInterface);

    virtual void updatePalette() {
        lastSize = QSize(0,0);
    }

protected:
    void paintEvent(QPaintEvent *);

private:
    QPainter *painter;
    QImage buffer;
    QSize lastSize;
    bool viewportChanged;
    QPainterPath cursorArrow;
    RVector cursorPosition;
    int darkGuiBackground;
    mutable QSize hint;
};

Q_DECLARE_METATYPE(RRulerQt*)

#endif
