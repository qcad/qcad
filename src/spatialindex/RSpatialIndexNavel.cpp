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
#include "RSpatialIndexNavel.h"
#include "RDebug.h"


#ifdef _MSC_VER
#define RSIMAXDOUBLE 1e300
#define RSIMINDOUBLE -1e300
#else
#define RSIMAXDOUBLE std::numeric_limits<double>::max()
#define RSIMINDOUBLE -std::numeric_limits<double>::max()
#endif



/**
 * Internal.
 */
RSpatialIndexNavel::RSiRegion::RSiRegion(
    double x1, double y1, double z1,
    double x2, double y2, double z2) {

    double p1[] = { 
        std::min(x1, x2), 
        std::min(y1, y2), 
        std::min(z1, z2) 
    };
    double p2[] = { 
        std::max(x1, x2), 
        std::max(y1, y2), 
        std::max(z1, z2) 
    };

    (*(SpatialIndex::Region*)this) = SpatialIndex::Region(p1, p2, 3);
}


/**
 * Internal.
 */
RSpatialIndexNavel::RSiPoint::RSiPoint(double x, double y, double z) {

    double p[] = {
        x,
        y,
        z
    };

    (*(SpatialIndex::Point*)this) = SpatialIndex::Point(p, 3);
}



/**
 * Creates a 2d spatial index in memory (r-tree, star shape).
 */
RSpatialIndexNavel::RSpatialIndexNavel() {
    RDebug::incCounter("RSpatialIndexNavel");
    init();
}



RSpatialIndexNavel::~RSpatialIndexNavel() {
    RDebug::decCounter("RSpatialIndexNavel");
    uninit();
}



//int RSpatialIndexNavel::dataToInt(const uint8_t* data) {
//    return (data[0] << 24 +
//            data[1] << 16 +
//            data[2] << 8 +
//            data[3] << 0);
//}

//void RSpatialIndexNavel::intToData(int i, uint8_t* data) {
//    data[0] = (i&0xFF000000) >> 24;
//    data[1] = (i&0x00FF0000) >> 16;
//    data[2] = (i&0x0000FF00) >> 8;
//    data[3] = (i&0x000000FF) >> 0;
//}


void RSpatialIndexNavel::init() {
    buff = SpatialIndex::StorageManager::createNewMemoryStorageManager();

    SpatialIndex::id_type indexIdentifier;
    int dimension = 3;

    // 0.7: results in much slower deletes
    // 0.1: crashes randomly with 'InvalidPageException: Unknown page id ...'
    // 0.2: seems to work reasonably well
    double minimumLoad = 0.2;
    // 100: slower for inserts
    size_t indexCapacity = 50;
    // 100: slower for inserts
    size_t leafCapacity = 50;
    tree = SpatialIndex::RTree::createNewRTree(
        *buff,
        minimumLoad,
        indexCapacity,
        leafCapacity,
        dimension,
        SpatialIndex::RTree::RV_RSTAR,
        indexIdentifier
    );
    //sidCounter = 0;
}



void RSpatialIndexNavel::uninit() {
    delete tree;
    delete buff;
    tree = NULL;
    buff = NULL;
    //sidCounter = 0;
}

RSpatialIndex* RSpatialIndexNavel::create() {
    return new RSpatialIndexNavel();
}

void RSpatialIndexNavel::clear() {
    uninit();
    init();
}

void RSpatialIndexNavel::bulkLoad(const QList<int>& ids, const QList<QList<RBox> >& bbs) {
    if (ids.isEmpty() || bbs.isEmpty()) {
        clear();
        return;
    }

    try {
        RSiDataStream stream(ids, bbs);
        uninit();

        buff = SpatialIndex::StorageManager::createNewMemoryStorageManager();
        SpatialIndex::id_type indexIdentifier;
        tree = SpatialIndex::RTree::createAndBulkLoadNewRTree(
                SpatialIndex::RTree::BLM_STR,
                stream,
                *buff,
                0.2, 50, 50,
                3,
                SpatialIndex::RTree::RV_RSTAR,
                indexIdentifier
        );
    }
    catch(Tools::IllegalArgumentException e) {
        qWarning() << "caught exception in spatial index: " << e.what().c_str();
    }
}
    
/**
 * Adds an item to the index.
 *
 * \param id ID of the item.
 * \param x1 lower value of the first dimension.
 * \param y1 lower value of the second dimension.
 * \param z1 lower value of the third dimension.
 * \param x2 higher value of the first dimension.
 * \param y2 higher value of the second dimension.
 * \param z2 higher value of the third dimension.
 * \param dataLength Legth of the data in bytes or 0.
 * \param data Pointer to the data associated with the item. The
 *      index makes a deep copy of the data, the caller is responsible 
 *      for deleting the data. NULL indicates that the item data is stored
 *      externally (e.g. in a map or list).
 */
