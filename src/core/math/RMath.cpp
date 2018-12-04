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
#ifdef Q_OS_WIN
// for _isnan:
#include <cfloat>
#endif

#include <complex>

#include <QRegExp>
#include <QScriptEngine>

#include "RDebug.h"
#include "RMath.h"
#include "RSettings.h"

/**
 * Last error encountered.
 */
QString RMath::lastError = "";
QString RMath::mathExt = QString();

/**
 * \return Absolute modulus.
 */
int RMath::absmod(int a, int b) {
    if (b == 0) {
        return a;
    }
    int m = a % b;
    if ((b < 0 && m > 0) || (b > 0 && m < 0)) {
        return b + m;
    }
    return m;
}

/**
 * \return v truncated (cut off) at decimal point.
 */
double RMath::trunc(double v) {
#if defined Q_OS_WIN
    if (v==0 || RMath::isNaN(v) || RMath::isInf(v)) {
        return v;
    }
    if (v >= 0.0) {
        return floor(v);
    }
    else {
        return ceil(v);
    }
#else
    return ::trunc(v);
#endif
}

/**
 * Safe pow function.
 *
 * \param x the base
 * \param y the exponent
 *
 * \return The value of x raised to the power of y.
 */
double RMath::pow(double x, double y) {
    errno = 0;
    double ret = ::pow(x, y);
    if (errno == EDOM) {
        qCritical("RMath::pow: EDOM in pow");
        ret = 0.0;
    } else if (errno == ERANGE) {
        qCritical("RMath::pow: ERANGE in pow");
        ret = 0.0;
    }
    return ret;
}

/**
 * \return true if v is non NaN and not Inf.
 */
bool RMath::isNormal(double v) {
    if (RMath::isNaN(v) || RMath::isInf(v)) {
        return false;
    }
    return true;
}

/**
 * \return true if v is NaN.
 */
bool RMath::isNaN(double v) {
#ifdef Q_OS_MAC
    return std::fpclassify(v)==FP_NAN;
#elif defined Q_OS_WIN
    return _isnan(v);
#else
    return std::isnan(v);
#endif
}

/**
 * \return true if v is Inf.
 */
bool RMath::isInf(double v) {
#ifdef Q_OS_MAC
    return std::fpclassify(v)==FP_INFINITE;
#elif defined Q_OS_WIN
    return !_finite(v);
#else
    return std::fpclassify(v)==FP_INFINITE;
#endif
}

bool RMath::isSane(double v) {
    return !isNaN(v) && !isInf(v) && v>-1e12 && v<1e12;
}

/**
 * Evaluates the given mathematical expression and returns the result.
 * Angles may be expressed in degrees (default), rad (#r), gon (#g)
 * or as surveyors angles (N#d#'#"E).
 */
