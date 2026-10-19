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
#ifndef RPOLYMESHDATA_H
#define RPOLYMESHDATA_H

#include "entity_global.h"

#include <QList>

#include "RBox.h"
#include "REntityData.h"
#include "RPolyMeshDataProxy.h"
#include "RVector.h"

class RDocument;
class RLine;
class RPolyline;
class RRefPoint;
class RShape;
class RTriangle;

/**
 * Stores and manages all data that defines the geometry of a polygon
 * mesh entity: a list of vertices and a list of faces, each face
 * referring to three or more vertices by index (indexed mesh with
 * shared vertices).
 *
 * The faces are stored as one flat list: for every face the number of
 * vertices followed by the vertex indices (0-based), e.g.
 * 3 0 1 2 4 1 5 6 2 for a triangle followed by a quad (the layout of
 * the DXF MESH entity). Optionally, edges can be marked as hidden
 * (see \ref isEdgeHidden): the edge with index k of a face starts at
 * the vertex with index k of that face.
 *
 * Geometry algorithms (edges, triangulation, reference points, splitting)
 * are implemented by a proxy (see RPolyMeshDataProxy). Without proxy,
 * a mesh holds its data but has no shapes and no reference points.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RPolyMeshData: public REntityData {

    friend class RPolyMeshEntity;

protected:
    RPolyMeshData(RDocument* document, const RPolyMeshData& data);

public:
    RPolyMeshData();
    RPolyMeshData(const QList<RVector>& vertices, const QList<int>& faces);
    virtual ~RPolyMeshData() {}

    virtual RS::EntityType getType() const {
        return RS::EntityPolyMesh;
    }

    virtual bool isValid() const {
        return !vertices.isEmpty() && !faces.isEmpty();
    }

    /**
     * \return True if all faces have at least three vertices and refer
     *      to existing vertices (false without proxy).
     */
    virtual bool isSane() const;

    /**
     * The geometry of a mesh is not accessible as properties, the whole
     * entity is replaced when it changes (see REntityData::cloneOnChange).
     */
    virtual bool cloneOnChange() const {
        return true;
    }

    void clear();

    QList<RVector> getVertices() const {
        return vertices;
    }
    void setVertices(const QList<RVector>& v) {
        vertices = v;
    }
    int countVertices() const {
        return vertices.length();
    }
    RVector getVertexAt(int index) const;
    void setVertexAt(int index, const RVector& v);
    /**
     * Appends the given vertex.
     *
     * \return The index of the new vertex.
     */
    int addVertex(const RVector& v);

    /**
     * \return The flat face list (vertex count followed by the vertex
     *      indices for every face, see class description).
     */
    QList<int> getFaces() const {
        return faces;
    }
    void setFaces(const QList<int>& f);
    int countFaces() const;
    /**
     * \return The vertex indices of the face with the given index
     *      (empty if out of range).
     */
    QList<int> getFace(int index) const;
    /**
     * \return The number of vertices of the face with the given index
     *      (0 if out of range).
     */
    int getFaceVertexCount(int index) const;
    /**
     * Appends a face with the given vertex indices (at least three).
     *
     * \return The index of the new face or -1.
     */
    int addFace(const QList<int>& indices);
    int addTriangle(int v1, int v2, int v3);
    int addQuad(int v1, int v2, int v3, int v4);

    /**
     * \return True if all faces are triangles.
     */
    bool isTriangleMesh() const;

    /**
     * \return True if the mesh has hidden edges.
     */
    bool hasHiddenEdges() const {
        return !hiddenEdges.isEmpty();
    }
    /**
     * \return Hidden edge flags, one per entry of the face list (entries
     *      of vertex counts unused), empty if no edges are hidden.
     */
    QList<bool> getHiddenEdges() const {
        return hiddenEdges;
    }
    void setHiddenEdges(const QList<bool>& h);
    /**
     * \return True if the given edge of the given face is hidden
     *      (edge k of a face starts at vertex k of the face).
     */
    bool isEdgeHidden(int faceIndex, int edgeIndex) const;
    void setEdgeHidden(int faceIndex, int edgeIndex, bool hidden);

    /**
     * Appends the vertices and faces of the given mesh to this mesh.
     */
    void append(const RPolyMeshData& other);

    /**
     * \return The faces of this mesh as triangles (empty without proxy).
     */
    QList<RTriangle> getTriangles() const;

    /**
     * Splits this mesh into parts with at most the given number of
     * vertices and faces, each face with at most the given number of
     * vertices (see RPolyMeshDataProxy::split). Without proxy, this
     * mesh is returned as one part.
     */
    QList<RPolyMeshData> split(int maxVertices, int maxFaces, int maxFaceVertices = 4) const;

    virtual RBox getBoundingBox(bool ignoreEmpty = false) const;
    virtual void to2D();
    virtual void setZ(double z);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const;

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;
    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    static bool hasProxy() {
        return polyMeshDataProxy!=NULL;
    }

    /**
     * \nonscriptable
     */
    static void setPolyMeshDataProxy(RPolyMeshDataProxy* p) {
        if (polyMeshDataProxy!=NULL) {
            delete polyMeshDataProxy;
        }
        polyMeshDataProxy = p;
    }

    /**
     * \nonscriptable
     */
    static RPolyMeshDataProxy* getPolyMeshDataProxy() {
        return polyMeshDataProxy;
    }

private:
    void updateFaceIndex() const;

private:
    QList<RVector> vertices;
    QList<int> faces;
    QList<bool> hiddenEdges;

    // start of every face in the face list (cache):
    mutable QList<int> faceOffsets;
    mutable bool faceOffsetsValid;

    static RPolyMeshDataProxy* polyMeshDataProxy;
};

Q_DECLARE_METATYPE(RPolyMeshData)
Q_DECLARE_METATYPE(RPolyMeshData*)
Q_DECLARE_METATYPE(const RPolyMeshData*)
Q_DECLARE_METATYPE(QSharedPointer<RPolyMeshData>)
Q_DECLARE_METATYPE(QList<RPolyMeshData>)

#endif
