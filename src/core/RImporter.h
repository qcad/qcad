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

#ifndef RIMPORTER_H
#define RIMPORTER_H

#include "core_global.h"

#include "RTransaction.h"

class RDocument;
class REntity;
class RVector;
class RMessageHandler;
class RProgressHandler;

/**
 * \brief Base class for importers.
 *
 * Importers import entities from a source (e.g. file, DB, network, ...) 
 * into a graphics document. The implementing importer is expected to call 
 * the import functions to add objects (e.g. entities) to the document. 
 * Custom import functions may be implemented to support custom entity types 
 * supported by a specific importer.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RImporter {
public:
    RImporter();
    RImporter(RDocument& document, RMessageHandler* messageHandler = NULL, RProgressHandler* progressHandler = NULL);
    virtual ~RImporter();

    virtual void startImport();
    virtual void endImport();

    /**
     * \nonscriptable
     */
    virtual void importObjectP(QSharedPointer<RObject> object);

    virtual void importObject(RObject* object);

    virtual void setCurrentBlockId(RBlock::Id id);
    virtual RBlock::Id getCurrentBlockId();

    RDocument& getDocument();
    void setDocument(RDocument* d);

    void setKnownVariable(RS::KnownVariable key, const QVariant& value);
    void setKnownVariable(RS::KnownVariable key, const RVector& value);

protected:
    RDocument* document;
    RMessageHandler* messageHandler;
    RProgressHandler* progressHandler;
    RTransaction transaction;
    RBlock::Id blockId;
};

Q_DECLARE_METATYPE(RImporter*)

#endif
