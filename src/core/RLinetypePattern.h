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

#ifndef RLINETYPEPATTERN_H
#define RLINETYPEPATTERN_H

#include "core_global.h"

#include <stdarg.h>
#include <math.h>

#include <QMetaType>
#include <QVector>



/**
 * Represents a linetype pattern which can be used to draw
 * dashed graphical elements.
 *
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RLinetypePattern {
public:
    /**
     * \nonscriptable
     */
    RLinetypePattern(const QString& name, int num...);
    void set(const QList<double> dashes);

    RLinetypePattern();
    RLinetypePattern(const QString& name);
    RLinetypePattern(const RLinetypePattern& other);
    ~RLinetypePattern();

    bool isValid() const;
    int getNumDashes() const;
    double getPatternLength() const;
    double getDashLengthAt(int i) const;
    double getLargestGap() const;
    bool hasDashAt(double pos) const;
    double getDelta(double pos) const;
    bool isSymmetrical(int i) const;
    void scale(double factor);

    QVector<qreal> getScreenBasedLinetype();

    RLinetypePattern& operator=(const RLinetypePattern& other);
    bool operator==(const RLinetypePattern& other) const;

private:
    QString name;
    int num;
    double* pattern;
    bool* symmetrical;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RLinetypePattern& p);

Q_DECLARE_METATYPE(RLinetypePattern*)
Q_DECLARE_METATYPE(const RLinetypePattern*)
Q_DECLARE_METATYPE(RLinetypePattern)
typedef QMap<QString,RLinetypePattern> _RMapQStringRLinetypePattern;
Q_DECLARE_METATYPE(_RMapQStringRLinetypePattern*)
Q_DECLARE_METATYPE(_RMapQStringRLinetypePattern)

#endif
