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

#ifndef RLINETYPE_H
#define RLINETYPE_H

#include "core_global.h"

#include <QColor>
#include <QCoreApplication>
#include <QIcon>
#include <QMetaType>
#include <QString>

#include "RLinetypePattern.h"
#include "RObject.h"
#include "RPropertyTypeId.h"
#include "RVector.h"

class RDocument;
class RTransaction;



/**
 * Represents a linetype in a drawing. A linetype is an object (RObject).
 * A drawing contains and owns a set of linetypes.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 */
class QCADCORE_EXPORT RLinetype: public RObject {

    //Q_DECLARE_TR_FUNCTIONS(RLinetype);

public:
    static RPropertyTypeId PropertyName;
    static RPropertyTypeId PropertyDescription;

public:
    RLinetype(RDocument* document=NULL);
    RLinetype(RDocument* document, const RLinetypePattern& pattern);

    virtual ~RLinetype();

    static void init();

    virtual RLinetype* clone() const {
        return new RLinetype(*this);
    }

    QString getName() const {
        return pattern.getName();
    }

    void setName(const QString& n) {
        pattern.setName(n);
    }

    QString getDescription() const {
        return pattern.getDescription();
    }

    void setDescription(const QString& d) {
        pattern.setDescription(d);
    }

    bool isValid() const;

    //static QList<QPair<QString, RLinetype> > getList(bool onlyFixed = false);

    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);
    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);

    virtual bool isSelectedForPropertyEditing();

    RLinetypePattern getPattern() const;
    void setPattern(const RLinetypePattern& p);

//    static QIcon getIcon(const RLinetype& linetype);
//  static QString getTitle(const RLinetype& linetype);

    bool operator==(const RLinetype & linetype) const;
    bool operator!=(const RLinetype & linetype) const;
    bool operator<(const RLinetype & linetype) const;

//private:
//    static void init(const QString& cn, const RLinetype& c);

private:
    RLinetypePattern pattern;
    //QString name;
    //QString description;
    //int flags;
    //int numberOfDashes;
    //double patternLength;
    //double* pattern;
    //static QList<QPair<QString, RLinetype> > list;
    //static QMap<RLinetype, QIcon> iconMap;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RLinetype& l);

Q_DECLARE_METATYPE(RLinetype)
Q_DECLARE_METATYPE(RLinetype*)
Q_DECLARE_METATYPE(QSharedPointer<RLinetype>)
Q_DECLARE_METATYPE(QSharedPointer<RLinetype>*)
typedef QPair<QString, RLinetype> _RPairStringRLinetype;
Q_DECLARE_METATYPE(_RPairStringRLinetype)
Q_DECLARE_METATYPE(QList< _RPairStringRLinetype >)

#endif
