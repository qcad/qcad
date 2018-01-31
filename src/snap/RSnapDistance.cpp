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
#include "RSnapDistance.h"

QList<RVector> RSnapDistance::snapEntity(QSharedPointer<REntity> entity,
    const RVector& point, const RBox& queryBox, RGraphicsView& view) {

    Q_UNUSED(point);
    Q_UNUSED(view);

    return entity->getPointsWithDistanceToEnd(distance, RS::FromAny, queryBox);
}

void RSnapDistance::showUiOptions() {
}

void RSnapDistance::hideUiOptions() {
}

void RSnapDistance::setDistance(double d) {
    distance = d;
}
