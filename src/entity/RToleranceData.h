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

#ifndef RTOLERANCEDATA_H
#define RTOLERANCEDATA_H

#include "entity_global.h"

#include "REntityData.h"
#include "RVector.h"

class RDocument;
class RLine;
class RRefPoint;

/**
 * Tolerance entity data class.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RToleranceData: public REntityData {
    friend class RToleranceEntity;

protected:
    RToleranceData(RDocument* document, const RToleranceData& data);

public:
    RToleranceData();

    virtual RS::EntityType getType() const {
        return RS::EntityTolerance;
    }
    virtual RShape* castToShape() {
        return NULL;
    }

    RVector getLocation() const {
        return location;
    }

    void setLocation(const RVector& l) {
        location = l;
        update();
    }

    RVector getDirection() const {
        return direction;
    }

    void setDirection(const RVector& d) {
        direction = d;
        update();
    }

    QList<QStringList> getFields() const;

    QString getText() const {
        return text;
    }
    void setText(const QString& t) {
        text = t;
        update();
    }
//    void addField(const QString& t) {
//        text += "%%v" + t;
//    }
//    void addLineBreak() {
//        text += "^J";
//    }

    double getDimtxt(bool scale = true) const;
    void setDimtxt(double f);

    double getDimscale() const;
    void setDimscale(double f);

    //double getDimscale(bool fromDocument=true) const;
    //void setDimScaleOverride(double v);


    virtual void scaleVisualProperties(double scaleFactor);

//    void setPolyline(const RPolyline& polyline) {
//        *((RPolyline*)this) = polyline;
//    }

    QList<RVector> getCorners() const;
    QList<RVector> getMiddels() const;

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center);
    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();

    QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const {
        //return RPolyline::getExploded(segments);
        return QList<QSharedPointer<RShape> >();
    }

    //virtual bool scale(const RVector& scaleFactors, const RVector& center);
    //virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const;

    virtual void update() const;

    QList<RTextData> getTextLabels() const;
    QList<RLine> getFrame() const;
    int getRows() const {
        return divisions.length();
    }

    RVector getPointOnEntity() const;

    virtual RVector getVectorTo(const RVector& point, bool limited=true, double strictRange = RMAXDOUBLE) const;

    void clearStyleOverrides() {
        dimscale = -1.0;
        dimtxt = -1.0;
        update();
    }

//    bool hasOverrides() const {
//        return overrides.isValid();
//    }

//    bool hasOverride(RS::KnownVariable key) const {
//        return overrides.hasOverride(key);
//    }

//    RDimStyleData getOverrides() const {
//        return overrides;
//    }

private:
    RVector location;
    RVector direction;
    /** Text code, e.g. {\Fgdt;b}%%v0.05%%v0.02%%vB%%v%%v */
    QString text;
    /** Dimension scale */
    //double dimScaleOverride;
    /** Block to use instead of arrow */
    RObject::Id dimToleranceBlockId;

    double dimscale;
    double dimtxt;

    // TODO: add alignment (top, bottom, left, right)
    // keep tolerance aligned when text, scale, etc. changes
    // store alignement in DXF/DWG as custom property

    mutable QList<QList<double> > divisions;
    mutable bool joinFirstField;
};

Q_DECLARE_METATYPE(RToleranceData)
Q_DECLARE_METATYPE(RToleranceData*)
Q_DECLARE_METATYPE(const RToleranceData*)
Q_DECLARE_METATYPE(QSharedPointer<RToleranceData>)

#endif
