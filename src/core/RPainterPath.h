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

#ifndef RPAINTERPATH_H
#define RPAINTERPATH_H

#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QFlags>

#include "RVector.h"

class RArc;
class RShape;
class RSpline;


/**
 * Extended painter path with a z-level and a pen.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class RPainterPath : public QPainterPath {

public:
    enum Mode {
        NoModes = 0x00,
        Selected = 0x01,
        Highlighted = 0x02,
        Invalid = 0x04,
        FixedPenColor = 0x08,
        FixedBrushColor = 0x10,
        AutoRegen = 0x20
    };
    Q_DECLARE_FLAGS(Modes, Mode)

public:
    RPainterPath();
    RPainterPath(const QPainterPath& path);
    virtual ~RPainterPath();

    QList<QSharedPointer<RShape> > getShapes() const;

    void moveTo(const RVector& v) {
        QPainterPath::moveTo(v.x, v.y);
    }

    void moveTo(qreal x, qreal y) {
        QPainterPath::moveTo(x, y);
    }

    void lineTo(const RVector& v) {
        QPainterPath::lineTo(v.x, v.y);
    }

    void lineTo(qreal x, qreal y) {
        QPainterPath::lineTo(x, y);
    }

    void quadTo(const RVector& cp, const RVector& v) {
        QPainterPath::quadTo(cp.x, cp.y, v.x, v.y);
    }

    void quadTo(qreal ctrlPtx, qreal ctrlPty, qreal endPtx, qreal endPty) {
        QPainterPath::quadTo(ctrlPtx, ctrlPty, endPtx, endPty);
    }

    void cubicTo(const RVector& cp1, const RVector& cp2, const RVector& v) {
        QPainterPath::cubicTo(cp1.x, cp1.y, cp2.x, cp2.y, v.x, v.y);
    }

    void cubicTo(qreal ctrlPt1x, qreal ctrlPt1y, qreal ctrlPt2x, qreal ctrlPt2y, qreal endPtx, qreal endPty) {
        QPainterPath::cubicTo(ctrlPt1x, ctrlPt1y, ctrlPt2x, ctrlPt2y, endPtx, endPty);
    }

//    bool contains(const QPointF& point) const {
//        return QPainterPath::contains(point);
//    }

//    bool contains(const QRectF& rectangle) const {
//        return QPainterPath::contains(rectangle);
//    }

//    bool contains(const QPainterPath& p) const {
//        return QPainterPath::contains(p);
//    }

    bool containsPoint(const RVector& v) const {
        return QPainterPath::contains(QPointF(v.x, v.y));
    }

    void addPath(const RPainterPath& path);
    void addArc(const RArc& arc);
    void addSpline(const RSpline& spline);

    void addRect(double x1, double y1, double x2, double y2);
    void addRect(const QRectF& rect);
    void addBox(const RBox& box);

    RBox getBoundingBox() const;

    RVector getStartPoint() const;
    RVector getEndPoint() const;

    bool isValid();
    void setValid(bool on);

    int getZLevel() const;
    void setZLevel(int zl);

    //bool hasPen() const;
    QPen getPen() const;
    void setPen(const QPen& p);

    QBrush getBrush() const;
    void setBrush(const QBrush& b);

    void setMode(RPainterPath::Mode mode, bool on = true);
    bool getMode(RPainterPath::Mode mode) const;

    void setHighlighted(bool on);
    bool isHighlighted() const;

    void setSelected(bool on);
    bool isSelected() const;

    void setFixedPenColor(bool on);
    bool isFixedPenColor() const;

    void setFixedBrushColor(bool on);
    bool isFixedBrushColor() const;

    void setAutoRegen(bool on);
    bool getAutoRegen() const;

    void setFeatureSize(double s);
    double getFeatureSize() const;

    void setPixelSizeHint(double s);
    double getPixelSizeHint() const;

    double getDistanceTo(const RVector& point) const;

    void addPoint(const RVector& position);
    bool hasPoints();
    void setPoints(const QList<RVector>& p);
    QList<RVector> getPoints() const;

    void transform(const QTransform& t);

    int getElementCount() const;
    double getXAt(int i) const;
    double getYAt(int i) const;
    QPainterPath::ElementType getTypeAt(int i) const;
    bool isEmpty() const;

private:
    int zLevel;
    QPen pen;
    QBrush brush;
    Modes modes;
    QList<RVector> points;
    double featureSize;
    double pixelSizeHint;
};

QDebug operator<<(QDebug dbg, RPainterPath& p);

//QDataStream& operator<< (QDataStream& stream, const RPainterPath& path);
//QDataStream& operator>> (QDataStream& stream, RPainterPath& path);
bool operator< (const RPainterPath& p1, const RPainterPath& p2);

Q_DECLARE_OPERATORS_FOR_FLAGS(RPainterPath::Modes)
Q_DECLARE_METATYPE(RPainterPath)
Q_DECLARE_METATYPE(RPainterPath*)
Q_DECLARE_METATYPE(QList<RPainterPath>)
Q_DECLARE_METATYPE(QList<RPainterPath>*)
Q_DECLARE_METATYPE(RPainterPath::Mode)
Q_DECLARE_METATYPE(RPainterPath::Mode*)

#endif
