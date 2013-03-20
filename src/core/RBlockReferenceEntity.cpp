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
#include "RBlockReferenceEntity.h"
#include "RExporter.h"
#include "RSettings.h"
#include "RStorage.h"

RPropertyTypeId RBlockReferenceEntity::PropertyCustom;
RPropertyTypeId RBlockReferenceEntity::PropertyHandle;
RPropertyTypeId RBlockReferenceEntity::PropertyType;
RPropertyTypeId RBlockReferenceEntity::PropertyBlock;
RPropertyTypeId RBlockReferenceEntity::PropertyLayer;
RPropertyTypeId RBlockReferenceEntity::PropertyLinetype;
RPropertyTypeId RBlockReferenceEntity::PropertyLineweight;
RPropertyTypeId RBlockReferenceEntity::PropertyColor;
RPropertyTypeId RBlockReferenceEntity::PropertyDrawOrder;

RPropertyTypeId RBlockReferenceEntity::PropertyReferencedBlock;
RPropertyTypeId RBlockReferenceEntity::PropertyPositionX;
RPropertyTypeId RBlockReferenceEntity::PropertyPositionY;
RPropertyTypeId RBlockReferenceEntity::PropertyPositionZ;
RPropertyTypeId RBlockReferenceEntity::PropertyScaleX;
RPropertyTypeId RBlockReferenceEntity::PropertyScaleY;
RPropertyTypeId RBlockReferenceEntity::PropertyScaleZ;
RPropertyTypeId RBlockReferenceEntity::PropertyRotation;


RBlockReferenceEntity::RBlockReferenceEntity(RDocument* document,
    const RBlockReferenceData& data, RObject::Id objectId) :
    REntity(document, objectId), data(document, data),
    recursionDepth(0) {
//  if (data.getDocument() == NULL) {
//      return;
//  }
//  RBlock::Id id = &this->data.blockId;
//  while (data.getDocument()->getBlockName(id) != "*Model_Space") {
//      QSharedPointer<RBlock> block = data.getDocument()->queryBlock(id);
//      if (block.isNull()) {
//          break;Y
//      }
//      id = block->getId();
//  }
}

RBlockReferenceEntity::~RBlockReferenceEntity() {
}

void RBlockReferenceEntity::init() {
    RBlockReferenceEntity::PropertyCustom.generateId(typeid(RBlockReferenceEntity), RObject::PropertyCustom);
    RBlockReferenceEntity::PropertyHandle.generateId(typeid(RBlockReferenceEntity), RObject::PropertyHandle);
    RBlockReferenceEntity::PropertyType.generateId(typeid(RBlockReferenceEntity), REntity::PropertyType);
    RBlockReferenceEntity::PropertyBlock.generateId(typeid(RBlockReferenceEntity), REntity::PropertyBlock);
    RBlockReferenceEntity::PropertyLayer.generateId(typeid(RBlockReferenceEntity), REntity::PropertyLayer);
    RBlockReferenceEntity::PropertyLinetype.generateId(typeid(RBlockReferenceEntity), REntity::PropertyLinetype);
    RBlockReferenceEntity::PropertyLineweight.generateId(typeid(RBlockReferenceEntity), REntity::PropertyLineweight);
    RBlockReferenceEntity::PropertyColor.generateId(typeid(RBlockReferenceEntity), REntity::PropertyColor);
    RBlockReferenceEntity::PropertyDrawOrder.generateId(typeid(RBlockReferenceEntity), REntity::PropertyDrawOrder);

    RBlockReferenceEntity::PropertyReferencedBlock.generateId(typeid(RBlockReferenceEntity), "", QT_TRANSLATE_NOOP("REntity", "Referenced Block"));
    RBlockReferenceEntity::PropertyPositionX.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "X"));
    RBlockReferenceEntity::PropertyPositionY.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RBlockReferenceEntity::PropertyPositionZ.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RBlockReferenceEntity::PropertyScaleX.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Scale"), QT_TRANSLATE_NOOP("REntity", "X"));
    RBlockReferenceEntity::PropertyScaleY.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Scale"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RBlockReferenceEntity::PropertyScaleZ.generateId(typeid(RBlockReferenceEntity), QT_TRANSLATE_NOOP("REntity", "Scale"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RBlockReferenceEntity::PropertyRotation.generateId(typeid(RBlockReferenceEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));
}