double RMath::eval(const QString& expression, bool* ok) {
    lastError = "";

    if (expression.isEmpty()) {
        if (ok!=NULL) {
            *ok = false;
        }
        lastError = "Expression is empty";
        //qDebug() << "RMath::evel: error: " << lastError;
        return RNANDOUBLE;
    }

    // handle *VARIES* from property editor efficiently:
    if (expression.startsWith("*") && expression.endsWith("*")) {
        return RNANDOUBLE;
    }

    if (ok!=NULL) {
        *ok = true;
    }

    QString expr = expression;

    // 'correct' commas in numbers to points:
    if (RSettings::getNumberLocale().decimalPoint()==',') {
        expr.replace(QRegExp("(\\d*),(\\d+)"), "\\1.\\2");
    }

    int idx = -1;

    // convert surveyor type angles (e.g. N10d30'12.5"E) to degrees:
    if (expr.contains(QRegExp("[NESW]", Qt::CaseInsensitive))) {
        // \b(?:(?:([NS])(?:([+-]?)(?:(?:(\d*\.?\d*)[d°])?(?:(\d*\.?\d*)')?(?:(\d*\.?\d*)")?|(\d*))([EW]))?)|([EW]))\b
        QRegExp re(
            "\\b"                               // a word
            "(?:"
              "(?:"
                "([NS])"                        // expression starts with nord or south
                "(?:"
                  "([+-]?)"                     // sign
                  "(?:"
                    "(?:(\\d*\\.?\\d*)[d°])?"   // degrees with d
                    "(?:(\\d*\\.?\\d*)')?"      // minutes with '
                    "(?:(\\d*\\.?\\d*)\")?"     // seconds with "
                    "|"                         // or...
                    "(\\d*)"                    // degrees without d
                  ")"
                  "([EW])"                      // east or west
                ")?"
              ")"
              "|"                               // or...
              "([EW])"                          // only east (0d) or west (180d)
            ")"
            "\\b",
            Qt::CaseInsensitive, QRegExp::RegExp2);

        do {
            idx = re.indexIn(expr);
            if (idx==-1) {
                break;
            }
            double angle = 0.0;
            QString sign;

            // "E" or "W":
            if (!re.cap(8).isEmpty()) {
                if (re.cap(8).toUpper()=="E") {
                    angle = 0.0;
                }
                else if (re.cap(8).toUpper()=="W") {
                    angle = 180.0;
                }
                else {
                    if (ok!=NULL) {
                        *ok = false;
                    }
                    lastError = "Invalid cardinal direction found (valid values are: N,E,S,W)";
                    return RNANDOUBLE;
                }
            }
            // "[NS]...[EW]":
            else {
                bool north = re.cap(1).toUpper()=="N";
                bool south = re.cap(1).toUpper()=="S";
                sign = re.cap(2);
                double degrees = 0.0;
                double minutes = 0.0;
                double seconds = 0.0;
                if (!re.cap(6).isEmpty()) {
                    degrees = re.cap(6).toDouble(ok);
                }
                else {
                    degrees = re.cap(3).toDouble(ok);
                    minutes = re.cap(4).toDouble(ok);
                    seconds = re.cap(5).toDouble(ok);
                }
                bool east = re.cap(7).toUpper()=="E";
                bool west = re.cap(7).toUpper()=="W";

                double base = (north ? 90.0 : 270.0);
                int dir = ((north && west) || (south && east) ? 1 : -1);
                angle = base + dir * (degrees + minutes/60.0 + seconds/3600.0);
            }

            expr.replace(
                re.cap(),
                QString("%1%2").arg(sign).arg(angle, 0, 'g', 16)
            );
        } while(idx!=-1);
    }

    //qDebug() << "RMath::eval: expression 001 is: " << expr;

    // convert radiant angles (e.g. "1.2r") to degrees:
    {
        QRegExp re("((?:\\.\\d+)|(?:\\d+\\.\\d*)|(?:\\d+))r\\b", Qt::CaseInsensitive, QRegExp::RegExp2);
        do {
            idx = re.indexIn(expr);
            if (idx==-1) {
                break;
            }
            QString match = re.cap(1);
            //qDebug() << "RMath::eval: match 001a is: " << match;
            expr.replace(
                re,
                QString("%1").arg(rad2deg(match.toDouble(ok)), 0, 'g', 16)
            );
            //qDebug() << "RMath::eval: expression 001a is: " << expr;
        } while(idx!=-1);
    }

    //qDebug() << "RMath::eval: expression 002 is: " << expr;

    // convert grad angles (e.g. "100g") to degrees:
    {
        QRegExp re("((?:\\.\\d+)|(?:\\d+\\.\\d*)|(?:\\d+))g\\b", Qt::CaseInsensitive, QRegExp::RegExp2);
        do {
            idx = re.indexIn(expr);
            if (idx==-1) {
                break;
            }
            QString match = re.cap(1);
            expr.replace(
                re,
                QString("%1").arg(gra2deg(match.toDouble(ok)), 0, 'g', 16)
            );
        } while(idx!=-1);
    }

    //qDebug() << "RMath::eval: expression 003 is: " << expr;

    // convert explicitely indicated degree angles (e.g. "90d30'5\"") to degrees:
    {
        QRegExp re(
            "(?:[^a-zA-Z0-9]|^)"                                // not preceded by letter or number (could be part of a function)
            "("
              "(?:((?:\\.\\d+)|(?:\\d+\\.\\d*)|(?:\\d+))[d°])"  // degrees
              "(?:((?:\\.\\d+)|(?:\\d+\\.\\d*)|(?:\\d+))')?"    // minutes
              "(?:((?:\\.\\d+)|(?:\\d+\\.\\d*)|(?:\\d+))\")?"   // seconds
            ")"
            "(?:[^\\d]|$)",             // followed by not a number or end
            Qt::CaseInsensitive, QRegExp::RegExp2);
        do {
            idx = re.indexIn(expr);
            if (idx==-1) {
                break;
            }

            double degrees = 0.0;
            double minutes = 0.0;
            double seconds = 0.0;
            degrees = re.cap(2).toDouble(ok);
            minutes = re.cap(3).toDouble(ok);
            seconds = re.cap(4).toDouble(ok);

            double angle = degrees + minutes/60.0 + seconds/3600.0;

            expr.replace(
                re.cap(1),
                QString("%1").arg(angle, 0, 'g', 16)
            );
        } while(idx!=-1);
    }

    // convert fraction notation to formula:
    // e.g. 7 3/32 to (7+3/32)
    {
        QRegExp re("(\\d+)[ ]+(\\d+/\\d+)", Qt::CaseInsensitive, QRegExp::RegExp2);
        do {
            idx = re.indexIn(expr);
            if (idx==-1) {
                break;
            }
            QString numberString = re.cap(1);
            QString fractionString = re.cap(2);
            expr.replace(
                re,
                QString("(%1+%2)").arg(numberString).arg(fractionString)
            );
        } while(idx!=-1);
    }

    // advanced feet/inch entering:
    // e.g. 12'3/4" -> (12*12+3/4)
    {
        QRegExp re("(\\d+)'\\s*([^+\\-\"][^\"]*)\"", Qt::CaseInsensitive, QRegExp::RegExp2);
        do {
            idx = re.indexIn(expr);
            if (idx==-1) {
                break;
            }
            QString feetString = re.cap(1);
            //qDebug() << "feetString:" << feetString;
            if (feetString.isEmpty()) {
                feetString="0";
                //qDebug() << "> feetString:" << feetString;
            }
            QString inchString = re.cap(2);
            //qDebug() << "inchString:" << inchString;
            expr.replace(
                        re,
                        //       ((FT)*12+(IN))
                        QString("(%1*12+(%2))")
                        .arg(feetString)             // feet (number)
                        .arg(inchString)             // inches (number or formula)
                        );
        } while(idx!=-1);
    }

    // convert foot indication to a factor of 12
    // e.g.
    // 10'5  -> 10*12+5
    // 10'   -> 10*12
    // an optional " at the end may be present and is ignored
    {
        QRegExp re("(\\d+)'[ ]*(\\d*)(\"?)", Qt::CaseInsensitive, QRegExp::RegExp2);
        do {
            idx = re.indexIn(expr);
            if (idx==-1) {
                break;
            }
            QString feetString = re.cap(1);
            QString inchString = re.cap(2);
            expr.replace(
                        re,
                        QString("(%1*12%2%3)")
                        .arg(feetString)                               // feet
                        .arg(inchString.isEmpty() ? "" : "+")
                        .arg(inchString)                               // inches
                        );
        } while(idx!=-1);
    }

    // single inch with sign entering:
    // e.g. 3" -> (3)
    // e.g. 3/4" -> (3/4)
    {
        QRegExp re("([^+\\-\"][^\"]*)\"", Qt::CaseInsensitive, QRegExp::RegExp2);
        do {
            idx = re.indexIn(expr);
            if (idx==-1) {
                break;
            }
            QString inchString = re.cap(1);
            expr.replace(
                        re,
                        QString("(%1)")
                        .arg(inchString)             // inches (number or formula)
                        );
        } while(idx!=-1);
    }

    static QScriptEngine e;

    if (mathExt.isNull()) {
        QString inputJs = "scripts/input.js";
        if (!QFileInfo(inputJs).exists()) {
            inputJs = ":scripts/input.js";
        }
        QFile file(inputJs);
        if (file.exists()) {
            if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
                mathExt = QString(file.readAll());
                file.close();
            }
        }
        else {
            qDebug() << "file not found: input.js";
        }
    }
    e.evaluate(mathExt);

    QScriptValue res = e.evaluate(expr);

    if (res.isError()) {
        if (ok!=NULL) {
            *ok = false;
        }
        lastError = res.toString();
        //qDebug() << "RMath::evel: error: " << lastError;
        return RNANDOUBLE;
    }

    if (!res.isNumber()) {
        if (ok != NULL) {
            *ok = false;
        }
        lastError = expr + " is not a number: " + res.toString();
        //qDebug() << "RMath::evel: error: " << lastError;
        return RNANDOUBLE;
    }

    //qDebug() << "res.toNumber(): " << res.toNumber();
    //qDebug() << "fpclassify: " << std::fpclassify(res.toNumber());

    if (!isNormal(res.toNumber())) {
        if (ok != NULL) {
            *ok = false;
        }
        lastError = expr + " is not a normal number";
        //qDebug() << "RMath::evel: error: " << lastError;
        return RNANDOUBLE;
    }

    return res.toNumber();
}

