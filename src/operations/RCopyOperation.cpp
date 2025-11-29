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
#include "RDocument.h"
#include "RCopyOperation.h"


RCopyOperation::RCopyOperation(const RVector& offset, RDocument& src)
    : offset(offset),
      src(src),
      scale(1.0),
      angle(0.0),
      center(0,0),
      flipHorizontal(false),
      flipVertical(false),
      toCurrentLayer(false),
      toCurrentBlock(false),
      overwriteLayers(true),
      overwriteBlocks(false),
      blockName(QString()),
      layerName(QString()),
      selectionOnly(true),
      clear(true),
      toModelSpaceBlock(true) {

}



RTransaction RCopyOperation::apply(RDocument& document, bool preview) {
    RTransaction transaction(document.getStorage(), text);
    transaction.setGroup(transactionGroup);
    transaction.setTypes(transactionTypes);

    copy(
        src, document,
        offset,
        scale,
        angle,
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
        selectionOnly,
        clear,
        toModelSpaceBlock,
        preview
    );



    transaction.end();
    return transaction;
}
