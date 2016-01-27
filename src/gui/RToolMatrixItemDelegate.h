/**
 * Copyright (C) 2015 The Qt Company Ltd.
 * Copyright (c) 2016 by Andrew Mustun.
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
 *
 * GNU Lesser General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 or version 3 as published by the Free
 * Software Foundation and appearing in the file LICENSE.LGPLv21 and
 * LICENSE.LGPLv3 included in the packaging of this file. Please review the
 * following information to ensure the GNU Lesser General Public License
 * requirements will be met: https://www.gnu.org/licenses/lgpl.html and
 * http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 * Derived from qttools/src/designer/src/lib/shared/sheet_delegate_p.h
 */

#ifndef RTOOLMATRIXITEMDELEGATE_H_
#define RTOOLMATRIXITEMDELEGATE_H_

#include "gui_global.h"

#include <QItemDelegate>
#include <QMetaType>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

/**
 * Tree widget item delegate. Decorates root items of QTreeWidget tool matrices.
 *
 * \ingroup gui
 * \scriptable
 * \generateScriptShell
 */
class QCADGUI_EXPORT RToolMatrixItemDelegate: public QItemDelegate {
    Q_OBJECT
public:
    RToolMatrixItemDelegate(QTreeView* view, QWidget* parent);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QSize sizeHint(const QStyleOptionViewItem& opt, const QModelIndex& index) const;

private:
    QTreeView* treeView;
};

Q_DECLARE_METATYPE(RToolMatrixItemDelegate*)

#endif
