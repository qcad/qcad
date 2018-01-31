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

#ifndef RTRANSACTIONSTACK_H
#define RTRANSACTIONSTACK_H

#include "core_global.h"

#include <QMetaType>

#include "RNonCopyable.h"
#include "RTransaction.h"

/**
 * A transaction stack handles transactions on a document. Transactions
 * are stored in a \ref RStorage "storage" implementation. 
 * Transactions can be undone and redone.
 *
 * \ingroup core
 */
class QCADCORE_EXPORT RTransactionStack : RNonCopyable {
public:
    RTransactionStack(RStorage& storage);
    ~RTransactionStack();

    void reset();

    QList<RTransaction> undo();
    QList<RTransaction> redo();
    bool isUndoAvailable() const;
    bool isRedoAvailable() const;
    QString getUndoableTransactionText() const;
    QString getRedoableTransactionText() const;

private:
    RStorage& storage;
};

Q_DECLARE_METATYPE(RTransactionStack*)

#endif
