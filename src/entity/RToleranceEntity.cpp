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
#include "RDebug.h"
#include "RDimensionEntity.h"
#include "RDocument.h"
#include "RExporter.h"
#include "RToleranceEntity.h"
#include "RPluginLoader.h"

RPropertyTypeId RToleranceEntity::PropertyCustom;
RPropertyTypeId RToleranceEntity::PropertyHandle;
RPropertyTypeId RToleranceEntity::PropertyProtected;
RPropertyTypeId RToleranceEntity::PropertyWorkingSet;
RPropertyTypeId RToleranceEntity::PropertyType;
RPropertyTypeId RToleranceEntity::PropertyBlock;
RPropertyTypeId RToleranceEntity::PropertyLayer;
RPropertyTypeId RToleranceEntity::PropertyLinetype;
RPropertyTypeId RToleranceEntity::PropertyLinetypeScale;
RPropertyTypeId RToleranceEntity::PropertyLineweight;
RPropertyTypeId RToleranceEntity::PropertyColor;
RPropertyTypeId RToleranceEntity::PropertyDisplayedColor;
RPropertyTypeId RToleranceEntity::PropertyDrawOrder;

RPropertyTypeId RToleranceEntity::PropertyLocationX;
RPropertyTypeId RToleranceEntity::PropertyLocationY;
RPropertyTypeId RToleranceEntity::PropertyLocationZ;
RPropertyTypeId RToleranceEntity::PropertyDirectionX;
RPropertyTypeId RToleranceEntity::PropertyDirectionY;
RPropertyTypeId RToleranceEntity::PropertyDirectionZ;
RPropertyTypeId RToleranceEntity::PropertyText;
RPropertyTypeId RToleranceEntity::PropertyDimscale;
RPropertyTypeId RToleranceEntity::PropertyDimtxt;


RToleranceEntity::RToleranceEntity(RDocument* document, const RToleranceData& data) :
    REntity(document), data(document, data) {
    RDebug::incCounter("RToleranceEntity");
}

RToleranceEntity::RToleranceEntity(const RToleranceEntity& other) : REntity(other) {
    RDebug::incCounter("RToleranceEntity");
    data = other.data;
}

RToleranceEntity::~RToleranceEntity() {
    RDebug::decCounter("RToleranceEntity");
}

