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
#include "RPainterPathEngine.h"

RPainterPathEngine::RPainterPathEngine()
    // starting with Qt 4.8.0 we have to specify feature QPaintEngine::PrimitiveTransform here
    // see QPainterPrivate::updateEmulationSpecifier
    : QPaintEngine(QPaintEngine::PainterPaths | QPaintEngine::PrimitiveTransform) {}

RPainterPathEngine::~RPainterPathEngine() {}

bool RPainterPathEngine::begin(QPaintDevice* device) {
    Q_UNUSED(device)

    return true;
}

bool RPainterPathEngine::end() {
    return true;
}

void RPainterPathEngine::updateState(const QPaintEngineState &state) {
    QPaintEngine::DirtyFlags flags = state.state();

    // required for Qt >= 4.8.0 for texts with unicode characters:
    if (flags & DirtyTransform) {
        transform = state.transform();
    }

    /*
    QPaintEngine::DirtyFlags flags = state.state();
    if (flags & DirtyPen) updatePen(state.pen());
    if (flags & DirtyBrush) updateBrush(state.brush());
    if (flags & DirtyBrushOrigin) updateBrushOrigin(state.brushOrigin());
    if (flags & DirtyFont) updateFont(state.font());
    if (flags & DirtyBackground) updateBackground(state.backgroundMode(), state.backgroundBrush());
    if (flags & DirtyTransform) updateMatrix(state.transform());
    if (flags & DirtyClipEnabled) updateClipEnabled(state.isClipEnabled());
    if (flags & DirtyClipRegion) updateClipRegion(state.clipRegion(), state.clipOperation());
    if (flags & DirtyClipPath) updateClipPath(state.clipPath(), state.clipOperation());
    if (flags & DirtyHints) updateRenderHints(state.renderHints());
    if (flags & DirtyCompositionMode) updateCompositionMode(state.compositionMode());
    if (flags & DirtyOpacity) updateOpacity(state.opacity());
    */
}

void RPainterPathEngine::drawPixmap(const QRectF& r, const QPixmap& pm, const QRectF& sr) {
    Q_UNUSED(r)
    Q_UNUSED(pm)
    Q_UNUSED(sr)
}

QPaintEngine::Type RPainterPathEngine::type() const {
    return QPaintEngine::User;
}

void RPainterPathEngine::drawPath(const QPainterPath& qpath) {
    RPainterPath path(qpath);
    path.setFillRule(Qt::WindingFill);
    path.setBrush(state->brush());
    if (state->brush().color().isValid()) {
        path.setFixedBrushColor(true);
    }
    // required for Qt >= 4.8.0 for texts with unicode characters:
    path.transform(transform);
    paths.append(path);
}

QList<RPainterPath> RPainterPathEngine::getPainterPaths() {
    return paths;
}

void RPainterPathEngine::drawPolygon(const QPointF* points, int pointCount, PolygonDrawMode mode) {
    if (pointCount==0) {
        return;
    }

    RPainterPath path;
    switch (mode) {
    case QPaintEngine::ConvexMode:
    case QPaintEngine::OddEvenMode:
        path.setFillRule(Qt::OddEvenFill);
        break;
    case QPaintEngine::WindingMode:
        path.setFillRule(Qt::WindingFill);
        break;
    case QPaintEngine::PolylineMode:
        path.setPen(state->pen());
        break;
    }

    path.setBrush(state->brush());
    if (state->brush().color().isValid()) {
        path.setFixedBrushColor(true);
    }

    path.moveTo(points[0]);
    for (int i=0; i<pointCount; i++) {
        path.lineTo(points[i]);
    }

    // required for Qt >= 4.8.0 for texts with unicode characters:
    path.transform(transform);
    paths.append(path);
}
