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

#ifndef RLINETYPEPATTERNMAP_H
#define RLINETYPEPATTERNMAP_H

#include <QString>
#include <QMap>

#include "RLinetypePattern.h"

/**
 * Provides access to the global, static map of available linetypes.
 * \todo Refactor to use linetypes that are stored in drawings and
 * allow for custom linetypes.
 *
 * \scriptable
 */
class RLinetypePatternMap: public QMap<QString, RLinetypePattern> {
public:
    RLinetypePatternMap();
    static RLinetypePattern getPattern(const QString& name);

private:
    static RLinetypePatternMap patternMap;
};

Q_DECLARE_METATYPE(RLinetypePatternMap*)
Q_DECLARE_METATYPE(RLinetypePatternMap)

#endif