void RToleranceEntity::init() {
    RToleranceEntity::PropertyCustom.generateId(RToleranceEntity::getRtti(), RObject::PropertyCustom);
    RToleranceEntity::PropertyHandle.generateId(RToleranceEntity::getRtti(), RObject::PropertyHandle);
    RToleranceEntity::PropertyProtected.generateId(RToleranceEntity::getRtti(), RObject::PropertyProtected);
    RToleranceEntity::PropertyWorkingSet.generateId(RToleranceEntity::getRtti(), RObject::PropertyWorkingSet);
    RToleranceEntity::PropertyType.generateId(RToleranceEntity::getRtti(), REntity::PropertyType);
    RToleranceEntity::PropertyBlock.generateId(RToleranceEntity::getRtti(), REntity::PropertyBlock);
    RToleranceEntity::PropertyLayer.generateId(RToleranceEntity::getRtti(), REntity::PropertyLayer);
    RToleranceEntity::PropertyLinetype.generateId(RToleranceEntity::getRtti(), REntity::PropertyLinetype);
    RToleranceEntity::PropertyLinetypeScale.generateId(RToleranceEntity::getRtti(), REntity::PropertyLinetypeScale);
    RToleranceEntity::PropertyLineweight.generateId(RToleranceEntity::getRtti(), REntity::PropertyLineweight);
    RToleranceEntity::PropertyColor.generateId(RToleranceEntity::getRtti(), REntity::PropertyColor);
    RToleranceEntity::PropertyDisplayedColor.generateId(RToleranceEntity::getRtti(), REntity::PropertyDisplayedColor);
    RToleranceEntity::PropertyDrawOrder.generateId(RToleranceEntity::getRtti(), REntity::PropertyDrawOrder);

    RToleranceEntity::PropertyLocationX.generateId(RToleranceEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Location"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyLocationY.generateId(RToleranceEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Location"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyLocationZ.generateId(RToleranceEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Location"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyDirectionX.generateId(RToleranceEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Direction"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyDirectionY.generateId(RToleranceEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Direction"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyDirectionZ.generateId(RToleranceEntity::getRtti(), QT_TRANSLATE_NOOP("REntity", "Direction"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
    RToleranceEntity::PropertyText.generateId(RToleranceEntity::getRtti(), "", QT_TRANSLATE_NOOP("REntity", "Text"));
    RToleranceEntity::PropertyDimscale.generateId(RToleranceEntity::getRtti(), RDimStyle::PropertyDimscale);
    if (RPluginLoader::hasPlugin("DWG")) {
        RToleranceEntity::PropertyDimtxt.generateId(RToleranceEntity::getRtti(), RDimStyle::PropertyDimtxt);
    }
}

bool RToleranceEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {
    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.location.x, value, PropertyLocationX == propertyTypeId);
    ret = ret || RObject::setMember(data.location.y, value, PropertyLocationY == propertyTypeId);
    ret = ret || RObject::setMember(data.location.z, value, PropertyLocationZ == propertyTypeId);
    ret = ret || RObject::setMember(data.direction.x, value, PropertyDirectionX == propertyTypeId);
    ret = ret || RObject::setMember(data.direction.y, value, PropertyDirectionY == propertyTypeId);
    ret = ret || RObject::setMember(data.direction.z, value, PropertyDirectionZ == propertyTypeId);
    ret = ret || RObject::setMember(getData().text, value, PropertyText == propertyTypeId);
    ret = ret || RObject::setMember(getData().dimscale, value, PropertyDimscale == propertyTypeId);
    ret = ret || RObject::setMember(getData().dimtxt, value, PropertyDimtxt == propertyTypeId);

//    if (PropertyDimScale == propertyTypeId) {
//        ret = ret || RObject::setMember(data.dimScaleOverride, value, PropertyDimScale == propertyTypeId);
//    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RToleranceEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertyLocationX) {
        return qMakePair(QVariant(data.location.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLocationY) {
        return qMakePair(QVariant(data.location.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyLocationZ) {
        return qMakePair(QVariant(data.location.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDirectionX) {
        return qMakePair(QVariant(data.direction.x), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDirectionY) {
        return qMakePair(QVariant(data.direction.y), RPropertyAttributes());
    } else if (propertyTypeId == PropertyDirectionZ) {
        return qMakePair(QVariant(data.direction.z), RPropertyAttributes());
    } else if (propertyTypeId == PropertyText) {
        return qMakePair(QVariant(getData().text), RPropertyAttributes(RPropertyAttributes::RichText|RPropertyAttributes::Label));
    } else if (propertyTypeId == PropertyDimscale || propertyTypeId == PropertyDimtxt) {
        double v;
        if (propertyTypeId == PropertyDimscale) {
            v = data.dimscale;
        }
        else {
            v = data.dimtxt;
        }
        if (v<0.0) {
            RDocument* doc = getDocument();
            if (doc!=NULL) {
                QSharedPointer<RDimStyle> dimStyle = getDocument()->queryDimStyleDirect();
                if (!dimStyle.isNull()) {
                    if (propertyTypeId == PropertyDimscale) {
                        v = dimStyle->getDouble(RS::DIMSCALE);
                    }
                    else {
                        v = dimStyle->getDouble(RS::DIMTXT);
                    }
                }
            }
        }

        RPropertyAttributes attr;

        if (propertyTypeId==RToleranceEntity::PropertyDimscale) {
            attr.setUnitLess(true);
        }

        return qMakePair(QVariant(v), attr);
    }
//    else if (propertyTypeId == PropertyDimScale) {
//        return qMakePair(QVariant(data.dimScaleOverride), RPropertyAttributes());
//    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RToleranceEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview)
    Q_UNUSED(forceSelected)

    const RDocument* doc = getDocument();
    if (doc==NULL) {
        return;
    }

    double dimtxt = getDimtxt();
    RVector cursor = getLocation() + RVector(dimtxt/2.0, 0);
    QList<RTextData> labels = getTextLabels();

    // render text strings with distance of h:
    for (int i=0; i<labels.length(); i++) {
        RTextData textData = labels[i];
        textData.setSelected(isSelected());

        //qDebug() << "sub:" << sub;

//        RTextData textData(cursor,
//                     cursor,
//                     dimtxt,
//                     100.0,
//                     RS::VAlignMiddle,
//                     RS::HAlignLeft,
//                     RS::LeftToRight,
//                     RS::AtLeast,
//                     1.0,
//                     sub,
//                     "Arial",
//                     false,
//                     false,
//                     0,
//                     false);

        if (textData.isSane()) {
            RDimensionEntity::renderDimensionText(e, doc, textData, data.isSelected(), forceSelected);
        }

        cursor += RVector(textData.getBoundingBox().getWidth(), 0);
        cursor += RVector(dimtxt, 0);
    }


    // render frame:
    QList<RLine> lines = getFrame();
    for (int i=0; i<lines.length(); i++) {
        RLine line = lines[i];
        e.exportLine(line);
    }

}

void RToleranceEntity::print(QDebug dbg) const {
    dbg.nospace() << "RToleranceEntity(";
    dbg.nospace() << "location: " << data.getLocation() << ", ";
    dbg.nospace() << "dimscale: " << data.getDimscale() << ", ";
    dbg.nospace() << "text: " << data.getText() << ", ";
    REntity::print(dbg);
    dbg.nospace()  << ")";
}
