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
#include "RLineweight.h"
#include "RSettings.h"

#include <QPainter>
#include <QPainterPath>

QList < QPair < QString, RLineweight::Lineweight > > RLineweight::list;
QMap<QPair<RLineweight::Lineweight, QPair<int, int> >, QIcon> RLineweight::iconMap;
bool RLineweight::isInitialized = false;

RLineweight::RLineweight() {
}

void RLineweight::init() {
    if (!isInitialized) {
        isInitialized = true;
        init(tr("By Layer"), RLineweight::WeightByLayer);
        init(tr("By Block"), RLineweight::WeightByBlock);
        init(tr("Default"), RLineweight::WeightByLwDefault);
        init(tr("0.00mm"), RLineweight::Weight000);
        init(tr("0.05mm"), RLineweight::Weight005);
        init(tr("0.09mm"), RLineweight::Weight009);
        init(tr("0.13mm (ISO)"), RLineweight::Weight013);
        init(tr("0.15mm"), RLineweight::Weight015);
        init(tr("0.18mm (ISO)"), RLineweight::Weight018);
        init(tr("0.20mm"), RLineweight::Weight020);
        init(tr("0.25mm (ISO)"), RLineweight::Weight025);
        init(tr("0.30mm"), RLineweight::Weight030);
        init(tr("0.35mm (ISO)"), RLineweight::Weight035);
        init(tr("0.40mm"), RLineweight::Weight040);
        init(tr("0.50mm (ISO)"), RLineweight::Weight050);
        init(tr("0.53mm"), RLineweight::Weight053);
        init(tr("0.60mm"), RLineweight::Weight060);
        init(tr("0.70mm (ISO)"), RLineweight::Weight070);
        init(tr("0.80mm"), RLineweight::Weight080);
        init(tr("0.90mm"), RLineweight::Weight090);
        init(tr("1.00mm (ISO)"), RLineweight::Weight100);
        init(tr("1.06mm"), RLineweight::Weight106);
        init(tr("1.20mm"), RLineweight::Weight120);
        init(tr("1.40mm (ISO)"), RLineweight::Weight140);
        init(tr("1.58mm"), RLineweight::Weight158);
        init(tr("2.00mm (ISO)"), RLineweight::Weight200);
        init(tr("2.11mm"), RLineweight::Weight211);
    }
}

void RLineweight::init(const QString& cn, RLineweight::Lineweight lineweight) {
    list.append(QPair<QString, RLineweight::Lineweight> (cn, lineweight));
    //iconMap.insert(lineweight, getIcon(lineweight));
    iconMap.insert(QPair<RLineweight::Lineweight, QPair<int, int> >(lineweight, QPair<int, int>(RDEFAULT_QSIZE_ICON.width(), RDEFAULT_QSIZE_ICON.height())), getIcon(lineweight));
}

QList<QPair<QString, RLineweight::Lineweight> > RLineweight::getList(bool onlyFixed, bool noDefault) {
    init();

    QList<QPair<QString, RLineweight::Lineweight> > l = list;

    if (onlyFixed || noDefault) {
        QString name;

        if (onlyFixed) {
            // remove "By Layer"
            name = getName(RLineweight::WeightByLayer);
            l.removeAll(QPair<QString, RLineweight::Lineweight> (name,
                    RLineweight::Lineweight(RLineweight::WeightByLayer)));

            // remove "By Block"
            name = getName(RLineweight::WeightByBlock);
            l.removeAll(QPair<QString, RLineweight::Lineweight> (name,
                    RLineweight::Lineweight(RLineweight::WeightByBlock)));
        }

        if (noDefault) {
            // remove "Default"
            name = getName(RLineweight::WeightByLwDefault);
            l.removeAll(QPair<QString, RLineweight::Lineweight> (name,
                    RLineweight::Lineweight(RLineweight::WeightByLwDefault)));
        }
    }

    return l;
}

QString RLineweight::getName(RLineweight::Lineweight lineweight) {
    QListIterator<QPair<QString, RLineweight::Lineweight> > i(list);
    while (i.hasNext()) {
        QPair<QString, RLineweight::Lineweight> p = i.next();
        if (p.second == lineweight) {
            return p.first;
        }
    }
    return QString();
}

QIcon RLineweight::getIcon(RLineweight::Lineweight lineweight, const QSize& size) {
    init();

    //if (iconMap.contains(lineweight)) {
    if (iconMap.contains(QPair<RLineweight::Lineweight, QPair<int, int> >(lineweight, QPair<int, int>(size.width(), size.height())))) {
        //return iconMap[lineweight];
        return iconMap[QPair<RLineweight::Lineweight, QPair<int, int> >(lineweight, QPair<int, int>(size.width(), size.height()))];
    }

    QImage img(size.width(), size.height(), QImage::Format_ARGB32_Premultiplied);
    img.fill(0);
    QPainter painter(&img);
    int w = img.width();
    int h = img.height();
    //  painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(0, 0, w, h, Qt::transparent);

    QPainterPath path;
    path.moveTo(0, h / 2);
    path.lineTo(w, h / 2);
    QColor penColor = (RSettings::hasDarkGuiBackground() ? Qt::white : Qt::black);
    painter.setPen(QPen(penColor, (h / 2) * (lineweight < 1 ? 1 : lineweight) / 200));
    painter.drawPath(path);
//  painter.setRenderHint(QPainter::Antialiasing, false);

//  painter.setPen(Qt::black);
//  painter.drawRect(0, 0, w - 1, h - 1);
    painter.end();
    QIcon ret(QPixmap::fromImage(img));
    iconMap.insert(QPair<RLineweight::Lineweight, QPair<int, int> >(lineweight, QPair<int, int>(size.width(), size.height())), ret);
    return ret;
}
