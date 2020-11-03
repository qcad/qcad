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
#include <QDir>
#include <QFileInfo>
#if QT_VERSION >= 0x050000
#include <QGuiApplication>
#else
#include <QApplication>
#endif
#include "RImageData.h"

RImageData::RImageData() :
    brightness(50),
    contrast(50),
    fade(0) {
}

RImageData::RImageData(RDocument* document, const RImageData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RImageData::RImageData(const RImageData& other) : REntityData(other) {
    *this = other;
}

RImageData::RImageData(const QString& fileName,
        const RVector& insertionPoint,
        const RVector& uVector,
        const RVector& vVector,
        int brightness,
        int contrast,
        int fade) :
        fileName(fileName),
        insertionPoint(insertionPoint),
        uVector(uVector),
        vVector(vVector),
        brightness(brightness),
        contrast(contrast),
        fade(fade) {

}

RImageData::~RImageData() {
}

RImageData& RImageData::operator =(const RImageData& other) {
    other.load();
    REntityData::operator=(other);

    fileName = other.fileName;
    insertionPoint = other.insertionPoint;
    uVector = other.uVector;
    vVector = other.vVector;
    brightness = other.brightness;
    contrast = other.contrast;
    fade = other.fade;
    image = other.image;

    return *this;
}

RBox RImageData::getBoundingBox(bool ignoreEmpty) const {
    Q_UNUSED(ignoreEmpty)

    RBox ret;
    QList<RLine> edges = getEdges();
    for (int i=0; i<edges.size(); i++) {
        ret.growToInclude(edges.at(i).getBoundingBox());
    }
    return ret;
}

RVector RImageData::getPointOnEntity() const {
    return insertionPoint;
}

double RImageData::getDistanceTo(const RVector& point, bool limited, double range, bool draft, double strictRange) const {
    Q_UNUSED(range)
    Q_UNUSED(draft)
    Q_UNUSED(strictRange)

    double minDist = RNANDOUBLE;
    QList<RLine> edges = getEdges();
    for (int i=0; i<edges.size(); i++) {
        //ret.growToInclude(edges.at(i).getBoundingBox());
        double dist = edges.at(i).getDistanceTo(point, limited);
        if (dist < minDist || RMath::isNaN(minDist)) {
            minDist = dist;
        }
    }

    // point not close to image border:
    if (RMath::isNaN(minDist) || strictRange<minDist) {
        RPolyline pl(getCorners(), true);
        if (pl.contains(point)) {
            minDist = strictRange;
        }
    }

    if (RMath::isNaN(minDist)) {
        return RMAXDOUBLE;
    }

    return minDist;
}

bool RImageData::intersectsWith(const RShape& shape) const {
    //const RLine* line = dynamic_cast<const RLine*>(&shape);
    //if (line!=NULL) {
        QList<RLine> edges = getEdges();
        for (int i=0; i<edges.size(); i++) {
            if (edges.at(i).intersectsWith(shape)) {
                return true;
            }
        }
    //}
    return false;
}

QList<RRefPoint> RImageData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;
    QList<RVector> corners = getCorners();
    for (int i=0; i<corners.count(); i++) {
        ret.append(corners[i]);
    }
    return ret;
}

bool RImageData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    bool ret = false;

    // scale image:
    RVector referencePointPx = mapToImage(referencePoint);
    RVector targetPointPx = mapToImage(targetPoint);

//#if QT_VERSION >= 0x050000
//    Qt::KeyboardModifiers mod = QGuiApplication::queryKeyboardModifiers();
//#else
//    Qt::KeyboardModifiers mod = QApplication::queryKeyboardModifiers();
//#endif

    // shift to keep aspect ratio:
    bool keepAspectRatio = modifiers.testFlag(Qt::ShiftModifier);
    // TODO: from center:
    //bool fromCenter = mod.testFlag(???);
    bool fromCenter = false;

    QList<RVector> cornersPx = getCornersPx();
    RBox box(cornersPx[0], cornersPx[2]);
    ret = box.scaleByReference(referencePointPx, targetPointPx, keepAspectRatio, fromCenter);

    if (ret) {
        cornersPx = box.getCorners2d();
        int wpx = getPixelWidth();
        int hpx = getPixelHeight();
        if (wpx!=0 && hpx!=0) {
            RVector ip = mapFromImage(cornersPx[0]);
            RVector uv = mapFromImage(cornersPx[1])-mapFromImage(cornersPx[0]);
            uv.setMagnitude2D(uv.getMagnitude2D()/wpx);
            RVector vv = mapFromImage(cornersPx[3])-mapFromImage(cornersPx[0]);
            vv.setMagnitude2D(vv.getMagnitude2D()/getPixelHeight());
            setInsertionPoint(ip);
            setUVector(uv);
            setVVector(vv);
        }
    }

    return ret;
}

bool RImageData::move(const RVector& offset) {
    insertionPoint.move(offset);
    return true;
}

bool RImageData::rotate(double rotation, const RVector& center) {
    insertionPoint.rotate(rotation, center);
    uVector.rotate(rotation);
    vVector.rotate(rotation);
    return true;
}

bool RImageData::scale(const RVector& scaleFactors, const RVector& center) {
    insertionPoint.scale(scaleFactors, center);
    uVector.scale(scaleFactors);
    vVector.scale(scaleFactors);
    return true;
}

