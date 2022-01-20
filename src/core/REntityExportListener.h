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

#ifndef RENTITYEXPORTLISTENER_H
#define RENTITYEXPORTLISTENER_H

#include "core_global.h"

#include <QSet>
#include <QString>
#include <QPair>

#include "REntity.h"

class RExporter;

/**
 * \brief Abstract base class for classes that wish to be notified when an entity is
 * exported.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT REntityExportListener {
public:
    virtual ~REntityExportListener() {}

    /**
     * Registers the given custom property as trigger. The exportEntity function is only
     * called for entities with a custom property that matches the given title and regular expression.
     */
    virtual void registerCustomProperty(const QString& title, const QString& regExp) {
        registeredProperties.insert(QPair<QString, QString>(title, regExp));
    }

    virtual bool checkCustomProperty(REntity* e) const {
        QSet<QPair<QString, QString> >::const_iterator it;
        for (it=registeredProperties.constBegin(); it!=registeredProperties.constEnd(); it++) {
            if (e->hasCustomProperty((*it).first, QRegExp((*it).second))) {
                return true;
            }
        }

        return false;
    }

    /**
     * Called by the document whenever an entity is exporter with 
     * one of the registered custom properties. Can be used to for example
     * to 'decorate' the entity.
     *
     * \param exporter The exporter to use to export decorations to.
     * \param entity The entity currently being drawn.
     */
    virtual void exportEntity(RExporter* exporter, REntity* entity) = 0;

private:
    QSet<QPair<QString, QString> > registeredProperties;
};

Q_DECLARE_METATYPE(REntityExportListener*)

#endif
