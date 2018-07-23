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

#ifndef RTREEWIDGET_H_
#define RTREEWIDGET_H_

#include "gui_global.h"

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QtDebug>

/**
 * Tree widget with some additional functionality for icons.
 *
 * \ingroup gui
 * \scriptable
 * \generateScriptShell
 */
class QCADGUI_EXPORT RTreeWidget: public QTreeWidget {

    Q_OBJECT

public:
    RTreeWidget(QWidget* parent=0);
    virtual ~RTreeWidget();

    void setSelectableColumn(int c) {
        selectableColumn = c;
    }

    QModelIndex	getIndex(QTreeWidgetItem* item, int column = 0) {
        return indexFromItem(item, column);
    }

    QTreeWidgetItem* getActiveItem();

protected:
    virtual void contextMenuEvent(QContextMenuEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void resizeEvent(QResizeEvent* event);

signals:
    void itemColumnClicked(QTreeWidgetItem* item, int column);
    void contextMenuRequested(QTreeWidgetItem* item, int column);

private:
    QVariant itemPressedData;
    int indexPressed;
    // selectable column or -1 for all:
    int selectableColumn;
};

Q_DECLARE_METATYPE(RTreeWidget*)

#endif
