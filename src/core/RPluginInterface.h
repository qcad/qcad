/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RPLUGININTERFACE_H
#define RPLUGININTERFACE_H

#include <QtPlugin>
#include <QMetaType>

QT_BEGIN_NAMESPACE
class QString;
class QScriptEngine;
QT_END_NAMESPACE

class RPluginInterface {
public:
    virtual ~RPluginInterface() {}

    virtual bool init() = 0;
    virtual void initScriptExtensions(QScriptEngine& engine) = 0;

    virtual QString getErrorString() = 0;
    virtual QString getVersionString() = 0;
    virtual QString getAboutString() = 0;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(RPluginInterface, "org.qcad.QCAD.RPluginInterface/1.0")
QT_END_NAMESPACE

Q_DECLARE_METATYPE(RPluginInterface*)


#endif
