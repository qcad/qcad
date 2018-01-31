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
#include <QDir>

#include "RScriptHandlerRegistry.h"
#include "RDebug.h"
#include "RScriptHandler.h"


QMap<QString, RScriptHandler*> RScriptHandlerRegistry::globalScriptHandlers;
QMap<QString, RScriptHandlerRegistry::FactoryFunction> RScriptHandlerRegistry::factoryFunctions;


RScriptHandlerRegistry::~RScriptHandlerRegistry() {
    QMapIterator<QString, RScriptHandler*> i(globalScriptHandlers);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }
}

/**
 * Registers a script handler.
 *
 * \param factoryFunction The function that can be used to instantiate
 *      the script handler.
 */
void RScriptHandlerRegistry::registerScriptHandler(FactoryFunction factoryFunction,
        const QList<QString>& fileExtensions) {

    QList<QString>::const_iterator it;
    for (it = fileExtensions.begin(); it != fileExtensions.end(); ++it) {
        if (factoryFunctions.count(*it) != 0) {
            qWarning("RScriptHandlerRegistry::registerScriptHandler: "
                "duplicate registration of file extension: '%s'",
                    (const char*) it->toUtf8());
            continue;
        }
        factoryFunctions[*it] = factoryFunction;
    }
}

/**
 * \return A new instance of the first script handler found that
 *      can handle the given file or NULL if no suitable handler
 *      can be found.
 */
RScriptHandler* RScriptHandlerRegistry::createScriptHandler(const QString& extension) {

    if (factoryFunctions.count(extension) != 0) {
        return factoryFunctions[extension]();
    }

    qCritical() << "no script handler found for extension" << extension;
    return NULL;
}

RScriptHandler* RScriptHandlerRegistry::getGlobalScriptHandler(
        const QString& extension) {
    if (globalScriptHandlers.count(extension) == 0) {
        RScriptHandler* handler = createScriptHandler(extension);
        if (handler == NULL) {
            qWarning() <<
                    QString(
                            "RScriptHandlerRegistry::getGlobalScriptHandler: "
                            "Creation of Script Handler for %1 failed.").arg(
                            extension);
            return NULL;
        }
        globalScriptHandlers[extension] = handler;
    }
    return globalScriptHandlers[extension];
}
