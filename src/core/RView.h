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

#ifndef RVIEW_H
#define RVIEW_H

#include "core_global.h"

#include <QString>
#include <QColor>
#include <QDebug>

#include "RGlobal.h"
#include "RObject.h"
#include "RBox.h"

class RDocument;

/**
 * Represents a view in a drawing.
 *
 * \ingroup core
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RView: public RObject {
public:
    static RPropertyTypeId PropertyName;
    static RPropertyTypeId PropertyCenterPoint;
    static RPropertyTypeId PropertyWidth;
    static RPropertyTypeId PropertyHeight;

public:
    RView();

    RView(RDocument* document, const QString& name, RVector centerPoint,
        double width, double height);

    virtual ~RView();

    static void init();

    virtual RS::EntityType getType() const {
        return RS::ObjectView;
    }

    virtual RView* clone() const;

    QString getName() const {
        return name;
    }

    void setName(const QString& n) {
        name = n;
    }

    RVector getCenterPoint() const {
        return centerPoint;
    }

    void setCenterPoint(const RVector& cPoint) {
        centerPoint = cPoint;
    }

    double getWidth() const {
        return width;
    }

    void setWidth(double w) {
        width = w;
    }

    double getHeight() const {
        return height;
    }

    void setHeight(double h) {
        height = h;
    }

    RBox getBox() {
        return RBox(centerPoint - RVector(width, height) / 2, centerPoint
                + RVector(width, height) / 2);
    }

    void scale(double factor) {
        centerPoint.scale(factor);
        width*=factor;
        height*=factor;
    }

    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);
    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);

private:
    QString name;
    RVector centerPoint;
    double width;
    double height;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RView& v);

Q_DECLARE_METATYPE(QSharedPointer<RView>)
Q_DECLARE_METATYPE(QSharedPointer<RView>*)
Q_DECLARE_METATYPE(RView)
Q_DECLARE_METATYPE(RView*)

#endif
