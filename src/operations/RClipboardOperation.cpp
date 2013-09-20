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

#include "RBlockReferenceEntity.h"
#include "RClipboardOperation.h"
#include "RSettings.h"
#include "RStorage.h"
#include "RUnit.h"


RClipboardOperation::RClipboardOperation() {
}

void RClipboardOperation::copy(
        RDocument& src, RDocument& dest,
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
        RTransaction& transaction,
        bool selectionOnly, bool clear,
        bool toModelSpaceBlock,
        bool preview) const {

    double unitScale = RUnit::convert(1.0, src.getUnit(), dest.getUnit());

    if (clear) {
        dest.clear();
    }

    QSet<REntity::Id> entityIds;
    if (selectionOnly) {
        entityIds = src.querySelectedEntities();
    }
    else {
        entityIds = src.queryAllEntities();
    }

    // Non-const offset. reset to 0/0/0 if copying to block
    //    (offset implemented as block reference offset).
    RVector off = offset;

    bool hasBlock = false;

    // this part is used to insert ('paste') blocks from the part library
    // as new blocks:
    QSharedPointer<RBlockReferenceEntity> refp;
    if (!blockName.isNull()) {
        QSharedPointer<RBlock> block;
        hasBlock = dest.hasBlock(blockName);

        // block does not exist in dest - or -
        // block exists in dest and must be overwritten:
        if (!hasBlock || overwriteBlocks) {
            block = QSharedPointer<RBlock> (new RBlock(&dest, blockName,
                    RVector(0, 0, 0)));
            transaction.overwriteBlock(block);
        }

        // block exists and must not be overwritten:
        else {
            block = dest.queryBlock(blockName);
        }

        Q_ASSERT(!block.isNull());

        // create new block reference that references new, overwritten or existing block
        // (insert later, when block is complete, so we have bounding box for spatial index):
        RBlockReferenceEntity* ref = new RBlockReferenceEntity(&dest,
                RBlockReferenceData(block->getId(), RVector(0,0,0),
                                    RVector(1.0, 1.0, 1.0), 0.0));
        refp = QSharedPointer<RBlockReferenceEntity>(ref);
        refp->setBlockId(dest.getCurrentBlockId());
        off = RVector(0, 0, 0);
        if (flipHorizontal) {
            refp->flipHorizontal();
        }
        if (flipVertical) {
            refp->flipVertical();
        }
        //ref->scale(scale * unitScale);
        refp->scale(scale);
        refp->rotate(rotation);
        refp->move(offset);

        scale = 1.0;
        rotation = 0.0;
        flipHorizontal = false;
        flipVertical = false;
        toCurrentLayer = false;
        //toCurrentBlock = false;
    }

    // copy entities from src to dest:
    //     if the block existed already in dest and is not overwritten,
    //     there's nothing to do here:
    if (!hasBlock || overwriteBlocks || preview) {
        copiedLayers.clear();
        copiedBlocks.clear();

        int counter = 0;
        QSet<REntity::Id>::iterator it;
        for (it=entityIds.begin(); it!=entityIds.end(); ++it) {
            if (preview && ++counter>RSettings::getPreviewEntities()) {
                break;
            }

            QSharedPointer<REntity> entity = src.queryEntityDirect(*it);
            if (entity.isNull() || entity->isUndone()) {
                continue;
            }

            copyEntity(
                        *entity.data(),
                        src, dest,
                        off, scale, unitScale, rotation,
                        flipHorizontal, flipVertical,
                        toCurrentLayer, toCurrentBlock,
                        overwriteLayers, overwriteBlocks,
                        blockName,
                        transaction,
                        toModelSpaceBlock       // to model space: true for copy
                        // (allow copy from inside any block definition),
                        // false for paste
                        );
        }
    }

    // only overwrite layers:
    else if (overwriteLayers) {
        copiedLayers.clear();

        int counter = 0;
        QSet<REntity::Id>::iterator it;
        for (it=entityIds.begin(); it!=entityIds.end(); ++it) {
            if (preview && ++counter>RSettings::getPreviewEntities()) {
                break;
            }

            QSharedPointer<REntity> entity = src.queryEntityDirect(*it);
            if (entity.isNull() || entity->isUndone()) {
                continue;
            }

            copyEntityLayer(
                        *entity.data(),
                        src, dest,
                        overwriteLayers,
                        transaction
                        );
        }
    }

    // copying of entire block complete, insert block reference now since
    // we now have the boudning box for the spatial index:
    if (!refp.isNull()) {
        transaction.addObject(refp, /* useCurrentAttributes =*/ true);
    }

    // if block was overwritten, we need to update the spatial index
    // entries for all block references of that block:
    //if (overwriteBlocks) {

    //}

    //qDebug() << "After copying block and block ref and entities: \n" << dest;

    transaction.endCycle();
}