/**
 * \return Last error encountered by a math function.
 */
QString RMath::getError() {
    return lastError;
}

/**
 * \return True if an error was encountered since the last check.
 */
bool RMath::hasError() {
    return !lastError.isEmpty();
}

/**
 * Converts the given angle in rad to the given angle format.
 * \todo Support different formats.
 */
QString RMath::angleToString(double a) {
    return QString("%1").arg(rad2deg(a));
}

QString RMath::trimTrailingZeroes(const QString& s) {
    if (!s.contains('.')) {
        return s;
    }

    QString ret = s;

    bool done = false;
    while (!done) {
        if (ret.size()>0) {
            if (ret.at(ret.size()-1)=='0') {
                ret = ret.left(ret.size()-1);
            }
            else if (ret.at(ret.size()-1)=='.') {
                ret = ret.left(ret.size()-1);
                done = true;
            }
            else {
                done = true;
            }
        }
        else {
            done = true;
        }
    }

    return ret;
}


/**
 * Converts radians to degrees.
 *
 * \param a angle in radians
 */
double RMath::rad2deg(double a) {
    return (a / (2.0 * M_PI) * 360.0);
}

/**
 * Converts grads to degrees.
 *
 * \param a angle in grad (gon)
 */
double RMath::gra2deg(double a) {
    return a / 400.0 * 360.0;
}

