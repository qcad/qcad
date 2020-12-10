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

#ifndef RHATCHDATA_H
#define RHATCHDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RHatchProxy.h"
#include "RLine.h"
#include "RPattern.h"
#include "RPainterPath.h"
#include "RPainterPathSource.h"
#include "RPoint.h"
#include "RVector.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a hatch or solid fill entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RHatchData: public REntityData, public RPainterPathSource {

    friend class RHatchEntity;

protected:
    RHatchData(RDocument* document, const RHatchData& data);

public:
    RHatchData();
    RHatchData(const RHatchData& other);
    RHatchData(bool solid, double scaleFactor, double angle, const QString& patternName);

    virtual RS::EntityType getType() const {
        return RS::EntityHatch;
    }
    RHatchData& operator=(const RHatchData& other);

    void clearBoundary();

    bool hasCustomPattern() const {
        return !pattern.getPatternLines().isEmpty();
    }

    RPattern getCustomPattern() const {
        return pattern;
    }

    void setCustomPattern(const RPattern& p) {
        pattern = p;
    }

    virtual bool cloneOnChange() const {
        // force clone to preserve custom pattern for undo:
        //return hasCustomPattern();
        // 20190510: always clone (since allowing non-uniform scaling of hatches)
        return true;
    }

    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    virtual RVector getPointOnEntity() const;
    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false, double strictRange = RMAXDOUBLE) const;
    virtual bool intersectsWith(const RShape& shape) const;

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual RShape* castToShape() {
        return NULL;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const;
    virtual QList<QSharedPointer<RShape> > getExploded() const;

    bool isSolid() const {
        return solid;
    }

    void setSolid(bool on) {
        solid = on;
        clearCustomPattern();
    }

    double getScale() const {
        return scaleFactor;
    }

    void setScale(double s) {
        scaleFactor = s;
        clearCustomPattern();
    }

    double getAngle() const {
        return angle;
    }

    void setAngle(double a) {
        angle = a;
        clearCustomPattern();
    }

    RVector getOriginPoint() const {
        return originPoint;
    }

    void setOriginPoint(const RVector& op, bool clearCustom = true) {
        originPoint = op;
        if (clearCustom) {
            clearCustomPattern();
        }
    }

    QString getPatternName() const {
        return patternName;
    }

    void setPatternName(const QString& n) {
        patternName = n;
        clearCustomPattern();
    }

    int getTransparency() const {
        return transparency;
    }

    void setTransparency(int t) {
        transparency = t;
    }

    void clearCustomPattern();

    void newLoop();
    void cancelLoop();
    void addBoundary(QSharedPointer<RShape> shape, bool addAutoLoops = true);
    RPainterPath getBoundaryPath(double pixelSizeHint = RDEFAULT_MIN1) const;
    virtual QList<RPainterPath> getPainterPaths(bool draft = false, double pixelSizeHint = RDEFAULT_MIN1) const;

    QList<QList<QSharedPointer<RShape> > > getBoundary() const {
        return boundary;
    }

    /**
     * \nonscriptable
     */
    QPair<QSharedPointer<RShape>, QSharedPointer<RShape> > getBoundaryElementsAt(int index, int& internalIndex) const;

    virtual void update() const;
    bool order();

    int getLoopCount() const {
        return boundary.count();
    }

    QList<QSharedPointer<RShape> > getLoopBoundary(int index) const;

    QList<RPolyline> getBoundaryAsPolylines(double segmentLength) const;

    int getComplexity() const;

    void setPattern(const RPattern& p) {
        pattern = p;
    }

    virtual RColor getColor() const {
        RColor c = REntityData::getColor();
        c.setAlpha(transparency);
        return c;
    }

    virtual RColor getColor(const RColor& unresolvedColor, const QStack<REntity *>& blockRefStack) const {
        RColor c = REntityData::getColor(unresolvedColor, blockRefStack);
        c.setAlpha(transparency);
        return c;
    }
    virtual RColor getColor(bool resolve, const QStack<REntity *>& blockRefStack) const {
        RColor c = REntityData::getColor(resolve, blockRefStack);
        c.setAlpha(transparency);
        return c;
    }

    static bool hasProxy() {
        return hatchProxy!=NULL;
    }

    /**
     * \nonscriptable
     */
    static void setHatchProxy(RHatchProxy* p) {
        if (hatchProxy!=NULL) {
            delete hatchProxy;
        }
        hatchProxy = p;
    }

    /**
     * \nonscriptable
     */
    static RHatchProxy* getHatchProxy() {
        return hatchProxy;
    }

protected:
    QList<RLine> getSegments(const RLine& line) const;

private:
    bool solid;
    double scaleFactor;
    double angle;
    QString patternName;
    RVector originPoint;
    int transparency;

    /**
     * Hatch boundary, ordered by loops, in strictly defined order.
     */
    QList<QList<QSharedPointer<RShape> > > boundary;

    /**
     * Custom pattern loaded from DXF file, not LIN file.
     * Pattern is stored independent of pattern origin point.
     */
    mutable RPattern pattern;

    mutable RPainterPath boundaryPath;
    mutable QList<RPainterPath> painterPaths;
    mutable bool dirty;
    mutable bool gotDraft;
    mutable double gotPixelSizeHint;

    static RHatchProxy* hatchProxy;
};

Q_DECLARE_METATYPE(RHatchData)
Q_DECLARE_METATYPE(RHatchData*)
Q_DECLARE_METATYPE(const RHatchData*)
Q_DECLARE_METATYPE(QSharedPointer<RHatchData>)

#endif
