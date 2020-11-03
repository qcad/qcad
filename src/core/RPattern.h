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

#ifndef RPATTERN_H
#define RPATTERN_H

#include "core_global.h"

#include <QChar>
#include <QMap>
#include <QPainterPath>
#include <QString>
#include <QSharedPointer>

#include "RBox.h"
#include "RShape.h"
#include "RPatternLine.h"


/**
 * Represents a hatch pattern.
 *
 * \ingroup core
 * \scriptable
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT RPattern {
public:
    static QList<QPair<QString, RPattern*> > loadAllFrom(const QString& fileName);

    RPattern();
    RPattern(const QString& name, const QString& description);
    ~RPattern();

    bool isValid() const {
        return !fileName.isEmpty();
    }

    bool hasDots() const;

    void clear() {
        fileName.clear();
        name.clear();
        description.clear();
        patternLines.clear();
    }

    /** \return the fileName of this pattern. */
    QString getFileName() const {
        return fileName;
    }

    /** \return the name of this pattern. */
    const QString getName() const {
        return name;
    }

    /** \return the description of this pattern. */
    const QString getDescription() const {
        return description;
    }

    /**
     * \return True if this pattern is already loaded.
     */
    bool isLoaded() const {
        return true;
    }

    void load() const { }

    QList<RPatternLine> getPatternLines() const {
        return patternLines;
    }

    void addPatternLine(const RPatternLine& patternLine) {
        patternLines.append(patternLine);
    }

    void scale(double f);
    void rotate(double a);

private:
    //! Pattern file name
    QString fileName;

    //! Pattern name
    QString name;

    //! Pattern description
    QString description;

    //! List of pattern line definitions.
    QList<RPatternLine> patternLines;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, const RPattern& p);

Q_DECLARE_METATYPE(RPattern)
Q_DECLARE_METATYPE(RPattern*)

#endif
