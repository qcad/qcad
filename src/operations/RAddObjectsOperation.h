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

#ifndef RADDOBJECTSOPERATION_H
#define RADDOBJECTSOPERATION_H

#include "operations_global.h"

#include <QList>
#include <QSharedPointer>

#include "RDocument.h"
#include "RExporter.h"
#include "ROperation.h"
#include "RTransaction.h"
#include "RVector.h"

class RObject;

/**
 * Implementation of an operation that adds entities.
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RAddObjectsOperation: public ROperation {
public:
    enum Flag {
        NoFlags       = 0x000,
        UseAttributes = 0x001,     /**< Use assigned attributes instead of current attributes (color, linetype, width) */
        ForceNew      = 0x002,     /**< Force adding existing entity as new, duplicate entity */
        GeometryOnly  = 0x004,     /**< Only geometric properties have changed (e.g. transformation) */
        Delete        = 0x008      /**< Delete object */
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    class RModifiedObjects {
    public:
        // constructor to mark cycles:
        RModifiedObjects()
            : object(QSharedPointer<RObject>()),
              flags(RAddObjectsOperation::NoFlags) {}

        // constructor to delete object:
        RModifiedObjects(QSharedPointer<RObject> object)
            : object(object),
              flags(RAddObjectsOperation::Delete) {}

        // constructor to add object:
        RModifiedObjects(QSharedPointer<RObject> object, bool useCurrentAttributes, bool forceNew)
            : object(object) {

            setUseAttributes(!useCurrentAttributes);
            setForceNew(forceNew);
        }

        // constructor to add object:
        RModifiedObjects(QSharedPointer<RObject> object, RAddObjectsOperation::Flags flags)
            : object(object), flags(flags) {}

        void setUseAttributes(bool on) {
            setFlag(RAddObjectsOperation::UseAttributes, on);
        }

        bool getUseAttributes() const {
            return getFlag(RAddObjectsOperation::UseAttributes);
        }

        void setForceNew(bool on) {
            setFlag(RAddObjectsOperation::ForceNew, on);
        }

        bool getForceNew() const {
            return getFlag(RAddObjectsOperation::ForceNew);
        }

        void setGeometryOnly(bool on) {
            setFlag(RAddObjectsOperation::GeometryOnly, on);
        }

        bool getGeometryOnly() const {
            return getFlag(RAddObjectsOperation::GeometryOnly);
        }

        void setDelete(bool on) {
            setFlag(RAddObjectsOperation::Delete, on);
        }

        bool getDelete() const {
            return getFlag(RAddObjectsOperation::Delete);
        }

        void setFlag(RAddObjectsOperation::Flag flag, bool on) {
            if (on) {
                flags |= flag;
            } else {
                flags &= ~flag;
            }
        }

        bool getFlag(RAddObjectsOperation::Flag flag) const {
            return (flags & flag) == flag;
        }

        QSharedPointer<RObject> object;
        RAddObjectsOperation::Flags flags;
    };


public:
    RAddObjectsOperation(bool undoable = true);
    RAddObjectsOperation(QList<QSharedPointer<RObject> >& list,
        bool useCurrentAttributes = true, bool undoable = true);
    virtual ~RAddObjectsOperation();

    /**
     * Adds the given object to this operation or replaces an object
     * already present with the same ID.
     */
    void replaceObject(const QSharedPointer<RObject>& object,
        bool useCurrentAttributes = true);

    QSharedPointer<RObject> getObject(RObject::Id id);

    void endCycle();

    void addObject(const QSharedPointer<RObject>& object,
        bool useCurrentAttributes=true, bool forceNew=false);

    void addObject(const QSharedPointer<RObject>& object,
        RAddObjectsOperation::Flags flags);

    void deleteObject(const QSharedPointer<RObject>& object);

    virtual RTransaction apply(RDocument& document, bool preview = false);

    int getPreviewCounter() const {
        return previewCounter;
    }

    void setLimitPreview(bool on) {
        limitPreview = on;
    }

    bool isEmpty() {
        return addedObjects.isEmpty();
    }

private:
    QList<RModifiedObjects> addedObjects;
    //QList<QPair<QSharedPointer<RObject>, bool> > addedObjects;
    int previewCounter;
    bool limitPreview;
};


Q_DECLARE_METATYPE(RAddObjectsOperation*)
Q_DECLARE_METATYPE(RAddObjectsOperation::Flag)
Q_DECLARE_METATYPE(RAddObjectsOperation::Flag*)
Q_DECLARE_METATYPE(QFlags<RAddObjectsOperation::Flag>)
Q_DECLARE_METATYPE(QFlags<RAddObjectsOperation::Flag>*)

#endif
