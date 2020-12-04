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
#include "RPropertyChange.h"
#include "RMetaTypes.h"

RPropertyChange::RPropertyChange(RPropertyTypeId propertyTypeId, QVariant oldValue, QVariant newValue) :
    propertyTypeId(propertyTypeId) {

    if (oldValue.type()==QVariant::UserType &&
        (oldValue.canConvert<QList<double> >() || !oldValue.isValid()) &&
        (newValue.canConvert<QList<double> >() || !newValue.isValid())) {

        QList<double> oldList;
        if (oldValue.isValid()) {
            oldList = oldValue.value<QList<double> >();
        }
        QList<double> newList;
        if (newValue.isValid()) {
            newList = newValue.value<QList<double> >();
        }

        QList<QPair<int, double> > oldCompact;
        QList<QPair<int, double> > newCompact;

        // entries were changed only:
        if (oldList.size() == newList.size()) {
            for (int i=0; i<oldList.size(); i++) {
                if (oldList.at(i) != newList.at(i)) {
                    oldCompact.append(QPair<int, double>(i, oldList.at(i)));
                    newCompact.append(QPair<int, double>(i, newList.at(i)));
                }
            }
        }

        // entries were appended and possibly changed:
        else if (oldList.size() < newList.size()) {
            for (int i=0; i<newList.size(); i++) {
                if (i>=oldList.size()) {
                    oldCompact.append(QPair<int, double>(i, RNANDOUBLE));
                    newCompact.append(QPair<int, double>(i, newList.at(i)));
                }
                else if (oldList.at(i) != newList.at(i)) {
                    oldCompact.append(QPair<int, double>(i, oldList.at(i)));
                    newCompact.append(QPair<int, double>(i, newList.at(i)));
                }
            }
        }

        // entries were removed and possibly changed:
        else if (oldList.size() > newList.size()) {
            for (int i=0; i<oldList.size(); i++) {
                if (i>=newList.size()) {
                    oldCompact.append(QPair<int, double>(i, oldList.at(i)));
                    newCompact.append(QPair<int, double>(i, RNANDOUBLE));
                }
                else if (oldList.at(i) != newList.at(i)) {
                    oldCompact.append(QPair<int, double>(i, oldList.at(i)));
                    newCompact.append(QPair<int, double>(i, newList.at(i)));
                }
            }
        }

        this->oldValue.setValue(oldCompact);
        this->newValue.setValue(newCompact);

        return;
    }

    else {
        if (oldValue.type()!=newValue.type() && oldValue.isValid() && newValue.isValid()) {
            qWarning() << "old and new property values for property " << propertyTypeId.getPropertyTitle() << " have different types:" << oldValue.typeName() << " vs. " << newValue.typeName();
        }
        this->oldValue = oldValue;
        this->newValue = newValue;
        return;
    }
}

QDebug operator<<(QDebug dbg, const RPropertyChange& p) {
    dbg.nospace()
        << "RPropertyChange("
        << p.propertyTypeId << ", ";
    if (p.oldValue.canConvert<QList<QPair<int, double> > >() &&
        p.newValue.canConvert<QList<QPair<int, double> > >()) {

        dbg.nospace() << "QList(";

        QList<QPair<int, double> > oldList = p.oldValue.value<QList<QPair<int, double> > >();
        QList<QPair<int, double> > newList = p.newValue.value<QList<QPair<int, double> > >();

        for (int i=0; i<qMax(oldList.size(), newList.size()); i++) {
            if (i>=oldList.size()) {
                dbg.nospace() << "[no entry] -> ";
            }
            else {
                dbg.nospace() << "[" << oldList.at(i).first << "," << oldList.at(i).second << "] -> ";
            }

            if (i>=newList.size()) {
                dbg.nospace() << "[no entry], ";
            }
            else {
                dbg.nospace() << "[" << newList.at(i).first << "," << newList.at(i).second << "], ";
            }
        }

        dbg.nospace() << ")";
    }
    else {
        dbg.nospace()
            << p.oldValue << " -> "
            << p.newValue;
    }

    dbg.nospace() << ")";

    return dbg.space();
}
