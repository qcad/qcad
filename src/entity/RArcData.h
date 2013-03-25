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

#ifndef RARCDATA_H
#define RARCDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RPoint.h"
#include "RVector.h"
#include "RArc.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of an arc entity.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RArcData: public REntityData, protected RArc {

    friend class RArcEntity;

protected:
    RArcData(RDocument* document, const RArcData& data);

public:
    RArcData();
    RArcData(const RArc& arc);
    RArcData(const RVector& center, double radius, double startAngle,
            double endAngle, bool reversed = false);

    RVector getCenter() const {
        return RArc::getCenter();
    }
    double getRadius() const {
        return RArc::getRadius();
    }
    double getBulge() const {
        return RArc::getBulge();
    }
    double getStartAngle() const {
        return RArc::getStartAngle();
    }
    double getEndAngle() const {
        return RArc::getEndAngle();
    }
    bool isReversed() const {
        return RArc::isReversed();
    }
    double getDirection1() const {
        return RArc::getDirection1();
    }
    double getDirection2() const {
        return RArc::getDirection2();
    }
    bool reverse() {
        return RArc::reverse();
    }

    RS::Ending getTrimEnd(const RVector& coord,
                            const RVector& trimPoint) {
        return RArc::getTrimEnd(coord, trimPoint);
    }
    void trimStartPoint(const RVector& p) {
        return RArc::trimStartPoint(p);
    }
    void trimEndPoint(const RVector& p) {
        return RArc::trimEndPoint(p);
    }

    double getLength() const {
        return RArc::getLength();
    }
    double getAngleLength(bool allowForZeroLength = false) const {
        return RArc::getAngleLength(allowForZeroLength);
    }

    virtual QList<RVector> getReferencePoints(
        RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, 
        const RVector& targetPoint);

    RPolyline approximateWithLines(double segmentLength) {
        return RArc::approximateWithLines(segmentLength);
    }

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX) const {
        Q_UNUSED(queryBox)

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new RArc(*this));
    }
};

Q_DECLARE_METATYPE(RArcData*)
Q_DECLARE_METATYPE(QSharedPointer<RArcData>)

#endif