/**
 * \return True if the given value is between the given limits.
 * \param inclusive True to accept values close to the limits within the given tolerance.
 */
bool RMath::isBetween(double value, double limit1, double limit2, bool inclusive, double tolerance) {
    if (fuzzyCompare(value, limit1, tolerance) || fuzzyCompare(value, limit2, tolerance)) {
        return inclusive;
    }
    double min = qMin(limit1, limit2);
    double max = qMax(limit1, limit2);
    return (value>=min && value<=max);
}

/**
 * Converts degrees to radians.
 *
 * \param a angle in degrees
 */
double RMath::deg2rad(double a) {
    return ((a / 360.0) * (2.0 * M_PI));
}

/**
 * Converts radians to gradians.
 *
 * \param a angle in radians
 */
double RMath::rad2gra(double a) {
    return (a / (2.0 * M_PI) * 400.0);
}

/**
 * Finds greatest common divider using Euclid's algorithm.
 * \sa http://en.wikipedia.org/wiki/Greatest_common_divisor
 *
 * \param a the first number
 *
 * \param b the second number
 *
 * \return The greatest common divisor of \c a and \c b.
 */
int RMath::getGcd(int a, int b) {
    int rem;

    while (b != 0) {
        rem = a % b;
        a = b;
        b = rem;
    }

    return a;
}

