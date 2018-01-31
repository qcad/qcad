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

#ifndef RATTRIBUTEDEFINITIONDATA_H
#define RATTRIBUTEDEFINITIONDATA_H

#include "entity_global.h"

#include <QTextLayout>

#include "RDocument.h"
#include "RTextData.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a block attribute definition entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RAttributeDefinitionData: public RTextBasedData {
    friend class RAttributeDefinitionEntity;

protected:
    RAttributeDefinitionData(RDocument* document, const RAttributeDefinitionData& data);

public:
    RAttributeDefinitionData() {}
    RAttributeDefinitionData(const RTextBasedData& textData, const QString& tag, const QString& prompt);
    virtual ~RAttributeDefinitionData() {}

    virtual RS::EntityType getType() const {
        return RS::EntityAttributeDefinition;
    }
    QString getTag() const {
        return tag;
    }

    void setTag(const QString& t) {
        tag = t;
    }

    QString getPrompt() const {
        return prompt;
    }

    void setPrompt(const QString& p) {
        prompt = p;
    }

    virtual QString getRenderedText(bool escUnicode=false) const;

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, const RAttributeDefinitionData& t);

private:
    QString tag;
    QString prompt;
};

Q_DECLARE_METATYPE(RAttributeDefinitionData)
Q_DECLARE_METATYPE(RAttributeDefinitionData*)
Q_DECLARE_METATYPE(const RAttributeDefinitionData*)
Q_DECLARE_METATYPE(QSharedPointer<RAttributeDefinitionData>)
Q_DECLARE_METATYPE(QSharedPointer<RAttributeDefinitionData>*)

#endif
