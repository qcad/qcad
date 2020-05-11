/**
 * Copyright (c) 2011-2020 by Andrew Mustun. All rights reserved.
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

#ifndef RTRANSFORMOP_H
#define RTRANSFORMOP_H

#include "../core_global.h"

#include "RMath.h"

/**
 * Represents a transform operation within an RTransform object.
 *
 * \ingroup math
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RTransformOp {
public:
    enum Type {
        Translation,
        Scale,
        Rotation
    };

    static RTransformOp createTranslation(qreal dx, qreal dy) {
        RTransformOp t;
        t.type = Translation;
        t.d1 = dx;
        t.d2 = dy;
        return t;
    }

    static RTransformOp createScale(qreal sx, qreal sy) {
        RTransformOp t;
        t.type = Scale;
        t.d1 = sx;
        t.d2 = sy;
        return t;
    }

    static RTransformOp createRotation(qreal a) {
        RTransformOp t;
        t.type = Rotation;
        t.d1 = a;
        t.d2 = RNANDOUBLE;
        return t;
    }

    RTransformOp::Type getType() const {
        return type;
    }

    qreal getD1() const {
        return d1;
    }

    qreal getD2() const {
        return d2;
    }

public:
    /**
     * \getter{getType}
     */
    RTransformOp::Type type;
    /**
     * \getter{getD1}
     */
    qreal d1;
    /**
     * \getter{getD2}
     */
    qreal d2;
};

Q_DECLARE_METATYPE(RTransformOp)
Q_DECLARE_METATYPE(RTransformOp::Type)
Q_DECLARE_METATYPE(RTransformOp*)

#endif