/**
 * Tests if angle a is between a1 and a2. a, a1 and a2 must be in the
 * range between 0 and 2*PI.
 * All angles in rad.
 *
 * \param a the test angle
 * \param a1 the lower limiting angle
 * \param a2 the upper limiting angle
 * \param reversed True for clockwise testing. False for ccw testing.
 * \return true if the angle a is between a1 and a2.
 */
bool RMath::isAngleBetween(double a, double a1, double a2, bool reversed) {

    a = RMath::getNormalizedAngle(a);
    a1 = RMath::getNormalizedAngle(a1);
    a2 = RMath::getNormalizedAngle(a2);

    bool ret = false;

    if (reversed) {
        double tmp = a1;
        a1 = a2;
        a2 = tmp;
    }

    if (a1 >= a2 - RS::AngleTolerance) {
        if (a >= a1 - RS::AngleTolerance || a <= a2 + RS::AngleTolerance) {
            ret = true;
        }
    } else {
        if (a >= a1 - RS::AngleTolerance && a <= a2 + RS::AngleTolerance) {
            ret = true;
        }
    }
    return ret;
}

/**
 * Gets the normalized angle from \c a.
 * Used to make sure that an angle is in the range between 0 and 2 pi.
 *
 * \param a the unnormalized angle, e.g. 8
 *
 * \return The angle \c a normalized to the range of \f$ 0 \ldots 2\pi \f$,
 * e.g. normalized angle from 8 is 1.716.
 */
double RMath::getNormalizedAngle(double a) {
    if (a >= 0.0) {
        int n = (int) floor(a / (2*M_PI));
        a -= 2*M_PI * n;
    } else {
        int n = (int) ceil(a / (-2*M_PI));
        a += 2*M_PI * n;
    }

    if (a>2*M_PI-RS::AngleTolerance) {
        a = 0.0;
    }

    return a;
}

/**
 * \return Angle a as angle relative to baseAngle.
 *         Result is in range -PI < result < PI.
 */
double RMath::getRelativeAngle(double a, double baseAngle) {
    double ret = a - baseAngle;
    if (ret>M_PI) {
        ret-=2*M_PI;
    }
    if (ret<-M_PI) {
        ret+=2*M_PI;
    }
    return ret;
}

/**
 * \param a1 first angle in rad
 * \param a2 second angle in rad
 *
 * \return The angle that needs to be added to a1 to reach a2.
 *         Always positive and less than 2*pi.
 */
double RMath::getAngleDifference(double a1, double a2) {
    double ret;

    if (a1 >= a2) {
        a2 += 2*M_PI;
    }
    ret = a2 - a1;

    if (ret >= 2*M_PI) {
        ret = 0.0;
    }

    return ret;
}

/**
 * \param a1 first angle in rad
 *
 * \param a2 s second angle in rad
 *
 * \return The angle that needs to be added to a1 to reach a2.
 *         Always between -pi and pi.
 */
double RMath::getAngleDifference180(double a1, double a2) {
    double ret;

    ret = a2 - a1;
    if (ret > M_PI) {
        ret = -(2*M_PI - ret);
    }
    if (ret < -M_PI) {
        ret = 2*M_PI + ret;
    }

    return ret;
}

/**
 * Adds 180° to the given angle if a text constructed with that angle
 * otherwise wouldn't be readable.
 * Used for dimension texts and for mirroring texts.
 *
 * \param angle the original angle
 *
 * \param readable true: make angle readable, false: unreadable
 *
 * \param corrected Pointer to boolean that will point to true if the given angle was
 *   corrected, false otherwise, or null.
 *
 * \return The given angle or the given \c angle + pi, depending which one
 * is readable from the bottom or right.
 */
double RMath::makeAngleReadable(double angle, bool readable, bool* corrected) {

    double ret;

    bool cor = isAngleReadable(angle) ^ readable;

    // quadrant 1 & 4
    if (!cor) {
        ret = angle;
    }
    // quadrant 2 & 3
    else {
        ret = angle + M_PI;
    }

    if (corrected != NULL) {
        *corrected = cor;
    }

    return ret;
}

