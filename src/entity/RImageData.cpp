/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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

    double minDist = RMAXDOUBLE;
    QList<RLine> edges = getEdges();
    for (int i=0; i<edges.size(); i++) {
        //ret.growToInclude(edges.at(i).getBoundingBox());
        double dist = edges.at(i).getDistanceTo(point, limited);
        if (dist < minDist) {
            minDist = dist;
        }
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
    //ret.append(insertionPoint);

    QList<RLine> edges = getEdges();
    for (int i=0; i<edges.count(); i++) {
        RLine l = edges.at(i);
        ret.append(l.getStartPoint());
    }

    return ret;
}

bool RImageData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint) {
    Q_UNUSED(referencePoint)
    Q_UNUSED(targetPoint)

    bool ret = false;
    // TODO scale image:
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

QList<RLine> RImageData::getEdges() const {
    load();

    QList<RLine> edges;

    //qDebug() << "image width: " << image.width();
    //qDebug() << "image u: " << uVector;
    //qDebug() << "image v: " << vVector;

    edges.append(RLine(RVector(0,0), RVector(image.width(),0)));
    edges.append(RLine(RVector(image.width(),0), RVector(image.width(),image.height())));
    edges.append(RLine(RVector(image.width(),image.height()), RVector(0,image.height())));
    edges.append(RLine(RVector(0,image.height()), RVector(0,0)));

    RVector scale = RVector(getUVector().getMagnitude(), getVVector().getMagnitude());

    if (RMath::getAngleDifference180(getUVector().getAngle(), getVVector().getAngle()) < 0.0) {
        scale.y *= -1;
    }

    double angle = getUVector().getAngle();

    for (int i=0; i<edges.size(); i++) {
        edges[i].scale(scale);
        edges[i].rotate(angle);
        edges[i].move(getInsertionPoint());

        //qDebug() << "edge: " << edges[i];
    }

    return edges;
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
