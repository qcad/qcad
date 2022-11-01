/**
 * Copyright (c) 2022 by Andrew Mustun. All rights reserved.
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

#ifndef RCOLUMNLAYOUT_H
#define RCOLUMNLAYOUT_H

#include "gui_global.h"

#include <QLayout>
#include <QToolBar>
#include <QPair>

class QToolButton;
class RGuiAction;

/**
 * \scriptable
 * \ingroup gui
 */
class QCADGUI_EXPORT RColumnLayout: public QLayout {

    Q_OBJECT

public:
    RColumnLayout(QWidget* parent, QToolBar* toolBar, int buttonSize);

//    void removeAction(QAction* a);

    // from QLayout, called by addWidget or addLayout:
    virtual void addItem(QLayoutItem* item);
    virtual int	count() const;
    virtual QLayoutItem* itemAt(int index) const;
    virtual QLayoutItem* takeAt(int index);

    static unsigned long int getAccumulatedSortOrder(QObject* item, const QString& objectName);
    static unsigned int getSortOrder(QObject* item, const QString& objectName);
    static unsigned int getGroupSortOrder(QObject* item, const QString& objectName);

    QSize minimumSize() const;
    QSize sizeHint() const;
    virtual void setGeometry(const QRect& rect);

    void setGeometry() const;

    /**
     * \nonscriptable
     */
    static bool itemLessThan(const QPair<QLayoutItem*, unsigned long int>& v1, const QPair<QLayoutItem*, unsigned long int>& v2) {
        return v1.second < v2.second;
    }

private:
    // map existing layout items to accumulated sort order:
    mutable QList<QPair<QLayoutItem*, unsigned long int> > itemList;

    // tool bar that hosts the layout:
    QToolBar* toolBar;

    mutable QSize sHint;
    mutable int sHintColumns;
    mutable int sHintWidth;
    mutable int sHintHeight;
    mutable bool sHintVerticalWhenFloating;
    mutable int sHintHorizontal;
    mutable int sHintIconSize;
};

#endif