/**
 * \param angle The text angle in rad
 *
 * \param tolerance The tolerance by which the angle still maybe
 * in the unreadable range.
 *
 * \return true: If the given angle is in a range that is readable
 * for texts created with that angle.
 */
bool RMath::isAngleReadable(double angle, double tolerance) {
    double angleCorrected = getNormalizedAngle(angle);
    if (angleCorrected > M_PI / 2.0 * 3.0 + tolerance || angleCorrected < M_PI / 2.0 + tolerance) {
        return true;
    } else {
        return false;
    }
}

/**
 * Tests if two angels point approximately in the same direction.
 *
 * \param dir1 first direction
 *
 * \param dir2 second direction
 *
 * \param tolerance Tolerance in rad.
 *
 * \retval true The two angles point in the same direction.
 *
 * \retval false The difference between the two angles is at
 * least \c tolerance radians.
 */
bool RMath::isSameDirection(double dir1, double dir2, double tolerance) {
    double diff = fabs(dir1 - dir2);
    if (diff < tolerance || diff > 2*M_PI - tolerance) {
        return true;
    } else {
        return false;
    }
}

/**
 * \return String representing the given number, expressed as fraction (# #/#).
 */
QString RMath::toFractionString(double v, int maxDenominator) {
    int number, numerator, denominator;
    toFraction(v, maxDenominator, number, numerator, denominator);

    if (number==0) {
        return QString("%1/%2").arg(numerator).arg(denominator);
    }
    else {
        if (numerator==0) {
            return QString("%1").arg(number);
        }
        else {
            return QString("%1 %2/%3").arg(number).arg(numerator).arg(denominator);
        }
    }
}

/**
 * \return Representation of the given number as fraction (number numerator/denominator).
 * Rounding occurs to satisfy the use of maxDenominator as maximum value for denominator.
 */
void RMath::toFraction(double v, int maxDenominator, int& number, int& numerator, int& denominator) {
    int in = (int)v;
    number = in;

    if (in==v) {
        number = in;
        numerator = 0;
        denominator = 1;
        return;
    }

    simplify(abs(mround((v-in)*maxDenominator)), maxDenominator, numerator, denominator);
}

/**
 * \return Simlified fraction for the given fraction (numerator/denomiator).
 */
void RMath::simplify(int numerator, int denominator, int& numeratorRes, int& denominatorRes) {
    int g = getGcd(numerator, denominator);
    numeratorRes = numerator/g;
    denominatorRes = denominator/g;
}

/**
 * \return True if the difference between v1 and v2 is less then the
 * given tolerance.
 */
bool RMath::fuzzyCompare(double v1, double v2, double tolerance) {
    return fabs(v1-v2) < tolerance;
}

bool RMath::fuzzyAngleCompare(double v1, double v2, double tolerance) {
    return fabs(getAngleDifference180(v1, v2)) < tolerance;
}

bool RMath::containsFuzzy(const QList<double>& values, double v, double tol) {
    for (int i=0; i<values.length(); i++) {
        if (RMath::fuzzyCompare(v, values[i], tol)) {
            return true;
        }
    }

    return false;
}

/**
 * \return Value given as drawing scale (#:#).
 */
double RMath::parseScale(const QString& scaleString) {
    int i;
//    double d;

    double scale = 1.0;

    QString s = scaleString;
    s.replace("'-", "'");
    s.replace("' -", "'");

    if (s.contains(':') || s.contains('=')) {
        if (s.contains(':')) {
            i = s.indexOf(':');
        }
        else {
            i = s.indexOf('=');
        }

        double n = RMath::eval(s.left(i));
        double d = RMath::eval(s.mid(i+1));
        if (RMath::isSane(n) && RMath::isSane(d) && d>1.0e-6 && n>1.0e-6) {
            scale = n/d;
        }
    }
    else {
        double f = RMath::eval(s);
        scale = f;
    }

    // don't allow scale to be 0 or less or NaN:
    if (scale<1.0e-12 || RMath::isNaN(scale)) {
        scale = 1.0;
    }

    return scale;
}

