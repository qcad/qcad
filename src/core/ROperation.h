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

#ifndef ROPERATION_H
#define ROPERATION_H

#include "core_global.h"

#include "RNonCopyable.h"
#include "RRequireHeap.h"
#include "RS.h"
#include "RTransaction.h"

class RDocument;
class RExporter;



/**
 * This abstract class is an interface for all operation implementations.
 * An operation encapsulates a modification that can be applied to a 
 * document. An implementing class might for example implement a move
 * operation that moves all selected entities by a given vector.
 * 
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT ROperation : public RRequireHeap, RNonCopyable {
public:
    ROperation(
        bool undoable=true,
        RS::EntityType entityTypeFilter = RS::EntityAll
    ) : transactionTypes(RTransaction::Generic),
        undoable(undoable),
        recordAffectedObjects(true),
        spatialIndexDisabled(false),
        allowInvisible(false),
        allowAll(false),
        entityTypeFilter(entityTypeFilter),
        transactionGroup(-1) {
        RDebug::incCounter("ROperation");
    }

    virtual ~ROperation() {
        RDebug::decCounter("ROperation");
    }
    
    /**
     * Applies this operation to selection in the given document.
     * This is used for both previews and the actual apply. In case
     * of a preview, the given document is a temporary document with
     * a storage that is linked to the real document for realistic
     * condiditions for the preview.
     */
    virtual RTransaction apply(RDocument& document, bool preview = false) = 0;

    RS::EntityType getEntityTypeFilter() const {
        return entityTypeFilter;
    }

    void setRecordAffectedObjects(bool on) {
        recordAffectedObjects = on;
    }

    void setSpatialIndexDisabled(bool on) {
        spatialIndexDisabled = on;
    }

    void setAllowInvisible(bool on) {
        allowInvisible = on;
    }

    void setAllowAll(bool on) {
        allowAll = on;
    }

    void setTransactionGroup(int g) {
        transactionGroup = g;
    }

    int getTransactionGroup() const {
        return transactionGroup;
    }

    void setText(const QString& t) {
        text = t;
    }

    QString getText() const {
        return text;
    }

    RTransaction::Types getTransactionTypes() const {
        return transactionTypes;
    }

    void setTransactionType(RTransaction::Type t, bool on = true) {
        if (on) {
            transactionTypes |= t;
        } else {
            transactionTypes &= ~t;
        }
    }

    bool getTransactionType(RTransaction::Type t) const {
        return (transactionTypes & t) == t;
    }

protected:
    RTransaction::Types transactionTypes;
    bool undoable;
    bool recordAffectedObjects;
    bool spatialIndexDisabled;
    bool allowInvisible;
    bool allowAll;
    RS::EntityType entityTypeFilter;
    int transactionGroup;
    QString text;
};

Q_DECLARE_METATYPE(ROperation*)

#endif
