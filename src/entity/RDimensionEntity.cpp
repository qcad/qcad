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
#include "RDimensionEntity.h"
#include "RExporter.h"
#include "RPluginLoader.h"
#include "RStorage.h"

RPropertyTypeId RDimensionEntity::PropertyCustom;
RPropertyTypeId RDimensionEntity::PropertyHandle;
RPropertyTypeId RDimensionEntity::PropertyProtected;
RPropertyTypeId RDimensionEntity::PropertyWorkingSet;
RPropertyTypeId RDimensionEntity::PropertyType;
RPropertyTypeId RDimensionEntity::PropertyBlock;
RPropertyTypeId RDimensionEntity::PropertyLayer;
RPropertyTypeId RDimensionEntity::PropertyLinetype;
RPropertyTypeId RDimensionEntity::PropertyLinetypeScale;
RPropertyTypeId RDimensionEntity::PropertyLineweight;
RPropertyTypeId RDimensionEntity::PropertyColor;
RPropertyTypeId RDimensionEntity::PropertyDisplayedColor;
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
RPropertyTypeId RDimensionEntity::PropertyDimScale;
RPropertyTypeId RDimensionEntity::PropertyDimBlockName;
RPropertyTypeId RDimensionEntity::PropertyAutoTextPos;
RPropertyTypeId RDimensionEntity::PropertyFontName;
//RPropertyTypeId RDimensionEntity::PropertyTextColor;
RPropertyTypeId RDimensionEntity::PropertyArrow1Flipped;
RPropertyTypeId RDimensionEntity::PropertyArrow2Flipped;

RPropertyTypeId RDimensionEntity::PropertyExtLineFix;
RPropertyTypeId RDimensionEntity::PropertyExtLineFixLength;

//RPropertyTypeId RDimensionEntity::PropertyHeight;
//RPropertyTypeId RDimensionEntity::PropertyAngle;
//RPropertyTypeId RDimensionEntity::PropertyLineSpacingFactor;
//RPropertyTypeId RDimensionEntity::PropertyHAlign;
//RPropertyTypeId RDimensionEntity::PropertyVAlign;

RPropertyTypeId RDimensionEntity::PropertyAutoLabel;
RPropertyTypeId RDimensionEntity::PropertyMeasuredValue;


RDimensionEntity::RDimensionEntity(RDocument* document) :
    REntity(document) {
}

RDimensionEntity::~RDimensionEntity() {
}

