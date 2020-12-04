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
#include <QSet>

#include "RDocument.h"
#include "RCopyOperation.h"
#include "RExporter.h"


RCopyOperation::RCopyOperation(const RVector& offset, RDocument& src)
    : clear(true), offset(offset), src(src) {
}



RTransaction RCopyOperation::apply(RDocument& document, bool preview) {
    RTransaction transaction(document.getStorage(), text);
    transaction.setGroup(transactionGroup);
    transaction.setTypes(transactionTypes);

    copy(
        src, document,
        offset,
        1.0, 0.0,             // scale, angle
        RVector(0,0),         // center
        false,                // flipHorizontal
        false,                // flipVertical
        false,                // toCurrentLayer
        false,                // toCurrentBlock
        true,                 // overwriteLayers
        false,                // overwriteBlocks
        QString(),            // blockName
        QString(),            // layerName
        transaction,
        true,                 // selectionOnly
        clear,                // clear
        true,                 // toModelSpace (clipboard root is always model space)
        preview
    );

    transaction.end();
    return transaction;
}