/**
 * Parses the given string as coordinate.
 *
 * \param relativeZero RVector position of relative zero point.
 * \param str String to parse (e.g. "34,15.6" or "@10,30" or "50<60", ...)
 *
 * \return undefined if the string is not a coordinate, an invalid RVector
 *      if str is an invalid coordinate or the RVector result.
 */
RVector RMath::parseCoordinate(const QString& coordinateString, const RVector& relativeZero) {
    QString str = coordinateString;
    QChar decimalPoint = RSettings::getCharValue("Input/DecimalPoint", '.');
    QChar cartCoordSep = RSettings::getCharValue("Input/CartesianCoordinateSeparator", ',');
    QChar polCoordSep = RSettings::getCharValue("Input/PolarCoordinateSeparator", '<');
    QChar relCoordPre = RSettings::getCharValue( "Input/RelativeCoordinatePrefix", '@');

    if (str.count(cartCoordSep)!=1 && str.count(polCoordSep)!=1) {
        // not a coordinate (not an error, could be another value such as a radius):
        return RVector::nanVector;
    }

    str = str.trimmed();

    if (str.isEmpty()) {
        // empty (not an error):
        return RVector::nanVector;
    }

    bool relative = false;
    if (str[0]==relCoordPre) {
        relative = true;
        str = str.mid(1);
    }

    QStringList sl;
    bool polar = false;
    if (str.count(cartCoordSep)==1) {
        sl = str.split(cartCoordSep);
        polar = false;
    }
    else {
        sl = str.split(polCoordSep);
        polar = true;
    }

    if (sl.length()!=2) {
        // invalid coordinate (error):
        return RVector::invalid;
    }

    // 'fix' decimal point:
    if (decimalPoint!='.') {
        sl[0] = sl[0].replace(decimalPoint, '.');
        sl[1] = sl[1].replace(decimalPoint, '.');
    }

    // evaluate x/y or radius/angle pair:
    double a0 = RMath::eval(sl[0]);
    double a1 = RMath::eval(sl[1]);

    if (isNaN(a0) || isNaN(a1)) {
        // invalid coordinate (error):
        return RVector::invalid;
    }

    RVector pos;
    if (polar) {
        // polar coordinate:
        pos = RVector::createPolar(a0,RMath::deg2rad(a1));
    }
    else {
        // Cartesian coordinate:
        pos = RVector(a0,a1);
    }

    // relative coordinate:
    if (relative) {
        pos = relativeZero + pos;
    }

    return pos;
}

void RMath::getQuadRoots(double p[], double r[][5]) {
    /*
    Array r[3][5] p[5]
    Roots of poly p[0]*x^2 + p[1]*x + p[2]=0
    x=r[1][k] + i r[2][k] k=1,2
    */
    double b,c,d;
    b=-p[1]/(2.0*p[0]);
    c=p[2]/p[0];
    d=b*b-c;
    if(d>=0.0) {
        if(b>0.0)
            b=(r[1][2]=(sqrt(d)+b));
        else
            b=(r[1][2]=(-sqrt(d)+b));
        r[1][1]=c/b;
        r[2][1]=(r[2][2]=0.0);
    }
    else {
        d=(r[2][1]=sqrt(-d));
        r[2][2]=-d;
        r[1][1]=(r[1][2]=b);
    }
}

