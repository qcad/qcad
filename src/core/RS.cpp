/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include "RColor.h"
#include "RGlobal.h"
#include "RLinetype.h"
#include "RLineweight.h"
#include "RPropertyAttributes.h"
#include "RSettings.h"
#include "RVector.h"

const double RS::PointTolerance = 1.0e-9;
const double RS::AngleTolerance = 1.0e-9;

bool RS::compare(const QVariant& v1, const QVariant& v2) {
    // 20120609: tolerance when comparing doubles (property editor)
    // 20140513: handle basic types since Qt 5 thinks it can convert double, bool, int to line type
    if (v1.type()==QVariant::Double && v2.type()==QVariant::Double) {
        return fabs(v1.toDouble() - v2.toDouble()) < RS::PointTolerance;
    }
    if (v1.type()==QVariant::Bool && v2.type()==QVariant::Bool) {
        return v1.toBool()==v2.toBool();
    }
    if (v1.type()==QVariant::Int && v2.type()==QVariant::Int) {
        return v1.toInt()==v2.toInt();
    }
    if (v1.type()==QVariant::UInt && v2.type()==QVariant::UInt) {
        return v1.toUInt()==v2.toUInt();
    }
    if (v1.type()==QVariant::LongLong && v2.type()==QVariant::LongLong) {
        return v1.toLongLong()==v2.toLongLong();
    }
    if (v1.type()==QVariant::ULongLong && v2.type()==QVariant::ULongLong) {
        return v1.toULongLong()==v2.toULongLong();
    }
    if (v1.type()==QVariant::String && v2.type()==QVariant::String) {
        return v1.toString()==v2.toString();
    }

    if (v1.canConvert<RColor> () && v2.canConvert<RColor> ()) {
        return v1.value<RColor> () == v2.value<RColor> ();
    }
    if (v1.canConvert<RLinetype> () && v2.canConvert<RLinetype> ()) {
        return v1.value<RLinetype> () == v2.value<RLinetype> ();
    }
    if (v1.canConvert<RLineweight::Lineweight> () && v2.canConvert<RLineweight::Lineweight> ()) {
        return v1.value<RLineweight::Lineweight> () == v2.value<RLineweight::Lineweight> ();
    }
    if (v1.canConvert<QList<RVector> > () && v2.canConvert<QList<RVector> > ()) {
        return v1.value<QList<RVector> > () == v2.value<QList<RVector> > ();
    }
    return v1 == v2;
}

bool RS::compare(const QPair<QVariant, RPropertyAttributes>& p1, const QPair<
                 QVariant, RPropertyAttributes>& p2) {
    return compare(p1.first, p2.first);
}
