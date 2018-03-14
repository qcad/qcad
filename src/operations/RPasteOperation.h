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

#ifndef RPASTEOPERATION_H
#define RPASTEOPERATION_H

#include "operations_global.h"

#include "RDocument.h"
#include "REntity.h"
#include "RExporter.h"
#include "RClipboardOperation.h"
#include "RVector.h"

/**
 * Implementation of an operation that pastes the clipboard
 * at a given reference point.
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RPasteOperation: public RClipboardOperation {
public:
    RPasteOperation(RDocument& sourceDocument);
    virtual ~RPasteOperation() {
    }

    void setOffsets(const QList<RVector>& offsets) {
        this->offsets = offsets;
    }
    void setRotations(const QList<double>& rotations) {
        this->rotations = rotations;
    }
    void setCenters(const QList<RVector>& centers) {
        this->centers = centers;
    }

    void setOffset(const RVector& offset) {
        if (this->offsets.isEmpty()) {
            this->offsets << offset;
        }
        else {
            this->offsets[0] = offset;
        }
    }
    RVector getOffset() {
        if (this->offsets.isEmpty()) {
            return RVector::invalid;
        }
        else {
            return this->offsets[0];
        }
    }
    void setScale(double scale) {
        this->scale = scale;
    }
    double getScale() {
        return this->scale;
    }
    void setRotation(double rotation) {
        if (this->rotations.isEmpty()) {
            this->rotations << rotation;
        }
        else {
            this->rotations[0] = rotation;
        }
    }
    double getRotation() {
        if (this->rotations.isEmpty()) {
            return 0.0;
        }
        else {
            return this->rotations[0];
        }
    }
    void setCenter(const RVector& centers) {
        if (this->centers.isEmpty()) {
            this->centers << centers;
        }
        else {
            this->centers[0] = centers;
        }
    }
    RVector getCenter() {
        if (this->centers.isEmpty()) {
            return RVector(0,0);
        }
        else {
            return this->centers[0];
        }
    }
    void setFlipHorizontal(bool flipHorizontal) {
        this->flipHorizontal = flipHorizontal;
    }
    bool getFlipHorizontal() {
        return this->flipHorizontal;
    }
    void setFlipVertical(bool flipVertical) {
        this->flipVertical = flipVertical;
    }
    bool getFlipVertical() {
        return this->flipVertical;
    }
    void setToCurrentLayer(bool toCurrentLayer) {
        this->toCurrentLayer = toCurrentLayer;
    }
    bool getToCurrentLayer() {
        return this->toCurrentLayer;
    }
    void setOverwriteLayers(bool overwriteLayers) {
        this->overwriteLayers = overwriteLayers;
    }
    bool getOverwriteLayers() {
        return this->overwriteLayers;
    }
    void setOverwriteBlocks(bool overwriteBlocks) {
        this->overwriteBlocks = overwriteBlocks;
    }
    bool getOverwriteBlocks() {
        return this->overwriteBlocks;
    }
    void setBlockName(const QString& blockName) {
        this->blockName = blockName;
    }
    QString getBlockName() {
        return this->blockName;
    }
    void setLayerName(const QString& layerName) {
        this->layerName = layerName;
    }
    QString getLayerName() {
        return this->layerName;
    }
    void setAttribute(const QString& tag, const QString& value) {
        attributes.insert(tag, value);
    }
    void setProperty(const QString& name, const QString& value) {
        properties.insert(name, value);
    }
    void setBlockProperty(const QString& name, const QString& value) {
        blockProperties.insert(name, value);
    }

    virtual RTransaction apply(RDocument& document, bool preview = false);

    RPolyline getBoundary(double unitFactor);

private:
    RDocument& sourceDocument;
    QList<RVector> offsets;
    double scale;
    QList<double> rotations;
    QList<RVector> centers;
    bool flipHorizontal;
    bool flipVertical;
    bool toCurrentLayer;
    bool overwriteLayers;
    bool overwriteBlocks;
    QString blockName;
    QString layerName;
    QMap<QString, QString> attributes;
    QMap<QString, QString> properties;
    QMap<QString, QString> blockProperties;
};

Q_DECLARE_METATYPE(RPasteOperation*)

#endif
