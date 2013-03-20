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
#include "RLineweightCombo.h"

RLineweightCombo::RLineweightCombo(QWidget *parent) :
    QComboBox(parent), onlyFixed(false) {

    setIconSize(QSize(32, 16));
    init();
    connect(this, SIGNAL(currentIndexChanged(int)),
        this, SLOT(lineweightChanged(int)));
}

void RLineweightCombo::lineweightChanged(int index) {
    if (itemData(index).value<RLineweight::Lineweight> ()
            == RLineweight::WeightInvalid) {
        return;
    }
    currentLineweight = itemData(index).value<RLineweight::Lineweight> ();
    emit valueChanged(currentLineweight);
}

void RLineweightCombo::init() {
    clear();
    setMaxVisibleItems(12);
    QVariant v;
    QListIterator<QPair<QString, RLineweight::Lineweight> > it(
            RLineweight::getList(onlyFixed));

    while (it.hasNext()) {
        QPair<QString, RLineweight::Lineweight> p = it.next();
        v.setValue<RLineweight::Lineweight> (p.second);
        addItem(RLineweight::getIcon(p.second), RLineweight::tr(
                (const char*) p.first.toUtf8()), v);
    }

    if (!onlyFixed) {
        setLineweight(RLineweight::WeightByLayer);
    } else {
        setLineweight(RLineweight::Weight025);
    }
}

bool RLineweightCombo::getOnlyFixed() {
    return onlyFixed;
}

void RLineweightCombo::setOnlyFixed(bool onlyFixed) {
    this->onlyFixed = onlyFixed;
    init();
}

RLineweight::Lineweight RLineweightCombo::getLineweight() {
    return itemData(currentIndex()).value<RLineweight::Lineweight> ();
}

void RLineweightCombo::setLineweight(RLineweight::Lineweight lw) {
    for (int i = 0; i < count(); ++i) {
        if (itemData(i).isValid() &&
          itemData(i).value<RLineweight::Lineweight> () == lw) {
            setCurrentIndex(i);
            return;
        }
    }
}
