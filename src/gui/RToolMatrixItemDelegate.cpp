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
 * Derived from qttools/src/designer/src/lib/shared/sheet_delegate.cpp
 */

#include <QAbstractItemModel>
#include <QDebug>
#include <QTreeView>
#include <QStyle>
#include <QPainter>

#include "RToolMatrixItemDelegate.h"

RToolMatrixItemDelegate::RToolMatrixItemDelegate(QTreeView* view, QWidget* parent)
    : QItemDelegate(parent),
      treeView(view)
{
}

void RToolMatrixItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    const QAbstractItemModel* model = index.model();
    Q_ASSERT(model);

    if (!model->parent(index).isValid()) {
//        bool hidden = model->data(index, Qt::UserRole+2).toBool();
//        qDebug() << "hidden: " << hidden;
//        if (hidden) {
//            return;
//        }

        // this is a top-level item.
        QStyleOptionButton buttonOption;

        buttonOption.state = option.state;
#ifdef Q_OS_MAC
        buttonOption.state |= QStyle::State_Raised;
#endif
        buttonOption.state &= ~QStyle::State_HasFocus;

        buttonOption.rect = option.rect;
        buttonOption.palette = option.palette;
        buttonOption.features = QStyleOptionButton::None;

        painter->save();
        QColor buttonColor(230, 230, 230);
        QBrush buttonBrush = option.palette.button();
        if (!buttonBrush.gradient() && buttonBrush.texture().isNull()) {
            buttonColor = buttonBrush.color();
        }
        QColor outlineColor = buttonColor.darker(150);
        QColor highlightColor = buttonColor.lighter(130);

        // Only draw topline if the previous item is expanded
        QModelIndex previousIndex = model->index(index.row() - 1, index.column());
        bool drawTopline = (index.row() > 0 && treeView->isExpanded(previousIndex));
        int highlightOffset = drawTopline ? 1 : 0;

        QLinearGradient gradient(option.rect.topLeft(), option.rect.bottomLeft());
        gradient.setColorAt(0, buttonColor.lighter(102));
        gradient.setColorAt(1, buttonColor.darker(106));

        painter->setPen(Qt::NoPen);
        painter->setBrush(gradient);
        painter->drawRect(option.rect);
        painter->setPen(highlightColor);
        painter->drawLine(option.rect.topLeft() + QPoint(0, highlightOffset),
                          option.rect.topRight() + QPoint(0, highlightOffset));
        painter->setPen(outlineColor);
        if (drawTopline) {
            painter->drawLine(option.rect.topLeft(), option.rect.topRight());
        }
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
        painter->restore();

        QStyleOption branchOption;
        static const int i = 9;
        QRect r = option.rect;
        branchOption.rect = QRect(r.left() + i/2, r.top() + (r.height() - i)/2, i, i);
        branchOption.palette = option.palette;
        branchOption.state = QStyle::State_Children;

        if (treeView->isExpanded(index)) {
            branchOption.state |= QStyle::State_Open;
        }

        treeView->style()->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, painter, treeView);

        // draw text
        QRect textrect = QRect(r.left() + i*2, r.top(), r.width() - ((5*i)/2), r.height());
        QString text = elidedText(option.fontMetrics, textrect.width(), Qt::ElideMiddle,
            model->data(index, Qt::DisplayRole).toString());
        treeView->style()->drawItemText(painter, textrect, Qt::AlignCenter,
            option.palette, treeView->isEnabled(), text);

    } else {
        QItemDelegate::paint(painter, option, index);
    }
}

QSize RToolMatrixItemDelegate::sizeHint(const QStyleOptionViewItem& opt, const QModelIndex& index) const {
//    const QAbstractItemModel* model = index.model();
//    Q_ASSERT(model);

    //QStyleOptionViewItem option = opt;
//    bool hidden = model->data(index, Qt::UserRole+2).toBool();
    QSize sz = QItemDelegate::sizeHint(opt, index) + QSize(2, 2);
//    if (hidden) {
//        sz.setHeight(0);
//    }
    return sz;
}
