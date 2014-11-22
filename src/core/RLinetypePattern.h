/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

#include <QCoreApplication>
#include <QMetaType>
#include <QString>
#include <QPair>
#include <QList>
#include <QVector>
#include <QMap>

#include "RPainterPath.h"

/**
 * Represents a linetype pattern which can be used to draw
 * dashed graphical elements.
 *
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RLinetypePattern {
    Q_DECLARE_TR_FUNCTIONS(RLinetypePattern);

public:
    /**
     * \nonscriptable
     */
    RLinetypePattern(bool metric, const QString& name, const QString& description, int num...);

    RLinetypePattern(bool metric, const QString& name, const QString& description, const QList<double>& dashes);

    void set(const QList<double>& dashes);

    static QList<QPair<QString, RLinetypePattern*> > loadAllFrom(bool metric, const QString& fileName);

    RLinetypePattern();
    RLinetypePattern(bool metric, const QString& name, const QString& description);
    RLinetypePattern(const RLinetypePattern& other);
    ~RLinetypePattern();

    bool isValid() const;
    int getNumDashes() const;
    QString getName() const;
    void setName(const QString& n);
    QString getDescription() const;
    void setDescription(const QString& d);

    QString getLabel() const;
    bool isMetric() const {
        return metric;
    }

    QList<double> getPattern() const;
    double getPatternLength() const;
    double getDashLengthAt(int i) const;
    QList<int> getShapeIndices() const;
    bool hasShapes() const;
    bool hasShapeAt(int i) const;
    QList<RPainterPath> getShapeAt(int i, const RVector& pos, double angle) const;
    //QString getShapeCodeAt(int i) const;
    void updateShapes();
    double getLargestGap() const;
    bool hasDashAt(double pos) const;
    double getDelta(double pos) const;
    bool isSymmetrical(int i) const;
    void scale(double factor);

    QVector<qreal> getScreenBasedLinetype();

    RLinetypePattern& operator=(const RLinetypePattern& other);
    bool operator==(const RLinetypePattern& other) const;

    bool isLoaded() { return true; }
    void load() {}

    //static QString fixName(const QString& n);
    static void initNameMap();

public:
    bool metric;
    QString name;
    QString description;
    QList<double> pattern;

    QMap<int, QList<RPainterPath> > shapes;
    QMap<int, QString> shapeTexts;
    QMap<int, QString> shapeTextStyles;
    QMap<int, int> shapeNumbers;
    QMap<int, double> shapeScales;
    QMap<int, double> shapeRotations;
    QMap<int, RVector> shapeOffsets;

    // internal info about segments at which the pattern is symmetrical:
    bool* symmetrical;

    static QMap<QString, QString> nameMap;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RLinetypePattern& p);

Q_DECLARE_METATYPE(RLinetypePattern*)
Q_DECLARE_METATYPE(const RLinetypePattern*)
Q_DECLARE_METATYPE(RLinetypePattern)
typedef QMap<QString,RLinetypePattern> _RMapQStringRLinetypePattern;
Q_DECLARE_METATYPE(_RMapQStringRLinetypePattern*)
Q_DECLARE_METATYPE(_RMapQStringRLinetypePattern)

#endif
