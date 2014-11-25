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
#include "RPainterPathExporter.h"

QMap<int, QMap<QString, QImage> > RLinetypeComboDelegate::previewCache;
int RLinetypeComboDelegate::previewHeight = 20;

RLinetypeComboDelegate::RLinetypeComboDelegate(QObject* parent) : QStyledItemDelegate(parent) {

}

void RLinetypeComboDelegate::paint(QPainter* painter,
                                   const QStyleOptionViewItem& option,
                                   const QModelIndex& index) const {

    QStyledItemDelegate::paint(painter, option, index);

    RLinetypeCombo* combo = dynamic_cast<RLinetypeCombo*>(parent());
    if (combo==NULL) {
        return;
    }

    RLinetypePattern pattern = combo->getLinetypePatternAt(index.row());

    QImage img = getPreviewImage(pattern, option.rect.width());

    painter->drawImage(option.rect.left(), option.rect.bottom()-previewHeight, img);
}

QSize RLinetypeComboDelegate::sizeHint(const QStyleOptionViewItem& option,
                                       const QModelIndex& index) const {
    return QSize(300,16+previewHeight);
}

QImage RLinetypeComboDelegate::getPreviewImage(const RLinetypePattern& pattern, int width) {
    width = width/10*10;

    if (previewCache.contains(width)) {
        if (previewCache.value(width).contains(pattern.getName())) {
            return previewCache.value(width).value(pattern.getName());
        }
    }

    QImage ret(width, previewHeight, QImage::Format_ARGB32);
    ret.fill(Qt::transparent);

    if (pattern.isValid()) {
        RPainterPath pp;

        RPainterPathExporter exp;
        exp.setExportZeroLinesAsPoints(false);
        exp.setLinetypePattern(pattern);
        RLine line(RVector(20,0), RVector(width-20,0));
        exp.exportLine(line);
        pp = exp.getPainterPath();
        if (pp.getBoundingBox().getHeight()>1.0) {
            double f = previewHeight*0.4 / pp.getBoundingBox().getHeight();
            RLinetypePattern patternScaled = pattern;
            patternScaled.scale(f);
            exp.setLinetypePattern(patternScaled);
            exp.exportLine(line);
            pp = exp.getPainterPath();
        }

        QPainter p(&ret);
        QTransform t;
        t.scale(1.0,-1.0);
        t.translate(0,-previewHeight/2);
        p.setTransform(t);
        p.drawPath(pp);
        p.end();
    }

    if (!previewCache.contains(width)) {
        previewCache.insert(width, QMap<QString, QImage>());
    }
    previewCache[width].insert(pattern.getName(), ret);

    return ret;
}
