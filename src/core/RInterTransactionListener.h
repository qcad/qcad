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

#ifndef RINTERTRANSACTIONLISTENER_H
#define RINTERTRANSACTIONLISTENER_H

#include "core_global.h"

class RDocument;
class REntity;
class RTransaction;



/**
 * \brief Abstract base class for classes that are interested in transactions
 * in progress.
 * This can for example be used to add objects to a transaction in progress,
 * remove objects from a transaction (to prevent modifications of those objects),
 * etc.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RInterTransactionListener {
public:
    virtual ~RInterTransactionListener() {}

    /**
     * Called at the end of every transaction, before the transaction is stored.
     */
    virtual void updateInterTransactionListener(RDocument* document, RTransaction* transaction=NULL) = 0;
};

Q_DECLARE_METATYPE(RInterTransactionListener*)

#endif
