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

#ifndef RCLIPBOARDOPERATION_H
#define RCLIPBOARDOPERATION_H

#include "operations_global.h"

#include <QMap>

#include "ROperation.h"

class RDocument;
class RBlock;
class REntity;
class RLayer;
class RLinetype;
class RVector;

#ifndef RQMapQStringQString
typedef QMap<QString, QString> RQMapQStringQString;
#endif

/**
 * Base class for clipboard related operations (copy, cut, paste).
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RClipboardOperation : public ROperation {
public:
    RClipboardOperation();
    virtual ~RClipboardOperation() {}

    virtual RTransaction apply(RDocument& document, bool preview = false) {
        // MSVC:
        //Q_UNUSED(document)
        Q_UNUSED(preview)
        return RTransaction();
    }

    void copy(RDocument& src, RDocument& dest,
        const RVector& offset,
        double scale,
        double rotation,
        const RVector& center,
        bool flipHorizontal,
        bool flipVertical,
        bool toCurrentLayer,
        bool toCurrentBlock,
        bool overwriteLayers,
        bool overwriteBlocks,
        const QString& blockName,
        const QString& layerName,
        RTransaction& transaction,
        bool selectionOnly, bool clear,
        bool toModelSpaceBlock,
        bool preview) {

        copy(src, dest,
                offset,
                scale,
                rotation,
                center,
                flipHorizontal,
                flipVertical,
                toCurrentLayer,
                toCurrentBlock,
                overwriteLayers,
                overwriteBlocks,
                blockName,
                layerName,
                transaction,
                selectionOnly, clear,
                toModelSpaceBlock,
                preview,
                RQMapQStringQString(),
                RQMapQStringQString(),
                RQMapQStringQString());
    }
    
    /**
     * \nonscriptable
     */
    void copy(RDocument& src, RDocument& dest,
        const RVector& offset,
        double scale,
        double rotation,
        const RVector& center,
        bool flipHorizontal,
        bool flipVertical,
        bool toCurrentLayer,
        bool toCurrentBlock,
        bool overwriteLayers,
        bool overwriteBlocks,
        const QString& blockName,
        const QString& layerName,
        RTransaction& transaction,
        bool selectionOnly, bool clear,
        bool toModelSpaceBlock,
        bool preview,
        const RQMapQStringQString& attributes,
        const RQMapQStringQString& properties,
        const RQMapQStringQString& blockProperties
    );

    void copyEntity(
            REntity& entity,
            RDocument& src, RDocument& dest,
            const RVector& offset,
            double scale,
            double unitScale,
            double rotation,
            const RVector& center,
            bool flipHorizontal,
            bool flipVertical,
            bool toCurrentLayer,
            bool toCurrentBlock,
            bool overwriteLayers,
            bool overwriteBlocks,
            const QString& blockName,
            const QString& layerName,
            RTransaction& transaction,
            bool toModelSpaceBlock) {

        copyEntity(
                entity,
                src, dest,
                offset,
                scale,
                unitScale,
                rotation,
                center,
                flipHorizontal,
                flipVertical,
                toCurrentLayer,
                toCurrentBlock,
                overwriteLayers,
                overwriteBlocks,
                blockName,
                layerName,
                transaction,
                toModelSpaceBlock,
                RQMapQStringQString()
        );
    }

    /**
     * \nonscriptable
     */
    void copyEntity(
        REntity& entity,
        RDocument& src, RDocument& dest,
        const RVector& offset,
        double scale,
        double unitScale,
        double rotation,
        const RVector& center,
        bool flipHorizontal,
        bool flipVertical,
        bool toCurrentLayer,
        bool toCurrentBlock,
        bool overwriteLayers,
        bool overwriteBlocks,
        const QString& blockName,
        const QString& layerName,
        RTransaction& transaction,
        bool toModelSpaceBlock,
        const RQMapQStringQString& attributes
    );

    QSharedPointer<RBlock> copyEntityBlock(
        REntity& entity,
        RDocument& src,
        RDocument& dest,
        bool overwriteBlocks,
        bool toCurrentBlock,
        const QString& blockName,
        RTransaction& transaction
    );

    QSharedPointer<RBlock> copyBlock(
        RObject::Id blockId,
        RDocument& src,
        RDocument& dest,
        bool overwriteBlocks,
        bool toCurrentBlock,
        const QString& blockName,
        RTransaction& transaction
    );

    QSharedPointer<RLayer> copyEntityLayer(
        REntity& entity,
        RDocument& src,
        RDocument& dest,
        bool overwriteLayers,
        RTransaction& transaction
    );

    QSharedPointer<RLayer> copyLayer(
        RObject::Id layerId,
        RDocument& src, RDocument& dest,
        bool overwriteLayers,
        RTransaction& transaction
    );

    QSharedPointer<RLinetype> copyEntityLinetype(
            REntity& entity,
            RDocument& src,
            RDocument& dest,
            bool overwriteLinetypes,
            RTransaction& transaction
            );

    QSharedPointer<RLinetype> copyLinetype(
            RObject::Id linetypeId,
            RDocument& src, RDocument& dest,
            bool overwriteLinetypes,
            RTransaction& transaction
            );

    void setCopyEmptyBlocks(bool on) {
        copyEmptyBlocks = on;
    }

    void setCopyAllLayers(bool on) {
        copyAllLayers = on;
    }

    void setKeepSelection(bool on) {
        keepSelection = on;
    }

    void setBlockOwnership(bool on) {
        blockOwnership = on;
    }

    void setCustomEntityType(RS::EntityType t) {
        customEntityType = t;
    }

private:
    QMap<QString, QSharedPointer<RLayer> > copiedLayers;
    QMap<QString, QSharedPointer<RLinetype> > copiedLinetypes;
    QMap<QString, QSharedPointer<RBlock> > copiedBlocks;
    QSet<RObject::Id> copiedBlockContents;
    bool copyEmptyBlocks;
    bool copyAllLayers;
    bool keepSelection;
    bool blockOwnership;
    RS::EntityType customEntityType;
};

Q_DECLARE_METATYPE(RClipboardOperation*)

#endif
