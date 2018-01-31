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

#ifndef RBLOCKLISTENERADAPTER_H_
#define RBLOCKLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RVector.h"
#include "RBlockListener.h"

/**
 * This block listener adapter emits signals on block events.
 * Used to simplify listening to block events from QObjects,
 * for instance from an ECMA script.
 *
 * \scriptable
 * \ingroup ecma
 */
class RBlockListenerAdapter: public QObject, public RBlockListener {
Q_OBJECT

public:
    RBlockListenerAdapter(QObject* parent=NULL) : QObject(parent) { }
    virtual ~RBlockListenerAdapter() { }

    virtual void updateBlocks(RDocumentInterface* documentInterface) {
        emit blocksUpdated(documentInterface);
    }

    virtual void setCurrentBlock(RDocumentInterface* documentInterface) {
        emit currentBlockSet(documentInterface);
    }

    virtual void clearBlocks() {
        emit blocksCleared();
    }

signals:
    void blocksUpdated(RDocumentInterface* documentInterface);
    void currentBlockSet(RDocumentInterface* documentInterface);
    void blocksCleared();
};

Q_DECLARE_METATYPE(RBlockListenerAdapter*)

#endif
