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
#include <QAbstractItemView>
#include <QSize>
#include <QPainter>

#include "RDebug.h"
#include "RLinetypeCombo.h"

RLinetypeCombo::RLinetypeCombo(QWidget* parent) :
    QComboBox(parent), onlyFixed(false) {
    setIconSize(QSize(32, 16));

    //init();

    //model()->setData()
    setItemDelegate(new RLinetypeComboDelegate(this));

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

    for (int i=0; i<count(); i++) {
        setItemData(i, Qt::AlignTop, Qt::TextAlignmentRole);
    }
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

    //qDebug() << "row: " << index.row();

    RLinetypePattern pattern = combo->getLinetypePatternAt(index.row());

    //qDebug() << "pat: " << pattern;

    QPen pen;
    QVector<qreal> p = pattern.getScreenBasedLinetype(true);
    //qDebug() << "p: " << p;
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
