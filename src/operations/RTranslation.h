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

#ifndef RTRANSLATION_H
#define RTRANSLATION_H

#include "operations_global.h"

#include "RTransformation.h"
#include "RVector.h"

/**
 * Helper class for RModifyObjectsOperation::transformSelection
 * 
 * \ingroup operations
 * \scriptable
 */
class QCADOPERATIONS_EXPORT RTranslation : public RTransformation {
public:
    RTranslation(const RVector& offset, double rotationAngle = 0.0, double scaleFactor = 1.0, const RVector& center = RVector::nullVector)
        : offset(offset),
          rotationAngle(rotationAngle),
          scaleFactor(scaleFactor),
          center(center) {}

    RVector offset;
    double rotationAngle;
    double scaleFactor;
    RVector center;
};

Q_DECLARE_METATYPE(RTranslation*)

#endif
