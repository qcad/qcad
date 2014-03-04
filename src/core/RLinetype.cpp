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
#include "RLinetype.h"
#include "RSettings.h"

RPropertyTypeId RLinetype::PropertyName;
QList<QPair<QString, RLinetype> > RLinetype::list;
QMap<RLinetype, QIcon> RLinetype::iconMap;

RLinetype::RLinetype(RDocument* document) : RObject(document) {
}

RLinetype::RLinetype(RDocument* document, const QString& name)
    : RObject(document), name(name) {
}

RLinetype::~RLinetype() {
}

bool RLinetype::operator==(const RLinetype & linetype) const {
    return getName().compare(linetype.getName(), Qt::CaseInsensitive) == 0;
}

bool RLinetype::operator!=(const RLinetype & linetype) const{
    return !operator ==(linetype);
}

void RLinetype::init() {
    RLinetype::PropertyName.generateId(typeid(RLinetype), "", "Name");

    init(tr("By Layer"), RLinetype(NULL, "BYLAYER"));
    init(tr("By Block"), RLinetype(NULL, "BYBLOCK"));
    init(tr("Continuous"), RLinetype(NULL, "CONTINUOUS"));
    init(tr("Dot"), RLinetype(NULL, "DOT"));
    init(tr("Dot (small)"), RLinetype(NULL, "DOT2"));
    init(tr("Dot (large)"), RLinetype(NULL, "DOTX2"));
    init(tr("Dash"), RLinetype(NULL, "DASHED"));
    init(tr("Dash (small)"), RLinetype(NULL, "DASHED2"));
    init(tr("Dash (large)"), RLinetype(NULL, "DASHEDX2"));
    init(tr("Dash Dot"), RLinetype(NULL, "DASHDOT"));
    init(tr("Dash Dot (small)"), RLinetype(NULL, "DASHDOT2"));
    init(tr("Dash Dot (large)"), RLinetype(NULL, "DASHDOTX2"));
    init(tr("Divide"), RLinetype(NULL, "DIVIDE"));
    init(tr("Divide (small)"), RLinetype(NULL, "DIVIDE2"));
    init(tr("Divide (large)"), RLinetype(NULL, "DIVIDEX2"));
    init(tr("Center"), RLinetype(NULL, "CENTER"));
    init(tr("Center (small)"), RLinetype(NULL, "CENTER2"));
    init(tr("Center (large)"), RLinetype(NULL, "CENTERX2"));
    init(tr("Border"), RLinetype(NULL, "BORDER"));
    init(tr("Border (small)"), RLinetype(NULL, "BORDER2"));
    init(tr("Border (large)"), RLinetype(NULL, "BORDERX2"));
}

void RLinetype::init(const QString& cn, const RLinetype& c) {
    list.append(QPair<QString, RLinetype> (cn, c));
    iconMap.insert(c, getIcon(c));
}

QList<QPair<QString, RLinetype> > RLinetype::getList(bool onlyFixed) {
    if (!onlyFixed) {
        return list;
    }

    QList<QPair<QString, RLinetype> > l = list;

    // remove "By Layer"
    l.removeAt(0);
    // remove "By Block"
    l.removeAt(0);

//  // remove "By Layer"
//  QString n = RLinetype(RLinetype::ByLayer).getName();
//  l.removeAll(QPair<QString, RLinetype> (n, RLinetype(RLinetype::ByLayer)));
//
//  // remove "By Block"
//  n = RLinetype(RLinetype::ByBlock).getName();
//  l.removeAll(QPair<QString, RLinetype> (n, RLinetype(RLinetype::ByBlock)));

    return l;
}

bool RLinetype::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    Q_UNUSED(transaction);

    bool ret = false;
    ret = RObject::setMember(name, value, PropertyName == propertyTypeId);
//  ret = ret || RObject::setProperty(frozen, value, PropertyFrozen == propertyTypeId);
    return ret;
}

QPair<QVariant, RPropertyAttributes> RLinetype::getProperty(
        RPropertyTypeId& propertyTypeId, bool /*humanReadable*/,
        bool /*noAttributes*/) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(name), RPropertyAttributes());
    }

    return qMakePair(QVariant(), RPropertyAttributes());
}

