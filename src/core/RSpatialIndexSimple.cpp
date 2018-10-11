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
#include "RSpatialIndexSimple.h"
#include "RBox.h"

RSpatialIndexSimple::RSpatialIndexSimple() {
}

RSpatialIndexSimple::~RSpatialIndexSimple() {
}

RSpatialIndex* RSpatialIndexSimple::create() {
    return new RSpatialIndexSimple();
}

void RSpatialIndexSimple::clear() {
    si.clear();
}

void RSpatialIndexSimple::addToIndex(
    int id, int pos,
    double x1, double y1, double z1,
    double x2, double y2, double z2) {
    
    Q_ASSERT(si[id].size()==pos);
    si[id].insert(pos, RBox(RVector(x1,y1,z1), RVector(x2,y2,z2)));
    //si.insert(id, RBox(RVector(x1,y1,z1), RVector(x2,y2,z2)));
}

//void RSpatialIndexSimple::removeFromIndex(int id) {
    /*
    QList<RBox> keys = si.keys(id);
    for (int i = 0; i < keys.size(); ++i) {
        si.remove(keys.at(i), id);
    }
    */
//    si.remove(id);
//}

bool RSpatialIndexSimple::removeFromIndex(
        int id, int pos,
        double x1, double y1, double z1,
        double x2, double y2, double z2) {

    Q_UNUSED(id)
    Q_UNUSED(pos)
    Q_UNUSED(x1)
    Q_UNUSED(y1)
    Q_UNUSED(z1)
    Q_UNUSED(x2)
    Q_UNUSED(y2)
    Q_UNUSED(z2)
    
    qFatal("not implemented");
    //RBox box(RVector(x1,y1,z1),RVector(x2,y2,z2));
    //si.remove(id);
    return true;
}

bool RSpatialIndexSimple::removeFromIndex(int id, const QList<RBox>& bb) {
    Q_UNUSED(bb)

    si.remove(id);
    return true;
}

QMap<int, QSet<int> > RSpatialIndexSimple::queryIntersected(
    double x1, double y1, double z1,
    double x2, double y2, double z2,
    RSpatialIndexVisitor* /*dataVisitor*/) {
    
    RBox box(RVector(x1,y1,z1),RVector(x2,y2,z2));
    QMap<int, QSet<int> > res;
    QMap<int, QList<RBox> >::iterator it;
    for (it=si.begin(); it!=si.end(); it++) {
        QList<RBox> bbs = it.value();
        for (int i=0; i<bbs.size(); i++) {
            if (box.intersects(bbs.at(i))) {
                //res.insert(it.key());
                res[it.key()].insert(i);
            }
        }
    }

    return res;
}

QMap<int, QSet<int> > RSpatialIndexSimple::queryContained(
    double x1, double y1, double z1,
    double x2, double y2, double z2,
    RSpatialIndexVisitor* /*dataVisitor*/) {

    RBox box(RVector(x1,y1,z1),RVector(x2,y2,z2));
    QMap<int, QSet<int> > res;
    QMap<int, QList<RBox> >::iterator it;
    for (it=si.begin(); it!=si.end(); it++) {
        QList<RBox> bbs = it.value();
        for (int i=0; i<bbs.size(); i++) {
            if (box.contains(bbs.at(i))) {
                //res.insert(it.key());
                res[it.key()].insert(i);
            }
        }
    }

    return res;
}

QMap<int, QSet<int> > RSpatialIndexSimple::queryNearestNeighbor(
    uint k,
    double x, double y, double z,
    RSpatialIndexVisitor* dataVisitor) {

    Q_UNUSED(k)
    Q_UNUSED(x)
    Q_UNUSED(y)
    Q_UNUSED(z)
    Q_UNUSED(dataVisitor)

    qFatal("not implemented");
    return QMap<int, QSet<int> >(); 
}
