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

#ifndef RCLIPBOARDOPERATION_H
#define RCLIPBOARDOPERATION_H

#include "operations_global.h"

#include <QMap>

#include "RDocument.h"
#include "REntity.h"
#include "RExporter.h"
#include "ROperation.h"
#include "RVector.h"

typedef QMap<QString, QString> RQMapQStringQString;

#define RDEFAULT_QMAP_QSTRING_QSTRING RQMapQStringQString()

/**
 * Base class for clipboard related operations (copy, cut, paste).
 * 
 * \ingroup operations
 * \scriptable
 * \abstract
 */
class QCADOPERATIONS_EXPORT RClipboardOperation : public ROperation {
public:
    RClipboardOperation();
    virtual ~RClipboardOperation() {}
    
protected:
    void copy(RDocument& src, RDocument& dest,
        const RVector& offset,
        double scale,
        double rotation,
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
        const RQMapQStringQString& attributes = RDEFAULT_QMAP_QSTRING_QSTRING
    ) const;

    void copyEntity(
        REntity& entity,
        RDocument& src, RDocument& dest,
        const RVector& offset,
        double scale,
        double unitScale,
        double rotation,
        bool flipHorizontal,
        bool flipVertical,
        bool toCurrentLayer,
        bool toCurrentBlock,
        bool overwriteLayers,
        bool overwriteBlocks,
        const QString& blockName,
        RTransaction& transaction,
        bool toModelSpaceBlock
    ) const;

    QSharedPointer<RLayer> copyEntityLayer(
        REntity& entity,
        RDocument& src,
        RDocument& dest,
        bool overwriteLayers,
        RTransaction& transaction
    ) const;

    QSharedPointer<RLayer> copyLayer(
        RLayer::Id layerId,
        RDocument& src, RDocument& dest,
        bool overwriteLayers,
        RTransaction& transaction
    ) const;

private:
    mutable QMap<QString, QSharedPointer<RLayer> > copiedLayers;
    mutable QMap<QString, QSharedPointer<RBlock> > copiedBlocks;
    mutable QSet<RBlock::Id> copiedBlockContents;
};

Q_DECLARE_METATYPE(RClipboardOperation*)

#endif
