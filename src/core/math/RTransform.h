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

#ifndef RTRANSFORM_H
#define RTRANSFORM_H

#include "../core_global.h"

#include <QTransform>

#include "RGlobal.h"
#include "RTransformOp.h"


/**
 * Represents a transform with recorded operations (reproducable).
 *
 * \ingroup math
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RTransform : public QTransform {
public:
    RTransform() {
    }

    RTransform& translate(qreal dx, qreal dy);
    RTransform& scale(qreal sx, qreal sy);
    RTransform& rotateRadians(qreal angle, Qt::Axis axis = Qt::ZAxis);
    RTransform& rotate(qreal angle, Qt::Axis axis = Qt::ZAxis);

    QList<RTransformOp> getOps() {
        return ops;
    }

private:
    QList<RTransformOp> ops;
};

Q_DECLARE_METATYPE(RTransform)
Q_DECLARE_METATYPE(RTransform*)

#endif
