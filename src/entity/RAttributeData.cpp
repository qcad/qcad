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
#include "RAttributeData.h"
#include "RAttributeDefinitionData.h"


RAttributeData::RAttributeData(RDocument* document, const RAttributeData& data)
    : RTextBasedData(document, data), invisible(false) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RAttributeData::RAttributeData(const RTextBasedData& textData, RBlockReferenceEntity::Id blockReferenceId, const QString& tag)
    : RTextBasedData(textData), tag(tag), invisible(false) {

    setParentId(blockReferenceId);
}

QString RAttributeData::getRenderedText(bool escUnicode) const {
    return RTextBasedData::getRenderedText(escUnicode);
}

RLinetype::Id RAttributeData::getLinetypeId(bool resolve, const QStack<REntity*>& blockRefStack) const {
    if (document!=NULL && linetypeId==document->getLinetypeByBlockId()) {
        RObject::Id parentId = getParentId();
        if (parentId!=RObject::INVALID_ID) {
            QSharedPointer<REntity> blockRef = document->queryEntityDirect(parentId);
            if (!blockRef.isNull()) {
                return blockRef->getLinetypeId(resolve, blockRefStack);
            }
        }
    }

    return REntityData::getLinetypeId(resolve, blockRefStack);
}

RLineweight::Lineweight RAttributeData::getLineweight(bool resolve, const QStack<REntity*>& blockRefStack) const {
    if (document!=NULL && lineweight==RLineweight::WeightByBlock) {
        RObject::Id parentId = getParentId();
        if (parentId!=RObject::INVALID_ID) {
            QSharedPointer<REntity> blockRef = document->queryEntityDirect(parentId);
            if (!blockRef.isNull()) {
                return blockRef->getLineweight(resolve, blockRefStack);
            }
        }
    }

    return REntityData::getLineweight(resolve, blockRefStack);
}

RColor RAttributeData::getColor(bool resolve, const QStack<REntity*>& blockRefStack) const {
    if (document!=NULL && color.isByBlock()) {
        RObject::Id parentId = getParentId();
        if (parentId!=RObject::INVALID_ID) {
            QSharedPointer<REntity> blockRef = document->queryEntityDirect(parentId);
            if (!blockRef.isNull()) {
                return blockRef->getColor(resolve, blockRefStack);
            }
        }
    }

    return REntityData::getColor(resolve, blockRefStack);
}

QDebug operator<<(QDebug dbg, const RAttributeData& t) {
    dbg.nospace() << "RAttributeData("
                  << "text: " << t.getEscapedText()
                  << ", blockReferenceId: " << t.getParentId()
                  << ", tag: " << t.tag
                  << ", position: " << t.getPosition()
                  << ")";
    return dbg;
}
