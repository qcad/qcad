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
#include "RTextBasedEntity.h"
#include "RExporter.h"

RPropertyTypeId RTextBasedEntity::PropertyCustom;
RPropertyTypeId RTextBasedEntity::PropertyHandle;
RPropertyTypeId RTextBasedEntity::PropertyType;
RPropertyTypeId RTextBasedEntity::PropertyBlock;
RPropertyTypeId RTextBasedEntity::PropertyLayer;
RPropertyTypeId RTextBasedEntity::PropertyLinetype;
RPropertyTypeId RTextBasedEntity::PropertyLinetypeScale;
RPropertyTypeId RTextBasedEntity::PropertyLineweight;
RPropertyTypeId RTextBasedEntity::PropertyColor;
RPropertyTypeId RTextBasedEntity::PropertyDisplayedColor;
RPropertyTypeId RTextBasedEntity::PropertyDrawOrder;

RPropertyTypeId RTextBasedEntity::PropertySimple;
RPropertyTypeId RTextBasedEntity::PropertyPositionX;
RPropertyTypeId RTextBasedEntity::PropertyPositionY;
RPropertyTypeId RTextBasedEntity::PropertyPositionZ;
RPropertyTypeId RTextBasedEntity::PropertyText;
RPropertyTypeId RTextBasedEntity::PropertyPlainText;
RPropertyTypeId RTextBasedEntity::PropertyFontName;
RPropertyTypeId RTextBasedEntity::PropertyHeight;
RPropertyTypeId RTextBasedEntity::PropertyAngle;
RPropertyTypeId RTextBasedEntity::PropertyXScale;
RPropertyTypeId RTextBasedEntity::PropertyBold;
RPropertyTypeId RTextBasedEntity::PropertyItalic;
RPropertyTypeId RTextBasedEntity::PropertyLineSpacingFactor;
RPropertyTypeId RTextBasedEntity::PropertyHAlign;
RPropertyTypeId RTextBasedEntity::PropertyVAlign;
RPropertyTypeId RTextBasedEntity::PropertyBackward;
RPropertyTypeId RTextBasedEntity::PropertyUpsideDown;


RTextBasedEntity::RTextBasedEntity(RDocument* document) :
    REntity(document) {
}

RTextBasedEntity::~RTextBasedEntity() {
}

