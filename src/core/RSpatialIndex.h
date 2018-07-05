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

#ifndef RSPATIALINDEX_H
#define RSPATIALINDEX_H

#include "core_global.h"

// MSVC <= 2008 does not have this:
//#include <stdint.h>

#include <QSet>
#include <QList>

#include "RBox.h"
#include "RDebug.h"
#include "RMath.h"
#include "RRequireHeap.h"
#include "RSpatialIndexVisitor.h"

class QCADCORE_EXPORT RSpatialIndexDebugVisitor : public RSpatialIndexVisitor {
public:
    RSpatialIndexDebugVisitor(QDebug dbg) : dbg(dbg) {}
    virtual ~RSpatialIndexDebugVisitor() {}
    virtual void visitData(
        int id,
        int pos,
        double x1, double y1, double z1,
        double x2, double y2, double z2);

    virtual void visitNode(
        double x1, double y1, double z1,
        double x2, double y2, double z2) {
        Q_UNUSED(x1)
        Q_UNUSED(y1)
        Q_UNUSED(z1)
        Q_UNUSED(x2)
        Q_UNUSED(y2)
        Q_UNUSED(z2)
    }

    QDebug dbg;
    QList<QPair<int, int> > matches;
};


/**
 * \brief Abstract base class for spatial index implementations.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RSpatialIndex: public RRequireHeap {
public:
    RSpatialIndex() {
    }

    virtual ~RSpatialIndex() {
    }

    static qint64 getSIId(int id, int pos);
    static int getId(qint64 siid);
    static int getPos(qint64 siid);

    virtual RSpatialIndex* create() = 0;
    virtual void clear() = 0;

    virtual void bulkLoad(const QList<int>& ids, const QList<QList<RBox> >& bbs);

    virtual void bulkLoadSimple(const QList<int>& ids, const QList<RBox>& bbs);

    /**
     * Adds a new entry into this spatial index.
     */
    virtual void addToIndex(
        int id, int pos,
        double x1, double y1, double z1,
        double x2, double y2, double z2
    ) = 0;

    /**
     * Adds a new entry into this spatial index.
     */
    virtual void addToIndex(
        int id, int pos,
        const RBox& bb
    );

    /**
     * Adds a new entry at multiple positions into this 
     * spatial index.
     */
    virtual void addToIndex(
        int id,
        const QList<RBox>& bbs
    );

    /**
     * Removes the entry with the given ID from this spatial index.
     */
    //virtual void removeFromIndex(int id) = 0;

    /**
     * Removes the entry with the given ID from this spatial index.
     * the bounding box is provided for fast lookup.
     */
    virtual bool removeFromIndex(
            int id, int pos,
            double x1, double y1, double z1,
            double x2, double y2, double z2) = 0;

    /**
     * Removes the entry with the given ID from this spatial index.
     * the bounding box is provided for faster lookup.
     */
    virtual bool removeFromIndex(int id, int pos, const RBox& bb);

    /**
     * Removes the entry with the given ID from this spatial index.
     * the bounding boxes are provided for faster lookup.
     */
    virtual bool removeFromIndex(int id, const QList<RBox>& bb);

    /**
     * Queries the index for all items that are completely inside or intersect
     * with the given box x1,y1,z1,x2,y2,z2.
     *
     * \param x1 lower region boundary of the first dimension.
     * \param y1 lower region boundary of the second dimension.
     * \param z1 lower region boundary of the third dimension.
     * \param x2 higher region boundary of the first dimension.
     * \param y2 higher region boundary of the second dimension.
     * \param z2 higher region boundary of the third dimension.
     * \param dataVisitor The item data is handed back to the caller over
     *      this object (visitor pattern).
     * \return map with IDs as keys and positions as values
     */
    virtual QMap<int, QSet<int> > queryIntersected(
        double x1, double y1, double z1,
        double x2, double y2, double z2,
        RSpatialIndexVisitor* dataVisitor=NULL
    ) = 0;

    /**
     * Queries the index for all items that are completely inside or intersect
     * with the given box.
     */
    virtual QMap<int, QSet<int> > queryIntersected(
        const RBox& b,
        RSpatialIndexVisitor* dataVisitor=NULL
    );

    /**
     * Queries the index for all items that are completely inside the given
     * box x1,y1,z1,x2,y2,z2.
     *
     * \param x1 lower region boundary of the first dimension.
     * \param y1 lower region boundary of the second dimension.
     * \param z1 lower region boundary of the third dimension.
     * \param x2 higher region boundary of the first dimension.
     * \param y2 higher region boundary of the second dimension.
     * \param z2 higher region boundary of the third dimension.
     * \param dataVisitor The item data is handed back to the caller over
     *      this object (visitor pattern).
     */
    virtual QMap<int, QSet<int> > queryContained(
        double x1, double y1, double z1,
        double x2, double y2, double z2,
        RSpatialIndexVisitor* dataVisitor=NULL
    ) = 0;

    /**
     * Queries the index for all items that are completely inside the given
     * box.
     */
    virtual QMap<int, QSet<int> > queryContained(
        const RBox& b,
        RSpatialIndexVisitor* dataVisitor=NULL
    );

    /**
     * Queries the index for closest neighbor items.
     *
     * \param x1 position of the first dimension.
     * \param y1 position of the second dimension.
     * \param z1 position of the third dimension.
     * \param dataVisitor The item data is handed back to the caller over
     *      this object (visitor pattern).
     */
    virtual QMap<int, QSet<int> > queryNearestNeighbor(
        unsigned int k,
        double x, double y, double z,
        RSpatialIndexVisitor* dataVisitor=NULL
    ) = 0;

    virtual QPair<int, int> queryNearestNeighbor(double x, double y, double z);

protected:
    int idCounter;
};

QCADCORE_EXPORT QDebug operator<<(QDebug dbg, RSpatialIndex& si);

Q_DECLARE_METATYPE(RSpatialIndex*)
Q_DECLARE_METATYPE(const RSpatialIndex*)

#endif
