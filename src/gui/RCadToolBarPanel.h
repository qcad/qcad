/**
 * Copyright (c) 2011-2022 by Andrew Mustun. All rights reserved.
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

#ifndef RCADTOOLBARPANEL_H_
#define RCADTOOLBARPANEL_H_

#include "gui_global.h"

#include <QMetaType>

#include "RWidget.h"

class RCadToolBar;
class RGuiAction;
class RColumnLayout;

/**
 * \ingroup gui
 * \scriptable
 */
class QCADGUI_EXPORT RCadToolBarPanel: public RWidget {
Q_OBJECT

public:
    RCadToolBarPanel(RCadToolBar* parent = 0, bool hasBackButton = true);

    void setBackMenuName(const QString& n) {
        backMenuName = n;
    }
    QString getBackMenuName() const {
        return backMenuName;
    }

    QString getButtonName(QAction* action) const;

    void removeAction(QAction* action);

    void insertAction(QAction* before, QAction* action);

    void addAction(QAction* action);

private:
    QString backMenuName;
    RColumnLayout* columnLayout;
};

Q_DECLARE_METATYPE(RCadToolBarPanel*)

#endif
