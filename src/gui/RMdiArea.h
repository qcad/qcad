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

#ifndef RMDIAREA_H_
#define RMDIAREA_H_

#include "gui_global.h"

#include <QMdiArea>
#include <QMetaType>

class QToolButton;
class RMdiChildQt;

/**
 * MDI area with tabbar that features add tab button.
 *
 * \ingroup gui
 * \scriptable
 * \generateScriptShell
 */
class QCADGUI_EXPORT RMdiArea: public QMdiArea {
    Q_OBJECT

public:
    RMdiArea(QWidget* parent=0);
    virtual ~RMdiArea();

    QToolButton* getAddTabButton() {
        return addTabButton;
    }

public slots:
    void updateTabBar(RMdiChildQt* child = NULL);
    void updateTabBarSize();
    void updateAddButtonLocation();
    void closeTab(int i);
    void activateTab(int i);

signals:
    void addTabClicked();

protected:
    virtual void resizeEvent(QResizeEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);

private:
    QTabBar* tabBarOri;
    QTabBar* tabBar;
    QWidget* addTabButtonWidget;
    QToolButton* addTabButton;
};

Q_DECLARE_METATYPE(RMdiArea*)

#endif