void RTextBasedEntity::init() {
    RTextBasedEntity::PropertyCustom.generateId(typeid(RTextBasedEntity), RObject::PropertyCustom);
    RTextBasedEntity::PropertyHandle.generateId(typeid(RTextBasedEntity), RObject::PropertyHandle);
    RTextBasedEntity::PropertyType.generateId(typeid(RTextBasedEntity), REntity::PropertyType);
    RTextBasedEntity::PropertyBlock.generateId(typeid(RTextBasedEntity), REntity::PropertyBlock);
    RTextBasedEntity::PropertyLayer.generateId(typeid(RTextBasedEntity), REntity::PropertyLayer);
    RTextBasedEntity::PropertyLinetype.generateId(typeid(RTextBasedEntity), REntity::PropertyLinetype);
    RTextBasedEntity::PropertyLinetypeScale.generateId(typeid(RTextBasedEntity), REntity::PropertyLinetypeScale);
    RTextBasedEntity::PropertyLineweight.generateId(typeid(RTextBasedEntity), REntity::PropertyLineweight);
    RTextBasedEntity::PropertyColor.generateId(typeid(RTextBasedEntity), REntity::PropertyColor);
    RTextBasedEntity::PropertyDisplayedColor.generateId(typeid(RTextBasedEntity), REntity::PropertyDisplayedColor);
    RTextBasedEntity::PropertyDrawOrder.generateId(typeid(RTextBasedEntity), REntity::PropertyDrawOrder);

    RTextBasedEntity::PropertySimple.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Simple"));
    RTextBasedEntity::PropertyPositionX.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RTextBasedEntity::PropertyPositionY.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RTextBasedEntity::PropertyPositionZ.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RTextBasedEntity::PropertyText.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Text"));
    RTextBasedEntity::PropertyPlainText.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Plain Text"));
    RTextBasedEntity::PropertyFontName.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Font Name"));
    RTextBasedEntity::PropertyHeight.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Text Height"), false, RPropertyAttributes::Geometry);
    RTextBasedEntity::PropertyAngle.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Text Angle"), false, RPropertyAttributes::Geometry);
    RTextBasedEntity::PropertyXScale.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "X Scale"));
    RTextBasedEntity::PropertyBold.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Bold"));
    RTextBasedEntity::PropertyItalic.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Italic"));
    RTextBasedEntity::PropertyLineSpacingFactor.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Line Spacing"));
    RTextBasedEntity::PropertyHAlign.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Horizontal"));
    RTextBasedEntity::PropertyVAlign.generateId(typeid(RTextBasedEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Vertical"));
    RTextBasedEntity::PropertyBackward.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Backward"));
    RTextBasedEntity::PropertyUpsideDown.generateId(typeid(RTextBasedEntity), "", QT_TRANSLATE_NOOP("REntity", "Upside Down"));
}

bool RTextBasedEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    //ret = ret || RObject::setMember(getData().simple, value, PropertySimple == propertyTypeId);
    ret = ret || RObject::setMember(getData().alignmentPoint.x, value, PropertyPositionX == propertyTypeId);
    ret = ret || RObject::setMember(getData().alignmentPoint.y, value, PropertyPositionY == propertyTypeId);
    ret = ret || RObject::setMember(getData().alignmentPoint.z, value, PropertyPositionZ == propertyTypeId);
    ret = ret || RObject::setMember(getData().text, value, PropertyText == propertyTypeId);
    ret = ret || RObject::setMember(getData().fontName, value, PropertyFontName == propertyTypeId);
    ret = ret || RObject::setMember(getData().textHeight, value, PropertyHeight == propertyTypeId);
    ret = ret || RObject::setMember(getData().angle, value, PropertyAngle == propertyTypeId);
    if (PropertyXScale == propertyTypeId) {
        // no negative x-scale:
        bool ok;
        double d = value.toDouble(&ok);
        if (ok) {
            setXScale(d);
            ret = true;
        }
    }
    else if (PropertyBold == propertyTypeId) {
        setBold(value.toBool());
        ret = true;
    }
    else if (PropertyItalic == propertyTypeId) {
        setItalic(value.toBool());
        ret = true;
    }
    else if (PropertySimple == propertyTypeId) {
        setSimple(value.toBool());
        ret = true;
    }
    else if (PropertyBackward == propertyTypeId) {
        setBackward(value.toBool());
        ret = true;
    }
    else if (PropertyUpsideDown == propertyTypeId) {
        setUpsideDown(value.toBool());
        ret = true;
    }
    //ret = ret || RObject::setMember(getData().bold, value, PropertyBold == propertyTypeId);
    //ret = ret || RObject::setMember(getData().italic, value, PropertyItalic == propertyTypeId);
    ret = ret || RObject::setMember((int&)getData().horizontalAlignment, value.value<int>(), PropertyHAlign == propertyTypeId);
    ret = ret || RObject::setMember((int&)getData().verticalAlignment, value.value<int>(), PropertyVAlign == propertyTypeId);

    if (PropertyLineSpacingFactor == propertyTypeId) {
        if (value.toDouble()>=0.0) {
            ret = ret || RObject::setMember(getData().lineSpacingFactor, value, true);
        }
    }

    if (ret) {
        getData().update();
    }
    return ret;
}

