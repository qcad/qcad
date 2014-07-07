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
#include "RDimensionEntity.h"
#include "RExporter.h"
#include "RPluginLoader.h"

RPropertyTypeId RDimensionEntity::PropertyCustom;
RPropertyTypeId RDimensionEntity::PropertyHandle;
RPropertyTypeId RDimensionEntity::PropertyType;
RPropertyTypeId RDimensionEntity::PropertyBlock;
RPropertyTypeId RDimensionEntity::PropertyLayer;
RPropertyTypeId RDimensionEntity::PropertyLinetype;
RPropertyTypeId RDimensionEntity::PropertyLineweight;
RPropertyTypeId RDimensionEntity::PropertyColor;
RPropertyTypeId RDimensionEntity::PropertyDrawOrder;

RPropertyTypeId RDimensionEntity::PropertyDefinitionPointX;
RPropertyTypeId RDimensionEntity::PropertyDefinitionPointY;
RPropertyTypeId RDimensionEntity::PropertyDefinitionPointZ;
RPropertyTypeId RDimensionEntity::PropertyMiddleOfTextX;
RPropertyTypeId RDimensionEntity::PropertyMiddleOfTextY;
RPropertyTypeId RDimensionEntity::PropertyMiddleOfTextZ;
RPropertyTypeId RDimensionEntity::PropertyText;
RPropertyTypeId RDimensionEntity::PropertyUpperTolerance;
RPropertyTypeId RDimensionEntity::PropertyLowerTolerance;
RPropertyTypeId RDimensionEntity::PropertyLinearFactor;
RPropertyTypeId RDimensionEntity::PropertyAutoTextPos;
RPropertyTypeId RDimensionEntity::PropertyFontName;
//RPropertyTypeId RDimensionEntity::PropertyHeight;
//RPropertyTypeId RDimensionEntity::PropertyAngle;
//RPropertyTypeId RDimensionEntity::PropertyLineSpacingFactor;
//RPropertyTypeId RDimensionEntity::PropertyHAlign;
//RPropertyTypeId RDimensionEntity::PropertyVAlign;

RPropertyTypeId RDimensionEntity::PropertyAutoLabel;
RPropertyTypeId RDimensionEntity::PropertyMeasuredValue;


RDimensionEntity::RDimensionEntity(RDocument* document, RObject::Id objectId) :
    REntity(document, objectId) {
}

RDimensionEntity::~RDimensionEntity() {
}

void RDimensionEntity::init() {
    RDimensionEntity::PropertyCustom.generateId(typeid(RDimensionEntity), RObject::PropertyCustom);
    RDimensionEntity::PropertyHandle.generateId(typeid(RDimensionEntity), RObject::PropertyHandle);
    RDimensionEntity::PropertyType.generateId(typeid(RDimensionEntity), REntity::PropertyType);
    RDimensionEntity::PropertyBlock.generateId(typeid(RDimensionEntity), REntity::PropertyBlock);
    RDimensionEntity::PropertyLayer.generateId(typeid(RDimensionEntity), REntity::PropertyLayer);
    RDimensionEntity::PropertyLinetype.generateId(typeid(RDimensionEntity), REntity::PropertyLinetype);
    RDimensionEntity::PropertyLineweight.generateId(typeid(RDimensionEntity), REntity::PropertyLineweight);
    RDimensionEntity::PropertyColor.generateId(typeid(RDimensionEntity), REntity::PropertyColor);
    RDimensionEntity::PropertyDrawOrder.generateId(typeid(RDimensionEntity), REntity::PropertyDrawOrder);

    RDimensionEntity::PropertyText.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Label"));
    RDimensionEntity::PropertyUpperTolerance.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Tolerance"), QT_TRANSLATE_NOOP("REntity", "Upper Limit"));
    RDimensionEntity::PropertyLowerTolerance.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Tolerance"), QT_TRANSLATE_NOOP("REntity", "Lower Limit"));
    RDimensionEntity::PropertyDefinitionPointX.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Definition Point"), QT_TRANSLATE_NOOP("REntity", "X"));
    RDimensionEntity::PropertyDefinitionPointY.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Definition Point"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RDimensionEntity::PropertyDefinitionPointZ.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Definition Point"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RDimensionEntity::PropertyMiddleOfTextX.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "X"));
    RDimensionEntity::PropertyMiddleOfTextY.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RDimensionEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "Z"));
