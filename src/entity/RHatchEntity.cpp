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
#include "RArc.h"
#include "RCircle.h"
#include "RMetaTypes.h"
#include "REllipse.h"
#include "RExporter.h"
#include "RHatchEntity.h"
#include "RLine.h"
#include "RPoint.h"
#include "RSpline.h"

RPropertyTypeId RHatchEntity::PropertyCustom;
RPropertyTypeId RHatchEntity::PropertyHandle;
RPropertyTypeId RHatchEntity::PropertyProtected;
RPropertyTypeId RHatchEntity::PropertyWorkingSet;
RPropertyTypeId RHatchEntity::PropertyType;
RPropertyTypeId RHatchEntity::PropertyBlock;
RPropertyTypeId RHatchEntity::PropertyLayer;
RPropertyTypeId RHatchEntity::PropertyLinetype;
RPropertyTypeId RHatchEntity::PropertyLinetypeScale;
RPropertyTypeId RHatchEntity::PropertyLineweight;
RPropertyTypeId RHatchEntity::PropertyColor;
RPropertyTypeId RHatchEntity::PropertyDisplayedColor;
RPropertyTypeId RHatchEntity::PropertyDrawOrder;

RPropertyTypeId RHatchEntity::PropertySolid;
RPropertyTypeId RHatchEntity::PropertyTransparency;

RPropertyTypeId RHatchEntity::PropertyPatternName;
RPropertyTypeId RHatchEntity::PropertyEntityPattern;
RPropertyTypeId RHatchEntity::PropertyScaleFactor;
RPropertyTypeId RHatchEntity::PropertyAngle;

RPropertyTypeId RHatchEntity::PropertyOriginX;
RPropertyTypeId RHatchEntity::PropertyOriginY;

RPropertyTypeId RHatchEntity::PropertyVertexNX;
RPropertyTypeId RHatchEntity::PropertyVertexNY;
RPropertyTypeId RHatchEntity::PropertyVertexNZ;


RHatchEntity::RHatchEntity(RDocument* document, const RHatchData& data) :
    REntity(document), data(document, data) {
}

RHatchEntity::~RHatchEntity() {
}

RHatchEntity* RHatchEntity::clone() const {
    return new RHatchEntity(*this);
}

