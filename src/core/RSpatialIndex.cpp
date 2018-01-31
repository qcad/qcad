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
#include "RSpatialIndex.h"

void RSpatialIndexDebugVisitor::visitData(
    int id,
    int pos,
    double x1, double y1, double z1,
    double x2, double y2, double z2) {

    //dbg.nospace()
    qDebug()
             << "id: " << id
             << " pos: " << pos
             << " box: ("
             << x1 << ", " << y1 << ", " << z1
             << " / "
             << x2 << ", " << y2 << ", " << z2
             << ")";

    QPair<int, int> p(id, pos);
    Q_ASSERT(!matches.contains(p));
    matches.append(p);
}

qint64 RSpatialIndex::getSIId(int id, int pos) {
    return ((qint64)pos << 32) + id;
}

int RSpatialIndex::getId(qint64 siid) {
    return (int)(siid & Q_INT64_C(0x00000000FFFFFFFF));
}

int RSpatialIndex::getPos(qint64 siid) {
    return (int)((siid & Q_INT64_C(0xFFFFFFFF00000000)) >> 32);
}

void RSpatialIndex::bulkLoad(const QList<int>& ids, const QList<QList<RBox> >& bbs) {
    for (int i=0; i<ids.length() && i<bbs.length(); i++) {
        addToIndex(ids[i], bbs[i]);
    }
}

void RSpatialIndex::bulkLoadSimple(const QList<int>& ids, const QList<RBox>& bbs) {
    QList<QList<RBox> > list;
    for (int i=0; i<bbs.length(); i++) {
        list.append(QList<RBox>() << bbs[i]);
    }
    bulkLoad(ids, list);
}

void RSpatialIndex::addToIndex(int id, const QList<RBox>& bbs) {
    for (int pos = 0; pos < bbs.size(); ++pos) {
        addToIndex(
            id, pos,
            bbs[pos]
        );
    }
}

void RSpatialIndex::addToIndex(int id, int pos, const RBox& bb) {
    addToIndex(
        id, pos,
        bb.c1.x, bb.c1.y, bb.c1.z,
        bb.c2.x, bb.c2.y, bb.c2.z
    );
}

bool RSpatialIndex::removeFromIndex(int id, int pos, const RBox& bb) {
    return removeFromIndex(
        id, pos,
        bb.c1.x, bb.c1.y, bb.c1.z,
        bb.c2.x, bb.c2.y, bb.c2.z
    );
}

bool RSpatialIndex::removeFromIndex(int id, const QList<RBox>& bb) {
    bool ok = true;

    for (int pos = 0; pos < bb.size(); ++pos) {
        ok = removeFromIndex(id, pos, bb.at(pos)) && ok;
    }

    return ok;

    //if (!ok) {
        // TODO:
        //removeFromIndex(id);
    //}
}

QMap<int, QSet<int> > RSpatialIndex::queryIntersected(const RBox& b,
    RSpatialIndexVisitor* dataVisitor) {

    return queryIntersected(
        b.c1.x, b.c1.y, b.c1.z,
        b.c2.x, b.c2.y, b.c2.z,
        dataVisitor
    );
}

QMap<int, QSet<int> > RSpatialIndex::queryContained(const RBox& b,
    RSpatialIndexVisitor* dataVisitor) {

    return queryContained(
        b.c1.x, b.c1.y, b.c1.z,
        b.c2.x, b.c2.y, b.c2.z,
        dataVisitor
    );
}

/**
 * Convenience implementation for scripts.
 */
QPair<int, int> RSpatialIndex::queryNearestNeighbor(double x, double y, double z) {
    QMap<int, QSet<int> > res = queryNearestNeighbor(1, x, y, z);
    QList<int> keys = res.keys();
    if (keys.length()<1) {
        qWarning() << "RSpatialIndex::queryNearestNeighbor: no result";
        return QPair<int, int>(-1,-1);
    }
    return QPair<int, int>(keys.at(0), res[keys.at(0)].toList().first());
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RSpatialIndex& si) {
    dbg.nospace() << "\nRSpatialIndex(";

    RSpatialIndexDebugVisitor v(dbg);
    QMap<int, QSet<int> > result = si.queryContained(
        -RMAXDOUBLE, -RMAXDOUBLE, -RMAXDOUBLE,
        RMAXDOUBLE, RMAXDOUBLE, RMAXDOUBLE, &v);

    /*
    QSetIterator<int> i(result);
    while (i.hasNext()) {
        dbg.nospace() << i.next() << ", ";
    }
    */

    dbg.nospace() << "\ntotal entries: " << v.matches.size() << ")";
    return dbg.space();
}