/**
 * Adds the given entity (and its layer(s) and block reference(s)) to the
 * given document.
 *
 * \param blockName Name of an existing block in dest
 */
void RClipboardOperation::copyEntity(
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
        bool toModelSpaceBlock) const {

    QSharedPointer<RLayer> destLayer = copyEntityLayer(entity, src, dest, overwriteLayers, transaction);

    // add block the entity belongs to, if the block exists it is overwritten
    // if 'overwriteBlocks' is true:
    QSharedPointer<RBlock> srcBlock =
        src.queryBlock(entity.getBlockId());
    if (srcBlock.isNull()) {
        qWarning("RClipboardOperation::copyToDocument: "
            "block of entity is NULL.");
        return;
    }
    QString srcBlockName = srcBlock->getName();
    QSharedPointer<RBlock> destBlock;
    if (copiedBlocks.contains(srcBlockName)) {
        destBlock = copiedBlocks.value(srcBlockName);
    }
    else {
        QString destBlockName;
        if (!blockName.isNull()) {
            destBlockName = blockName;
        }
        else {
            if (toCurrentBlock) {
                destBlockName = dest.getBlockName(dest.getCurrentBlockId());
            }
            else {
                destBlockName = srcBlock->getName();
            }
        }
        if (!dest.hasBlock(destBlockName) || (overwriteBlocks && blockName.isNull())) {
            destBlock = QSharedPointer<RBlock> (srcBlock->clone());
            dest.getStorage().setObjectId(*destBlock.data(), RObject::INVALID_ID);
            dest.getStorage().setObjectHandle(*destBlock.data(), RObject::INVALID_HANDLE);
            destBlock->setDocument(&dest);
            if (dest.hasBlock(destBlockName)) {
                if (!transaction.overwriteBlock(destBlock)) {
                    destBlock = dest.queryBlock(destBlockName);
                }
            }
            else {
                transaction.addObject(destBlock);
            }
        } else {
            destBlock = dest.queryBlock(destBlockName);
        }

        copiedBlocks.insert(srcBlockName, destBlock);
    }

    Q_ASSERT(destBlock->getId()!=RBlock::INVALID_ID);

    // entity is a block reference:
    // add entities of the block the block reference refers to (the block
    // definition is then added automatically):
    RBlockReferenceEntity* blockRef =
        dynamic_cast<RBlockReferenceEntity*>(&entity);
    if (blockRef!=NULL) {
        QSharedPointer<RBlock> refBlock =
            src.queryBlock(blockRef->getReferencedBlockId());
        if (refBlock.isNull()) {
            qWarning("RClipboardOperation::copyToDocument: "
                "entity references a NULL block.");
            return;
        }

        // TODO: don't do this twice:
        //qDebug() << "RClipboardOperation::copyToDocument: copying block: " << refBlock->getName();
        // if block exists in dest, it has already been copied or was
        // already there and needs to be overwritten:
        QSharedPointer<RBlock> refBlockDest = dest.queryBlock(refBlock->getName());
        if (refBlockDest.isNull() || overwriteBlocks) {
            QSet<REntity::Id> ids = src.queryBlockEntities(refBlock->getId());
            bool first = true;
            QSet<REntity::Id>::iterator it;
            for (it=ids.begin(); it!=ids.end(); ++it) {
                QSharedPointer<REntity> e = src.queryEntityDirect(*it);
                if (e.isNull()) {
                    continue;
                }
                copyEntity(
                    *e.data(),
                    src, dest,
                    RVector::nullVector,
                    1.0,          // scale from user options not applied to block contents 
                                  // but to block reference
                    unitScale, 
                    0.0,
                    false, false, // no flips
                    false, false, // keep original block and layer
                    overwriteLayers, first && overwriteBlocks,
                    QString(),
                    transaction,
                    false         // not to model space but actual block
                );
                first = false;
            }
        }
    }

    // add entity self:
    QSharedPointer<REntity> destEntity = QSharedPointer<REntity>(entity.clone());
    //dest.getStorage().setObjectId(*destEntity.data(), RObject::INVALID_ID);
    dest.getStorage().setObjectHandle(*destEntity.data(), RObject::INVALID_HANDLE);
    destEntity->setSelected(false);

    // apply transformations:
    if (flipHorizontal) {
        destEntity->flipHorizontal();
    }
    if (flipVertical) {
        destEntity->flipVertical();
    }
    if (blockRef!=NULL) {
        destEntity->scale(scale);
    }
    else {
        destEntity->scale(scale * unitScale);
    }
    destEntity->rotate(rotation);
    // correct block reference offset. necessary for unit conversion:
    if (blockRef!=NULL && src.getUnit()!=dest.getUnit()) {
        destEntity->move(-blockRef->getPosition());
        destEntity->move(blockRef->getPosition() * unitScale);
    }
    destEntity->move(offset);

    destEntity->setDocument(&dest);
    if (toCurrentLayer) {
        // paste to current layer:
        destEntity->setLayerId(dest.getCurrentLayerId());
    }
    else {
        // paste to original layer:
        Q_ASSERT(!destLayer.isNull());
        destEntity->setLayerId(destLayer->getId());
    }

    if (toModelSpaceBlock) {
        destEntity->setBlockId(dest.getModelSpaceBlockId());
    }
    else {
        destEntity->setBlockId(destBlock->getId());
    }

    // correct referenced block id of pasted block reference:
    QSharedPointer<RBlockReferenceEntity> destBlockRef =
        destEntity.dynamicCast<RBlockReferenceEntity>();
    if (!destBlockRef.isNull() && blockRef!=NULL) {
        QString bn = src.getBlockName(blockRef->getReferencedBlockId());
        RBlock::Id blockId = dest.getBlockId(bn);
        destBlockRef->setReferencedBlockId(blockId);
//        qDebug() << "not yet updated block ref: " << *destBlockRef;
//        destBlockRef->update();
//        qDebug() << "updated block ref: " << *destBlockRef;
    }

    transaction.addObject(destEntity, false, true);
}

