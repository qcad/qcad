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
#include "RImporter.h"

#include "RDocument.h"
#include "REntity.h"
#include "RObject.h"
#include "RStorage.h"

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
    transaction.setExistingBlockDetectionDisabled(true);
    transaction.setBlockRecursionDetectionDisabled(true);
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
    //qDebug() << "importObjectP: " << *object;
    //RDebug::startTimer();
    transaction.addObject(object, false);
//    if (RDebug::stopTimer("importObjectP")>10) {
//        qDebug() << "importObjectP (slow): " << *object;
//    }
}

/**
 * Provided for script importers as importObjectP will loose the object ID.
 */
void RImporter::importObject(RObject* object) {
    QSharedPointer<RObject> shp = QSharedPointer<RObject>(object->clone());
    transaction.addObject(shp, false);
    *object = *shp.data();
}

/**
 * Ends the import. Reimplementations should call this base
 * implementation first since this commits the transaction
 * after importing entities into the document.
 */
void RImporter::endImport() {
    transaction.end();
    document->rebuildSpatialIndex();

    // TODO: check block recursion
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
