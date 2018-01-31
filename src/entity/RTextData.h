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

#ifndef RTEXTDATA_H
#define RTEXTDATA_H

#include "entity_global.h"

#include "RDocument.h"
#include "RTextBasedData.h"
#include "RVector.h"

/**
 * Text entity data class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RTextData: public RTextBasedData {
    friend class RTextEntity;

protected:
    RTextData(RDocument* document, const RTextData& data);

public:
    RTextData();
    RTextData(const RTextBasedData& data);
    RTextData(const RVector& position,
              const RVector& alignmentPoint,
              double textHeight,
              double textWidth,
              RS::VAlign verticalAlignment,
              RS::HAlign horizontalAlignment,
              RS::TextDrawingDirection drawingDirection,
              RS::TextLineSpacingStyle lineSpacingStyle,
              double lineSpacingFactor,
              const QString& text,
              const QString& fontName,
              bool bold,
              bool italic,
              double angle,
              bool simple);

    virtual RS::EntityType getType() const {
        return RS::EntityText;
    }
};

Q_DECLARE_METATYPE(RTextData)
Q_DECLARE_METATYPE(RTextData*)
Q_DECLARE_METATYPE(const RTextData*)
Q_DECLARE_METATYPE(QSharedPointer<RTextData>)
Q_DECLARE_METATYPE(QSharedPointer<RTextData>*)

#endif
