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
#include <QColorDialog>
#include <QColor>

#include "RColorCombo.h"
#include "RColor.h"

RColorCombo::RColorCombo(QWidget *parent) :
    QComboBox(parent), onlyFixed(false), showAlphaChannel(false) {
    setIconSize(QSize(16, 10));
    init();
    connect(this, SIGNAL(currentIndexChanged(int)),
            this, SLOT(colorChanged(int)));
}

void RColorCombo::init() {
    clear();
    setMaxVisibleItems(20);
    QVariant v;
    QListIterator<QPair<QString, RColor> > it(RColor::getList(onlyFixed));
    QColor prev;

    int i = 0;
    bool lastIsSeparator = false;
    while (it.hasNext()) {
        QPair<QString, RColor> p = it.next();

        if (p.second.isValid()) {
            v.setValue(p.second);
            addItem(RColor::getIcon(p.second, iconSize()), p.first, v);
            lastIsSeparator = false;
        } else {
            // separator:
            if (p.first=="---") {
                if (!lastIsSeparator) {
                    insertSeparator(count());
                }
                lastIsSeparator = true;
                continue;
            }
            else {
                // others...
                if (!lastIsSeparator) {
                    insertSeparator(count());
                }
                addItem(RColor::getIcon(p.second, iconSize()), p.first);
                lastIsSeparator = false;
                continue;
            }
        }

//        if (p.second==RColor(QString("#ffffff")) && prev==RColor(QString("#c0c0c0")) && i<25) {
//            if (!lastIsSeparator) {
//                insertSeparator(count());
//            }
//            lastIsSeparator = true;
//        }

        prev = p.second;
        i++;
    }

    if (!onlyFixed) {
        setColor(RColor(RColor::ByLayer));
    } else {
        setColor(RColor(Qt::black));
    }
}

bool RColorCombo::getOnlyFixed() {
    return onlyFixed;
}

void RColorCombo::setOnlyFixed(bool onlyFixed) {
    this->onlyFixed = onlyFixed;
    init();
}

bool RColorCombo::getShowAlphaChannel() {
    return showAlphaChannel;
}

void RColorCombo::setShowAlphaChannel(bool showAlphaChannel) {
    this->showAlphaChannel = showAlphaChannel;
    init();
}

void RColorCombo::colorChanged(int index) {
    if (index<0) {
        return;
    }

    emit dialogRunning(true);
    if (!itemData(index).isValid()) {
        QColor clr;
        if (isVisible()) {
            clr = QColorDialog::getColor(currentColor, NULL, "",
                    showAlphaChannel ? QColorDialog::ShowAlphaChannel
                            : (QColorDialog::ColorDialogOption) 0);
        }
        if (clr.isValid()) {
            currentColor = clr;
        }
        setColor(currentColor);
    } else {
        if (!itemData(index).value<RColor> ().isValid()) {
            return;
        }
        currentColor = itemData(index).value<RColor> ();
    }
    emit valueChanged(currentColor);
    emit dialogRunning(false);
}

RColor RColorCombo::getColor() {
    return currentColor;
}

void RColorCombo::setColor(const RColor& col) {
    for (int i = 0; i < count(); ++i) {
        if (itemData(i).isValid()) {
            RColor c = itemData(i).value<RColor> ();
            if (c==col) {
                currentColor = c;
                setCurrentIndex(i);
                return;
            }
        }
    }
    if (!col.isFixed() || !col.isValid()) {
        return;
    }
    currentColor = col;
    QVariant v;
    v.setValue(currentColor);
    blockSignals(true);
    QString custom = tr("Custom");
    int i = findText(custom, Qt::MatchExactly);
    if (i != -1) {
        removeItem(i);
    }
    insertItem(count() - 1, RColor::getIcon(currentColor, iconSize()), custom, v);
    setCurrentIndex(count() - 2);
    blockSignals(false);
}
