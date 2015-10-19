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
#include "RExporter.h"
#include "RSettings.h"
#include "RStorage.h"
#include "RViewportEntity.h"

RPropertyTypeId RViewportEntity::PropertyCustom;
RPropertyTypeId RViewportEntity::PropertyHandle;
RPropertyTypeId RViewportEntity::PropertyType;
RPropertyTypeId RViewportEntity::PropertyBlock;
RPropertyTypeId RViewportEntity::PropertyLayer;
RPropertyTypeId RViewportEntity::PropertyLinetype;
RPropertyTypeId RViewportEntity::PropertyLinetypeScale;
RPropertyTypeId RViewportEntity::PropertyLineweight;
RPropertyTypeId RViewportEntity::PropertyColor;
RPropertyTypeId RViewportEntity::PropertyDisplayedColor;
RPropertyTypeId RViewportEntity::PropertyDrawOrder;

RPropertyTypeId RViewportEntity::PropertyCenterX;
RPropertyTypeId RViewportEntity::PropertyCenterY;
RPropertyTypeId RViewportEntity::PropertyCenterZ;
RPropertyTypeId RViewportEntity::PropertyWidth;
RPropertyTypeId RViewportEntity::PropertyHeight;
RPropertyTypeId RViewportEntity::PropertyScale;
RPropertyTypeId RViewportEntity::PropertyViewCenterX;
RPropertyTypeId RViewportEntity::PropertyViewCenterY;
RPropertyTypeId RViewportEntity::PropertyViewTargetX;
RPropertyTypeId RViewportEntity::PropertyViewTargetY;
RPropertyTypeId RViewportEntity::PropertyViewTargetZ;


RViewportEntity::RViewportEntity(RDocument* document, const RViewportData& data,
        RObject::Id objectId) :
    REntity(document, objectId), data(document, data) {
}

RViewportEntity::~RViewportEntity() {
}

