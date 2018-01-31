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

#ifndef RIMPORTLISTENERADAPTER_H_
#define RIMPORTLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RImportListener.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RImportListenerAdapter: public QObject, public RImportListener {
Q_OBJECT

public:
    virtual ~RImportListenerAdapter() { }

    virtual void preImportEvent(RDocumentInterface* documentInterface) {
        emit preImport(documentInterface);
    }

    virtual void postImportEvent(RDocumentInterface* documentInterface) {
        emit postImport(documentInterface);
    }

signals:
    void preImport(RDocumentInterface* documentInterface);
    void postImport(RDocumentInterface* documentInterface);
};

Q_DECLARE_METATYPE(RImportListenerAdapter*)

#endif
