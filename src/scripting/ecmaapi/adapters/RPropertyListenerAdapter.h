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

#ifndef RPROPERTYLISTENERADAPTER_H
#define RPROPERTYLISTENERADAPTER_H

#include <QMetaType>
#include <QObject>

#include "RPropertyListener.h"

class RDocumentInterface;
class RDocument;
class RDocumentInterface;
class RObject;
class RPropertyListener;
class RPropertyListenerAdapter;


/**
 * \ingroup ecma
 * \scriptable
 */
class RPropertyListenerAdapter : public QObject, public RPropertyListener {
Q_OBJECT

public:
    virtual ~RPropertyListenerAdapter() {}

    virtual void updateFromDocument(RDocument* document, bool onlyChanges,
              RS::EntityType entityTypeFilter = RS::EntityAll, bool manual = false, bool showOnRequest = false) {

        emit updatedFromDocument(document, onlyChanges, entityTypeFilter, manual, showOnRequest);
    }

    virtual void updateFromObject(RObject* object, RDocument* document = NULL) {
        emit updatedFromObject(object, document);
    }

    virtual void clearEditor() {
        emit clearedEditor();
    }

signals:
    void updatedFromDocument(RDocument* document, bool onlyChanges, RS::EntityType entityTypeFilter, bool manual, bool showOnRequest);
    void updatedFromObject(RObject* object, RDocument* document);
    void clearedEditor();
};

Q_DECLARE_METATYPE(RPropertyListenerAdapter*)

#endif
