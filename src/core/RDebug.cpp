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
#include <stdlib.h>

#include <QDebug>

#include "RDebug.h"

//FILE* RDebug::stream=stderr;

#ifdef Q_OS_MAC
QMap<int, uint64_t> RDebug::timerMac;
#else
QMap<int, QTime> RDebug::timer;
#endif

void RDebug::printBacktrace(const QString& prefix) {
#if !defined(Q_OS_WIN32)
    void *array[10];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace(array, 10);
    strings = backtrace_symbols(array, size);

    qDebug("Obtained %zd stack frames.\n", size);

    for(i = 0; i < size; i++) {
        qDebug("%s%s\n", (const char*)prefix.toUtf8(), strings[i]);
    }

    free(strings);
#else
    Q_UNUSED(prefix)
#endif
}

void RDebug::startTimer(int id) {
#ifdef Q_OS_MAC
    timerMac[id] = mach_absolute_time();
#else
    timer[id].start();
#endif
}


int RDebug::stopTimer(int id, const QString& msg) {
#ifdef Q_OS_MAC
    Nanoseconds elapsedNano;
    uint64_t end = mach_absolute_time();
    uint64_t elapsed = end - timerMac[id];
    elapsedNano = AbsoluteToNanoseconds( *(AbsoluteTime *) &elapsed );
    int t = (unsigned int)((* (uint64_t *) &elapsedNano) / 1000000);
    timerMac.remove(id);
#else
    int t = timer[id].elapsed();
    timer.remove(id);
#endif
    /*
    va_list varg;
    va_start(varg, format);
    fprintf(stream, "TIMER: %d ms ", t);
    printV(format, varg);
    va_end(varg);
    */
    qDebug() << "TIMER: " << t << "ms - " << msg;
    return t;
}

void RDebug::hexDump(const QString& str) {
    QByteArray ba = str.toUtf8();
    for (int i=0; i<ba.length(); i++) {
        qDebug() << QString("0x%1 (%2)").arg((int)ba.at(i), 0, 16).arg(ba.at(i));
    }
}
