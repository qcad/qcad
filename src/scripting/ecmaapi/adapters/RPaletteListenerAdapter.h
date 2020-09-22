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

#ifndef RPALETTELISTENERADAPTER_H_
#define RPALETTELISTENERADAPTER_H_

#include <QObject>

#include "RPaletteListener.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RPaletteListenerAdapter: public QObject, public RPaletteListener {
Q_OBJECT

public:
    RPaletteListenerAdapter(QObject* parent=NULL) : QObject(parent) { }
    virtual ~RPaletteListenerAdapter() { }

    virtual void updatePalette() {
        emit paletteChanged();
    }

signals:
    void paletteChanged();
};

Q_DECLARE_METATYPE(RPaletteListenerAdapter*)

#endif
