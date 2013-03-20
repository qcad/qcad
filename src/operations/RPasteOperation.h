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

#ifndef RPASTEOPERATION_H
#define RPASTEOPERATION_H

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
class RPasteOperation: public RClipboardOperation {
public:
    RPasteOperation(RDocument& sourceDocument);
    virtual ~RPasteOperation() {
    }

    void setOffset(const RVector& offset) {
        this->offset = offset;
    }
    RVector getOffset() {
        return this->offset;
    }
    void setScale(double scale) {
        this->scale = scale;
    }
    double getScale() {
        return this->scale;
    }
    void setRotation(double rotation) {
        this->rotation = rotation;
    }
    double getRotation() {
        return this->rotation;
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

    virtual RTransaction apply(RDocument& document, bool preview = false) const;

    RPolyline getBoundary(double unitFactor);

private:
    RDocument& sourceDocument;
    RVector offset;
    double scale;
    double rotation;
    bool flipHorizontal;
    bool flipVertical;
    bool toCurrentLayer;
    bool overwriteLayers;
    bool overwriteBlocks;
    QString blockName;
};

Q_DECLARE_METATYPE(RPasteOperation*)

#endif
