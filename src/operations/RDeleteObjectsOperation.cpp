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
#include "RDocument.h"
#include "RDeleteObjectsOperation.h"

RDeleteObjectsOperation::RDeleteObjectsOperation(bool undoable) :
    ROperation(undoable), list() {
}

RDeleteObjectsOperation::RDeleteObjectsOperation(
        QList<QSharedPointer<RObject> >& list, bool undoable) :
    ROperation(undoable), list(list) {
}

void RDeleteObjectsOperation::deleteObject(const QSharedPointer<RObject>& o) {
    list.append(o);
}

RTransaction RDeleteObjectsOperation::apply(RDocument& document, bool preview) const {
    RTransaction transaction(document.getStorage(), "Deleting object(s)",
            undoable);
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].isNull()) {
            qWarning() << "RDeleteObjectsOperation::apply: "
                    "list contains NULL object";
            continue;
        }
        transaction.deleteObject(list[i], &document);
    }
    transaction.end(&document);
    return transaction;
}

void RDeleteObjectsOperation::preview(RDocument& /*document*/,
        RExporter& /*exporter*/) const {
}
