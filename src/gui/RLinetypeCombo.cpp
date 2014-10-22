/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include <QSize>

#include "RDebug.h"
#include "RLinetypeCombo.h"

RLinetypeCombo::RLinetypeCombo(QWidget* parent) :
    QComboBox(parent), onlyFixed(false) {
    setIconSize(QSize(32, 16));

    //init();

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
    }

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
        addItem(p.getIcon(), p.getLabel(), v);
    }

    if (!onlyFixed) {
        setLinetypePattern("BYLAYER");
    } else {
        setLinetypePattern("CONTINUOUS");
    }
}

RLinetypePattern RLinetypeCombo::getLinetypePattern() {
    return itemData(currentIndex()).value<RLinetypePattern> ();
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
