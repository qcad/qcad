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

#include <QMap>
#include <QPair>
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

RLineweight::Lineweight RLineweight::getClosestMatch(double lw) {
    if (lw<(Weight000+Weight005)/200.0) {
        return Weight000;
    }
    if (lw<(Weight005+Weight009)/200.0) {
        return Weight005;
    }
    if (lw<(Weight009+Weight013)/200.0) {
        return Weight009;
    }
    if (lw<(Weight013+Weight015)/200.0) {
        return Weight013;
    }
    if (lw<(Weight015+Weight018)/200.0) {
        return Weight015;
    }
    if (lw<(Weight018+Weight020)/200.0) {
        return Weight018;
    }
    if (lw<(Weight020+Weight025)/200.0) {
        return Weight020;
    }
    if (lw<(Weight025+Weight030)/200.0) {
        return Weight025;
    }
    if (lw<(Weight030+Weight035)/200.0) {
        return Weight030;
    }
    if (lw<(Weight035+Weight040)/200.0) {
        return Weight035;
    }
    if (lw<(Weight040+Weight050)/200.0) {
        return Weight040;
    }
    if (lw<(Weight050+Weight053)/200.0) {
        return Weight050;
    }
    if (lw<(Weight053+Weight060)/200.0) {
        return Weight053;
    }
    if (lw<(Weight060+Weight070)/200.0) {
        return Weight060;
    }
    if (lw<(Weight070+Weight080)/200.0) {
        return Weight070;
    }
    if (lw<(Weight080+Weight090)/200.0) {
        return Weight080;
    }
    if (lw<(Weight090+Weight100)/200.0) {
        return Weight090;
    }
    if (lw<(Weight100+Weight106)/200.0) {
        return Weight100;
    }
    if (lw<(Weight106+Weight120)/200.0) {
        return Weight106;
    }
    if (lw<(Weight120+Weight140)/200.0) {
        return Weight120;
    }
    if (lw<(Weight140+Weight158)/200.0) {
        return Weight140;
    }
    if (lw<(Weight158+Weight200)/200.0) {
        return Weight158;
    }
    if (lw<(Weight200+Weight211)/200.0) {
        return Weight200;
    }
    return Weight211;
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
