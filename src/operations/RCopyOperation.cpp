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
#include <QSet>

#include "RDocument.h"
#include "RCopyOperation.h"
#include "RExporter.h"


RCopyOperation::RCopyOperation(const RVector& offset, RDocument& src)
    : offset(offset), src(src) {
}



RTransaction RCopyOperation::apply(RDocument& document, bool preview) const {
    RTransaction transaction(document.getStorage(), "Copy");

    copy(
        src, document,
        offset,
        1.0, 0.0,             // scale, angle
        false,                // flipHorizontal
        false,                // flipVertical
        false,                // toCurrentLayer
        false,                // toCurrentBlock
        true,                 // overwriteLayers
        false,                // overwriteBlocks
        QString(),            // blockName
        transaction,
        true,                 // selectionOnly
        true,                 // clear
        true,                 // toModelSpace (clipboard root is always model space)
        preview
    );

    transaction.end();
    return transaction;
}



void RCopyOperation::preview(RDocument& /*document*/, RExporter& /*exporter*/) const {
}

