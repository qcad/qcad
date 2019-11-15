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
    Q_DECLARE_TR_FUNCTIONS(RLinetypePattern)

    friend class RLinetype;

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
    double getScreenScale() const;
    void setScreenScale(double s);
    bool getNoOffset() const;
    void setNoOffset(bool n);

    QString getLabel() const;
    bool isMetric() const {
        return metric;
    }
    void setMetric(bool on) {
        metric = on;
    }

    bool setPatternString(const QString& patternString);
    QString getPatternString() const;
    QList<double> getPattern() const;
    double getPatternLength() const;
    double getDashLengthAt(int i) const;
    double getDashOffsetAt(const QList<double>& dashes, int i) const;

    bool hasShapeNumberAt(int i) const;
    int getShapeNumberAt(int i) const;
    void setShapeNumberAt(int i, int num);

    bool hasShapeScaleAt(int i) const;
    double getShapeScaleAt(int i) const;
    void setShapeScaleAt(int i, double s);

    bool hasShapeRotationAt(int i) const;
    double getShapeRotationAt(int i) const;
    void setShapeRotationAt(int i, double r);

    bool hasShapeOffsetAt(int i) const;
    RVector getShapeOffsetAt(int i) const;
    void setShapeOffsetAt(int i, const RVector& offset);

    bool hasShapeTextAt(int i) const;
    QString getShapeTextAt(int i) const;
    void setShapeTextAt(int i, const QString& s);

    bool hasShapeTextStyleAt(int i) const;
    QString getShapeTextStyleAt(int i) const;
    void setShapeTextStyleAt(int i, const QString& s);

    QList<int> getShapeIndices() const;
    bool hasShapes() const;
    bool hasShapeAt(int i) const;
    QList<RPainterPath> getShapeAt(int i) const;
    void updateShapes();
    double getLargestGap() const;
    bool hasDashAt(double pos) const;
    double getDelta(double pos) const;
    double getPatternOffset(double length);
    QList<double> getSymmetries() const {
        return symmetries;
    }

    /**
     * \nonscriptable
     */
    double getPatternOffsetAt(double length, double symmetryPos, double* gap = NULL, bool end = false);
    void scale(double factor);

    QVector<qreal> getScreenBasedLinetype();

    RLinetypePattern& operator=(const RLinetypePattern& other);
    bool operator==(const RLinetypePattern& other) const;
    bool operator<(const RLinetypePattern& other) const;

    bool isLoaded() { return true; }
    void load() {}

    static void initNameMap();

private:
    bool metric;
    QString name;
    QString description;
    double screenScale;
    bool noOffset;
    mutable QString patternString;

    QList<double> pattern;

    QMap<int, QList<RPainterPath> > shapes;
    QMap<int, QString> shapeTexts;
    QMap<int, QString> shapeTextStyles;
    QMap<int, int> shapeNumbers;
    QMap<int, double> shapeScales;
    QMap<int, double> shapeRotations;
    QMap<int, RVector> shapeOffsets;

    // internal info about segments at which the pattern is symmetrical:
    QList<double> symmetries;

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
