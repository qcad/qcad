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

#ifndef RSPATIALINDEXVISITOR_H
#define RSPATIALINDEXVISITOR_H

#include "core_global.h"

//#include <stdint.h>


/**
 * \brief Abstract base class for classes that are interested in
 * the data of spatial index items.
 *
 * \scriptable
 * \ingroup core
 */
class QCADCORE_EXPORT RSpatialIndexVisitor {
public:
    virtual ~RSpatialIndexVisitor() {}
    /**
     * \nonscriptable
     */
    virtual void visitData(
        int id,
        int pos,
        double x1, double y1, double z1,
        double x2, double y2, double z2
    ) = 0;

    virtual void visitNode(
        double x1, double y1, double z1,
        double x2, double y2, double z2
    ) = 0;
};

Q_DECLARE_METATYPE(RSpatialIndexVisitor*)

#endif
