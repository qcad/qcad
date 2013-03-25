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

#ifndef RUNIT_H
#define RUNIT_H

#include "core_global.h"

#include "RS.h"
#include "RVector.h"

class RDocument;

/**
 * Conversion methods for units
 *
 * \scriptable
 */
class QCADCORE_EXPORT RUnit {
public:
    //static RS::Unit stringToUnit(const QString& u);

    static QString formatLinear(double length, RS::Unit unit,
                                  RS::LinearFormat format,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false);
    static QString formatScientific(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false);
    static QString formatDecimal(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false);
    static QString formatEngineering(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false);
    static QString formatArchitectural(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false);
    static QString formatFractional(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false);
    static QString trimTrailingZeroes(const QString& s);

    static QString formatAngle(double angle, RS::AngleFormat format,
                                 int prec,
                                 bool showLeadingZeroes=true,
                                 bool showTrailingZeroes=false);

    /*
    static RVector paperFormatToSize(RS::PaperFormat p);
    static RS::PaperFormat paperSizeToFormat(const RVector s);
    
    static QString paperFormatToString(RS::PaperFormat p);
    static RS::PaperFormat stringToPaperFormat(const QString& p);
    */

    static bool isMetric(RS::Unit unit);
    static double convert(double value, RS::Unit source, RS::Unit dest);
    static RVector convert(const RVector& value, RS::Unit source, RS::Unit dest);
    static double getFactorToM(RS::Unit unit);
    static QString unitToSymbol(RS::Unit unit);
    static QString unitToName(RS::Unit unit, bool tr=true);
    static QString getLabel(double v, RDocument& document,
                            bool maxPrecision=false,
                            bool forceSuppressTrailingZeroes=false);

    static QString doubleToString(double value, double prec,
        bool showLeadingZeroes=true, bool showTrailingZeroes=false);
    static QString doubleToString(double value, int prec,
        bool showLeadingZeroes=true, bool showTrailingZeroes=false);
};

Q_DECLARE_METATYPE(RUnit*)

#endif
