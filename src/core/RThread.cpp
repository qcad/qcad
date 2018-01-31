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
#include <QDebug>

#if !defined(_MSC_VER) || _MSC_VER > 1500
#include <stdint.h>
#endif
#include "RThread.h"

RThread::RThread(QObject * parent) :
    QThread(parent) {
}

RThread::~RThread() {
}

void RThread::start() {
    QThread::start();
}

void RThread::run() {
    qDebug() << "RThread::run: " << RThread::currentThreadAddress();

    emit dorun();
    //  QThread::run();
//      int i=0;
//      while (i<10000000) {
//          qDebug() << "RThread::run: " << i;
//          ++i;
//      }
    //  exec();
}

void RThread::yieldCurrentThread() {
    QThread::yieldCurrentThread();
}

QString RThread::currentThreadAddress() {
    return QString("0x%1").arg((intptr_t)QThread::currentThread(), 0, 16);
}

QString RThread::currentThreadName() {
    if (QThread::currentThread()==NULL) {
        return "NULL";
    }
    return QThread::currentThread()->objectName();
}

RThread* RThread::currentThread() {
    return qobject_cast<RThread*>(QThread::currentThread());
}
