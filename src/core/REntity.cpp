/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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
#include "RDocument.h"
#include "REntity.h"
#include "RExplodable.h"
#include "RShape.h"
#include "RSpline.h"

RPropertyTypeId REntity::PropertyCustom;
RPropertyTypeId REntity::PropertyHandle;
RPropertyTypeId REntity::PropertyProtected;
RPropertyTypeId REntity::PropertyType;
RPropertyTypeId REntity::PropertyBlock;
RPropertyTypeId REntity::PropertyLayer;
RPropertyTypeId REntity::PropertyLinetype;
RPropertyTypeId REntity::PropertyLinetypeScale;
RPropertyTypeId REntity::PropertyLineweight;
RPropertyTypeId REntity::PropertyColor;
RPropertyTypeId REntity::PropertyDisplayedColor;
RPropertyTypeId REntity::PropertyDrawOrder;

RPropertyTypeId REntity::PropertyMinX;
RPropertyTypeId REntity::PropertyMaxX;
RPropertyTypeId REntity::PropertyMinY;
RPropertyTypeId REntity::PropertyMaxY;
RPropertyTypeId REntity::PropertySizeX;
RPropertyTypeId REntity::PropertySizeY;

REntity::REntity(RDocument* document)
    : RObject(document) {

    RDebug::incCounter("REntity");
}

REntity::REntity(const REntity& other) : RObject(other) {
    RDebug::incCounter("REntity");
}

REntity::~REntity() {
    RDebug::decCounter("REntity");
    //qDebug() << "deleting entity: " << QString("0x%1").arg((long int)this, 0, 16);
    //qDebug() << "deleting entity: " << getId();
}

bool REntity::isComplex(const RS::EntityType type) {
    return (type==RS::EntityAttributeDefinition ||
            type==RS::EntityAttribute ||
            type==RS::EntityHatch ||
            type==RS::EntityTextBased ||
            type==RS::EntityText ||
            isDimension(type));
}

bool REntity::isDimension(const RS::EntityType type) {
    return (type==RS::EntityDimension ||
            type==RS::EntityDimAligned ||
            type==RS::EntityDimLinear ||
            type==RS::EntityDimRotated ||
            type==RS::EntityDimRadial ||
            type==RS::EntityDimDiametric ||
            type==RS::EntityDimAngular ||
            type==RS::EntityDimOrdinate);
}

void REntity::init() {
    REntity::PropertyCustom.generateId(typeid(REntity), RObject::PropertyCustom);
    REntity::PropertyHandle.generateId(typeid(REntity), RObject::PropertyHandle);
    REntity::PropertyProtected.generateId(typeid(REntity), RObject::PropertyProtected);
    REntity::PropertyType.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Type"));
    REntity::PropertyBlock.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Block ID"));
    REntity::PropertyLayer.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Layer"));
    REntity::PropertyLinetype.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Linetype"));
    REntity::PropertyLinetypeScale.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Linetype Scale"));
    REntity::PropertyLineweight.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Lineweight"));
    REntity::PropertyColor.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Color"));
    REntity::PropertyDisplayedColor.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Displayed Color"));
    REntity::PropertyDrawOrder.generateId(typeid(REntity), "", QT_TRANSLATE_NOOP("REntity", "Draw Order"));

    REntity::PropertyMinX.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Boundary"), QT_TRANSLATE_NOOP("REntity", "Left"));
    REntity::PropertyMinY.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Boundary"), QT_TRANSLATE_NOOP("REntity", "Bottom"));
    REntity::PropertyMaxX.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Boundary"), QT_TRANSLATE_NOOP("REntity", "Right"));
    REntity::PropertyMaxY.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Boundary"), QT_TRANSLATE_NOOP("REntity", "Top"));

    REntity::PropertySizeX.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Size"), QT_TRANSLATE_NOOP("REntity", "Width"));
    REntity::PropertySizeY.generateId(typeid(REntity), QT_TRANSLATE_NOOP("REntity", "Size"), QT_TRANSLATE_NOOP("REntity", "Height"));
}

/**
 * \copydoc REntityData::getLineweight
 */
