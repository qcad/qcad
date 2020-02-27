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

#ifndef RLINEWEIGHT_H_
#define RLINEWEIGHT_H_

#include "core_global.h"

#include <QCoreApplication>
#include <QMetaType>
#include <QString>
#include <QIcon>
#include <QPair>
#include <QMap>
#include <QList>

#ifndef RDEFAULT_QSIZE_ICON
#define RDEFAULT_QSIZE_ICON QSize(32,10)
#endif

/**
 * \scriptable
 * \copyable
 */
class QCADCORE_EXPORT RLineweight {

    Q_DECLARE_TR_FUNCTIONS(RLineweight)

public:
    enum Lineweight {
        Weight000 = 0,
        Weight005 = 5,
        Weight009 = 9,
        Weight013 = 13,
        Weight015 = 15,
        Weight018 = 18,
        Weight020 = 20,
        Weight025 = 25,
        Weight030 = 30,
        Weight035 = 35,
        Weight040 = 40,
        Weight050 = 50,
        Weight053 = 53,
        Weight060 = 60,
        Weight070 = 70,
        Weight080 = 80,
        Weight090 = 90,
        Weight100 = 100,
        Weight106 = 106,
        Weight120 = 120,
        Weight140 = 140,
        Weight158 = 158,
        Weight200 = 200,
        Weight211 = 211,
        WeightByLayer = -1,
        WeightByBlock = -2,
        WeightByLwDefault = -3,
        WeightInvalid = -4
    };

public:
    RLineweight();
    static QList<QPair<QString, RLineweight::Lineweight> > getList(bool onlyFixed, bool noDefault = false);
    static QIcon getIcon(RLineweight::Lineweight color, const QSize& size = RDEFAULT_QSIZE_ICON);
    static QString getName(RLineweight::Lineweight lineweight);

private:
    static void init();
    static void init(const QString& cn, RLineweight::Lineweight lineweight);

private:
    static bool isInitialized;
    static QList<QPair<QString, RLineweight::Lineweight> > list;
    //static QMap<RLineweight::Lineweight, QIcon> iconMap;
    static QMap<QPair<RLineweight::Lineweight, QPair<int, int> >, QIcon> iconMap;

};

Q_DECLARE_METATYPE(RLineweight)
Q_DECLARE_METATYPE(RLineweight*)
Q_DECLARE_METATYPE(RLineweight::Lineweight)
typedef QPair<QString, RLineweight::Lineweight> _RPairStringRLineweight;
Q_DECLARE_METATYPE(_RPairStringRLineweight)
Q_DECLARE_METATYPE(QList< _RPairStringRLineweight >)

#endif /* RLINEWEIGHT_H_ */
