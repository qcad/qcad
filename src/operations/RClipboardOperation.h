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

#include "RDocument.h"
#include "REntity.h"
#include "RExporter.h"
#include "ROperation.h"
#include "RVector.h"

#ifndef RQMapQStringQString
typedef QMap<QString, QString> RQMapQStringQString;
#endif

#define RDEFAULT_QMAP_QSTRING_QSTRING RQMapQStringQString()

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
        Q_UNUSED(document)
        Q_UNUSED(preview)
        return RTransaction();
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
        const RQMapQStringQString& attributes = RDEFAULT_QMAP_QSTRING_QSTRING,
        const RQMapQStringQString& properties = RDEFAULT_QMAP_QSTRING_QSTRING,
        const RQMapQStringQString& blockProperties = RDEFAULT_QMAP_QSTRING_QSTRING
    );

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
        const RQMapQStringQString& attributes = RDEFAULT_QMAP_QSTRING_QSTRING
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
        RBlock::Id blockId,
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
        RLayer::Id layerId,
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
            RLinetype::Id linetypeId,
            RDocument& src, RDocument& dest,
            bool overwriteLinetypes,
            RTransaction& transaction
            );

    void setCopyEmptyBlocks(bool on) {
        copyEmptyBlocks = on;
    }

private:
    QMap<QString, QSharedPointer<RLayer> > copiedLayers;
    QMap<QString, QSharedPointer<RLinetype> > copiedLinetypes;
    QMap<QString, QSharedPointer<RBlock> > copiedBlocks;
    QSet<RBlock::Id> copiedBlockContents;
    bool copyEmptyBlocks;
};

Q_DECLARE_METATYPE(RClipboardOperation*)

#endif