void RSpatialIndexNavel::addToIndex(
    int id, int pos,
    double x1, double y1, double z1,
    double x2, double y2, double z2) {

    //qDebug() << "RSpatialIndexNavel::addToIndex: id: " << id << ", pos: " << pos << ", " << x1 << "," << y1 << "/" << x2 << "," << y2;

    //qDebug() << "\tbefore: " << *this;

    if (RMath::isNaN(x1) || RMath::isNaN(y1) || RMath::isNaN(z1) ||
            RMath::isNaN(x2) || RMath::isNaN(y2) || RMath::isNaN(z2)) {

        qWarning() << "trying to add NaN values to spatial index";
        return;
    }

    addToIndex(
        id, pos,
        RSpatialIndexNavel::RSiRegion(
                    qMin(x1, x2), qMin(y1, y2), qMin(z1, z2),
                    qMax(x1, x2), qMax(y1, y2), qMax(z1, z2))
        //dataLength,
        //data
    );

    //qDebug() << "\tafter: " << *this << "\n\n";
}

void RSpatialIndexNavel::addToIndex(int id, int pos, const RBox& bb) {
    RSpatialIndex::addToIndex(id, pos, bb);
}

/**
 * Internal.
 */
void RSpatialIndexNavel::addToIndex(
    int id, int pos,
    const RSiRegion &region, size_t dataLength, const uint8_t *data) {

//    sidCounter++;

//    sidToId.insert(sidCounter, id);
//    if (idToSid.contains(id)) {
//        idToSid[id].append(sidCounter);
//    }
//    else {
//        idToSid.insert(id, QList<int>() << sidCounter);
//    }

    //RDebug::startTimer(16);
    tree->insertData(dataLength, data, region, RSpatialIndex::getSIId(id, pos));
    //RDebug::stopTimer(16, "insert data");
}

bool RSpatialIndexNavel::removeFromIndex(int id, int pos, const RBox &bb) {
    return RSpatialIndex::removeFromIndex(id, pos, bb);
}

bool RSpatialIndexNavel::removeFromIndex(int id, const QList<RBox>& bb) {
    //bool ok = true;

//    QList<int> sids = idToSid.value(id);
//    qDebug() << "bb.size(): " << bb.size();
//    qDebug() << "sids.size(): " << sids.size();
//    if (bb.size()!=sids.size()) {
//        qWarning() << "RSpatialIndexNavel::removeFromIndex: no remove...";
//        return;
//    }

    //Q_ASSERT(bb.size()==sids.size());

    bool ok = true;
    for (int pos = 0; pos < bb.size(); ++pos) {
        ok = removeFromIndex(id, pos, bb[pos]) && ok;
    }
    //idToSid.remove(id);

    //if (!ok) {
        // TODO:
        //removeFromIndex(id);
    //}

    return ok;
}

bool RSpatialIndexNavel::removeFromIndex(
        int id, int pos,
        double x1, double y1, double z1,
        double x2, double y2, double z2) {

    //RDebug::startTimer(4);
    //QList<int> sids = idToSid.value(id);
    //RDebug::stopTimer(4, "removeFromIndex: 001");

    double p1[] = { qMin(x1, x2), qMin(y1, y2), qMin(z1, z2) };
    double p2[] = { qMax(x1, x2), qMax(y1, y2), qMax(z1, z2) };
    SpatialIndex::Region r(p1, p2, 3);
    //for (int i=0; i<sids.size(); i++) {
        //qDebug() << "RSpatialIndexNavel::removeFromIndex: " << id << " / " << pos;
        //RDebug::startTimer(4);
        if (tree->deleteData(r, RSpatialIndex::getSIId(id, pos))) {
            //RDebug::stopTimer(4, "removeFromIndex: 002");
            //RDebug::stopTimer(4, "RSpatialIndexNavel::removeFromIndex");
            return true;
        }
    //}

    //RDebug::printBacktrace();
//    qWarning() << QString(
//                      "RSpatialIndexNavel::removeFromIndex: "
//                      "entry not found, id: %1, pos: %2, %3,%4,%5 / %6,%7,%8")
//                  .arg(id).arg(pos)
//                  .arg(x1) .arg(y1) .arg(z1)
//                  .arg(x2) .arg(y2) .arg(z2);
    // TODO: call removeFromIndex with id (inefficient?)
    //qDebug() << "spatial index: " << *this;
    //Q_ASSERT(false);

    return false;

    /*
    bool ret = false;
 
    RSiGetRegionVisitor rv(id);
    queryContained(
                qMin(x1, x2)-RS::PointTolerance,
                qMin(y1, y2)-RS::PointTolerance,
                qMin(z1, z2)-RS::PointTolerance,
                qMax(x1, x2)+RS::PointTolerance,
                qMax(y1, y2)+RS::PointTolerance,
                qMax(z1, z2)+RS::PointTolerance,
                &rv);
 
    if (rv.found) {
        if (tree->deleteData(rv.region, id)) {
            ret = true;
        }
    }
 
    if (!ret) {
        qWarning() << QString(
                          "RSpatialIndexNavel::removeFromIndex: "
                          "entry %1 found, id: %2, %3,%4,%5 / %6,%7,%8")
                      .arg(ret ? "" : "NOT")
                      .arg(id)
                      .arg(x1) .arg(y1) .arg(z1)
                      .arg(x2) .arg(y2) .arg(z2);
    }
 //   qWarning() << "RSpatialIndexNavel::removeFromIndex: "
 //                 << *this;
 
    return false;
    */
}

