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
#include "RSingleton.h"

QMap<QString, RSingleton*> RSingleton::map;

RSingleton::RSingleton() {
    static bool called = false;
        if (!called) {
//            QObject::connect(qApp, SIGNAL(aboutToQuit()), &cleaner,
//                             SLOT(cleanUp()));
            called = true;
        }
    }


void RSingleton::cleanUp() {
    QMapIterator<QString, RSingleton*> i(RSingleton::map);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }
    RSingleton::map.clear();
}
