/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

#ifndef RBLOCK_H
#define RBLOCK_H

#include "core_global.h"

#include <QString>
#include <QDebug>

#include "RGlobal.h"
#include "RObject.h"
#include "RVector.h"
#include "RPropertyTypeId.h"

class RDocument;
class RTransaction;

/**
 * Represents a block definition in a drawing.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RBlock: public RObject {
public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyName;
    static RPropertyTypeId PropertyFrozen;

public:
    RBlock();

    RBlock(RDocument* document, const QString& name, const RVector& origin);

    virtual ~RBlock();

    static void init();

    virtual RS::EntityType getType() const {
        return RS::ObjectBlock;
    }

    virtual RBlock* clone() const;

    QString getName() const {
        return name;
    }

    void setName(const QString& n);

    bool isFrozen() const {
        return frozen;
    }

    void setFrozen(bool on) {
        if (QString::compare(name, modelSpaceName, Qt::CaseInsensitive)!=0) {
            frozen = on;
        }
    }

    bool isAnonymous() const {
        return anonymous;
    }

    void setAnonymous(bool on) {
        if (QString::compare(name, modelSpaceName, Qt::CaseInsensitive)!=0) {
            anonymous = on;
        }
    }

    void setOrigin(const RVector& origin) {
        this->origin = origin;
    }

    RVector getOrigin() const {
        return origin;
    }

    virtual QPair<QVariant, RPropertyAttributes> getProperty(RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);
    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);

    virtual bool isSelectedForPropertyEditing();

public:
    static const QString modelSpaceName;

protected:
    /**
     * \nonscriptable
     */
    virtual void print(QDebug dbg) const;

private:
    QString name;
    bool frozen;
    bool anonymous;
    RVector origin;
};


Q_DECLARE_METATYPE(QSharedPointer<RBlock>)
Q_DECLARE_METATYPE(QSharedPointer<RBlock>*)
Q_DECLARE_METATYPE(RBlock)
Q_DECLARE_METATYPE(RBlock*)

#endif
