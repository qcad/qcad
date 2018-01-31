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

#ifndef RSCRIPTACTION_H
#define RSCRIPTACTION_H

#include "core_global.h"

#include "RAction.h"
#include "RMainWindow.h"

/**
 * Script backed action.
 *
 * \ingroup core
 * \scriptable
 * \abstract
 */
class QCADCORE_EXPORT RScriptAction: public RAction {

public:
    RScriptAction(const QString& scriptFile, RGuiAction* guiAction);
    QString getScriptFile() {
        return scriptFile;
    }

protected:
    QString scriptFile;
};

Q_DECLARE_METATYPE(RScriptAction*)

#endif
