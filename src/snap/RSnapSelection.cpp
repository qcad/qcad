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
#include "RBox.h"
#include "RDocument.h"
#include "RGraphicsView.h"
#include "RSnapSelection.h"



RVector RSnapSelection::snap(const RVector& position, RGraphicsView& view, double range) {
    Q_UNUSED(range);

    lastSnap = RVector::invalid;
    status = RSnap::Unknown;

    document = view.getDocument();
    referencePoints = calculateReferencePoints(document);

    if (referencePoints.isEmpty()) {
        lastSnap = position;
        lastSnap.valid = false;
        return lastSnap;
    }

    QList<RVector> candidates = RRefPoint::toVectorList(referencePoints);

    int index = position.getClosestIndex2D(candidates);
    if (index<0 || index>=candidates.length()) {
        lastSnap = position;
        lastSnap.valid = false;
        return lastSnap;
    }

    switch (index) {
    case 0: status = RSnap::TopLeft; break;
    case 1: status = RSnap::TopMiddle; break;
    case 2: status = RSnap::TopRight; break;
    case 3: status = RSnap::MiddleLeft; break;
    case 4: status = RSnap::MiddleMiddle; break;
    case 5: status = RSnap::MiddleRight; break;
    case 6: status = RSnap::BottomLeft; break;
    case 7: status = RSnap::BottomMiddle; break;
    case 8: status = RSnap::BottomRight; break;
    default: status = RSnap::Unknown; break;
    }

    lastSnap = candidates[index];
    return lastSnap;
}

/**
 * \return The nine possible snap points (corners, edge midpoints and
 * center of the selection box), with the appropriate
 * Top / VMiddle / Bottom and Left / HMiddle / Right flags set.
 * Empty list if there is no selection.
 */
QList<RRefPoint> RSnapSelection::getSnapReferencePoints() const {
    //if (referencePoints.isEmpty()) {
        referencePoints = calculateReferencePoints(document);
    //}
    return referencePoints;
}

/**
 * \return The nine reference points of the selection box of the given
 * document (corners, edge midpoints and center) in the order top left,
 * top middle, top right, middle left, center, middle right, bottom left,
 * bottom middle, bottom right. Empty list if there is no selection.
 */
QList<RRefPoint> RSnapSelection::calculateReferencePoints(RDocument* document) {
    QList<RRefPoint> ret;

    if (document==NULL || !document->hasSelection()) {
        return ret;
    }

    RBox box = document->getSelectionBox();
    if (!box.isSane()) {
        return ret;
    }

    RVector min = box.getMinimum();
    RVector max = box.getMaximum();
    RVector center = box.getCenter();

    ret.append(RRefPoint(RVector(min.x, max.y), RRefPoint::Flags(RRefPoint::FromSnap | RRefPoint::Top) | RRefPoint::Left));
    ret.append(RRefPoint(RVector(center.x, max.y), RRefPoint::Flags(RRefPoint::FromSnap | RRefPoint::Top) | RRefPoint::HMiddle));
    ret.append(RRefPoint(RVector(max.x, max.y), RRefPoint::Flags(RRefPoint::FromSnap | RRefPoint::Top) | RRefPoint::Right));
    ret.append(RRefPoint(RVector(min.x, center.y), RRefPoint::Flags(RRefPoint::FromSnap | RRefPoint::VMiddle) | RRefPoint::Left));
    ret.append(RRefPoint(RVector(center.x, center.y), RRefPoint::Flags(RRefPoint::FromSnap | RRefPoint::VMiddle) | RRefPoint::HMiddle));
    ret.append(RRefPoint(RVector(max.x, center.y), RRefPoint::Flags(RRefPoint::FromSnap | RRefPoint::VMiddle) | RRefPoint::Right));
    ret.append(RRefPoint(RVector(min.x, min.y), RRefPoint::Flags(RRefPoint::FromSnap | RRefPoint::Bottom) | RRefPoint::Left));
    ret.append(RRefPoint(RVector(center.x, min.y), RRefPoint::Flags(RRefPoint::FromSnap | RRefPoint::Bottom) | RRefPoint::HMiddle));
    ret.append(RRefPoint(RVector(max.x, min.y), RRefPoint::Flags(RRefPoint::FromSnap | RRefPoint::Bottom) | RRefPoint::Right));

    return ret;
}