RLineweight::Lineweight REntity::getLineweight(bool resolve,
    const QStack<REntity*>& blockRefStack) const {

    QStack<REntity*> newBlockRefStack = blockRefStack;
    if (!newBlockRefStack.isEmpty() && this==(REntity*)newBlockRefStack.top()) {
        newBlockRefStack.pop();
    }

    return getData().getLineweight(resolve, newBlockRefStack);
}

/**
 * \copydoc REntityData::getColor
 */
RColor REntity::getColor(bool resolve, const QStack<REntity*>& blockRefStack) {
    QStack<REntity*> newBlockRefStack = blockRefStack;
    if (!newBlockRefStack.isEmpty() && this==(REntity*)newBlockRefStack.top()) {
        newBlockRefStack.pop();
    }

    return getData().getColor(resolve, newBlockRefStack);
}

/**
 * \copydoc REntityData::getLineweightInUnits
 */
double REntity::getLineweightInUnits(const QStack<REntity*>& blockRefStack) const {
    QStack<REntity*> newBlockRefStack = blockRefStack;
    if (!newBlockRefStack.isEmpty() && this==(REntity*)newBlockRefStack.top()) {
        newBlockRefStack.pop();
    }
    return getData().getLineweightInUnits(newBlockRefStack);
}

/**
 * \copydoc REntityData::getLinetypeId
 */
RLinetype::Id REntity::getLinetypeId(bool resolve, const QStack<REntity*>& blockRefStack) const {
    QStack<REntity*> newBlockRefStack = blockRefStack;
    if (!newBlockRefStack.isEmpty() && this==(REntity*)newBlockRefStack.top()) {
        newBlockRefStack.pop();
    }
    return getData().getLinetypeId(resolve, newBlockRefStack);
}

/**
 * Copies all attributes (layer, block, color, line weight, line style) from the given entity.
 */
void REntity::copyAttributesFrom(const REntity* entity, bool copyBlockId) {
    if (entity==NULL) {
        qWarning("REntity::copyAttributesFrom: source entity is NULL");
        return;
    }

    if (getDocument()!=entity->getDocument()) {
        qWarning("REntity::copyAttributesFrom: source entity not from same document");
        return;
    }

    copyAttributesFrom(entity->getData(), copyBlockId);

//    setLayerId(entity->getLayerId());
//    if (copyBlockId) {
//        setBlockId(entity->getBlockId());
//    }
//    setColor(entity->getColor());
//    setLineweight(entity->getLineweight());
//    setLinetypeId(entity->getLinetypeId());
//    setLinetypeScale(entity->getLinetypeScale());
//    setDrawOrder(entity->getDrawOrder());
}

void REntity::copyAttributesFrom(const REntityData& entityData, bool copyBlockId) {
    if (getDocument()!=entityData.getDocument()) {
        qWarning("REntity::copyAttributesFrom: source entity not from same document");
        return;
    }

    setLayerId(entityData.getLayerId());
    if (copyBlockId) {
        setBlockId(entityData.getBlockId());
    }
    setColor(entityData.getColor());
    setLineweight(entityData.getLineweight());
    setLinetypeId(entityData.getLinetypeId());
    setLinetypeScale(entityData.getLinetypeScale());
    setDrawOrder(entityData.getDrawOrder());
}

QList<RVector> REntity::getIntersectionPoints(
        const REntity& other, bool limited, const RBox& queryBox, bool ignoreComplex) const {

    bool same = false;

    // avoid intersection finding for intersections of interpolated entities
    // (e.g. splines) with themselves:
    if (getId()!=INVALID_ID && getId()==other.getId() && getDocument()==other.getDocument()) {
        const RShape* shape = getData().castToConstShape();
        if (shape!=NULL && shape->isInterpolated()) {
            same = true;
        }

        const RPolyline* pl = dynamic_cast<const RPolyline*>(shape);
        if (pl!=NULL) {
            same = true;
        }

        // if entity is not interpolated and not a polyline, there are no intersections in entity self:
        if (!same) {
            return QList<RVector>();
        }
    }

    return getData().getIntersectionPoints(other.getData(), limited, same, queryBox, ignoreComplex);
}

QList<RVector> REntity::getIntersectionPoints(const RShape& shape, bool limited, const RBox& queryBox, bool ignoreComplex) const {
    return getData().getIntersectionPoints(shape, limited, queryBox, ignoreComplex);
}

