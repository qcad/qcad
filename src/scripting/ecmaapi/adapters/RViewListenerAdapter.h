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

#ifndef RVIEWLISTENERADAPTER_H_
#define RVIEWLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RVector.h"
#include "RViewListener.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RViewListenerAdapter: public QObject, public RViewListener {
Q_OBJECT

public:
    RViewListenerAdapter(QObject* parent=NULL) : QObject(parent) { }
    virtual ~RViewListenerAdapter() { }

    virtual void updateViews(RDocumentInterface* documentInterface) {
        emit viewsUpdated(documentInterface);
    }

    virtual void clearViews() {
        emit viewsCleared();
    }

signals:
    void viewsUpdated(RDocumentInterface* documentInterface);
    void viewsCleared();
};

Q_DECLARE_METATYPE(RViewListenerAdapter*)

#endif