QPair<QVariant, RPropertyAttributes> RTextBasedEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertySimple) {
        return qMakePair(QVariant(getData().isSimple()), RPropertyAttributes(RPropertyAttributes::AffectsOtherProperties));
    } else if (propertyTypeId == PropertyPositionX) {
        return qMakePair(QVariant(getData().alignmentPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionY) {
        return qMakePair(QVariant(getData().alignmentPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyPositionZ) {
        return qMakePair(QVariant(getData().alignmentPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyText) {
        return qMakePair(QVariant(getData().text), RPropertyAttributes(RPropertyAttributes::RichText|RPropertyAttributes::Label));
    } else if (humanReadable && propertyTypeId == PropertyPlainText) {
        return qMakePair(QVariant(getData().getPlainText()), RPropertyAttributes(RPropertyAttributes::Label|RPropertyAttributes::ReadOnly));
    } else if (propertyTypeId == PropertyFontName) {
        return qMakePair(QVariant(getData().fontName), RPropertyAttributes(RPropertyAttributes::Style));
    } else if (propertyTypeId == PropertyHeight) {
        return qMakePair(QVariant(getData().textHeight), RPropertyAttributes());
    } else if (propertyTypeId == PropertyAngle) {
        return qMakePair(QVariant(getData().angle), RPropertyAttributes(RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyXScale) {
        return qMakePair(QVariant(getData().xScale), RPropertyAttributes());
    } else if (propertyTypeId == PropertyBold) {
        return qMakePair(QVariant(getData().isBold()), RPropertyAttributes());
    } else if (propertyTypeId == PropertyItalic) {
        return qMakePair(QVariant(getData().isItalic()), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLineSpacingFactor) {
        return qMakePair(QVariant(getData().lineSpacingFactor), RPropertyAttributes());
    } else if (propertyTypeId == PropertyHAlign) {
//        return qMakePair(QVariant(getData().horizontalAlignment), RPropertyAttributes(RPropertyAttributes::AffectsOtherProperties));
        return qMakePair(QVariant(getData().horizontalAlignment), RPropertyAttributes());
    } else if (propertyTypeId == PropertyVAlign) {
//        return qMakePair(QVariant(getData().verticalAlignment), RPropertyAttributes(RPropertyAttributes::AffectsOtherProperties));
        return qMakePair(QVariant(getData().verticalAlignment), RPropertyAttributes());
    } else if (propertyTypeId == PropertyBackward) {
        return qMakePair(QVariant(getData().isBackward()), RPropertyAttributes(isSimple() ? RPropertyAttributes::NoOptions : RPropertyAttributes::Invisible));
    } else if (propertyTypeId == PropertyUpsideDown) {
        return qMakePair(QVariant(getData().isUpsideDown()), RPropertyAttributes(isSimple() ? RPropertyAttributes::NoOptions : RPropertyAttributes::Invisible));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RTextBasedEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview)

    // TODO: use transforms:
    RTextBasedData data = getData();
//    data.move(-getAlignmentPoint());
//    data.rotate(-getAngle(), RVector(0,0));
//    data.setXScale(1.0);

//    RTransform t;
//    t.translate(getAlignmentPoint().x, getAlignmentPoint().y);
//    t.rotate(RMath::rad2deg(getAngle()));
//    t.scale(getXScale(), 1);
//    e.exportTransform(t);

    if (e.isTextRenderedAsText()) {
        // export text as text and return part that cannot be rendered as text as paths:
        QList<RPainterPath> paths = e.exportText(data, forceSelected);

        // export part of text that can only be rendered as painter paths (CAD fonts):
        e.exportPainterPaths(paths, getPosition().z);
    }
    else {
        e.exportPainterPathSource(data, getPosition().z);
    }

//    e.exportEndTransform();
}

QSharedPointer<REntity> RTextBasedEntity::scaleNonUniform(const RVector& scaleFactors, const RVector& center) {
    return QSharedPointer<REntity>();
}

void RTextBasedEntity::print(QDebug dbg) const {
    dbg.nospace() << "RTextBasedEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", alignmentPoint: " << getAlignmentPoint()
                  << ", position: " << getPosition()
                  << ", text: " << getPlainText()
                  << ", textHeight: " << getTextHeight()
                  << ", textWidth: " << getTextWidth()
                  << ", drawingDirection: " << getDrawingDirection()
                  << ")";
}
