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

#ifndef RNEWDOCUMENTLISTENERADAPTER_H_
#define RNEWDOCUMENTLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RNewDocumentListener.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RNewDocumentListenerAdapter: public QObject, public RNewDocumentListener {
Q_OBJECT

public:
    virtual ~RNewDocumentListenerAdapter() { }

    virtual void updateNewDocumentListener(RDocument* document, RTransaction* transaction, bool beforeLoad) {
        emit newDocument(document, transaction, beforeLoad);
    }

signals:
    void newDocument(RDocument* document, RTransaction* transaction, bool beforeLoad);
};

Q_DECLARE_METATYPE(RNewDocumentListenerAdapter*)

#endif