QPair<QVariant, RPropertyAttributes> REntity::getProperty(
        RPropertyTypeId& propertyTypeId,
        bool humanReadable, bool noAttributes) {

    if (propertyTypeId == PropertyType) {
        return qMakePair(QVariant(getType()), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyBlock) {
        return qMakePair(QVariant(getData().getBlockId()),
                         RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyLayer) {
        if (humanReadable) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                RPropertyAttributes attr;
                if (!noAttributes) {
                    // TODO: filter out locked layers:
                    attr.setChoices(document->getLayerNames());
                }
                return qMakePair(QVariant(document->getLayerName(
                        getData().getLayerId())), attr);
            }
        }
        else {
            return qMakePair(QVariant(getData().getLayerId()),
                    RPropertyAttributes());
        }
    }
    else if (propertyTypeId == PropertyLinetype) {
        if (humanReadable) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                RPropertyAttributes attr;
//                if (!noAttributes) {
//                    attr.setChoices(document->getLinetypeNames());
//                }
                QString desc = document->getLinetypeLabel(getData().getLinetypeId());
                return qMakePair(QVariant(desc), attr);
            }
        }
        else {
            return qMakePair(QVariant(getData().getLinetypeId()),
                    RPropertyAttributes());
        }
    }
    else if (propertyTypeId == PropertyLinetypeScale) {
        return qMakePair(QVariant(getData().getLinetypeScale()), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyLineweight) {
        QVariant v;
        v.setValue<RLineweight::Lineweight>(getData().getLineweight());
        return qMakePair(v, RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyColor) {
        QVariant var;
        var.setValue<RColor> (getData().getColor());
        return qMakePair(var, RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyDrawOrder) {
        return qMakePair(QVariant(getData().getDrawOrder()), RPropertyAttributes());
    }

    // human readable properties (not relevant for transactions):
    if (humanReadable) {
        if (propertyTypeId == PropertyDisplayedColor) {
            QVariant var;
            var.setValue<RColor> (getDisplayColor());
            return qMakePair(var, RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyMinX) {
            return qMakePair(QVariant(getBoundingBox().getMinimum().x), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyMinY) {
            return qMakePair(QVariant(getBoundingBox().getMinimum().y), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyMaxX) {
            return qMakePair(QVariant(getBoundingBox().getMaximum().x), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertyMaxY) {
            return qMakePair(QVariant(getBoundingBox().getMaximum().y), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertySizeX) {
            return qMakePair(QVariant(getBoundingBox().getWidth()), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
        else if (propertyTypeId == PropertySizeY) {
            return qMakePair(QVariant(getBoundingBox().getHeight()), RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
    }

    return RObject::getProperty(propertyTypeId, humanReadable, noAttributes);
}

bool REntity::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value, RTransaction* transaction) {

    bool ret = RObject::setProperty(propertyTypeId, value, transaction);

    if (propertyTypeId == PropertyBlock) {
        ret = ret || RObject::setMember(getData().blockId, value.toInt(), true);
    } else if (propertyTypeId == PropertyLayer) {
        if (value.type() == QVariant::Int || value.type() == QVariant::LongLong) {
            ret = ret || RObject::setMember(getData().layerId, value.toInt(), true);
        } else if (value.type() == QVariant::String) {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                ret = ret || RObject::setMember(getData().layerId,
                        document->getLayerId(value.toString()), true);
            }
        }
    } else if (propertyTypeId == PropertyLinetype) {
        if (value.type() == QVariant::Int || value.type() == QVariant::LongLong) {
            ret = ret || RObject::setMember(getData().linetypeId, value.toInt(), true);
        } else {
            RDocument* document = getData().getDocument();
            if (document != NULL) {
                RLinetypePattern t = value.value<RLinetypePattern> ();
                int id = document->getLinetypeId(t.getName());
                ret = ret || RObject::setMember(getData().linetypeId, id, true);
            }
        }
    } else if (propertyTypeId == PropertyLinetypeScale) {
        ret = ret || RObject::setMember(getData().linetypeScale, value.toDouble(), true);
    } else if (propertyTypeId == PropertyLineweight) {
        if (value.type()==QVariant::Int || value.type()==QVariant::Double) {
            ret = ret || RObject::setMember((int&)getData().lineweight,
                value.value<int>(), true);
        }
        else {
            ret = ret || RObject::setMember((int&)getData().lineweight,
                (int)value.value<RLineweight::Lineweight>(), true);
        }
    } else if (propertyTypeId == PropertyColor) {
        ret = ret || RObject::setMember(getData().color, value, true);
    } else if (propertyTypeId == PropertyDrawOrder) {
        ret = ret || RObject::setMember(getData().drawOrder, value, true);
    }

    return ret;
}

/**
 * \return true if this entity is visible (i.e. is not on a frozen or hidden layer
 * or in a frozen block).
 */
bool REntity::isVisible() const {
    const RDocument* doc = getDocument();
    if (doc==NULL) {
        return true;
    }

    RLayer::Id layerId = getLayerId();
    bool isLayer0 = doc->getLayerName(layerId)=="0";
    bool ignoreLayerVisibility = false;

//    qDebug() << "entity: ";
//    dump();
//    qDebug() << "layer: " << doc->getLayerName(layerId);
//    qDebug() << "model space: " << doc->getModelSpaceBlockId();
//    qDebug() << "block ID: " << getBlockId();
//    qDebug() << "layer 0 compat: " << RSettings::isLayer0CompatibilityOn();

    if (isLayer0 &&
        RSettings::isLayer0CompatibilityOn() &&
        doc->getModelSpaceBlockId()!=getBlockId()) {

        // entity is on layer 0 and not in model space block:
        // if layer 0 compatibility is on, the visibility of layer 0
        // does not affect the visibility of the entity:
        ignoreLayerVisibility = true;
    }

//    qDebug() << "ignoreLayerVisibility:" << ignoreLayerVisibility;

    // check if layer is frozen:
    if (doc->isLayerFrozen(layerId) && !ignoreLayerVisibility) {
        if (getType()!=RS::EntityViewport) {
            return false;
        }
    }

    // check if layer is off and this is not a block reference:
    // block references on layer X remain visible if X is off but not frozen:
    if (doc->isLayerOff(layerId) && !ignoreLayerVisibility) {
        if (getType()!=RS::EntityBlockRef) {
            return false;
        }
    }

    // if entity is on layer 0 and layer of current rendering context block reference
    // is off, entity is off:
    // -> this is implemented in RBlockReference::exportEntity

    // check if block is frozen:
    if (getType()==RS::EntityBlockRef) {
        const RBlockReferenceEntity* blockRef = dynamic_cast<const RBlockReferenceEntity*>(this);
        if (blockRef!=NULL) {
            RBlock::Id blockId = blockRef->getReferencedBlockId();
            if (blockId!=RBlock::INVALID_ID) {
                QSharedPointer<RBlock> block = doc->queryBlockDirect(blockId);
                if (!block.isNull() && block->isFrozen()) {
                    return false;
                }
            }
        }
    }

    return true;
}

/**
 * \return true if this entity can be edited (i.e. is not on a locked layer).
 */
bool REntity::isEditable(bool allowInvisible) const {
    if (getDocument()==NULL) {
        return true;
    }

    // entities that are not visible are never editable:
    if (!allowInvisible && !isVisible()) {
        return false;
    }

    // entities on locked layers are not editable:
    if (getDocument()->isLayerLocked(getLayerId())) {
        return false;
    }

    return true;
}

/**
 * \copydoc REntityData::setSelected
 */
void REntity::setSelected(bool on) {
    getData().setSelected(on);
}

/**
 * Stream operator for QDebug
 */
void REntity::print(QDebug dbg) const {
    dbg.nospace() << "REntity(";
    RObject::print(dbg);
    dbg.nospace() 
        << ", type: " << getType()
        << ", layerId: " << getLayerId()
        << ", blockId: " << getBlockId()
        << ", parentId: " << getParentId()
        << ", childIds: " << getDocument()->queryChildEntities(getId())
        << ", lineweight: " << getLineweight()
        << ", linetypeId: " << getLinetypeId()
        << ", linetypeScale: " << getLinetypeScale()
        << ", color: " << getColor()
        << ", drawOrder: " << getDrawOrder()
        << ", selectionStatus: " << isSelected()
        << ", boundingBoxes: " << getBoundingBoxes()
        << ")";
}
