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

#include "RBlockReferenceEntity.h"
#include "RDocument.h"
#include "RExporter.h"
#include "RPasteOperation.h"
#include "RPolyline.h"

RPasteOperation::RPasteOperation(RDocument& sourceDocument)
    : sourceDocument(sourceDocument),
    scale(1.0),
    flipHorizontal(false),
    flipVertical(false),
    toCurrentLayer(false),
    overwriteLayers(false),
    overwriteBlocks(false) {
}

RTransaction RPasteOperation::apply(RDocument& document, bool preview) {
    RTransaction transaction(document.getStorage(), text, undoable);
    transaction.setGroup(transactionGroup);
    transaction.setTypes(transactionTypes);

    // 20151118: allow also entities on locked / invisible layers to be pasted:
    transaction.setAllowAll(true);

    if (offsets.isEmpty()) {
        offsets.append(RVector(0,0));
    }

    int iMax = offsets.length();
    if (preview && iMax>10) {
        iMax = 10;
    }

    double rotation = 0.0;
    if (rotations.length()==1) {
        // same rotation for all pasted instances:
        rotation = rotations[0];
    }

    RVector center;
    if (centers.length()==1) {
        // same center for all pasted instances:
        center = centers[0];
    }

    for (int i=0; i<iMax; i++) {
        copy(
            sourceDocument, document,
            offsets[i], scale,
            i < rotations.length() ? rotations[i] : rotation,
            i < centers.length() ? centers[i] : center,
            flipHorizontal, flipVertical,
            toCurrentLayer, /*toCurrentBlock=*/ true,
            overwriteLayers && i==0, overwriteBlocks && i==0,
            blockName,
            layerName,
            transaction,
            false, false,
            false,           // toModelSpace (paste to current block, not model space)
            preview,
            attributes,
            properties,
            blockProperties
        );
    }

    transaction.end();

    return transaction;
}

RPolyline RPasteOperation::getBoundary(double unitFactor) {
    RBox box = sourceDocument.getBoundingBox();
    RPolyline polyline = box.getPolyline2d();
    if (flipHorizontal) {
        polyline.flipHorizontal();
    }
    if (flipVertical) {
        polyline.flipVertical();
    }
    polyline.scale(scale * unitFactor);
    polyline.rotate(getRotation());
    polyline.move(getOffset());
    return polyline;
}
