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

#ifndef RCADTOOLBAR_H_
#define RCADTOOLBAR_H_

#include "gui_global.h"

#include <QToolBar>
#include <QMetaType>

class RCadToolBarPanel;
class QStackedLayout;

/**
 * \ingroup gui
 * \scriptable
 */
class QCADGUI_EXPORT RCadToolBar: public QToolBar {
Q_OBJECT

public:
    RCadToolBar(const QString& title, QWidget* parent = 0);

    RCadToolBarPanel* getPanel(const QString& title, const QString& objectName, bool hasBackButton = true);

    RCadToolBarPanel* getCurrentPanel() const;
    QString getCurrentPanelName() const;

    void showPanel(const QString& name, bool isBack = false);

    void updateIconSize();

public slots:
    bool back();
    void toggleVerticalWhenFloating(bool on);

protected:
    virtual void contextMenuEvent(QContextMenuEvent* event);


private:
    QWidget* widget;
    QStackedLayout* stackedLayout;
};

Q_DECLARE_METATYPE(RCadToolBar*)

#endif
