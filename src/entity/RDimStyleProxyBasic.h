/**
 * Copyright (c) 2011-2021 by Andrew Mustun. All rights reserved.
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

#ifndef RDIMSTYLEPROXYBASIC_H
#define RDIMSTYLEPROXYBASIC_H

#include "entity_global.h"

#include <QList>
#include <QSharedPointer>

#include "RDimStyleProxy.h"

class RDimRotatedEntity;
class RDocument;
class RShape;
class RTextData;
class RVector;
class RDimensionData;
class RLine;

/**
 * Proxy for advanced dimension style functionality and rendering. May be implemented
 * by a plugin.
 *
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimStyleProxyBasic : public RDimStyleProxy {
public:
    virtual ~RDimStyleProxyBasic() {}

    virtual void render(const RDimStyle& dimStyle, const REntityData& entity, bool preview, bool forceSelected);

protected:
    void renderDimRotated();
    void renderDimAligned();
    void renderDimOrdinate();
    void renderDimRadial();
    void renderDimDiametric();
    void renderDimAngular2L();

    void updateTextPosition(const QString& text, double textWidth, const RVector& dimLine1, const RVector& dimLine2, bool corrected);

    virtual QList<QSharedPointer<RShape> > getDimensionLineShapes(const RVector& p1, const RVector& p2, bool arrow1, bool arrow2) const;
    bool hasSpaceForArrows(double dimLineLength) const;
    QList<QSharedPointer<RShape> > getArrow(const RVector& position, double direction) const;
    void adjustExtensionLineFixLength(RLine& extLine1, RLine& extLine2, bool addDimExe = true) const;

protected:
    const RDocument* document;
    const RDimensionData* dimensionData;
    const RDimStyle* dimStyle;
    bool preview;
    bool forceSelected;
};

#endif
