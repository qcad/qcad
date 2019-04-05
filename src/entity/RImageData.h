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

#ifndef RIMAGEDATA_H
#define RIMAGEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RLine.h"
#include "RPainterPath.h"
#include "RPoint.h"
#include "RVector.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a raster image entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RImageData: public REntityData {

    friend class RImageEntity;

protected:
    RImageData(RDocument* document, const RImageData& data);

public:
    RImageData();
    RImageData(const RImageData& other);
    RImageData(const QString& fileName,
        const RVector& insertionPoint,
        const RVector& uVector,
        const RVector& vVector,
        int brightness,
        int contrast,
        int fade);
    virtual ~RImageData();

    virtual RS::EntityType getType() const {
        return RS::EntityImage;
    }
    RImageData& operator=(const RImageData& other);

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

    virtual RShape* castToShape() {
        return NULL;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const;

    QString getFileName() const {
        return fileName;
    }
    void setFileName(const QString& fn) {
        fileName = fn;
    }

    RVector getInsertionPoint() const {
        return insertionPoint;
    }
    void setInsertionPoint(const RVector& ip) {
        insertionPoint = ip;
    }
    double getAngle() const {
        return uVector.getAngle();
    }
    void setAngle(double a) {
        uVector.setAngle(a);
        vVector.setAngle(a + M_PI/2.0);
    }
    RVector getUVector() const {
        return uVector;
    }
    void setUVector(const RVector& v) {
        uVector = v;
    }
    RVector getVVector() const {
        return vVector;
    }
    void setVVector(const RVector& v) {
        vVector = v;
    }
    void setWidth(double w, bool keepRatio=false);
    void setHeight(double h, bool keepRatio=false);
    double getWidth() const;
    double getHeight() const;
    int getPixelWidth() const;
    int getPixelHeight() const;
    //RVector getScaleFactor() const {
    //    return scaleFactor;
    //}
    int getBrightness() const {
        return brightness;
    }
    void setBrightness(int v) {
        brightness = v;
    }
    int getContrast() const {
        return contrast;
    }
    void setContrast(int v) {
        contrast = v;
    }
    int getFade() const {
        return fade;
    }
    void setFade(int v) {
        fade = v;
    }
    QImage getImage() const;

    void load() const;
    void reload();

    RVector getScaleVector() const;
    RVector mapToImage(const RVector& v) const;
    RVector mapFromImage(const RVector& v) const;

    QList<RVector> getCornersPx() const;
    QList<RVector> getCorners() const;
    QList<RLine> getEdges() const;

private:
    mutable QString fileName;
    RVector insertionPoint;
    RVector uVector;
    RVector vVector;
    int brightness;
    int contrast;
    int fade;
    mutable QImage image;
};

Q_DECLARE_METATYPE(RImageData)
Q_DECLARE_METATYPE(RImageData*)
Q_DECLARE_METATYPE(const RImageData*)
Q_DECLARE_METATYPE(QSharedPointer<RImageData>)

#endif
