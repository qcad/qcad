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
#include "RMath.h"

class RDimRotatedEntity;
class RDocument;
class RShape;
class RTextData;
class RVector;
class RDimensionData;
class RArc;
class RLine;

/**
 * Proxy for advanced dimension style functionality and rendering. May be implemented
 * by a plugin.
 *
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimStyleProxyBasic : public RDimStyleProxy {
public:
    RDimStyleProxyBasic() :
        document(NULL), dimensionData(NULL), dimStyle(NULL), preview(false), forceSelected(false), outsideArrow1(false), outsideArrow2(false) {}

    virtual ~RDimStyleProxyBasic() {}

    virtual void render(const RDimStyle& dimStyle, const REntityData& entity, bool preview, bool forceSelected);

protected:
    virtual void renderPrivate(const RDimStyle& dimStyle, const REntityData& entity, bool preview, bool forceSelected);

    virtual void renderDimRotated();
    virtual void renderDimAligned();
    virtual void renderDimOrdinate();
    virtual void renderDimRadial();
    virtual void renderDimDiametric();
    virtual void renderDimAngular();

    virtual void breakUpDimArc(QList<QSharedPointer<RShape> >& shapes, QSharedPointer<RArc> dimArc) {
        Q_UNUSED(shapes)
        Q_UNUSED(dimArc)
    }

    virtual void updateTextPosition(const QString& text, double textWidth, const RVector& dimLine1, const RVector& dimLine2, bool corrected, double angleHint = RNANDOUBLE);

    virtual void updateOutsideArrow(const RVector& p1, const RVector& p2);
    virtual QList<QSharedPointer<RShape> > getDimensionLineShapes(const RVector& p1, const RVector& p2, bool arrow1, bool arrow2, double angleHint = RNANDOUBLE) const;
    virtual bool hasSpaceForArrows(double dimLineLength) const;
    virtual QList<QSharedPointer<RShape> > getArrow(const RVector& position, double direction) const;
    virtual void adjustExtensionLineFixLength(RLine& extLine1, RLine& extLine2, bool addDimExe = true) const;

protected:
    const RDocument* document;
    const RDimensionData* dimensionData;
    const RDimStyle* dimStyle;
    bool preview;
    bool forceSelected;
    mutable bool outsideArrow1;
    mutable bool outsideArrow2;
};

#endif
