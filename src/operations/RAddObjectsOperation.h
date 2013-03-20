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

#ifndef RADDOBJECTSOPERATION_H
#define RADDOBJECTSOPERATION_H

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
class RAddObjectsOperation: public ROperation {
public:
    RAddObjectsOperation(bool undoable = true);
    RAddObjectsOperation(QList<QSharedPointer<RObject> >& list,
        bool useCurrentAttributes = true, bool undoable = true);
    virtual ~RAddObjectsOperation() {
    }

    void addObject(const QSharedPointer<RObject>& object,
        bool useCurrentAttributes = true);

    virtual RTransaction apply(RDocument& document, bool preview = false) const;

    int getPreviewCounter() const {
        return previewCounter;
    }

    void setLimitPreview(bool on) {
        limitPreview = on;
    }

private:
    QList<QPair<QSharedPointer<RObject>, bool> > list;
    int previewCounter;
    bool limitPreview;
};

Q_DECLARE_METATYPE(RAddObjectsOperation*)

#endif
