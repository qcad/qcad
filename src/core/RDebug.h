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

#ifndef RDEBUG_H
#define RDEBUG_H

#include "core_global.h"

#include <fstream>
#include <ostream>
#include <stdarg.h>
#include <stdio.h>

#include <QString>
#include <QTime>
#include <QMap>
#include <QFile>
#include <QMetaType>

#if defined(Q_OS_MAC) && !defined(Q_OS_IOS)
#include <CoreServices/CoreServices.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#undef check
#endif

#if !defined(Q_OS_WIN) && !defined(Q_OS_ANDROID)
#include <execinfo.h>
#endif

#ifndef RDEFAULT_QSTRING
#define RDEFAULT_QSTRING QString()
#endif

/**
 * This class provides some static methods for printing debugging information to
 * stderr. The methods accept a format string and parameters in the same way
 * as the printf functions from standard C.
 *
 * Messages can be logged with different priorities.
 *
 * While there is no restriction as to what is logged, it is a good idea to
 * log the class name and function name first.
 *
 * \code
 * // output for development:
 * qDebug("RMyClass::myFunction: i = %d", i);
 * // warnings ("this should not happen under normal cicumstances"):
 * qWarning("RMyClass::myFunction: cannot open file '%s'", fileName);
 * // indication for a bug in the application:
 * qWarning("RMyClass::myFunction: parent is NULL. Aborting.");
 * \endcode
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RDebug {
public:
    static void printBacktrace(const QString& prefix = RDEFAULT_QSTRING);

    /**
     * Starts a timer with the given ID.
     */
    static void startTimer(int id=0);

    /**
     * Stops the timer with the given ID and prints the given message together 
     * with the time that has elapsed.
     */
    static uint stopTimer(int id, const QString& msg, uint msThreshold = 0);

    /**
     * Stops the timer with ID 0 and prints the given message together 
     * with the time that has elapsed.
     */
    static uint stopTimer(const QString& msg) {
        return stopTimer(0, msg);
    }

    static void timeStamp();

    static void hexDump(const QString& str);

    static void incCounter(const QString& id = RDEFAULT_QSTRING);
    static void decCounter(const QString& id = RDEFAULT_QSTRING);
    static int getCounter(const QString& id = RDEFAULT_QSTRING);
    static void printCounter(const QString& id = RDEFAULT_QSTRING);
    static void printCounters();

    static void setPrefix(const QString& p) {
        prefix = p;
    }
    static QString getPrefix() {
        return prefix;
    }

private:
#if defined(Q_OS_MAC) && !defined(Q_OS_IOS)
    static QMap<int, uint64_t> timerMac;
#else
    static QMap<int, QTime> timer;
#endif
    static QMap<QString, int> counter;
    static QString prefix;
};

Q_DECLARE_METATYPE(RDebug*)

#endif