//    RDimensionEntity::PropertyFontName.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Font"));
//    RDimensionEntity::PropertyHeight.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Height"));
//    RDimensionEntity::PropertyAngle.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));
//    RDimensionEntity::PropertyLineSpacingFactor.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Line Spacing"));
//    RDimensionEntity::PropertyHAlign.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Horizontal"));
//    RDimensionEntity::PropertyVAlign.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Vertical"));

    RDimensionEntity::PropertyAutoLabel.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Auto Label"));
    RDimensionEntity::PropertyMeasuredValue.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Measured Value"));
    RDimensionEntity::PropertyLinearFactor.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Linear Factor"));
    RDimensionEntity::PropertyAutoTextPos.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Auto Label Position"));
}

bool RDimensionEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(getData().definitionPoint.x, value, PropertyDefinitionPointX == propertyTypeId);
    ret = ret || RObject::setMember(getData().definitionPoint.y, value, PropertyDefinitionPointY == propertyTypeId);
    ret = ret || RObject::setMember(getData().definitionPoint.z, value, PropertyDefinitionPointZ == propertyTypeId);
    if (RObject::setMember(getData().textPositionCenter.x, value, PropertyMiddleOfTextX == propertyTypeId)) {
        ret = true;
        getData().autoTextPos = false;
        getData().textPositionSide = RVector::invalid;
        //getData().updateFromTextPosition();
    }
    if (RObject::setMember(getData().textPositionCenter.y, value, PropertyMiddleOfTextY == propertyTypeId)) {
        ret = true;
        getData().autoTextPos = false;
        getData().textPositionSide = RVector::invalid;
        //getData().updateFromTextPosition();
    }
    if (RObject::setMember(getData().textPositionCenter.z, value, PropertyMiddleOfTextZ == propertyTypeId)) {
        ret = true;
        getData().autoTextPos = false;
        getData().textPositionSide = RVector::invalid;
        //getData().updateFromTextPosition();
    }
    ret = ret || RObject::setMember(getData().text, value, PropertyText == propertyTypeId);
    ret = ret || RObject::setMember(getData().upperTolerance, value, PropertyUpperTolerance == propertyTypeId);
    ret = ret || RObject::setMember(getData().lowerTolerance, value, PropertyLowerTolerance == propertyTypeId);
    ret = ret || RObject::setMember(getData().linearFactor, value, PropertyLinearFactor == propertyTypeId);
    ret = ret || RObject::setMember(getData().autoTextPos, value, PropertyAutoTextPos == propertyTypeId);