void RDimensionEntity::init() {
    RDimensionEntity::PropertyCustom.generateId(typeid(RDimensionEntity), RObject::PropertyCustom);
    RDimensionEntity::PropertyHandle.generateId(typeid(RDimensionEntity), RObject::PropertyHandle);
    RDimensionEntity::PropertyProtected.generateId(typeid(RDimensionEntity), RObject::PropertyProtected);
    RDimensionEntity::PropertyWorkingSet.generateId(typeid(RDimensionEntity), RObject::PropertyWorkingSet);
    RDimensionEntity::PropertyType.generateId(typeid(RDimensionEntity), REntity::PropertyType);
    RDimensionEntity::PropertyBlock.generateId(typeid(RDimensionEntity), REntity::PropertyBlock);
    RDimensionEntity::PropertyLayer.generateId(typeid(RDimensionEntity), REntity::PropertyLayer);
    RDimensionEntity::PropertyLinetype.generateId(typeid(RDimensionEntity), REntity::PropertyLinetype);
    RDimensionEntity::PropertyLinetypeScale.generateId(typeid(RDimensionEntity), REntity::PropertyLinetypeScale);
    RDimensionEntity::PropertyLineweight.generateId(typeid(RDimensionEntity), REntity::PropertyLineweight);
    RDimensionEntity::PropertyColor.generateId(typeid(RDimensionEntity), REntity::PropertyColor);
    RDimensionEntity::PropertyDisplayedColor.generateId(typeid(RDimensionEntity), REntity::PropertyDisplayedColor);
    RDimensionEntity::PropertyDrawOrder.generateId(typeid(RDimensionEntity), REntity::PropertyDrawOrder);

    RDimensionEntity::PropertyText.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Label"));
    RDimensionEntity::PropertyUpperTolerance.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Tolerance"), QT_TRANSLATE_NOOP("REntity", "Upper Limit"));
    RDimensionEntity::PropertyLowerTolerance.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Tolerance"), QT_TRANSLATE_NOOP("REntity", "Lower Limit"));
    RDimensionEntity::PropertyDefinitionPointX.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Definition Point"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimensionEntity::PropertyDefinitionPointY.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Definition Point"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimensionEntity::PropertyDefinitionPointZ.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Definition Point"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RDimensionEntity::PropertyMiddleOfTextX.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RDimensionEntity::PropertyMiddleOfTextY.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RDimensionEntity::PropertyMiddleOfTextZ.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Text Position"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
//    RDimensionEntity::PropertyFontName.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Font"));
//    RDimensionEntity::PropertyTextColor.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Text Color"));
    RDimensionEntity::PropertyArrow1Flipped.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Flip First Arrow"));
    RDimensionEntity::PropertyArrow2Flipped.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Flip Second Arrow"));

    RDimensionEntity::PropertyExtLineFix.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Fixed Extension Line"));
    RDimensionEntity::PropertyExtLineFixLength.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Extension Line Length"));

//    RDimensionEntity::PropertyHeight.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Height"));
//    RDimensionEntity::PropertyAngle.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Angle"));
//    RDimensionEntity::PropertyLineSpacingFactor.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Line Spacing"));
//    RDimensionEntity::PropertyHAlign.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Horizontal"));
//    RDimensionEntity::PropertyVAlign.generateId(typeid(RDimensionEntity), QT_TRANSLATE_NOOP("REntity", "Alignment"), QT_TRANSLATE_NOOP("REntity", "Vertical"));

    RDimensionEntity::PropertyAutoLabel.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Auto Label"));
    RDimensionEntity::PropertyMeasuredValue.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Measured Value"));
    RDimensionEntity::PropertyLinearFactor.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Linear Factor"));
    RDimensionEntity::PropertyDimScale.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Scale"));
    RDimensionEntity::PropertyDimBlockName.generateId(typeid(RDimensionEntity), "", QT_TRANSLATE_NOOP("REntity", "Block Name"));
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
    ret = ret || RObject::setMember(getData().dimScaleOverride, value, PropertyDimScale == propertyTypeId);
    ret = ret || RObject::setMember(getData().dimBlockName, value, PropertyDimBlockName == propertyTypeId);
    ret = ret || RObject::setMember(getData().autoTextPos, value, PropertyAutoTextPos == propertyTypeId);
    if (RPluginLoader::hasPlugin("DWG")) {
//        ret = ret || RObject::setMember(getData().fontName, value, PropertyFontName == propertyTypeId);
//        ret = ret || RObject::setMember(getData().textColor, value, PropertyTextColor == propertyTypeId);
        ret = ret || RObject::setMember(getData().arrow1Flipped, value, PropertyArrow1Flipped == propertyTypeId);
        ret = ret || RObject::setMember(getData().arrow2Flipped, value, PropertyArrow2Flipped == propertyTypeId);

        ret = ret || RObject::setMember(getData().extLineFix, value, PropertyExtLineFix == propertyTypeId);
        ret = ret || RObject::setMember(getData().extLineFixLength, value, PropertyExtLineFixLength == propertyTypeId);
    }
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
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {
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
        if (getType()==RS::EntityDimAngular2L || getType()==RS::EntityDimAngular3P) {
            return qMakePair(QVariant(getData().getAutoLabel()),
                             RPropertyAttributes(RPropertyAttributes::ReadOnly | RPropertyAttributes::Angle));
        }
        else {
            return qMakePair(QVariant(getData().getAutoLabel()),
                             RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
    } else if (propertyTypeId == PropertyMeasuredValue) {
        if (getType()==RS::EntityDimAngular2L || getType()==RS::EntityDimAngular3P) {
            return qMakePair(QVariant(getData().getMeasuredValue()),
                             RPropertyAttributes(RPropertyAttributes::ReadOnly | RPropertyAttributes::Angle));
        }
        else {
            return qMakePair(QVariant(getData().getMeasuredValue()),
                             RPropertyAttributes(RPropertyAttributes::ReadOnly));
        }
    } else if (propertyTypeId == PropertyLinearFactor) {
        return qMakePair(QVariant(getData().linearFactor), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimScale) {
        return qMakePair(QVariant(getData().dimScaleOverride), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDimBlockName) {
        return qMakePair(QVariant(getData().dimBlockName), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    } else if (propertyTypeId == PropertyAutoTextPos) {
        return qMakePair(QVariant(getData().autoTextPos), RPropertyAttributes(RPropertyAttributes::Invisible));
    }

//    else if (propertyTypeId == PropertyFontName) {
//        return qMakePair(QVariant(getData().fontName),
//            RPropertyAttributes(RPropertyAttributes::Style));
//    }

//    else if (propertyTypeId == PropertyTextColor) {
//        return qMakePair(QVariant(getData().textColor), RPropertyAttributes());
//    }

    else if (propertyTypeId == PropertyArrow1Flipped) {
        return qMakePair(QVariant(getData().arrow1Flipped), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyArrow2Flipped) {
        return qMakePair(QVariant(getData().arrow2Flipped), RPropertyAttributes());
    }

    else if (propertyTypeId == PropertyExtLineFix) {
        return qMakePair(QVariant(getData().extLineFix), RPropertyAttributes());
    }
    else if (propertyTypeId == PropertyExtLineFixLength) {
        return qMakePair(QVariant(getData().extLineFixLength), RPropertyAttributes());
    }

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

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}

void RDimensionEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);

    // make sure text data is removed:
    //e.unexportEntity(e.getBlockRefOrEntity()->getId());

    const RDimensionData& data = getData();

    // if a block is assiciated with this dimension, look up and export block:
    QSharedPointer<RBlockReferenceEntity> dimBlockReference = data.getDimensionBlockReference();
    if (!dimBlockReference.isNull()) {
        getDocument()->getStorage().setObjectId(*dimBlockReference, getId());
        e.exportEntity(*dimBlockReference, preview, false, isSelected());
        return;
    }

    data.dirty = true;

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
    RTextData& textData = data.getTextData();
    if (textData.isSane()) {
        //QVariant v = getDocument()->getKnownVariable(RS::DIMCLRT, RColor(RColor::ByBlock));
        //RColor textColor = v.value<RColor>();
        if (e.isTextRenderedAsText()) {
            //textData.setColor(textColor);
            QList<RPainterPath> paths = e.exportText(textData, forceSelected);
            e.exportPainterPaths(paths);
        }
        else {
            // render text as paths:
            // set brush explicitely:
            QVariant v = getDocument()->getKnownVariable(RS::DIMCLRT, RColor(RColor::ByBlock));
            RColor textColor = v.value<RColor>();
            if (!textColor.isByBlock()) {
                brush.setColor(textColor);
            }
            e.setBrush(brush);
            e.exportPainterPathSource(textData);
        }
    }

    e.setBrush(Qt::NoBrush);

    data.dirty = false;
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
                  << ", dimscale: " << getData().getDimScale(false)
                  << ")";
}

/**
 * \return All used dimension block names (upper case).
 */
QSet<QString> RDimensionEntity::getDimensionBlockNames(RDocument* doc) {
    if (doc==NULL) {
        return QSet<QString>();
    }

    QSet<QString> ret;

    QList<RS::EntityType> dimTypes;
    dimTypes.append(RS::EntityDimLinear);
    dimTypes.append(RS::EntityDimAligned);
    dimTypes.append(RS::EntityDimRotated);
    dimTypes.append(RS::EntityDimRadial);
    dimTypes.append(RS::EntityDimDiametric);
    dimTypes.append(RS::EntityDimAngular2L);
    dimTypes.append(RS::EntityDimAngular3P);
    dimTypes.append(RS::EntityDimOrdinate);

    QSet<REntity::Id> ids = doc->queryAllEntities(false, true, dimTypes);
    QSet<REntity::Id>::iterator it;
    for (it=ids.begin(); it!=ids.end(); it++) {
        int id = *it;
        QSharedPointer<REntity> e = doc->queryEntityDirect(id);
        QSharedPointer<RDimensionEntity> dimEntity = e.dynamicCast<RDimensionEntity>();
        if (dimEntity.isNull()) {
            continue;
        }

        ret.insert(dimEntity->getDimBlockName().toUpper());
    }

    return ret;
}
