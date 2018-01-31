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
#include <cmath>

#include "RBox.h"
#include "RTextLabel.h"
#include "RLine.h"
#include "RDebug.h"

/**
 * Creates a point object with an invalid position
 */
RTextLabel::RTextLabel() {
}

/**
 * Creates a point object with the given position.
 *
 * \param position the position
 *
 */
RTextLabel::RTextLabel(const RVector& position, const QString& text,
                       const QVariant& userData) :
    RPoint(position), text(text), userData(userData) {
}

RTextLabel::~RTextLabel() {
}

void RTextLabel::print(QDebug dbg) const {
    dbg.nospace() << "RTextLabel(";
    RShape::print(dbg);
    dbg.nospace() << ", position: " << getPosition()
                  << ", text: " << getText()
                  << ")";
}
