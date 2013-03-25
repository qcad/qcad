/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RRUNNER_H_
#define RRUNNER_H_

#include "core_global.h"

/**
 * \scriptable
 * \generateScriptShell
 */
class QCADCORE_EXPORT RRunner {
    friend class RThread;
protected:
    /**
     * \todo Should be pure virtual
     */
    virtual void run() { }
};

Q_DECLARE_METATYPE(RRunner*)

#endif /* RRUNNER_H_ */