bool RImageData::mirror(const RLine& axis) {
    insertionPoint.mirror(axis);
    uVector.mirror(RVector(0.0,0.0), axis.getEndPoint()-axis.getStartPoint());
    vVector.mirror(RVector(0.0,0.0), axis.getEndPoint()-axis.getStartPoint());
    return true;
}

QList<QSharedPointer<RShape> > RImageData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(queryBox)
    Q_UNUSED(ignoreComplex)
    Q_UNUSED(segment)

    QList<QSharedPointer<RShape> > ret;
    return ret;
}

void RImageData::reload() {
    image = QImage();
    load();
}

void RImageData::load() const {
    if (!image.isNull()) {
        return;
    }

    // file name might be empty during import:
    if (fileName.isEmpty()) {
        return;
    }

    // load image from absolute path:
    if (QFileInfo(fileName).exists()) {
        if (!image.load(fileName)) {
            qWarning() << "RImageData::load: failed: " << fileName;
        }
        return;
    }

    QString docPath;
    const RDocument* document = getDocument();
    if (document!=NULL) {
        QString docFileName = document->getFileName();
        if (!docFileName.isEmpty()) {
            docPath = QFileInfo(docFileName).absolutePath();
        }
    }

    // load image from relative path:
    if (QFileInfo(fileName).isRelative()) {
        QString absPath = docPath + QDir::separator() + fileName;
        if (QFileInfo(absPath).exists()) {
            if (!image.load(absPath)) {
                qWarning() << "RImageData::load: failed: " << absPath;
            }
            fileName = absPath;
            return;
        }
    }

    // load image from same path as drawing file:
    QString absPath = docPath + QDir::separator() + QFileInfo(fileName).fileName();
    if (QFileInfo(absPath).exists()) {
        if (!image.load(absPath)) {
            qWarning() << "RImageData::load: failed: " << absPath;
        }
        fileName = absPath;
        return;
    }
}

RVector RImageData::getScaleVector() const {
    RVector ret = RVector(getUVector().getMagnitude(), getVVector().getMagnitude());
    if (RMath::getAngleDifference180(getUVector().getAngle(), getVVector().getAngle()) < 0.0) {
        ret.y *= -1;
    }
    return ret;
}

/**
 * Maps the given drawing coordinates to image pixel coordinates.
 */
RVector RImageData::mapToImage(const RVector& v) const {
    RVector ret = v;
    RVector scale = getScaleVector();
    ret.move(-getInsertionPoint());
    ret.rotate(-getUVector().getAngle());
    if (!RMath::fuzzyCompare(scale.x, 0.0) && !RMath::fuzzyCompare(scale.y, 0.0)) {
        ret.scale(RVector(1/scale.x, 1/scale.y));
    }
    return ret;
}

/**
 * Maps the given coordinate from image pixels to drawing coordinates.
 */
RVector RImageData::mapFromImage(const RVector& v) const {
    RVector ret = v;
    RVector scale = getScaleVector();
    ret.scale(scale);
    ret.rotate(getUVector().getAngle());
    ret.move(getInsertionPoint());
    return ret;
}

QList<RVector> RImageData::getCornersPx() const {
    QList<RVector> ret;
    ret.append(RVector(0,0));
    ret.append(RVector(image.width(),0));
    ret.append(RVector(image.width(),image.height()));
    ret.append(RVector(0,image.height()));
    return ret;
}

QList<RVector> RImageData::getCorners() const {
    load();

    QList<RVector> ret = getCornersPx();
    for (int i=0; i<ret.size(); i++) {
        ret[i] = mapFromImage(ret[i]);
    }
    return ret;
}

QList<RLine> RImageData::getEdges() const {
    QList<RVector> corners = getCorners();
    QList<RLine> ret;
    for (int i=0; i<corners.length(); ++i) {
        ret.append(RLine(corners[i], corners[(i+1)%corners.length()]));
    }
    return ret;
}

QImage RImageData::getImage() const {
    load();
    return image;
}

void RImageData::setWidth(double w, bool keepRatio) {
    if (w<RS::PointTolerance) {
        return;
    }
    double imageWidth = getImage().width();
    if (fabs(imageWidth)<RS::PointTolerance) {
        return;
    }
    double m2 = w / imageWidth;
    uVector.setMagnitude2D(m2);
    if (keepRatio) {
        double m1 = vVector.getMagnitude2D();
        if (m1<RS::PointTolerance) {
            return;
        }
        double f = m2/m1;
        vVector.setMagnitude2D(vVector.getMagnitude2D() * f);
    }
}

void RImageData::setHeight(double h, bool keepRatio) {
    if (h<RS::PointTolerance) {
        return;
    }
    double imageHeight = getImage().height();
    if (fabs(imageHeight)<RS::PointTolerance) {
        return;
    }
    double m2 = h / imageHeight;
    vVector.setMagnitude2D(m2);
    if (keepRatio) {
        double m1 = uVector.getMagnitude2D();
        if (m1<RS::PointTolerance) {
            return;
        }
        double f = m2/m1;
        uVector.setMagnitude2D(uVector.getMagnitude2D() * f);
    }
}

double RImageData::getWidth() const {
    double m2 = uVector.getMagnitude2D();
    double imageWidth = getImage().width();
    return m2 * imageWidth;
}

double RImageData::getHeight() const {
    double m2 = vVector.getMagnitude2D();
    double imageHeight = getImage().height();
    return m2 * imageHeight;
}

int RImageData::getPixelWidth() const {
    return getImage().width();
}

int RImageData::getPixelHeight() const {
    return getImage().height();
}