bool RLinetype::isSelectedForPropertyEditing() {
    return false;
}

bool RLinetype::isValid() const {
    return !name.isNull();
}


QString RLinetype::getTitle(const RLinetype& linetype) {
    QListIterator<QPair<QString, RLinetype> > i(list);
    while (i.hasNext()) {
        QPair<QString, RLinetype> p = i.next();
        if (p.second == linetype) {
            return p.first;
        }
    }
    return "";
}

QIcon RLinetype::getIcon(const RLinetype& linetype) {
    if (!RSettings::isGuiEnabled()) {
        return QIcon();
    }

    if (iconMap.contains(linetype)) {
        return iconMap[linetype];
    }

    if (linetype == RLinetype(NULL, "BYBLOCK")) {
        return QIcon(":/qcad/linetype_byblock.svg");
    }
    if (linetype == RLinetype(NULL, "BYLAYER")) {
        return QIcon(":/qcad/linetype_bylayer.svg");
    }
    if (linetype == RLinetype(NULL, "CONTINUOUS")) {
        return QIcon(":/qcad/linetype_continuous.svg");
    }
    if (linetype == RLinetype(NULL, "DOT")) {
        return QIcon(":/qcad/linetype_dot.svg");
    }
    if (linetype == RLinetype(NULL, "DOT2")) {
        return QIcon(":/qcad/linetype_dot2.svg");
    }
    if (linetype == RLinetype(NULL, "DOTX2")) {
        return QIcon(":/qcad/linetype_dotx2.svg");
    }
    if (linetype == RLinetype(NULL, "DASHED")) {
        return QIcon(":/qcad/linetype_dashed.svg");
    }
    if (linetype == RLinetype(NULL, "DASHED2")) {
        return QIcon(":/qcad/linetype_dashed2.svg");
    }
    if (linetype == RLinetype(NULL, "DASHEDX2")) {
        return QIcon(":/qcad/linetype_dashedx2.svg");
    }
    if (linetype == RLinetype(NULL, "DASHDOT")) {
        return QIcon(":/qcad/linetype_dashdot.svg");
    }
    if (linetype == RLinetype(NULL, "DASHDOT2")) {
        return QIcon(":/qcad/linetype_dashdot2.svg");
    }
    if (linetype == RLinetype(NULL, "DASHDOTX2")) {
        return QIcon(":/qcad/linetype_dashdotx2.svg");
    }
    if (linetype == RLinetype(NULL, "DIVIDE")) {
        return QIcon(":/qcad/linetype_divide.svg");
    }
    if (linetype == RLinetype(NULL, "DIVIDE2")) {
        return QIcon(":/qcad/linetype_divide2.svg");
    }
    if (linetype == RLinetype(NULL, "DIVIDEX2")) {
        return QIcon(":/qcad/linetype_dividex2.svg");
    }
    if (linetype == RLinetype(NULL, "CENTER")) {
        return QIcon(":/qcad/linetype_center.svg");
    }
    if (linetype == RLinetype(NULL, "CENTER2")) {
        return QIcon(":/qcad/linetype_center2.svg");
    }
    if (linetype == RLinetype(NULL, "CENTERX2")) {
        return QIcon(":/qcad/linetype_centerx2.svg");
    }
    if (linetype == RLinetype(NULL, "BORDER")) {
        return QIcon(":/qcad/linetype_border.svg");
    }
    if (linetype == RLinetype(NULL, "BORDER2")) {
        return QIcon(":/qcad/linetype_border2.svg");
    }
    if (linetype == RLinetype(NULL, "BORDERX2")) {
        return QIcon(":/qcad/linetype_borderx2.svg");
    }

    return QIcon();
}

bool RLinetype::operator<(const RLinetype & linetype) const {
    return getName().toLower() < linetype.getName().toLower();
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RLinetype& l) {
    dbg.nospace() << "RLinetype(NULL, " << l.getName() << ")";
    return dbg.space();
}
