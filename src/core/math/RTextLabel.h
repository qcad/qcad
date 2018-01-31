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

#ifndef RTEXTLABEL_H
#define RTEXTLABEL_H

#include "../core_global.h"

#include "RPoint.h"
#include "RVector.h"
#include "RBox.h"

#ifndef RDEFAULT_QVARIANT
#define RDEFAULT_QVARIANT QVariant()
#endif

/**
 * Text label. Mainly used to add to preview as information 
 * for the user, e.g. to display current snap mode.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 */
class QCADCORE_EXPORT RTextLabel: public RPoint {
public:
    RTextLabel();
    RTextLabel(const RVector& position, const QString& text, const QVariant& userData = RDEFAULT_QVARIANT);
    virtual ~RTextLabel();

    virtual RTextLabel* clone() const {
        return new RTextLabel(*this);
    }

    QString getText() const {
        return text;
    }
    QVariant getUserData() const {
        return userData;
    }

protected:
    virtual void print(QDebug dbg) const;

public:
    QString text;
    QVariant userData;
};

Q_DECLARE_METATYPE(RTextLabel)
Q_DECLARE_METATYPE(RTextLabel*)
Q_DECLARE_METATYPE(QSharedPointer<RTextLabel>)
Q_DECLARE_METATYPE(QSharedPointer<RTextLabel>*)
Q_DECLARE_METATYPE(QList<RTextLabel>)

#endif