QSharedPointer<RLayer> RClipboardOperation::copyEntityLayer(
    REntity& entity,
    RDocument& src, RDocument& dest,
    bool overwriteLayers,
    RTransaction& transaction) const {

    // add layer the entity is on, if the layer exists it is overwritten
    // if overwriteLayers is true:
    QSharedPointer<RLayer> srcLayer =
        src.queryLayer(entity.getLayerId());
    if (srcLayer.isNull()) {
        qWarning("RClipboardOperation::copyToDocument: "
            "layer of entity is NULL.");
        return QSharedPointer<RLayer>();
    }
    QString srcLayerName = srcLayer->getName();
    QSharedPointer<RLayer> destLayer;
    if (copiedLayers.contains(srcLayerName)) {
        destLayer = copiedLayers.value(srcLayerName);
        Q_ASSERT(!destLayer.isNull());
    }
    else {
        if (!dest.hasLayer(srcLayerName) || overwriteLayers) {
            destLayer = QSharedPointer<RLayer>(srcLayer->clone());
            destLayer->setDocument(&dest);
            if (destLayer->getDocument()!=srcLayer->getDocument()) {
                dest.getStorage().setObjectId(*destLayer.data(), RObject::INVALID_ID);
                dest.getStorage().setObjectHandle(*destLayer.data(), RObject::INVALID_HANDLE);
            }
            transaction.addObject(destLayer);
        }
        else {
            destLayer = dest.queryLayer(srcLayerName);
            Q_ASSERT(!destLayer.isNull());
        }

        copiedLayers.insert(srcLayerName, destLayer);
    }

    return destLayer;
}
