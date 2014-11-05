/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
#include <QPainter>

#include "RLinetypeCombo.h"
#include "RLinetypeComboDelegate.h"

void RLinetypeComboDelegate::paint(QPainter* painter,
                                   const QStyleOptionViewItem& option,
                                   const QModelIndex& index) const {

    QStyledItemDelegate::paint(painter, option, index);

    RLinetypeCombo* combo = dynamic_cast<RLinetypeCombo*>(parent());
    if (combo==NULL) {
        return;
    }

    //painter->drawLine(0,0,100,100);
    //if (option.state & QStyle::State_Selected) {
    //    painter->fillRect(option.rect, option.palette.highlight());
    //}
//    else {
//        painter->fillRect(option.rect, Qt::green);
//    }

    //index.data.setValue();

    //QStyledItemDelegate::paint(painter, option, index);

//    qDebug() << "row: " << index.row();

    RLinetypePattern pattern = combo->getLinetypePatternAt(index.row());

//    qDebug() << "pat: " << pattern;

    QPen pen;
    QVector<qreal> p = pattern.getScreenBasedLinetype();
    //qDebug() << "label: " << pattern.getLabel() << "p: " << p << "metric: " << pattern.isMetric();
    pen.setDashPattern(p);
    painter->setPen(pen);
    int y = option.rect.center().y() + option.rect.height()/4;
    int m = 20;
    painter->drawLine(option.rect.left()+m, y, option.rect.right()-m, y);
}

QSize RLinetypeComboDelegate::sizeHint(const QStyleOptionViewItem& option,
                                       const QModelIndex& index) const {
    return QSize(300,24);
}
