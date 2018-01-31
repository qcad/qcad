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

#ifndef RLINETYPECOMBODELEGATE_H_
#define RLINETYPECOMBODELEGATE_H_

#include "gui_global.h"

#include <QStyledItemDelegate>

#include "RLinetypePattern.h"

/**
 * \ingroup gui
 */
class QCADGUI_EXPORT RLinetypeComboDelegate: public QStyledItemDelegate {
public:
    RLinetypeComboDelegate(QObject* parent);

    void paint(QPainter* painter,
               const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QSize sizeHint(const QStyleOptionViewItem& option,
                   const QModelIndex& index) const;

    QImage getPreviewImage(const RLinetypePattern& pattern, int width) const;

private:
    static int previewHeight;
    mutable QMap<int, QMap<QString, QImage> > previewCache;
};

Q_DECLARE_METATYPE(RLinetypeComboDelegate*)

#endif
