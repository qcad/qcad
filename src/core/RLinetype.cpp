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
RPropertyTypeId RLinetype::PropertyDescription;
//QList<QPair<QString, RLinetype> > RLinetype::list;
//QMap<RLinetype, QIcon> RLinetype::iconMap;

RLinetype::RLinetype(RDocument* document) : RObject(document) {
}

RLinetype::RLinetype(RDocument* document, const RLinetypePattern& pattern)
    : RObject(document), pattern(pattern) {
}

RLinetype::~RLinetype() {
}

bool RLinetype::operator==(const RLinetype & linetype) const {
    return getName().compare(linetype.getName(), Qt::CaseInsensitive) == 0;
}

bool RLinetype::operator!=(const RLinetype & linetype) const{
    return !operator ==(linetype);
}

//void RLinetype::init() {
//    RLinetype::PropertyName.generateId(typeid(RLinetype), "", "Name");

//    init(tr("By Layer"), RLinetype(NULL, "BYLAYER"));
//    init(tr("By Block"), RLinetype(NULL, "BYBLOCK"));
//    init(tr("Continuous"), RLinetype(NULL, "CONTINUOUS"));

//    // set up linetypes
//    RLinetypePatternMap::init();
//}

//void RLinetype::init(const QString& cn, const RLinetype& c) {
//    list.append(QPair<QString, RLinetype> (cn, c));
//    iconMap.insert(c, getIcon(c));
//}

//QList<QPair<QString, RLinetype> > RLinetype::getList(bool onlyFixed) {
//    if (!onlyFixed) {
//        return list;
//    }

//    QList<QPair<QString, RLinetype> > l = list;

//    // remove "By Layer"
//    l.removeAt(0);
//    // remove "By Block"
//    l.removeAt(0);

////  // remove "By Layer"
////  QString n = RLinetype(RLinetype::ByLayer).getName();
////  l.removeAll(QPair<QString, RLinetype> (n, RLinetype(RLinetype::ByLayer)));
////
////  // remove "By Block"
////  n = RLinetype(RLinetype::ByBlock).getName();
////  l.removeAll(QPair<QString, RLinetype> (n, RLinetype(RLinetype::ByBlock)));

//    return l;
//}

void RLinetype::init() {
    RLinetype::PropertyName.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Name"));
    RLinetype::PropertyDescription.generateId(typeid(RLinetype), "", QT_TRANSLATE_NOOP("RLinetype", "Description"));
}

bool RLinetype::setProperty(RPropertyTypeId propertyTypeId,
    const QVariant& value, RTransaction* transaction) {

    Q_UNUSED(transaction);

    bool ret = false;
    ret = RObject::setMember(pattern.name, value, PropertyName == propertyTypeId);
//  ret = ret || RObject::setProperty(frozen, value, PropertyFrozen == propertyTypeId);
    return ret;
}

QPair<QVariant, RPropertyAttributes> RLinetype::getProperty(
        RPropertyTypeId& propertyTypeId, bool /*humanReadable*/,
        bool /*noAttributes*/) {

    if (propertyTypeId == PropertyName) {
        return qMakePair(QVariant(pattern.name), RPropertyAttributes());
    }

    return qMakePair(QVariant(), RPropertyAttributes());
}

bool RLinetype::isSelectedForPropertyEditing() {
    return false;
}

bool RLinetype::isValid() const {
    return !pattern.name.isNull();
}


//QString RLinetype::getTitle(const RLinetype& linetype) {
//    QListIterator<QPair<QString, RLinetype> > i(list);
//    while (i.hasNext()) {
//        QPair<QString, RLinetype> p = i.next();
//        if (p.second == linetype) {
//            return p.first;
//        }
//    }
//    return "";
//}

RLinetypePattern RLinetype::getPattern() const {
    return pattern;
}

void RLinetype::setPattern(const RLinetypePattern& p) {
    pattern = p;
}

//QIcon RLinetype::getIcon(const RLinetype& linetype) {
//    if (!RSettings::isGuiEnabled()) {
//        return QIcon();
//    }

//    if (iconMap.contains(linetype)) {
//        return iconMap[linetype];
//    }

//    if (linetype == RLinetype(NULL, "BYBLOCK")) {
//        return QIcon(":/qcad/linetype_byblock.svg");
//    }
//    if (linetype == RLinetype(NULL, "BYLAYER")) {
//        return QIcon(":/qcad/linetype_bylayer.svg");
//    }
//    if (linetype == RLinetype(NULL, "CONTINUOUS")) {
//        return QIcon(":/qcad/linetype_continuous.svg");
//    }
//    if (linetype == RLinetype(NULL, "DOT")) {
//        return QIcon(":/qcad/linetype_dot.svg");
//    }
//    if (linetype == RLinetype(NULL, "DOT2")) {
//        return QIcon(":/qcad/linetype_dot2.svg");
//    }
//    if (linetype == RLinetype(NULL, "DOTX2")) {
//        return QIcon(":/qcad/linetype_dotx2.svg");
//    }
//    if (linetype == RLinetype(NULL, "DASHED")) {
//        return QIcon(":/qcad/linetype_dashed.svg");
//    }
//    if (linetype == RLinetype(NULL, "DASHED2")) {
//        return QIcon(":/qcad/linetype_dashed2.svg");
//    }
//    if (linetype == RLinetype(NULL, "DASHEDX2")) {
//        return QIcon(":/qcad/linetype_dashedx2.svg");
//    }
//    if (linetype == RLinetype(NULL, "DASHDOT")) {
//        return QIcon(":/qcad/linetype_dashdot.svg");
//    }
//    if (linetype == RLinetype(NULL, "DASHDOT2")) {
//        return QIcon(":/qcad/linetype_dashdot2.svg");
//    }
//    if (linetype == RLinetype(NULL, "DASHDOTX2")) {
//        return QIcon(":/qcad/linetype_dashdotx2.svg");
//    }
//    if (linetype == RLinetype(NULL, "DIVIDE")) {
//        return QIcon(":/qcad/linetype_divide.svg");
//    }
//    if (linetype == RLinetype(NULL, "DIVIDE2")) {
//        return QIcon(":/qcad/linetype_divide2.svg");
//    }
//    if (linetype == RLinetype(NULL, "DIVIDEX2")) {
//        return QIcon(":/qcad/linetype_dividex2.svg");
//    }
//    if (linetype == RLinetype(NULL, "CENTER")) {
//        return QIcon(":/qcad/linetype_center.svg");
//    }
//    if (linetype == RLinetype(NULL, "CENTER2")) {
//        return QIcon(":/qcad/linetype_center2.svg");
//    }
//    if (linetype == RLinetype(NULL, "CENTERX2")) {
//        return QIcon(":/qcad/linetype_centerx2.svg");
//    }
//    if (linetype == RLinetype(NULL, "BORDER")) {
//        return QIcon(":/qcad/linetype_border.svg");
//    }
//    if (linetype == RLinetype(NULL, "BORDER2")) {
//        return QIcon(":/qcad/linetype_border2.svg");
//    }
//    if (linetype == RLinetype(NULL, "BORDERX2")) {
//        return QIcon(":/qcad/linetype_borderx2.svg");
//    }

//    // return default bylayer
//    return QIcon(":/qcad/linetype_bylayer.svg");
//}

bool RLinetype::operator<(const RLinetype & linetype) const {
    return getName().toLower() < linetype.getName().toLower();
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, const RLinetype& l) {
    dbg.nospace() << "RLinetype(" << (RObject&)l << ", " << l.getPattern() << ")";
    return dbg.space();
}