//    if (RPluginLoader::hasPlugin("DWG")) {
//        ret = ret || RObject::setMember(getData().fontName, value, PropertyFontName == propertyTypeId);
//    }
//    ret = ret || RObject::setMember(getData().textHeight, value, PropertyHeight == propertyTypeId);
//    ret = ret || RObject::setMember(getData().angle, value, PropertyAngle == propertyTypeId);
//    ret = ret || RObject::setMember(getData().lineSpacingFactor, value, PropertyLineSpacingFactor == propertyTypeId);
//    ret = ret || RObject::setMember((int&)getData().horizontalAlignment, value.value<int>(), PropertyHAlign == propertyTypeId);
//    ret = ret || RObject::setMember((int&)getData().verticalAlignment, value.value<int>(), PropertyVAlign == propertyTypeId);

    if (ret) {
        getData().update();
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RDimensionEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes) {
    if (propertyTypeId == PropertyDefinitionPointX) {
        return qMakePair(QVariant(getData().definitionPoint.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDefinitionPointY) {
        return qMakePair(QVariant(getData().definitionPoint.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDefinitionPointZ) {
        return qMakePair(QVariant(getData().definitionPoint.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyMiddleOfTextX) {
        if (getData().textPositionSide.isValid()) {
            return qMakePair(QVariant(getData().textPositionSide.x), RPropertyAttributes());
        }
        else {
            return qMakePair(QVariant(getData().textPositionCenter.x), RPropertyAttributes());
        }
    } else if (propertyTypeId == PropertyMiddleOfTextY) {
        if (getData().textPositionSide.isValid()) {
            return qMakePair(QVariant(getData().textPositionSide.y), RPropertyAttributes());
        }
        else {
            return qMakePair(QVariant(getData().textPositionCenter.y), RPropertyAttributes());
        }
    } else if (propertyTypeId == PropertyMiddleOfTextZ) {
        if (getData().textPositionSide.isValid()) {
            return qMakePair(QVariant(getData().textPositionSide.z), RPropertyAttributes());
        }
        else {
            return qMakePair(QVariant(getData().textPositionCenter.z), RPropertyAttributes());
        }
    } else if (propertyTypeId == PropertyText) {
        return qMakePair(QVariant(getData().text),
                         RPropertyAttributes(RPropertyAttributes::DimensionLabel));
    } else if (propertyTypeId == PropertyUpperTolerance) {
        return qMakePair(QVariant(getData().upperTolerance),
                         RPropertyAttributes(RPropertyAttributes::Label));
    } else if (propertyTypeId == PropertyLowerTolerance) {
        return qMakePair(QVariant(getData().lowerTolerance),
                         RPropertyAttributes(RPropertyAttributes::Label));
    } else if (propertyTypeId == PropertyAutoLabel) {
        if (getType()==RS::EntityDimAngular) {
            return qMakePair(QVariant(getData().getAutoLabel()),
                             RPropertyAttributes(RPropertyAttributes::ReadOnly | RPropertyAttributes::Angle));
        }
        else {
            return qMakePair(QVariant(getData().getAutoLabel()),
                             RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
    } else if (propertyTypeId == PropertyMeasuredValue) {
        if (getType()==RS::EntityDimAngular) {
            return qMakePair(QVariant(getData().getMeasuredValue()),
                             RPropertyAttributes(RPropertyAttributes::ReadOnly | RPropertyAttributes::Angle));
        }
        else {
            return qMakePair(QVariant(getData().getMeasuredValue()),
                             RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
    } else if (propertyTypeId == PropertyLinearFactor) {
        return qMakePair(QVariant(getData().linearFactor), RPropertyAttributes());
    } else if (propertyTypeId == PropertyAutoTextPos) {
        return qMakePair(QVariant(getData().autoTextPos), RPropertyAttributes(RPropertyAttributes::Invisible));
    }

//    else if (propertyTypeId == PropertyFontName) {
//        return qMakePair(QVariant(getData().fontName),
//            RPropertyAttributes(RPropertyAttributes::Style));
//    }
    /*else if (propertyTypeId == PropertyHeight) {
        return qMakePair(QVariant(getData().textHeight), RPropertyAttributes());
    } else if (propertyTypeId == PropertyAngle) {
        return qMakePair(QVariant(getData().angle), RPropertyAttributes(
            RPropertyAttributes::Angle));
    } else if (propertyTypeId == PropertyLineSpacingFactor) {
        return qMakePair(QVariant(getData().lineSpacingFactor), RPropertyAttributes());
    } else if (propertyTypeId == PropertyHAlign) {
        return qMakePair(QVariant(getData().horizontalAlignment), RPropertyAttributes());
    } else if (propertyTypeId == PropertyVAlign) {
        return qMakePair(QVariant(getData().verticalAlignment), RPropertyAttributes());
    }*/

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RDimensionEntity::exportEntity(RExporter& e, bool preview) const {
    Q_UNUSED(preview);

    getData().dirty = true;

    // export shapes:
    QList<QSharedPointer<RShape> > shapes = getShapes();
    //e.setBrush(Qt::NoBrush);
    //e.exportShapes(shapes);
    QBrush brush = e.getBrush();

    for (int i=0; i<shapes.size(); i++) {
        QSharedPointer<RShape> s = shapes.at(i);
        if (s.isNull()) {
            continue;
        }

        // triangles (arrows) are filled:
        if (!s.dynamicCast<RTriangle>().isNull()) {
            e.setBrush(brush);
        }

        // lines are not filled:
        else {
            e.setBrush(Qt::NoBrush);
        }

        e.exportShape(s);
    }

    // export text label:
    RTextData& textData = getData().getTextData();
    //qDebug() << "export dim: angle: " << textData.getAngle();
    e.setBrush(brush);
    e.exportPainterPathSource(textData);

    e.setBrush(Qt::NoBrush);

    getData().dirty = false;
}

void RDimensionEntity::print(QDebug dbg) const {
    dbg.nospace() << "RDimensionEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", definitionPoint: " << getData().definitionPoint
                  << ", autoTextPos: " << getData().autoTextPos
                  << ", middleOfText: " << getData().getTextPosition()
                  << ", text: " << getData().text
                  << ", upper tolerance: " << getData().upperTolerance
                  << ", lower tolerance: " << getData().lowerTolerance
                  << ", measurement (label): " << getData().getMeasurement(true)
                  << ", measurement (stored): " << getData().getMeasurement(false)
                  << ")";
}
