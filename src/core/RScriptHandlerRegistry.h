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

#ifndef RSCRIPTHANDLERREGISTRY_H
#define RSCRIPTHANDLERREGISTRY_H

#include "core_global.h"

#include <QList>
#include <QMetaType>
#include <QString>

#include "RNonCopyable.h"
#include "RDocumentInterface.h"
#include "RAction.h"
#include "RGuiAction.h"
#include "RScriptAction.h"
#include "RMainWindow.h"
#include "RSingleton.h"


/**
 * Script Handler Registry for global Script Handlers.
 *
 * \ingroup core
 */
class QCADCORE_EXPORT RScriptHandlerRegistry: public RSingleton {

    friend class RSingleton;

public:
    typedef RScriptHandler* (*FactoryFunction)();

    virtual ~RScriptHandlerRegistry();

    static void registerScriptHandler(FactoryFunction factoryFunction,
            const QList<QString>& fileExtensions);

    static RScriptHandler* createScriptHandler(const QString& extension);
    static RScriptHandler* getGlobalScriptHandler(const QString& extension);

protected:
    static QMap<QString, RScriptHandler*> globalScriptHandlers;
    static QMap<QString, FactoryFunction> factoryFunctions;
};

#endif
