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

#ifndef RCOPYOPERATION_H
#define RCOPYOPERATION_H

#include "operations_global.h"

#include "RClipboardOperation.h"
#include "RVector.h"

class RDocument;

/**
 * Implementation of an operation that copies the selection of the
 * given document to the clipboard
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RCopyOperation : public RClipboardOperation {
public:
    RCopyOperation(const RVector& offset, RDocument& src);
    virtual ~RCopyOperation() {}
    
    virtual RTransaction apply(RDocument& document, bool preview = false);

    void setClear(bool on) {
        clear = on;
    }

    // setter / getters:
    void setScale(double s) {
        scale = s;
    }
    double getScale() const {
        return scale;
    }
    void setAngle(double a) {
        angle = a;
    }
    double getAngle() const {
        return angle;
    }
    void setCenter(const RVector& c) {
        center = c;
    }
    RVector getCenter() const {
        return center;
    }
    void setFlipHorizontal(bool on) {
        flipHorizontal = on;
    }
    bool getFlipHorizontal() const {
        return flipHorizontal;
    }
    void setFlipVertical(bool on) {
        flipVertical = on;
    }
    bool getFlipVertical() const {
        return flipVertical;
    }
    void setToCurrentLayer(bool on) {
        toCurrentLayer = on;
    }
    bool getToCurrentLayer() const {
        return toCurrentLayer;
    }
    void setToCurrentBlock(bool on) {
        toCurrentBlock = on;
    }
    bool getToCurrentBlock() const {
        return toCurrentBlock;
    }
    void setOverwriteLayers(bool on) {
        overwriteLayers = on;
    }
    bool getOverwriteLayers() const {
        return overwriteLayers;
    }
    void setOverwriteBlocks(bool on) {
        overwriteBlocks = on;
    }
    bool getOverwriteBlocks() const {
        return overwriteBlocks;
    }
    void setBlockName(const QString& n) {
        blockName = n;
    }
    QString getBlockName() const {
        return blockName;
    }
    void setLayerName(const QString& n) {
        layerName = n;
    }
    QString getLayerName() const {
        return layerName;
    }
    void setSelectionOnly(bool on) {
        selectionOnly = on;
    }
    bool getSelectionOnly() const {
        return selectionOnly;
    }
    void setToModelSpaceBlock(bool on) {
        toModelSpaceBlock = on;
    }
    bool getToModelSpaceBlock() const {
        return toModelSpaceBlock;
    }

private:
    RDocument& src;

    RVector offset;
    double scale;
    double angle;
    RVector center;
    bool flipHorizontal;
    bool flipVertical;
    bool toCurrentLayer;
    bool toCurrentBlock;
    bool overwriteLayers;
    bool overwriteBlocks;
    QString blockName;
    QString layerName;
    bool selectionOnly;
    bool clear;
    bool toModelSpaceBlock;
};

Q_DECLARE_METATYPE(RCopyOperation*)

#endif
