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

#ifndef RSPATIALINDEXVISITORADAPTER_H
#define RSPATIALINDEXVISITORADAPTER_H

#include "RDebug.h"
#include "RSpatialIndexVisitor.h"


/**
 * \brief Base class for classes that are interested in
 * the data of spatial index items. Not abstract, so it
 * can be used in script environments with prototype based
 * OOP as base class.
 *
 * \ingroup ecma
 * \scriptable
 * \generateScriptShell
 */
class RSpatialIndexVisitorAdapter : public RSpatialIndexVisitor {
public:
    virtual ~RSpatialIndexVisitorAdapter() {}

    virtual void visitData(
        int id, int pos,
        double x1, double y1, double z1,
        double x2, double y2, double z2
    ) {
        Q_UNUSED(id)
        Q_UNUSED(x1)
        Q_UNUSED(y1)
        Q_UNUSED(z1)
        Q_UNUSED(x2)
        Q_UNUSED(y2)
        Q_UNUSED(z2)
    }

    /**
     * \nonscriptable
     */
//    virtual void visitData(
//        int id, int pos,
//        double x1, double y1, double z1,
//        double x2, double y2, double z2
//    ) {
//        //Q_UNUSED(size)
//        //Q_UNUSED(data)
//        visitData(id, pos, x1,y1,z1, x2,y2,z2);
//    }


    virtual void visitNode(
        double x1, double y1, double z1,
        double x2, double y2, double z2
    ) {
        Q_UNUSED(x1)
        Q_UNUSED(y1)
        Q_UNUSED(z1)
        Q_UNUSED(x2)
        Q_UNUSED(y2)
        Q_UNUSED(z2)
    }
};

Q_DECLARE_METATYPE(RSpatialIndexVisitorAdapter*)

#endif