void RHatchEntity::init() {
    RHatchEntity::PropertyCustom.generateId(typeid(RHatchEntity), RObject::PropertyCustom);
    RHatchEntity::PropertyHandle.generateId(typeid(RHatchEntity), RObject::PropertyHandle);
    RHatchEntity::PropertyProtected.generateId(typeid(RHatchEntity), RObject::PropertyProtected);
    RHatchEntity::PropertyWorkingSet.generateId(typeid(RHatchEntity), RObject::PropertyWorkingSet);
    RHatchEntity::PropertyType.generateId(typeid(RHatchEntity), REntity::PropertyType);
    RHatchEntity::PropertyBlock.generateId(typeid(RHatchEntity), REntity::PropertyBlock);
    RHatchEntity::PropertyLayer.generateId(typeid(RHatchEntity), REntity::PropertyLayer);
    RHatchEntity::PropertyLinetype.generateId(typeid(RHatchEntity), REntity::PropertyLinetype);
    RHatchEntity::PropertyLinetypeScale.generateId(typeid(RHatchEntity), REntity::PropertyLinetypeScale);
    RHatchEntity::PropertyLineweight.generateId(typeid(RHatchEntity), REntity::PropertyLineweight);
    RHatchEntity::PropertyColor.generateId(typeid(RHatchEntity), REntity::PropertyColor);
    RHatchEntity::PropertyDisplayedColor.generateId(typeid(RHatchEntity), REntity::PropertyDisplayedColor);
    RHatchEntity::PropertyDrawOrder.generateId(typeid(RHatchEntity), REntity::PropertyDrawOrder);

    RHatchEntity::PropertySolid.generateId(typeid(RHatchEntity), "", QT_TRANSLATE_NOOP("REntity", "Solid"));
    RHatchEntity::PropertyTransparency.generateId(typeid(RHatchEntity), "", QT_TRANSLATE_NOOP("REntity", "Alpha"));

    RHatchEntity::PropertyPatternName.generateId(typeid(RHatchEntity), QT_TRANSLATE_NOOP("REntity", "Pattern"), QT_TRANSLATE_NOOP("REntity", "Name"));
    RHatchEntity::PropertyEntityPattern.generateId(typeid(RHatchEntity), QT_TRANSLATE_NOOP("REntity", "Pattern"), QT_TRANSLATE_NOOP("REntity", "From Entity"));
    RHatchEntity::PropertyAngle.generateId(typeid(RHatchEntity), QT_TRANSLATE_NOOP("REntity", "Pattern"), QT_TRANSLATE_NOOP("REntity", "Angle"), false, RPropertyAttributes::Geometry);
    RHatchEntity::PropertyScaleFactor.generateId(typeid(RHatchEntity), QT_TRANSLATE_NOOP("REntity", "Pattern"), QT_TRANSLATE_NOOP("REntity", "Scale"), false, RPropertyAttributes::Geometry);

    RHatchEntity::PropertyOriginX.generateId(typeid(RHatchEntity), QT_TRANSLATE_NOOP("REntity", "Origin"), QT_TRANSLATE_NOOP("REntity", "X"));
    RHatchEntity::PropertyOriginY.generateId(typeid(RHatchEntity), QT_TRANSLATE_NOOP("REntity", "Origin"), QT_TRANSLATE_NOOP("REntity", "Y"));

    RHatchEntity::PropertyVertexNX.generateId(typeid(RHatchEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "X"), false, RPropertyAttributes::Geometry);
    RHatchEntity::PropertyVertexNY.generateId(typeid(RHatchEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Y"), false, RPropertyAttributes::Geometry);
    RHatchEntity::PropertyVertexNZ.generateId(typeid(RHatchEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Z"), false, RPropertyAttributes::Geometry);
}

bool RHatchEntity::setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
    RTransaction* transaction) {

    bool ret = REntity::setProperty(propertyTypeId, value, transaction);

    ret = ret || RObject::setMember(data.solid, value, PropertySolid == propertyTypeId);
    ret = ret || RObject::setMember(data.transparency, value, PropertyTransparency == propertyTypeId);

    ret = ret || RObject::setMember(data.patternName, value, PropertyPatternName == propertyTypeId);
    ret = ret || RObject::setMember(data.scaleFactor, value, PropertyScaleFactor == propertyTypeId);
    ret = ret || RObject::setMember(data.angle, value, PropertyAngle == propertyTypeId);

    ret = ret || RObject::setMember(data.originPoint.x, value, PropertyOriginX == propertyTypeId);
    ret = ret || RObject::setMember(data.originPoint.y, value, PropertyOriginY == propertyTypeId);

    if (data.hasCustomPattern()) {
        // user adjusted property: drop custom pattern
        data.pattern.clear();
    }

    ret = ret || setBoundaryVector(RObject::X, value, PropertyVertexNX == propertyTypeId);
    ret = ret || setBoundaryVector(RObject::Y, value, PropertyVertexNY == propertyTypeId);
    ret = ret || setBoundaryVector(RObject::Z, value, PropertyVertexNZ == propertyTypeId);

    if (ret) {
        data.update();
    }

    return ret;
}

/**
 * Sets some x, y or z components of some nodes.
 * \param value list of values to change in format QList<QPair<int, double> > >
 */
bool RHatchEntity::setBoundaryVector(RObject::XYZ xyz, const QVariant& value, bool condition) {
    if (!condition) {
        return false;
    }

    if (!value.canConvert<QList<QPair<int, double> > >()) {
        qWarning() << QString("RHatchEntity::setBoundaryVector: "
                              "'%1' is not a QList<QPair<int, double> >")
                      .arg(value.toString());
        return false;
    }

    bool ret = false;

    QList<QPair<int, double> > pairList = value.value<QList<QPair<int, double> > >();
    QList<QPair<int, double> >::iterator it;
    for (it=pairList.begin(); it!=pairList.end(); ++it) {
        int i = (*it).first;
        double v = (*it).second;
        int internalIndex;

        QPair<QSharedPointer<RShape>, QSharedPointer<RShape> > shapes;
        shapes = data.getBoundaryElementsAt(i, internalIndex);

        // move end point of first element (or center):
        if (!shapes.first.isNull()) {
            QSharedPointer<RLine> line = shapes.first.dynamicCast<RLine>();
            if (!line.isNull()) {
                line->setEndPoint(setComponent(line->getEndPoint(), v, xyz));
                ret = true;
            }

            QSharedPointer<RArc> arc = shapes.first.dynamicCast<RArc>();
            if (!arc.isNull()) {
                arc->moveEndPoint(setComponent(arc->getEndPoint(), v, xyz));
                ret = true;
            }

            QSharedPointer<RCircle> circle = shapes.first.dynamicCast<RCircle>();
            if (!circle.isNull()) {
                circle->setCenter(setComponent(circle->getCenter(), v, xyz));
                Q_ASSERT(shapes.second.isNull());
                ret = true;
            }

            QSharedPointer<REllipse> ellipse = shapes.first.dynamicCast<REllipse>();
            if (!ellipse.isNull()) {
                if (ellipse->isFullEllipse()) {
                    ellipse->setCenter(setComponent(ellipse->getCenter(), v, xyz));
                    Q_ASSERT(shapes.second.isNull());
                    ret = true;
                }
                else {
                    ellipse->moveEndPoint(setComponent(ellipse->getEndPoint(), v, xyz), false);
                    ret = true;
                }
            }

            QSharedPointer<RSpline> spline = shapes.first.dynamicCast<RSpline>();
            if (!spline.isNull()) {
                // move control point of spline:
                if (internalIndex!=0 && shapes.second.isNull()) {
                    QList<RVector> controlPoints = spline->getControlPoints();
                    controlPoints[internalIndex] = setComponent(controlPoints[internalIndex], v, xyz);
                    spline->setControlPoints(controlPoints);
                }
                else {
                    QList<RVector> controlPoints = spline->getControlPoints();
                    controlPoints[controlPoints.size()-1] = setComponent(controlPoints[controlPoints.size()-1], v, xyz);
                    spline->setControlPoints(controlPoints);
                }
                ret = true;
            }
        }
        else {
            Q_ASSERT(false);
        }

        // move start point of second element:
        if (!shapes.second.isNull()) {
            QSharedPointer<RLine> line = shapes.second.dynamicCast<RLine>();
            if (!line.isNull()) {
                line->setStartPoint(setComponent(line->getStartPoint(), v, xyz));
                ret = true;
            }

            QSharedPointer<RArc> arc = shapes.second.dynamicCast<RArc>();
            if (!arc.isNull()) {
                arc->moveStartPoint(setComponent(arc->getStartPoint(), v, xyz));
                ret = true;
            }

            QSharedPointer<REllipse> ellipse = shapes.second.dynamicCast<REllipse>();
            if (!ellipse.isNull()) {
                if (!ellipse->isFullEllipse()) {
                    ellipse->moveStartPoint(setComponent(ellipse->getStartPoint(), v, xyz), false);
                    ret = true;
                }
            }

            QSharedPointer<RSpline> spline = shapes.second.dynamicCast<RSpline>();
            if (!spline.isNull()) {
                spline->setStartPoint(setComponent(spline->getStartPoint(), v, xyz));
                ret = true;
            }
        }
    }

    return ret;
}

RVector RHatchEntity::setComponent(const RVector& p, double v, RObject::XYZ xyz) {
    RVector ret = p;

    switch (xyz) {
    case RObject::X:
        ret.x = v;
        break;
    case RObject::Y:
        ret.y = v;
        break;
    case RObject::Z:
        ret.z = v;
        break;
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RHatchEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable, bool noAttributes, bool showOnRequest) {

    if (propertyTypeId == PropertySolid) {
        //return qMakePair(QVariant(data.solid), RPropertyAttributes(RPropertyAttributes::AffectsOtherProperties));
        return qMakePair(QVariant(data.solid), RPropertyAttributes());
    }

    RPropertyAttributes::Option op = RPropertyAttributes::NoOptions;
    QString name = data.patternName;
    if (data.isSolid()) {
        op = RPropertyAttributes::ReadOnly;
        name = "SOLID";
    }

    if (propertyTypeId == PropertyTransparency) {
        return qMakePair(QVariant(data.transparency), RPropertyAttributes());
    }

    if (propertyTypeId == PropertyPatternName) {
        return qMakePair(QVariant(name), RPropertyAttributes(RPropertyAttributes::Pattern|op));
    } else if (propertyTypeId == PropertyEntityPattern) {
        return qMakePair(QVariant(data.hasCustomPattern() ? QT_TRANSLATE_NOOP("REntity", "Yes") : QT_TRANSLATE_NOOP("REntity", "No")), RPropertyAttributes(RPropertyAttributes::ReadOnly));
    } else if (propertyTypeId == PropertyScaleFactor) {
        return qMakePair(QVariant(data.scaleFactor), RPropertyAttributes(op));
    } else if (propertyTypeId == PropertyAngle) {
        return qMakePair(QVariant(data.angle), RPropertyAttributes(RPropertyAttributes::Angle|op));
    } else if (propertyTypeId == PropertyOriginX) {
        return qMakePair(QVariant(data.originPoint.x), RPropertyAttributes(op));
    } else if (propertyTypeId == PropertyOriginY) {
        return qMakePair(QVariant(data.originPoint.y), RPropertyAttributes(op));
    }

    if (propertyTypeId == PropertyVertexNX ||
             propertyTypeId == PropertyVertexNY ||
             propertyTypeId == PropertyVertexNZ) {
        QList<double> list;

        // add x,y or z of all reference points along the boundary to list of doubles:
        for (int i=0; i<data.boundary.size(); ++i) {
            QList<QSharedPointer<RShape> > loop = data.boundary.at(i);
            for (int k=0; k<loop.size(); ++k) {
                QSharedPointer<RShape> shape = loop.at(k);

                QList<RVector> pointList;

                QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
                if (!line.isNull()) {
                    pointList.append(line->getStartPoint());
                }

                QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
                if (!arc.isNull()) {
                    pointList.append(arc->getStartPoint());
                }

                QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
                if (!circle.isNull()) {
                    pointList.append(circle->getCenter());
                }

                QSharedPointer<REllipse> ellipseArc = shape.dynamicCast<REllipse>();
                if (!ellipseArc.isNull()) {
                    if (ellipseArc->isFullEllipse()) {
                        pointList.append(ellipseArc->getCenter());
                    }
                    else {
                        pointList.append(ellipseArc->getStartPoint());
                    }
                }

                QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
                if (!spline.isNull()) {
                    // for splines, we add all control points for undo/redo:
                    pointList.append(spline->getControlPoints());
                    pointList.removeLast();
                }

                // add x,y or z component to double list:
                for (int n=0; n<pointList.size(); n++) {
                    RVector vector = pointList.at(n);
                    if (propertyTypeId == PropertyVertexNX) {
                        list.append(vector.x);
                    }
                    else if (propertyTypeId == PropertyVertexNY) {
                        list.append(vector.y);
                    }
                    else if (propertyTypeId == PropertyVertexNZ) {
                        list.append(vector.z);
                    }
                }

                //indexCounter++;
            }
        }

        QVariant v;
        v.setValue(list);
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes, showOnRequest);
}


void RHatchEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    e.exportPainterPathSource(data);
}

void RHatchEntity::print(QDebug dbg) const {
    dbg.nospace() << "RHatchEntity(";
    REntity::print(dbg);
    dbg.nospace() << ", solid: " << data.solid
                  << ", scale: " << data.scaleFactor
                  << ", angle: " << RMath::rad2deg(data.angle)
                  << ", origin: " << data.originPoint
                  << ", pattern: " << data.patternName;

    dbg.nospace() << ",\nboundary: \n";
    for (int i=0; i<data.boundary.size(); ++i) {
        dbg.nospace() << "\tloop " << i << ": \n";
        QList<QSharedPointer<RShape> > loop = data.boundary.at(i);
        for (int k=0; k<loop.size(); ++k) {
            QSharedPointer<RShape> shape = loop.at(k);
            dbg.nospace() << "   " << shape->getStartPoint() << ", " << shape->getEndPoint() << "\n";
        }
    }
    dbg.nospace() << ")";
}

void RHatchEntity::setViewportContext(const RViewportData& vp) {
    // apply viewport transforms:
    RVector offs =  vp.getViewCenter()*vp.getScale() + vp.getViewTarget()*vp.getScale() - data.getOriginPoint()*vp.getScale();
    offs.rotate(vp.getRotation());

    // make sure custom pattern is not cleared here:
    data.setOriginPoint(vp.getCenter() - offs, false);

    // rotate custom pattern:
    if (data.hasCustomPattern()) {
        RPattern p = data.getCustomPattern();
        p.rotate(vp.getRotation());
        data.setCustomPattern(p);
    }
}
