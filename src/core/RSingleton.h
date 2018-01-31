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

#ifndef RSINGLETON_H_
#define RSINGLETON_H_

#include "core_global.h"

#include <QApplication>
#include <QObject>
#include <QMap>
#include <QString>
#include <typeinfo>
#include "RDebug.h"

/**
 * \ingroup core
 */
class QCADCORE_EXPORT RSingleton {
public:
    virtual ~RSingleton() {
    }
    template<class Derived>
        static Derived& getInstance();
        static void cleanUp();

protected:
    RSingleton();

private:
    static QMap<QString, RSingleton*> map;
};

Q_DECLARE_METATYPE(RSingleton*)

template<class Derived>
Derived& RSingleton::getInstance() {
    if (!map.contains(typeid(Derived).name())) {
        map[typeid(Derived).name()] = new Derived;
    }
    Derived* d = dynamic_cast<Derived*> (map[typeid(Derived).name()]);
    if (d == NULL) {
        Q_ASSERT("RSingleton::getInstance(): \"Derived\" in not a singleton");
    }
    return *d;
}

#endif /* RSINGLETON_H_ */
