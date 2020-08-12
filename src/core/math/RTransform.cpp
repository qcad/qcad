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
#include "RTransform.h"
#include "RTransformOp.h"

RTransform& RTransform::translate(qreal dx, qreal dy) {
    ops.append(RTransformOp::createTranslation(dx, dy));
    QTransform::translate(dx, dy);
    return *this;
}

RTransform& RTransform::scale(qreal sx, qreal sy) {
    ops.append(RTransformOp::createScale(sx, sy));
    QTransform::scale(sx, sy);
    return *this;
}

RTransform& RTransform::rotateRadians(qreal angle, Qt::Axis axis) {
    ops.append(RTransformOp::createRotation(angle));
    QTransform::rotateRadians(angle, axis);
    return *this;
}

RTransform& RTransform::rotate(qreal angle, Qt::Axis axis) {
    ops.append(RTransformOp::createRotation(RMath::deg2rad(angle)));
    QTransform::rotate(angle, axis);
    return *this;
}
