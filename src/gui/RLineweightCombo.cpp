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
#include <QDebug>
#include <QSize>

#include "RDebug.h"
#include "RLineweightCombo.h"
#include "RSettings.h"

RLineweightCombo::RLineweightCombo(QWidget *parent) :
    QComboBox(parent), onlyFixed(false), noDefault(false) {

    setIconSize(QSize(16, 16));
    init();
    connect(this, SIGNAL(currentIndexChanged(int)),
        this, SLOT(lineweightChanged(int)));
}

void RLineweightCombo::lineweightChanged(int index) {
    if (itemData(index).value<RLineweight::Lineweight> () == RLineweight::WeightInvalid) {
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
            RLineweight::getList(onlyFixed, noDefault));

    while (it.hasNext()) {
        QPair<QString, RLineweight::Lineweight> p = it.next();
        v.setValue<RLineweight::Lineweight> (p.second);
        addItem(RLineweight::getIcon(p.second, QSize(16, 16)), p.first, v);
    }

    if (!onlyFixed) {
        setLineweight(RLineweight::WeightByLayer);
    } else {
        // TODO: make configurable:
        //RLineweight::Lineweight lw = RSettings::getIntValue("");
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

bool RLineweightCombo::getNoDefault() {
    return noDefault;
}

void RLineweightCombo::setNoDefault(bool noDefault) {
    this->noDefault = noDefault;
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
