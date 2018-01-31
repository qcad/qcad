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

#ifndef RLISTVIEW_H_
#define RLISTVIEW_H_

#include "gui_global.h"

#include <QWidget>
#include <QListView>
#include <QEvent>
#include <QHelpEvent>

/**
 * \scriptable
 * \generateScriptShell
 * \ingroup gui
 */
class QCADGUI_EXPORT RListView: public QListView {

Q_OBJECT

public:
    RListView(QWidget* parent = 0);
    virtual ~RListView() {}

signals:
    void signalContextMenuEvent(QContextMenuEvent* e);
    void signalMouseMoveEvent(QMouseEvent* e);
    void signalMousePressEvent(QMouseEvent* e);
    void signalMouseReleaseEvent(QMouseEvent* e);
    void signalDragEnterEvent(QDragEnterEvent* e);
    void signalDragMoveEvent(QDragMoveEvent* e);
    void signalDropEvent(QDropEvent* e);
    void signalStartDrag(Qt::DropActions supportedActions);
    void signalSelectionChanged(const QItemSelection& selected,
        const QItemSelection& deselected);
    void signalCurrentChanged(const QModelIndex& current,
        const QModelIndex& previous);
    void signalToolTipRequested(QHelpEvent* e);

protected:
    virtual void contextMenuEvent(QContextMenuEvent* e) {
        QListView::contextMenuEvent(e);
        emit signalContextMenuEvent(e);
    }
    virtual void mousePressEvent(QMouseEvent* e) {
        QListView::mousePressEvent(e);
        emit signalMousePressEvent(e);
    }
    virtual void mouseReleaseEvent(QMouseEvent* e) {
        QListView::mouseReleaseEvent(e);
        emit signalMouseReleaseEvent(e);
    }
    virtual void mouseMoveEvent(QMouseEvent* e) {
        QListView::mouseMoveEvent(e);
        emit signalMouseMoveEvent(e);
    }
    virtual void dragEnterEvent(QDragEnterEvent* e) {
        QListView::dragEnterEvent(e);
        emit signalDragEnterEvent(e);
    }
    virtual void dragMoveEvent(QDragMoveEvent* e) {
        QListView::dragMoveEvent(e);
        emit signalDragMoveEvent(e);
    }
    virtual void dropEvent(QDropEvent* e) {
        QListView::dropEvent(e);
        emit signalDropEvent(e);
    }
    virtual void startDrag(Qt::DropActions supportedActions) {
        QListView::startDrag(supportedActions);
        emit signalStartDrag(supportedActions);
    }
    virtual void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {
        QListView::selectionChanged(selected, deselected);
        emit signalSelectionChanged(selected, deselected);
    }
    virtual void currentChanged(const QModelIndex& current, const QModelIndex& previous) {
        QListView::currentChanged(current, previous);
        emit signalCurrentChanged(current, previous);
    }

    /**
     * \nonscriptable
     */
    virtual bool event(QEvent* event);
};

Q_DECLARE_METATYPE(RListView*)

#endif
