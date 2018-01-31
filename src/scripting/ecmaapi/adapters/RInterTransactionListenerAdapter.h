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

#ifndef RINTERTRANSACTIONLISTENERADAPTER_H_
#define RINTERTRANSACTIONLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RInterTransactionListener.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RInterTransactionListenerAdapter: public QObject, public RInterTransactionListener {
Q_OBJECT

public:
    virtual ~RInterTransactionListenerAdapter() { }

    virtual void updateInterTransactionListener(RDocument* doc=NULL, RTransaction* transaction=NULL) {
        emit transactionInProgress(doc, transaction);
    }

signals:
    void transactionInProgress(RDocument* doc, RTransaction* transaction);
};

Q_DECLARE_METATYPE(RInterTransactionListenerAdapter*)

#endif
