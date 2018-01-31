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

#ifndef RPAINTERPATHENGINE_H
#define RPAINTERPATHENGINE_H

#include "core_global.h"

#include <QPaintEngine>
//#include "private/qtextengine_p.h"
//#include "private/qfontengine_p.h"

#include "RPainterPath.h"

/**
 * Experimental.
 *
 * \ingroup core
 */
class QCADCORE_EXPORT RPainterPathEngine : public QPaintEngine {
public:
    RPainterPathEngine();
    virtual ~RPainterPathEngine();

    virtual bool begin(QPaintDevice *device);
    virtual bool end();

    virtual void updateState(const QPaintEngineState &state);

    //virtual void drawTextItem(const QPointF &p, const QTextItem &textItem);

    virtual void drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr);

    virtual QPaintEngine::Type type() const;

    virtual void drawPath(const QPainterPath& path);

    QList<RPainterPath> getPainterPaths();

    virtual void drawPolygon(const QPointF *points, int pointCount, PolygonDrawMode mode);

private:
    QList<RPainterPath> paths;
    QTransform transform;
};

#endif
