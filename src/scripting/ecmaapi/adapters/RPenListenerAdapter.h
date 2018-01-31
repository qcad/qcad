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

#ifndef RPENLISTENERADAPTER_H_
#define RPENLISTENERADAPTER_H_

#include <QObject>

#include "RDocumentInterface.h"
#include "RPenListener.h"

/**
 * \scriptable
 * \ingroup ecma
 */
class RPenListenerAdapter: public QObject, public RPenListener {
Q_OBJECT

public:
    RPenListenerAdapter(QObject* parent=NULL) : QObject(parent) { }
    virtual ~RPenListenerAdapter() { }

    virtual void updatePen(RDocumentInterface* documentInterface) {
        emit penUpdated(documentInterface);
    }

    virtual void clearPen() {
        emit penCleared();
    }

signals:
    void penUpdated(RDocumentInterface* documentInterface);
    void penCleared();
};

Q_DECLARE_METATYPE(RPenListenerAdapter*)

#endif