/**
 * Removes the item with the given ID from this spatial index.
 */
//void RSpatialIndexNavel::removeFromIndex(int id) {
//    QList<int> sids = idToSid.value(id);
//    for (int i=0; i<sids.size(); i++) {
//        RSiGetRegionVisitor v(sids.at(i));
//        QSet<int> res =
//                queryIntersected(
//                    RSIMINDOUBLE, RSIMINDOUBLE, RSIMINDOUBLE,
//                    RSIMAXDOUBLE, RSIMAXDOUBLE, RSIMAXDOUBLE,
//                    &v
//                    );

//        if (v.found) {
//            tree->deleteData(v.region, id);
//        }
//    }
//}



QMap<int, QSet<int> > RSpatialIndexNavel::queryIntersected(
    double x1, double y1, double z1,
    double x2, double y2, double z2,
    RSpatialIndexVisitor* dataVisitor) {

    return queryIntersected(
        RSpatialIndexNavel::RSiRegion(x1,y1,z1, x2,y2,z2), 
        dataVisitor
    );
}



/**
 * Internal.
 */
QMap<int, QSet<int> > RSpatialIndexNavel::queryIntersected(
    const RSpatialIndexNavel::RSiRegion& region, 
    RSpatialIndexVisitor* dataVisitor) {

    QMap<int, QSet<int> > result;
    RSpatialIndexNavel::Visitor visitor(result, dataVisitor);
    tree->intersectsWithQuery(region, visitor);

    return result;
}



QMap<int, QSet<int> > RSpatialIndexNavel::queryContained(
    double x1, double y1, double z1, 
    double x2, double y2, double z2,
    RSpatialIndexVisitor* dataVisitor) {

    return queryContained(
        RSpatialIndexNavel::RSiRegion(x1, y1, z1, x2, y2, z2), 
        dataVisitor
    );
}



/**
 * Internal.
 */
QMap<int, QSet<int> > RSpatialIndexNavel::queryContained(
    const RSpatialIndexNavel::RSiRegion& region, 
    RSpatialIndexVisitor* dataVisitor) {

    QMap<int, QSet<int> > result;
    RSpatialIndexNavel::Visitor visitor(result, dataVisitor);
    tree->containsWhatQuery(region, visitor);

    return result;
}


QMap<int, QSet<int> > RSpatialIndexNavel::queryNearestNeighbor(
    unsigned int k,
    double x, double y, double z,
    RSpatialIndexVisitor *dataVisitor) {

    return queryNearestNeighbor(
        k,
        RSpatialIndexNavel::RSiPoint(x, y, z),
        dataVisitor
    );
}



/**
 * Internal.
 */
QMap<int, QSet<int> > RSpatialIndexNavel::queryNearestNeighbor(
    unsigned int k,
    const RSiPoint& point, RSpatialIndexVisitor* dataVisitor) {

    QMap<int, QSet<int> > result;
    RSpatialIndexNavel::Visitor visitor(result, dataVisitor);
    tree->nearestNeighborQuery(k, point, visitor);

    return result;
}

QPair<int, int> RSpatialIndexNavel::queryNearestNeighbor(double x, double y, double z) {
    return RSpatialIndex::queryNearestNeighbor(x, y, z);
}