bool RBlockReferenceEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value) {
    bool ret = REntity::setProperty(propertyTypeId, value);

    ret = ret || RObject::setMember(data.position.x, value, PropertyPositionX == propertyTypeId);
    ret = ret || RObject::setMember(data.position.y, value, PropertyPositionY == propertyTypeId);
    ret = ret || RObject::setMember(data.position.z, value, PropertyPositionZ == propertyTypeId);

    ret = ret || RObject::setMember(data.scaleFactors.x, value, PropertyScaleX == propertyTypeId && fabs(value.toDouble())>RS::PointTolerance);
    ret = ret || RObject::setMember(data.scaleFactors.y, value, PropertyScaleY == propertyTypeId && fabs(value.toDouble())>RS::PointTolerance);
    ret = ret || RObject::setMember(data.scaleFactors.z, value, PropertyScaleZ == propertyTypeId && fabs(value.toDouble())>RS::PointTolerance);

    ret = ret || RObject::setMember(data.rotation, value, PropertyRotation == propertyTypeId);

    if (propertyTypeId == PropertyReferencedBlock) {
        if (value.type() == QVariant::Int ||
            value.type() == QVariant::LongLong) {

            ret = ret || RObject::setMember(
                getData().referencedBlockId, value.toInt(), true);
        } else if (value.type() == QVariant::String) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                ret = ret || RObject::setMember(getData().referencedBlockId,
                        document->getBlockId(value.toString()), true);
            }
        }
    }

    if (ret) {
        data.update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RBlockReferenceEntity::getProperty(
        RPropertyTypeId propertyTypeId,
        bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyType) {
        return qMakePair(QVariant(RS::EntityBlockRef),
            RPropertyAttributes(RPropertyAttributes::ReadOnly));
    } else if (propertyTypeId == PropertyPositionX) {
        return qMakePair(QVariant(data.position.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionY) {
        return qMakePair(QVariant(data.position.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionZ) {
        return qMakePair(QVariant(data.position.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyScaleX) {
        return qMakePair(QVariant(data.scaleFactors.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyScaleY) {
        return qMakePair(QVariant(data.scaleFactors.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyScaleZ) {
        return qMakePair(QVariant(data.scaleFactors.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyRotation) {
        return qMakePair(QVariant(data.rotation), 
            RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyReferencedBlock) {
        if (humanReadable) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                RPropertyAttributes attr;
                // TODO
                if (!noAttributes) {
                    QSet<QString> blockNames = document->getBlockNames();
                    QSet<QString> filtered;
                    QSet<QString>::iterator it;
                    for (it=blockNames.begin(); it!=blockNames.end(); it++) {
                        if (!(*it).startsWith("*")) {
                            filtered.insert(*it);
                        }
                    }
                    attr.setChoices(filtered);
                }
                return qMakePair(QVariant(document->getBlockName(
                        getData().getReferencedBlockId())), attr);
            }
        } else {
            return qMakePair(QVariant(getData().getReferencedBlockId()),
                    RPropertyAttributes());
        }
    }
    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}

void RBlockReferenceEntity::exportEntity(RExporter& e, bool preview) const {
    const RDocument* document = getDocument();
    if (document==NULL) {
        qWarning() << "RBlockReferenceEntity::exportEntity: document is NULL";
        return;
    }

    recursionDepth++;

    /*
    if (recursionDepth>10) {
        recursionDepth--;
        qWarning("RBlockReferenceEntity::exportEntity: "
            "maximum recursion depth reached");
        return;
    }
    */

    data.update();

    QSet<REntity::Id> ids = document->queryBlockEntities(data.referencedBlockId);
    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);
    int i;
    QList<REntity::Id>::iterator it;
    for (it = list.begin(), i = 0; it != list.end(); it++, i++) {
        if (preview && i>RSettings::getPreviewEntities()) {
            break;
        }

        QSharedPointer<REntity> entity = data.queryEntity(*it);
        if (entity.isNull()) {
            qWarning("RBlockReferenceEntity::exportEntity: "
                "entity %d is NULL", *it);
            continue;
        }
        e.exportEntity(*entity, true);
    }

    // too slow:
//    RDebug::startTimer(4);

//    if (preview) {
//        // TODO: if we interrupted to limit the preview, add bounding box to preview
//        RBox bb = data.getBoundingBox();
//        QList<RLine> l = bb.getLines2d();
//        for (int k=0; k<l.count(); ++k) {
//            e.exportLine(l[k]);
//        }
//    }

//    RDebug::stopTimer(4, "bb");

    recursionDepth--;
}

void RBlockReferenceEntity::print(QDebug dbg) const {
    dbg.nospace() << "RBlockReferenceEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", position: " << getPosition();
    dbg.nospace() << ", scale: " << getScaleFactors();
    dbg.nospace() << ", rotation: " << getRotation();
    dbg.nospace() << ", referencedBlockId: " << getReferencedBlockId();
    dbg.nospace() << ")";
}
