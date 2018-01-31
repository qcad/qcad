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
#include <QAbstractItemView>
#include <QSize>
#include <QPainter>

#include "RDebug.h"
#include "RLinetypeCombo.h"
#include "RLinetypeComboDelegate.h"

RLinetypeCombo::RLinetypeCombo(QWidget* parent) :
    QComboBox(parent), onlyFixed(false) {
    setIconSize(QSize(32, 16));

    view()->setAlternatingRowColors(true);

    QPalette p = palette();
    QColor baseColor = p.color(QPalette::Base);
    p.setColor(QPalette::AlternateBase, baseColor.darker(110));
    setPalette(p);

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(linetypePatternChanged(int)));
}

void RLinetypeCombo::linetypePatternChanged(int index) {
    if (!itemData(index).isValid()) {
        return;
    }
    emit valueChanged(itemData(index).value<RLinetypePattern> ());
}

void RLinetypeCombo::init(RDocument* doc) {
    clear();
    setMaxVisibleItems(12);

    if (doc!=NULL) {
        patterns = doc->getLinetypePatterns();
        qSort(patterns.begin(), patterns.end());
    }

    // change delegate if document changes to clear preview cache:
    setItemDelegate(new RLinetypeComboDelegate(this));

    reinit();
}

void RLinetypeCombo::reinit() {
    QVariant v;
    for (int i=0; i<patterns.length(); i++) {
        RLinetypePattern p = patterns[i];

        if (onlyFixed && p.getName().toUpper()=="BYLAYER") {
            continue;
        }
        if (onlyFixed && p.getName().toUpper()=="BYBLOCK") {
            continue;
        }

        v.setValue<RLinetypePattern>(p);
        addItem(p.getLabel(), v);
    }

    if (!onlyFixed) {
        setLinetypePattern("BYLAYER");
    } else {
        setLinetypePattern("CONTINUOUS");
    }

    for (int i=0; i<count(); i++) {
        setItemData(i, Qt::AlignTop, Qt::TextAlignmentRole);
    }

//    RLinetypeComboDelegate* d = dynamic_cast<RLinetypeComboDelegate*>(itemDelegate());
//    if (d!=NULL) {
//        d->setMetric(doc);
//    }
}

RLinetypePattern RLinetypeCombo::getLinetypePattern() {
    return itemData(currentIndex()).value<RLinetypePattern> ();
}

RLinetypePattern RLinetypeCombo::getLinetypePatternAt(int i) {
    if (i<0 || i>=count()) {
        return RLinetypePattern();
    }

    return itemData(i).value<RLinetypePattern> ();
}

void RLinetypeCombo::setLinetypePattern(const QString& name) {
    for (int i = 0; i < count(); ++i) {
        if (itemData(i).isValid()) {
            RLinetypePattern t = itemData(i).value<RLinetypePattern> ();
            //if (t.getName().toUpper() == name.toUpper()) {
            if (t.getName().toUpper() == name.toUpper()) {
                setCurrentIndex(i);
                return;
            }
        }
    }
}

void RLinetypeCombo::setLinetypePattern(const RLinetypePattern& linetypePattern) {
    for (int i = 0; i < count(); ++i) {
        if (itemData(i).isValid()) {
            RLinetypePattern t = itemData(i).value<RLinetypePattern> ();
            if (t == linetypePattern) {
                setCurrentIndex(i);
                return;
            }
        }
    }
}

bool RLinetypeCombo::getOnlyFixed() {
    return onlyFixed;
}

void RLinetypeCombo::setOnlyFixed(bool onlyFixed) {
    this->onlyFixed = onlyFixed;
    reinit();
}