void RMath::getCubicRoots(double p[], double r[][5]) {
    /*
    Array r[3][5] p[5]
    Roots of poly p[0]*x^3 + p[1]*x^2 + p[2]*x + p[3] = 0
    x=r[1][k] + i r[2][k] k=1,...,3
    Assumes 0<arctan(x)<pi/2 for x>0
    */
    double s,t,b,c,d;
    int k;
    if(p[0]!=1.0)
    {
        for(k=1;k<4;k++)
            p[k]=p[k]/p[0];
        p[0]=1.0;
    }
    s=p[1]/3.0;
    t=s*p[1];
    b=0.5*(s*(t/1.5-p[2])+p[3]);
    t=(t-p[2])/3.0;
    c=t*t*t;
    d=b*b-c;
    if(d>=0.0) {
        d=pow((sqrt(d)+fabs(b)),1.0/3.0);
        if(d!=0.0) {
            if(b>0.0)
                b=-d;
            else
                b=d;
            c=t/b;
        }
        d=r[2][2]=sqrt(0.75)*(b-c);
        b=b+c;
        c=r[1][2]=-0.5*b-s;
        if((b>0.0 && s<=0.0) || (b<0.0 && s>0.0)) {
            r[1][1]=c;
            r[2][1]=-d;
            r[1][3]=b-s;
            r[2][3]=0.0;
        }
        else {
            r[1][1]=b-s;
            r[2][1]=0.0;
            r[1][3]=c;
            r[2][3]=-d;
        }

    } /* end 2 equal or complex roots */
    else {
        if(b==0.0)
            d=atan(1.0)/1.5;
        else
            d=atan(sqrt(-d)/fabs(b))/3.0;
        if(b<0.0)
            b=2.0*sqrt(t);
        else
            b=-2.0*sqrt(t);
        c=cos(d)*b;
        t=-sqrt(0.75)*sin(d)*b-0.5*c;
        d=-t-c-s;
        c=c-s;
        t=t-s;
        if(fabs(c)>fabs(t)) {
            r[1][3]=c;
        }
        else {
            r[1][3]=t;
            t=c;
        }
        if(fabs(d)>fabs(t)) {
            r[1][2]=d;
        }
        else {
            r[1][2]=t;
            t=d;
        }
        r[1][1]=t;
        for(k=1;k<4;k++)
            r[2][k]=0.0;
    }
    return;
}

void RMath::getBiQuadRoots(double p[],double r[][5]) {
    /*
    Array r[3][5] p[5]
    Roots of poly p[0]*x^4 + p[1]*x^3 + p[2]*x^2 + p[3]*x + p[4] = 0
    x=r[1][k] + i r[2][k] k=1,...,4
    */
    double a,b,c,d,e;
    int k,j;
    if(p[0] != 1.0)
    {
        for(k=1;k<5;k++)
            p[k]=p[k]/p[0];
        p[0]=1.0;
    }
    e=0.25*p[1];
    b=2.0*e;
    c=b*b;
    d=0.75*c;
    b=p[3]+b*(c-p[2]);
    a=p[2]-d;
    c=p[4]+e*(e*a-p[3]);
    a=a-d;
    p[1]=0.5*a;
    p[2]=(p[1]*p[1]-c)*0.25;
    p[3]=b*b/(-64.0);
    if(p[3]<0.0)
    {
        getCubicRoots(p,r);
        for(k=1;k<4;k++)
        {
            if(r[2][k]==0.0 && r[1][k]>0.0)
            {
                d=r[1][k]*4.0;
                a=a+d;
                if(a>=0.0 && b>=0.0)
                    p[1]=sqrt(d);
                else if(a<=0.0 && b<=0.0)
                    p[1]=sqrt(d);
                else
                    p[1]=-sqrt(d);
                b=0.5*(a+b/p[1]);
                goto QUAD;
            }

        }

    }
    if(p[2]<0.0)
    {
        b=sqrt(c);
        d=b+b-a;
        p[1]=0.0;
        if(d>0.0)
            p[1]=sqrt(d);
    }
    else
    {
        if(p[1]>0.0)
            b=sqrt(p[2])*2.0+p[1];
        else
            b=-sqrt(p[2])*2.0+p[1];
        if(b!=0.0)
        {
            p[1]=0.0;
        }
        else
        {
            for(k=1;k<5;k++)
            {
                r[1][k]=-e;
                r[2][k]=0.0;
            }
            goto END;
        }
    }
QUAD:
    p[2]=c/b;
    getQuadRoots(p,r);
    for(k=1;k<3;k++)
        for(j=1;j<3;j++)
            r[j][k+2]=r[j][k];
    p[1]=-p[1];
    p[2]=b;
    getQuadRoots(p,r);
    for(k=1;k<5;k++)
        r[1][k]=r[1][k]-e;
END:
    return;
}