void RViewportEntity::init() {
    RViewportEntity::PropertyCustom.generateId(typeid(RViewportEntity), RObject::PropertyCustom);
    RViewportEntity::PropertyHandle.generateId(typeid(RViewportEntity), RObject::PropertyHandle);
    RViewportEntity::PropertyType.generateId(typeid(RViewportEntity), REntity::PropertyType);
    RViewportEntity::PropertyBlock.generateId(typeid(RViewportEntity), REntity::PropertyBlock);
    RViewportEntity::PropertyLayer.generateId(typeid(RViewportEntity), REntity::PropertyLayer);
    RViewportEntity::PropertyLinetype.generateId(typeid(RViewportEntity), REntity::PropertyLinetype);
    RViewportEntity::PropertyLinetypeScale.generateId(typeid(RViewportEntity), REntity::PropertyLinetypeScale);
    RViewportEntity::PropertyLineweight.generateId(typeid(RViewportEntity), REntity::PropertyLineweight);
    RViewportEntity::PropertyColor.generateId(typeid(RViewportEntity), REntity::PropertyColor);
    RViewportEntity::PropertyDisplayedColor.generateId(typeid(RViewportEntity), REntity::PropertyDisplayedColor);
    RViewportEntity::PropertyDrawOrder.generateId(typeid(RViewportEntity), REntity::PropertyDrawOrder);

    RViewportEntity::PropertyCenterX.generateId(typeid(RViewportEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "X"));
    RViewportEntity::PropertyCenterY.generateId(typeid(RViewportEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RViewportEntity::PropertyCenterZ.generateId(typeid(RViewportEntity), QT_TRANSLATE_NOOP("REntity", "Position"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RViewportEntity::PropertyWidth.generateId(typeid(RViewportEntity), "", QT_TRANSLATE_NOOP("REntity", "Width"));
    RViewportEntity::PropertyHeight.generateId(typeid(RViewportEntity), "", QT_TRANSLATE_NOOP("REntity", "Height"));
    RViewportEntity::PropertyScale.generateId(typeid(RViewportEntity), "", QT_TRANSLATE_NOOP("REntity", "Scale"));
    RViewportEntity::PropertyViewCenterX.generateId(typeid(RViewportEntity), QT_TRANSLATE_NOOP("REntity", "View Center"), QT_TRANSLATE_NOOP("REntity", "X"));
    RViewportEntity::PropertyViewCenterY.generateId(typeid(RViewportEntity), QT_TRANSLATE_NOOP("REntity", "View Center"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RViewportEntity::PropertyViewTargetX.generateId(typeid(RViewportEntity), QT_TRANSLATE_NOOP("REntity", "View Target"), QT_TRANSLATE_NOOP("REntity", "X"));
    RViewportEntity::PropertyViewTargetY.generateId(typeid(RViewportEntity), QT_TRANSLATE_NOOP("REntity", "View Target"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RViewportEntity::PropertyViewTargetZ.generateId(typeid(RViewportEntity), QT_TRANSLATE_NOOP("REntity", "View Target"), QT_TRANSLATE_NOOP("REntity", "Z"));
}

bool RViewportEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);
    ret = ret || RObject::setMember(data.center.x, value, PropertyCenterX == propertyTypeId);
    ret = ret || RObject::setMember(data.center.y, value, PropertyCenterY == propertyTypeId);
    ret = ret || RObject::setMember(data.center.z, value, PropertyCenterZ == propertyTypeId);
    ret = ret || RObject::setMember(data.width, value, PropertyWidth == propertyTypeId);
    ret = ret || RObject::setMember(data.height, value, PropertyHeight == propertyTypeId);
    ret = ret || RObject::setMember(data.scale, value, PropertyScale == propertyTypeId);
    ret = ret || RObject::setMember(data.viewCenter.x, value, PropertyViewCenterX == propertyTypeId);
    ret = ret || RObject::setMember(data.viewCenter.y, value, PropertyViewCenterY == propertyTypeId);
    ret = ret || RObject::setMember(data.viewTarget.x, value, PropertyViewTargetX == propertyTypeId);
    ret = ret || RObject::setMember(data.viewTarget.y, value, PropertyViewTargetY == propertyTypeId);
    ret = ret || RObject::setMember(data.viewTarget.z, value, PropertyViewTargetZ == propertyTypeId);
    return ret;
}

QPair<QVariant, RPropertyAttributes> RViewportEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes) {
    if (propertyTypeId == PropertyCenterX) {
        return qMakePair(QVariant(data.center.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterY) {
        return qMakePair(QVariant(data.center.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyCenterZ) {
        return qMakePair(QVariant(data.center.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyWidth) {
        return qMakePair(QVariant(data.width), RPropertyAttributes());
    } else if (propertyTypeId == PropertyHeight) {
        return qMakePair(QVariant(data.height), RPropertyAttributes());
    } else if (propertyTypeId == PropertyScale) {
        return qMakePair(QVariant(data.scale), RPropertyAttributes());
    } else if (propertyTypeId == PropertyViewCenterX) {
        return qMakePair(QVariant(data.viewCenter.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyViewCenterY) {
        return qMakePair(QVariant(data.viewCenter.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyViewTargetX) {
        return qMakePair(QVariant(data.viewTarget.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyViewTargetY) {
        return qMakePair(QVariant(data.viewTarget.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyViewTargetZ) {
        return qMakePair(QVariant(data.viewTarget.z), RPropertyAttributes());
    }
    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RViewportEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);
    // return;

    RDocument* doc = (RDocument*)getDocument();
    if (doc==NULL) {
        return;
    }

    RBox viewportBox(data.center, data.width, data.height);

    // viewport frame:
    e.setBrush(Qt::NoBrush);
    //qDebug() << "exporting viewport: " << viewportBox;
    e.exportRectangle(viewportBox.c1, viewportBox.c2);

    // clip rectangle export
    e.setClipping(true);

//    RBlockReferenceEntity modelSpace(doc, RBlockReferenceData(doc->getModelSpaceBlockId(), data.center, RVector(1,1), 0));
//    modelSpace.update();
//    modelSpace.exportEntity(e, preview);

    //e.exportPoint(data);
    RVector offset(0,0);
    offset -= data.viewCenter * data.scale;
    offset -= data.viewTarget * data.scale;

    qDebug() << "center: " << data.viewCenter;
    qDebug() << "target: " << data.viewTarget;

    // create temporary block reference to model space block:
    RBlockReferenceData modelSpaceData(
        doc,
        RBlockReferenceData(
            doc->getModelSpaceBlockId(),
            data.center + offset,
            RVector(data.scale, data.scale),
            0
        )
    );
    modelSpaceData.update();

    // render model space block reference into viewport:
    QSet<REntity::Id> ids = doc->queryBlockEntities(doc->getModelSpaceBlockId());
    QList<REntity::Id> list = doc->getStorage().orderBackToFront(ids);
    int i;
    QList<REntity::Id>::iterator it;
    for (it = list.begin(), i = 0; it != list.end(); it++, i++) {
        if (preview && i>RSettings::getPreviewEntities()) {
            break;
        }

        QSharedPointer<REntity> entity = modelSpaceData.queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }

        RBox bb = entity->getBoundingBox();
        if (!viewportBox.intersects(bb)) {
            continue;
        }

        entity->scaleVisualProperties(data.scale);

        e.exportEntity(*entity, preview, true);
    }

    e.setClipping(false);
}

void RViewportEntity::print(QDebug dbg) const {
    dbg.nospace() << "RViewportEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", center: " << data.getCenter()
                  << ", width: " << data.getWidth()
                  << ", height: " << data.getHeight()
    << ")";
}
