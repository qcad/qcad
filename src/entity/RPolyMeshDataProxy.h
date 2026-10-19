/**
 * Copyright (c) 2011-2026 by Andrew Mustun. All rights reserved.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

#ifndef RPOLYMESHDATAPROXY_H
#define RPOLYMESHDATAPROXY_H

#include "entity_global.h"

#include <QList>
#include <QSharedPointer>

#include "RS.h"

class RBox;
class RPolyMeshData;
class RRefPoint;
class RShape;
class RTriangle;
class RVector;

/**
 * Proxy for polygon mesh functionality (edges, triangulation,
 * reference points, splitting). May be implemented by a plugin.
 *
 * \ingroup entity
 */
class QCADENTITY_EXPORT RPolyMeshDataProxy {
public:
    virtual ~RPolyMeshDataProxy() {}

    /**
     * \return The visible edges of the given mesh as shapes (lines),
     *      every edge once. Edges outside the given query box are
     *      omitted if the box is valid.
     */
    virtual QList<QSharedPointer<RShape> > getShapes(const RPolyMeshData& data, const RBox& queryBox, bool ignoreComplex, bool segment) const = 0;

    /**
     * \return The faces of the given mesh as triangles (faces with more
     *      than three vertices are triangulated).
     */
    virtual QList<RTriangle> getTriangles(const RPolyMeshData& data) const = 0;

    virtual QList<RRefPoint> getReferencePoints(const RPolyMeshData& data, RS::ProjectionRenderingHint hint) const = 0;

    virtual bool moveReferencePoint(RPolyMeshData& data, const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) const = 0;

    /**
     * Splits the given mesh into parts with at most the given number of
     * vertices and faces, each face with at most the given number of
     * vertices (faces with more vertices are triangulated). Vertices
     * shared by faces of different parts are duplicated.
     *
     * \return The parts (one part if the mesh fits into the limits).
     */
    virtual QList<RPolyMeshData> split(const RPolyMeshData& data, int maxVertices, int maxFaces, int maxFaceVertices) const = 0;

    /**
     * \return True if all faces of the given mesh have at least three
     *      vertices and refer to existing vertices.
     */
    virtual bool isSane(const RPolyMeshData& data) const = 0;
};

#endif
