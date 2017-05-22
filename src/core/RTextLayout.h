/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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

#ifndef RTEXTLAYOUT_H
#define RTEXTLAYOUT_H

#include "core_global.h"

#include <QTextLayout>
#include <QSharedPointer>
#include <QList>
#include <QTransform>

#include "RPainterPath.h"

/**
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RTextLayout {
public:
    RTextLayout() : height(0.0) {}

    /**
     * \nonscriptable
     */
    RTextLayout(QSharedPointer<QTextLayout> layout, const QTransform& transform, const QColor& color) : layout(layout), transform(transform), color(color), height(0.0) {}

    RTextLayout(const QList<RPainterPath>& pps, const QColor& color) : painterPaths(pps), color(color), height(0.0) {}

    bool isEmpty() const {
        return layout.isNull() && painterPaths.isEmpty();
    }

    bool hasLayout() const {
        return !layout.isNull();
    }

    QSharedPointer<QTextLayout> getLayout() const {
        return layout;
    }

    QTransform getTransform() const {
        return transform;
    }

    QColor getColor() const {
        return color;
    }

    QString getText() const {
        if (layout.isNull()) {
            return QString();
        }
        return layout->text();
    }

    QString getFont() const {
        if (layout.isNull()) {
            return QString();
        }
        return layout->font().family();
    }

    bool isBold() const {
        if (layout.isNull()) {
            return false;
        }
        return layout->font().bold();
    }

    bool isItalic() const {
        if (layout.isNull()) {
            return false;
        }
        return layout->font().italic();
    }

    RVector getPosition() const {
        if (layout.isNull()) {
            return RVector::invalid;
        }
        return RVector(layout->position().x(), layout->position().y());
    }

    double getHeight() const {
        return height;
    }

    QSharedPointer<QTextLayout> layout;
    QTransform transform;
    QList<RPainterPath> painterPaths;
    QColor color;
    double height;
};

Q_DECLARE_METATYPE(RTextLayout)
Q_DECLARE_METATYPE(RTextLayout*)

#endif
