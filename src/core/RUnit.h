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

#ifndef RUNIT_H
#define RUNIT_H

#include "core_global.h"

#include "RS.h"
#include "RVector.h"

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

#ifndef RDEFAULT_DOT
#define RDEFAULT_DOT '.'
#endif

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
                                  bool showTrailingZeroes=false,
                                  bool onlyPreciseResult=false,
                                  char decimalSeparator=RDEFAULT_DOT);
    static QString formatScientific(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false,
                                  bool onlyPreciseResult=false);
    static QString formatDecimal(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false,
                                  bool onlyPreciseResult=false,
                                  char decimalSeparator=RDEFAULT_DOT);
    static QString formatEngineering(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false,
                                  bool onlyPreciseResult=false);
    static QString formatArchitectural(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false,
                                  bool onlyPreciseResult=false);
    static QString formatFractional(double length, RS::Unit unit,
                                  int prec, bool showUnit=false,
                                  bool showLeadingZeroes=true, 
                                  bool showTrailingZeroes=false,
                                  bool onlyPreciseResult=false);

    static QString formatAngle(double angle, RS::AngleFormat format,
                               int prec,
                               bool showLeadingZeroes=true,
                               bool showTrailingZeroes=false,
                               char decimalSeparator=RDEFAULT_DOT);

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
    static RS::Unit parseUnit(const QString& str);
    static QString unitToSymbol(RS::Unit unit, bool asText=false);
    static QString unitToName(RS::Unit unit, bool tr=true);
    static QString getLabel(double v, RDocument& document,
                            int precisionOverride=RDEFAULT_MIN1,
                            bool forceSuppressTrailingZeroes=false,
                            bool onlyPreciseResult=false,
                            char decimalSeparator=RDEFAULT_DOT);

    static QString doubleToString(double value, double prec,
        bool showLeadingZeroes=true, bool showTrailingZeroes=false,
        char decimalSeparator=RDEFAULT_DOT);
    static QString doubleToString(double value, int prec,
        bool showLeadingZeroes=true, bool showTrailingZeroes=false,
        char decimalSeparator=RDEFAULT_DOT);

    // workaround: make the second version also accessible by scripts:
    static QString doubleToStringDec(double value, int prec,
        bool showLeadingZeroes=true, bool showTrailingZeroes=false,
        char decimalSeparator=RDEFAULT_DOT) {

        return doubleToString(value, prec, showLeadingZeroes, showTrailingZeroes, decimalSeparator);
    }
};

Q_DECLARE_METATYPE(RUnit*)

#endif
