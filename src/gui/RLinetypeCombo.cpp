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
#include <QSet>

#include "RDebug.h"
#include "RLinetypeCombo.h"

RLinetypeCombo::RLinetypeCombo(QWidget *parent) :
    QComboBox(parent), onlyFixed(false) {
    setIconSize(QSize(32, 16));

    init();

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(linetypeChanged(int)));
}

void RLinetypeCombo::linetypeChanged(int index) {
    if (!itemData(index).isValid()) {
        return;
    }
    if (!itemData(index).value<RLinetype> ().isValid()) {
        return;
    }
    emit valueChanged(itemData(index).value<RLinetype> ());
}

void RLinetypeCombo::init() {
    clear();
    setMaxVisibleItems(12);
    QVariant v;
    QListIterator<QPair<QString, RLinetype> > it(RLinetype::getList(onlyFixed));

    while (it.hasNext()) {
        QPair<QString, RLinetype> p = it.next();
        if (p.second.isValid()) {
            v.setValue<RLinetype> (p.second);
            addItem(RLinetype::getIcon(p.second), RLinetype::tr(
                    (const char*) p.first.toUtf8()), v);
        } else {
            addItem(RLinetype::getIcon(p.second), RLinetype::tr(
                    (const char*) p.first.toUtf8()));
        }
    }

    if (!onlyFixed) {
        setLinetype(RLinetype(NULL, "BYLAYER"));
    } else {
        setLinetype(RLinetype(NULL, "CONTINUOUS"));
    }
}

RLinetype RLinetypeCombo::getLinetype() {
    return itemData(currentIndex()).value<RLinetype> ();
}

void RLinetypeCombo::setLinetype(const RLinetype& linetype) {
    for (int i = 0; i < count(); ++i) {
        if (itemData(i).isValid()) {
            RLinetype t = itemData(i).value<RLinetype> ();
            if (t == linetype) {
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
    init();
}
