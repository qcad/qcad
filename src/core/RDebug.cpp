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
#include <stdlib.h>

#include <QDebug>
#include <QStringList>

#include "RDebug.h"

//FILE* RDebug::stream=stderr;

#if defined(Q_OS_MAC) && !defined(Q_OS_IOS)
QMap<int, uint64_t> RDebug::timerMac;
#else
QMap<int, QTime> RDebug::timer;
#endif
QMap<QString, int> RDebug::counter;
QString RDebug::prefix;

void RDebug::printBacktrace(const QString& prefix) {
#if !defined(Q_OS_WIN) && !defined(Q_OS_ANDROID)
    void *array[20];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace(array, 20);
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
#if defined(Q_OS_MAC) && !defined(Q_OS_IOS)
    timerMac[id] = mach_absolute_time();
#else
    timer[id].start();
#endif
}


uint RDebug::stopTimer(int id, const QString& msg, uint msThreshold) {
#if defined(Q_OS_MAC) && !defined(Q_OS_IOS)
    Nanoseconds elapsedNano;
    uint64_t end = mach_absolute_time();
    uint64_t elapsed = end - timerMac[id];
    elapsedNano = AbsoluteToNanoseconds( *(AbsoluteTime *) &elapsed );
    uint64_t t = (* (uint64_t *) &elapsedNano);
    timerMac.remove(id);
#else
    unsigned long long t = timer[id].elapsed() * 1000000;
    timer.remove(id);
#endif

    if (t/1000000>=msThreshold) {
        qDebug() << "TIMER: " << t << "ns (" << t/1000000 << "ms )" << " - " << msg;
    }
    return t;
}

void RDebug::timeStamp() {
    qDebug() << QTime::currentTime().toString("HH:mm:ss:zzz");
}

void RDebug::hexDump(const QString& str) {
    QByteArray ba = str.toUtf8();
    for (int i=0; i<ba.length(); i++) {
        qDebug() << QString("0x%1 (%2)").arg((int)ba.at(i), 0, 16).arg(ba.at(i));
    }
}

void RDebug::incCounter(const QString& id) {
    if (!counter.contains(id)) {
        counter[id] = 0;
    }
    //qDebug() << id << "+";
    counter[id]++;
}

void RDebug::decCounter(const QString& id) {
    if (!counter.contains(id)) {
        counter[id] = 0;
    }
    //qDebug() << id << "-";
    counter[id]--;
}

int RDebug::getCounter(const QString& id) {
    if (!counter.contains(id)) {
        return 0;
    }
    return counter[id];
}

void RDebug::printCounter(const QString& id) {
    if (!counter.contains(id)) {
        return;
    }
    qDebug() << "counter: " << id << ": " << counter[id];
}

void RDebug::printCounters() {
    QStringList keys = counter.keys();
    for (int i=0; i<keys.length(); i++) {
        qDebug() << "counter: " << keys[i] << ": " << counter[keys[i]];
    }
}
