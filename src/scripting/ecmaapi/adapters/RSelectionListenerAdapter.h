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

#ifndef RSELECTIONLISTENERADAPTER_H_
#define RSELECTIONLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RSelectionListener.h"
#include "RMainWindow.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RSelectionListenerAdapter: public QObject, public RSelectionListener {
Q_OBJECT

public:
    RSelectionListenerAdapter(QObject* parent=NULL) : QObject(parent) { }
    virtual ~RSelectionListenerAdapter() { }

    virtual void updateSelectionListener(RDocumentInterface* documentInterface) {
        emit selectionChanged(documentInterface);
    }

signals:
    void selectionChanged(RDocumentInterface* documentInterface);
};

Q_DECLARE_METATYPE(RSelectionListenerAdapter*)

#endif
