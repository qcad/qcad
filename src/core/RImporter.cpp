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
#include "RImporter.h"

#include "RDocument.h"
#include "REntity.h"
#include "RObject.h"
#include "RStorage.h"
#include "RMainWindow.h"

RImporter::RImporter() :
    document(NULL),
    messageHandler(NULL),
    progressHandler(NULL),
    blockId(RBlock::INVALID_ID) {
}

RImporter::RImporter(RDocument& document, RMessageHandler* messageHandler, RProgressHandler* progressHandler) :
    document(&document),
    messageHandler(messageHandler),
    progressHandler(progressHandler),
    transaction(document.getStorage(), "Importing", false),
    blockId(RBlock::INVALID_ID) {

    transaction.setRecordAffectedObjects(false);
    transaction.setAllowAll(true);
    transaction.setSpatialIndexDisabled(true);
    transaction.setExistingLayerDetectionDisabled(true);
    transaction.setExistingLinetypeDetectionDisabled(true);
    transaction.setExistingBlockDetectionDisabled(true);
    transaction.setBlockRecursionDetectionDisabled(true);
    transaction.setKeepHandles(true);
}

RImporter::~RImporter() {
}

/**
 * Starts the import. Reimplementations should call this base
 * implementation first since this starts a transaction.
 */
void RImporter::startImport() {
}

/**
 * Imports an entity into the document.
 */
void RImporter::importObjectP(QSharedPointer<RObject> object) {
    transaction.addObject(object, false);
}

/**
 * Provided for script importers as importObjectP will loose the object ID.
 */
void RImporter::importObject(RObject* object) {
    //QSharedPointer<RObject> pObject = QSharedPointer<RObject>(object->clone());
    QSharedPointer<RObject> pObject = QSharedPointer<RObject>(object);
    transaction.addObject(pObject, false);
    *object = *pObject.data();
}

/**
 * Ends the import. Reimplementations should call this base
 * implementation first since this commits the transaction
 * after importing entities into the document.
 */
void RImporter::endImport() {
    transaction.end();

    // ground all directly recursive block references:
    int counter = 0;
    QList<QPair<QString, QString> >  blockNames;
    QSet<RBlock::Id> blockIds = document->queryAllBlocks();
    QSet<RBlock::Id>::const_iterator it;
    for (it=blockIds.constBegin(); it!=blockIds.constEnd(); it++) {
        RBlock::Id blockId = *it;

        QSet<REntity::Id> ids = document->queryBlockEntities(blockId);
        QSet<REntity::Id>::const_iterator it2;
        for (it2=ids.constBegin(); it2!=ids.constEnd(); it2++) {
            REntity::Id entityId = *it2;

            QSharedPointer<REntity> entity = document->queryEntityDirect(entityId);
            QSharedPointer<RBlockReferenceEntity> blockRef = entity.dynamicCast<RBlockReferenceEntity>();
            if (blockRef.isNull()) {
                // ignore non block reference entities:
                continue;
            }

            RBlock::Id refBlockId = blockRef->getReferencedBlockId();

            if (refBlockId==blockId) {
                blockNames.append(QPair<QString, QString>(document->getBlockName(refBlockId), document->getBlockName(refBlockId)));
                blockRef->setReferencedBlockId(RBlock::INVALID_ID);
                counter++;
            }
        }
    }

    if (RMainWindow::hasMainWindow() && counter>0) {
        //blockNames = blockNames.toSet().toList();
        RMainWindow::getMainWindow()->handleUserWarning(
            QString("Grounded %1 recursive block references:")
                    .arg(counter)
        );

        QList<QPair<QString, QString> >::iterator it;
        for (it=blockNames.begin(); it!=blockNames.end(); it++) {
            RMainWindow::getMainWindow()->handleUserWarning(
                QString("Grounded recursive block reference to block %1 in block %2")
                    .arg(it->first)
                    .arg(it->second)
            );
        }
    }

    //qDebug() << "rebuilding spatial index";
    document->rebuildSpatialIndex();
    //qDebug() << "rebuilding spatial index: OK";

    QSet<REntity::Id> entityIds = document->queryAllEntities(false, true);
    QSet<REntity::Id>::const_iterator it2;
    for (it2=entityIds.constBegin(); it2!=entityIds.constEnd(); it2++) {
        REntity::Id entityId = *it2;

        QSharedPointer<REntity> entity = document->queryEntityDirect(entityId);
        entity->setAutoUpdatesBlocked(false);
    }
}

void RImporter::setCurrentBlockId(RBlock::Id id) {
    this->blockId = id;
}

RBlock::Id RImporter::getCurrentBlockId() {
    return blockId;
}

RDocument& RImporter::getDocument() {
    return *document;
}

void RImporter::setDocument(RDocument* d) {
    document = d;
}

void RImporter::setKnownVariable(RS::KnownVariable key, const QVariant& value) {
    document->setKnownVariable(key, value, &transaction);
}

void RImporter::setKnownVariable(RS::KnownVariable key, const RVector& value) {
    document->setKnownVariable(key, value, &transaction);
}
