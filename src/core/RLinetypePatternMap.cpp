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
#include "RLinetypePatternMap.h"

RLinetypePatternMap RLinetypePatternMap::patternMap;

RLinetypePatternMap::RLinetypePatternMap() {
    insert("BYLAYER", RLinetypePattern());
    insert("BYBLOCK", RLinetypePattern());

    insert("CONTINUOUS", RLinetypePattern(1, 10.0));

    insert("BORDER", RLinetypePattern(6, 12.0, -6.0, 12.0, -5.95, 0.1, -5.95));
    insert("BORDER2", RLinetypePattern(6, 6.0, -3.0, 6.0, -2.95, 0.1, -2.95));
    insert("BORDERX2", RLinetypePattern(6, 24.0, -12.0, 24.0, -11.95, 0.1, -11.95));

    insert("CENTER", RLinetypePattern(4, 32.0, -6.0, 6.0, -6.0));
    insert("CENTER2", RLinetypePattern(4, 16.0, -3.0, 3.0, -3.0));
    insert("CENTERX2", RLinetypePattern(4, 64.0, -12.0, 12.0, -12.0));

    insert("DASHDOT", RLinetypePattern(4, 12.0, -5.95, 0.1, -5.95));
    insert("DASHDOT2", RLinetypePattern(4, 6.0, -2.95, 0.1, -2.95));
    insert("DASHDOTX2", RLinetypePattern(4, 24.0, -11.95, 0.1, -11.95));

    insert("DASHED", RLinetypePattern(2, 12.0, -6.0));
    insert("DASHED2", RLinetypePattern(2, 6.0, -3.0));
    insert("DASHEDX2", RLinetypePattern(2, 24.0, -12.0));

    insert("DIVIDE", RLinetypePattern(6, 12.0, -5.9, 0.15, -5.9, 0.15, -5.9));
    insert("DIVIDE2", RLinetypePattern(6, 6.0, -2.9, 0.15, -2.9, 0.15, -2.9));
    insert("DIVIDEX2", RLinetypePattern(6, 24.0, -11.9, 0.15, -11.9, 0.15, -11.9));

    insert("DOT", RLinetypePattern(2, 0.1, -6.2));
    insert("DOT2", RLinetypePattern(2, 0.1, -3.1));
    insert("DOTX2", RLinetypePattern(2, 0.1, -12.4));
}

RLinetypePattern RLinetypePatternMap::getPattern(const QString& name) {
    if (patternMap.contains(name.toUpper())) {
        return patternMap[name.toUpper()];
    }
    return RLinetypePattern();
}
