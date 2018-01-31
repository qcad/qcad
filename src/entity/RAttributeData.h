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

#ifndef RATTRIBUTEDATA_H
#define RATTRIBUTEDATA_H

#include "entity_global.h"

#include <QTextLayout>

#include "RBlockReferenceEntity.h"
#include "RDocument.h"
#include "RTextData.h"

class RAttributeDefinitionData;

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a block attribute entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RAttributeData: public RTextBasedData {
    friend class RAttributeEntity;

protected:
    RAttributeData(RDocument* document, const RAttributeData& data);

public:
    RAttributeData() {}
    RAttributeData(const RTextBasedData& textData, RBlockReferenceEntity::Id blockReferenceId, const QString& tag);
    virtual ~RAttributeData() {}

    virtual RS::EntityType getType() const {
        return RS::EntityAttribute;
    }
    virtual QString getRenderedText(bool escUnicode=false) const;

    QString getTag() const {
        return tag;
    }

    void setTag(const QString& t) {
        tag = t;
    }

    bool isInvisible() const {
        return invisible;
    }

    void setInvisible(bool i) {
        invisible = i;
    }

    virtual RLinetype::Id getLinetypeId(bool resolve, const QStack<REntity*>& blockRefStack) const;
    virtual RLineweight::Lineweight getLineweight(bool resolve, const QStack<REntity*>& blockRefStack) const;
    virtual RColor getColor(bool resolve, const QStack<REntity*>& blockRefStack) const;
    virtual RColor getColor() const {
        return RTextBasedData::getColor();
    }

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, const RAttributeData& t);

private:
    QString tag;
    bool invisible;
};

Q_DECLARE_METATYPE(RAttributeData)
Q_DECLARE_METATYPE(RAttributeData*)
Q_DECLARE_METATYPE(const RAttributeData*)
Q_DECLARE_METATYPE(QSharedPointer<RAttributeData>)
Q_DECLARE_METATYPE(QSharedPointer<RAttributeData>*)

#endif
