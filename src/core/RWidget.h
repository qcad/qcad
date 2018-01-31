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

#ifndef RWIDGET_H_
#define RWIDGET_H_

#include "core_global.h"

#include <QWidget>
#include <QMetaType>

/**
 * Widget with some additional functionality for scripts
 *
 * \ingroup gui
 * \scriptable
 * \generateScriptShell
 */
class QCADCORE_EXPORT RWidget: public QWidget {

    Q_OBJECT

public:
    RWidget(QWidget* parent=0);
    virtual ~RWidget();

    virtual void removeAction(QAction* action);
    virtual void addAction(QAction* action);
    virtual void insertAction(QAction* before, QAction* action);

signals:
    void actionAdded(QAction* action);
};

Q_DECLARE_METATYPE(RWidget*)

#endif
