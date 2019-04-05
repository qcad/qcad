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

#ifndef RELLIPSEDATA_H
#define RELLIPSEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RPoint.h"
#include "RVector.h"
#include "REllipse.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of an ellipse entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT REllipseData: public REntityData, protected REllipse {

    friend class REllipseEntity;

protected:
    REllipseData(RDocument* document, const REllipseData& data);

public:
    REllipseData();
    REllipseData(const REllipse& ellipse);
    REllipseData(
        const RVector& center, 
        const RVector& majorPoint, 
        double ratio, 
        double startParam, double endParam, 
        bool reversed = false);

    virtual RS::EntityType getType() const {
        return RS::EntityEllipse;
    }
    REllipse getEllipse() {
        return *this;
    }

    QList<RVector> getFoci() const {
        return REllipse::getFoci();
    }
    RVector getCenter() const {
        return REllipse::getCenter();
    }
    double getMajorRadius() const {
        return REllipse::getMajorRadius();
    }
    RVector getMajorPoint() const {
        return REllipse::getMajorPoint();
    }
    RVector getMinorPoint() const {
        return REllipse::getMinorPoint();
    }
    void setMinorPoint(const RVector& p) {
        REllipse::setMinorPoint(p);
    }
    double getRatio() const {
        return REllipse::getRatio();
    }
    double getAngle() const {
        return REllipse::getAngle();
    }
    double getStartParam() const {
        return REllipse::getStartParam();
    }
    double getEndParam() const {
        return REllipse::getEndParam();
    }
    bool isFullEllipse() const {
        return REllipse::isFullEllipse();
    }

    double getParamTo(const RVector& pos) {
        return REllipse::getParamTo(pos);
    }

    double getLength() const {
        return REllipse::getLength();
    }

    double getSweep() const {
        return REllipse::getSweep();
    }

    RVector getPointAt(double angle) const {
        return REllipse::getPointAt(angle);
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool reverse() {
        return REllipse::reverse();
    }

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const {
        Q_UNUSED(queryBox)
        Q_UNUSED(ignoreComplex)
        Q_UNUSED(segment)

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new REllipse(*this));
    }
};

Q_DECLARE_METATYPE(REllipseData)
Q_DECLARE_METATYPE(REllipseData*)
Q_DECLARE_METATYPE(const REllipseData*)
Q_DECLARE_METATYPE(QSharedPointer<REllipseData>)

#endif
