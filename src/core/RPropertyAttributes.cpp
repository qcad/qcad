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
#include "RPropertyAttributes.h"

void RPropertyAttributes::mixWith(const RPropertyAttributes & other) {
    setAffectsOtherProperties(affectsOtherProperties() || other.affectsOtherProperties());
    setInvisible(isInvisible() || other.isInvisible());

#if QT_VERSION >= 0x060000
    QSet<QString> otherSet(other.choices.begin(), other.choices.end());
#else
    QSet<QString> otherSet = other.choices.toSet();
#endif

    // Store intersection while preserving order of first choices list:
    QStringList res;
    for (int i=0; i<choices.length(); ++i) {
        if (otherSet.contains(choices[i])) {
            res.append(choices[i]);
        }
    }

    choices = res;
}


void RPropertyAttributes::setOption(RPropertyAttributes::Option option, bool on) {
    if (on) {
        options |= option;
    } else {
        options &= ~option;
    }
}
