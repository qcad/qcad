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
#include "RMixedOperation.h"

RMixedOperation::RMixedOperation(bool undoable) :
    ROperation(undoable), list() {

    RDebug::incCounter("RMixedOperation");
}

void RMixedOperation::setMode(Modes& modes, RMixedOperation::Mode mode, bool on) {
    if (on) {
        modes |= mode;
    } else {
        modes &= ~mode;
    }
}

bool RMixedOperation::getMode(const Modes& modes, RMixedOperation::Mode mode) const {
    return (modes & mode) == mode;
}

QSharedPointer<RObject> RMixedOperation::addObject(const QSharedPointer<RObject>& obj,
    bool useCurrentAttributes, bool forceNew) {

    if (obj.isNull()) {
        return obj;
    }

    Modes modes = RMixedOperation::NoMode;
    if (useCurrentAttributes) {
        setMode(modes, RMixedOperation::UseCurrentAttributes);
    }
    if (forceNew) {
        setMode(modes, RMixedOperation::ForceNew);
    }

    list.append(QPair<QSharedPointer<RObject>, Modes>(obj, modes));

    return obj;
}

void RMixedOperation::deleteObject(const QSharedPointer<RObject>& obj) {
    if (obj.isNull()) {
        return;
    }

    Modes modes = RMixedOperation::NoMode;
    setMode(modes, RMixedOperation::Delete);
    list.append(QPair<QSharedPointer<RObject>, Modes>(obj, modes));
}

void RMixedOperation::endCycle() {
    Modes modes = RMixedOperation::NoMode;
    setMode(modes, RMixedOperation::EndCycle);
    list.append(QPair<QSharedPointer<RObject>, Modes>(QSharedPointer<RObject>(), modes));
}

RTransaction RMixedOperation::apply(RDocument& document, bool preview) {
    Q_UNUSED(preview)

    RTransaction transaction(document.getStorage(), text, undoable);
    transaction.setGroup(transactionGroup);
    transaction.setTypes(transactionTypes);

    for (int i = 0; i < list.size(); ++i) {
        if (list[i].first.isNull()) {
            qWarning() << "RMixedOperation::apply: "
                    "list contains NULL object";
            continue;
        }

        if (getMode(list[i].second, RMixedOperation::EndCycle)) {
            transaction.endCycle();
        }
        else if (getMode(list[i].second, RMixedOperation::Delete)) {
            transaction.deleteObject(list[i].first);
        }
        else {
            transaction.addObject(list[i].first,
                getMode(list[i].second, RMixedOperation::UseCurrentAttributes),
                getMode(list[i].second, RMixedOperation::ForceNew));
        }
    }

    transaction.end();
    return transaction;
}
