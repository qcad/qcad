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

#ifndef RTRANSACTIONLISTENERADAPTER_H_
#define RTRANSACTIONLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RTransactionListener.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RTransactionListenerAdapter: public QObject, public RTransactionListener {
Q_OBJECT

public:
    virtual ~RTransactionListenerAdapter() { }

    virtual void updateTransactionListener(RDocument* document,
        RTransaction* transaction=NULL) {

        emit transactionUpdated(document, transaction);
    }

signals:
    void transactionUpdated(RDocument* document, RTransaction* transaction);
};

Q_DECLARE_METATYPE(RTransactionListenerAdapter*)

#endif
