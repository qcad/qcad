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

#ifndef RCOLOR_H_
#define RCOLOR_H_

#include "core_global.h"

#include <QCoreApplication>
#include <QObject>
#include <QColor>
#include <QMetaType>
#include <QMap>
#include <QIcon>
#include <QDebug>

#ifndef RDEFAULT_QSIZE_ICON
#define RDEFAULT_QSIZE_ICON QSize(32,10)
#endif

/**
 * Color. Fixed RGBA or ByLayer or ByBlock.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RColor: public QColor {

    Q_DECLARE_TR_FUNCTIONS(RColor);


public:
    friend QCADCORE_EXPORT QDataStream& operator<<(QDataStream& stream, const RColor& color);

    friend QCADCORE_EXPORT QDataStream& operator>>(QDataStream& stream, RColor& color);

    enum Mode {
        ByLayer, ByBlock, Fixed
    };

public:
    RColor();
    RColor(int r, int g, int b, int a = 255, RColor::Mode mode = RColor::Fixed);
    RColor(RColor::Mode mode);
    explicit RColor(const QString& name, RColor::Mode mode = RColor::Fixed);

    /**
     * \nonscriptable
     */
    RColor(Qt::GlobalColor color, RColor::Mode mode = RColor::Fixed);
    /**
     * \nonscriptable
     */
    RColor(const QColor& color, RColor::Mode mode = RColor::Fixed);

    int getCustomColorCode() const;
    int getColorIndex() const;

    static void removeColor(const QString& cn);
    static void addColor(const QString& cn, const RColor& c);
    static RColor createFromCadIndex(const QString& code) {
        return createFromCadIndex(code.toInt());
    }
    static RColor createFromCadIndex(int code);
    static RColor createFromCadCustom(const QString& code) {
        return createFromCadCustom(code.toInt());
    }
    static RColor createFromCadCustom(int code);
    static RColor createFromName(const QString& name);

    static QList<QPair<QString, RColor> > getList(bool onlyFixed = false);
    static QIcon getIcon(const RColor& color, const QSize& size = RDEFAULT_QSIZE_ICON);

    unsigned long long getHash() const;

    bool isValid() const;
    QString getName() const;
    bool isByLayer() const;
    bool isByBlock() const;
    bool isFixed() const;

    QColor toCompat() const;
    void setCompat(const QColor& col);

    static RColor getHighlighted(const RColor& color, const QColor& bgColor, int minDist = 75);
    static RColor getFaded(const RColor& color, const QColor& bgColor, double factor = 1);

    //bool equalsCorrected(const RColor & color) const;

    bool operator==(const RColor & color) const;
    bool operator!=(const RColor & color) const;
    bool operator<(const RColor & color) const;

public:
    static QColor CompatByLayer;
    static QColor CompatByBlock;

private:
    static void init();
    static void init(const QString& cn, const RColor& c);

private:
    static bool isInitialized;
    static QList<QPair<QString, RColor> > list;
    static QMap<QPair<RColor, QPair<int, int> >, QIcon> iconMap;
    //static QVector<RColor> cadColors;
    Mode mode;

private:
    static const double cadColors[][3];
};

/**
 *\nonscriptable
 */
QCADCORE_EXPORT QDataStream& operator<<(QDataStream& stream, const RColor& color);

/**
 *\nonscriptable
 */
QCADCORE_EXPORT QDataStream& operator>>(QDataStream& stream, RColor& color);

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RColor& c);

Q_DECLARE_METATYPE(RColor)
Q_DECLARE_METATYPE(RColor*)
typedef QPair<QString, RColor> _RPairStringRColor;
Q_DECLARE_METATYPE(_RPairStringRColor)
Q_DECLARE_METATYPE(QList< _RPairStringRColor >)
Q_DECLARE_METATYPE(RColor::Mode)

#endif /* RCOLOR_H_ */
