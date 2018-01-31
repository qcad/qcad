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
#include "RTextData.h"
#include "RUnit.h"

RTextData::RTextData() {
}

RTextData::RTextData(RDocument* document, const RTextData& data)
    : RTextBasedData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RTextData::RTextData(const RTextBasedData& data)
    : RTextBasedData(data) {
}

RTextData::RTextData(const RVector& position,
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
              bool simple)
    : RTextBasedData(position,
        alignmentPoint, textHeight, textWidth,
        verticalAlignment, horizontalAlignment,
        drawingDirection, lineSpacingStyle, lineSpacingFactor,
        text, fontName, bold, italic, angle, simple) {
}
