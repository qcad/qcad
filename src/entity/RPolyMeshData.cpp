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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
#include "RPolyMeshData.h"
#include "RDocument.h"
#include "RLine.h"
#include "RPolyline.h"
#include "RRefPoint.h"
#include "RShape.h"
#include "RTriangle.h"

RPolyMeshDataProxy* RPolyMeshData::polyMeshDataProxy = NULL;

RPolyMeshData::RPolyMeshData() :
    REntityData(), faceOffsetsValid(false) {
}

RPolyMeshData::RPolyMeshData(RDocument* document, const RPolyMeshData& data)
    : REntityData(document), faceOffsetsValid(false) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RPolyMeshData::RPolyMeshData(const QList<RVector>& vertices, const QList<int>& faces) :
    REntityData(), vertices(vertices), faces(faces), faceOffsetsValid(false) {
}

bool RPolyMeshData::isSane() const {
    if (!hasProxy()) {
        return false;
    }
    return polyMeshDataProxy->isSane(*this);
}

void RPolyMeshData::clear() {
    vertices.clear();
    faces.clear();
    hiddenEdges.clear();
    faceOffsets.clear();
    faceOffsetsValid = false;
}

RVector RPolyMeshData::getVertexAt(int index) const {
    if (index<0 || index>=vertices.length()) {
        return RVector::invalid;
    }
    return vertices[index];
}

void RPolyMeshData::setVertexAt(int index, const RVector& v) {
    if (index<0 || index>=vertices.length()) {
        return;
    }
    vertices[index] = v;
}

int RPolyMeshData::addVertex(const RVector& v) {
    vertices.append(v);
    return vertices.length()-1;
}

void RPolyMeshData::setFaces(const QList<int>& f) {
    faces = f;
    hiddenEdges.clear();
    faceOffsetsValid = false;
}

void RPolyMeshData::updateFaceIndex() const {
    if (faceOffsetsValid) {
        return;
    }
    faceOffsets.clear();
    int i = 0;
    while (i<faces.length()) {
        int n = faces[i];
        if (n<=0) {
            // invalid face list, stop here:
            break;
        }
        faceOffsets.append(i);
        i += n + 1;
    }
    faceOffsetsValid = true;
}

int RPolyMeshData::countFaces() const {
    updateFaceIndex();
    return faceOffsets.length();
}

QList<int> RPolyMeshData::getFace(int index) const {
    updateFaceIndex();
    QList<int> ret;
    if (index<0 || index>=faceOffsets.length()) {
        return ret;
    }
    int o = faceOffsets[index];
    int n = faces[o];
    for (int k=1; k<=n && o+k<faces.length(); k++) {
        ret.append(faces[o+k]);
    }
    return ret;
}

int RPolyMeshData::getFaceVertexCount(int index) const {
    updateFaceIndex();
    if (index<0 || index>=faceOffsets.length()) {
        return 0;
    }
    return faces[faceOffsets[index]];
}

int RPolyMeshData::addFace(const QList<int>& indices) {
    if (indices.length()<3) {
        return -1;
    }
    updateFaceIndex();
    faceOffsets.append(faces.length());
    faces.append(indices.length());
    faces.append(indices);
    if (!hiddenEdges.isEmpty()) {
        for (int k=0; k<=indices.length(); k++) {
            hiddenEdges.append(false);
        }
    }
    return faceOffsets.length()-1;
}

int RPolyMeshData::addTriangle(int v1, int v2, int v3) {
    return addFace(QList<int>() << v1 << v2 << v3);
}

int RPolyMeshData::addQuad(int v1, int v2, int v3, int v4) {
    return addFace(QList<int>() << v1 << v2 << v3 << v4);
}

bool RPolyMeshData::isTriangleMesh() const {
    updateFaceIndex();
    for (int i=0; i<faceOffsets.length(); i++) {
        if (faces[faceOffsets[i]]!=3) {
            return false;
        }
    }
    return true;
}

void RPolyMeshData::setHiddenEdges(const QList<bool>& h) {
    if (h.length()!=faces.length()) {
        hiddenEdges.clear();
        return;
    }
    hiddenEdges = h;
}

bool RPolyMeshData::isEdgeHidden(int faceIndex, int edgeIndex) const {
    if (hiddenEdges.isEmpty()) {
        return false;
    }
    updateFaceIndex();
    if (faceIndex<0 || faceIndex>=faceOffsets.length()) {
        return false;
    }
    int o = faceOffsets[faceIndex];
    int n = faces[o];
    if (edgeIndex<0 || edgeIndex>=n) {
        return false;
    }
    int i = o + 1 + edgeIndex;
    if (i>=hiddenEdges.length()) {
        return false;
    }
    return hiddenEdges[i];
}

void RPolyMeshData::setEdgeHidden(int faceIndex, int edgeIndex, bool hidden) {
    updateFaceIndex();
    if (faceIndex<0 || faceIndex>=faceOffsets.length()) {
        return;
    }
    int o = faceOffsets[faceIndex];
    int n = faces[o];
    if (edgeIndex<0 || edgeIndex>=n) {
        return;
    }
    if (hiddenEdges.isEmpty()) {
        if (!hidden) {
            return;
        }
        for (int i=0; i<faces.length(); i++) {
            hiddenEdges.append(false);
        }
    }
    hiddenEdges[o + 1 + edgeIndex] = hidden;
}

void RPolyMeshData::append(const RPolyMeshData& other) {
    int offset = vertices.length();
    vertices.append(other.vertices);

    bool hidden = !hiddenEdges.isEmpty() || !other.hiddenEdges.isEmpty();
    if (hidden && hiddenEdges.isEmpty()) {
        for (int i=0; i<faces.length(); i++) {
            hiddenEdges.append(false);
        }
    }

    int i = 0;
    while (i<other.faces.length()) {
        int n = other.faces[i];
        if (n<=0) {
            break;
        }
        faces.append(n);
        if (hidden) {
            hiddenEdges.append(false);
        }
        for (int k=1; k<=n && i+k<other.faces.length(); k++) {
            faces.append(other.faces[i+k] + offset);
            if (hidden) {
                hiddenEdges.append(i+k<other.hiddenEdges.length() ? other.hiddenEdges[i+k] : false);
            }
        }
        i += n + 1;
    }
    faceOffsetsValid = false;
}

QList<RTriangle> RPolyMeshData::getTriangles() const {
    if (!hasProxy()) {
        return QList<RTriangle>();
    }
    return polyMeshDataProxy->getTriangles(*this);
}

QList<RPolyMeshData> RPolyMeshData::split(int maxVertices, int maxFaces, int maxFaceVertices) const {
    if (!hasProxy()) {
        return QList<RPolyMeshData>() << *this;
    }
    return polyMeshDataProxy->split(*this, maxVertices, maxFaces, maxFaceVertices);
}

RBox RPolyMeshData::getBoundingBox(bool ignoreEmpty) const {
    Q_UNUSED(ignoreEmpty)

    RBox ret;
    for (int i=0; i<vertices.length(); i++) {
        ret.growToInclude(vertices[i]);
    }
    return ret;
}

void RPolyMeshData::to2D() {
    setZ(0.0);
}

void RPolyMeshData::setZ(double z) {
    for (int i=0; i<vertices.length(); i++) {
        vertices[i].z = z;
    }
}

QList<QSharedPointer<RShape> > RPolyMeshData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment, QList<RObject::Id>* entityIds) const {
    Q_UNUSED(entityIds)

    if (!hasProxy()) {
        return QList<QSharedPointer<RShape> >();
    }
    return polyMeshDataProxy->getShapes(*this, queryBox, ignoreComplex, segment);
}

QList<RRefPoint> RPolyMeshData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    if (!hasProxy()) {
        return QList<RRefPoint>();
    }
    return polyMeshDataProxy->getReferencePoints(*this, hint);
}

bool RPolyMeshData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    if (!hasProxy()) {
        return false;
    }
    return polyMeshDataProxy->moveReferencePoint(*this, referencePoint, targetPoint, modifiers);
}

bool RPolyMeshData::move(const RVector& offset) {
    for (int i=0; i<vertices.length(); i++) {
        vertices[i].move(offset);
    }
    return true;
}

bool RPolyMeshData::rotate(double rotation, const RVector& center) {
    for (int i=0; i<vertices.length(); i++) {
        vertices[i].rotate(rotation, center);
    }
    return true;
}

bool RPolyMeshData::scale(const RVector& scaleFactors, const RVector& center) {
    for (int i=0; i<vertices.length(); i++) {
        vertices[i].scale(scaleFactors, center);
    }
    return true;
}

bool RPolyMeshData::mirror(const RLine& axis) {
    // mirror in the XY plane, keep Z (RVector::mirror does not handle
    // 3D points):
    RLine axis2D(RVector(axis.getStartPoint().x, axis.getStartPoint().y),
                 RVector(axis.getEndPoint().x, axis.getEndPoint().y));
    for (int i=0; i<vertices.length(); i++) {
        RVector v(vertices[i].x, vertices[i].y);
        v.mirror(axis2D);
        vertices[i].x = v.x;
        vertices[i].y = v.y;
    }
    return true;
}

bool RPolyMeshData::flipHorizontal() {
    for (int i=0; i<vertices.length(); i++) {
        vertices[i].flipHorizontal();
    }
    return true;
}

bool RPolyMeshData::flipVertical() {
    for (int i=0; i<vertices.length(); i++) {
        vertices[i].flipVertical();
    }
    return true;
}

bool RPolyMeshData::stretch(const RPolyline& area, const RVector& offset) {
    bool ret = false;
    for (int i=0; i<vertices.length(); i++) {
        if (area.contains(vertices[i], true)) {
            vertices[i].move(offset);
            ret = true;
        }
    }
    return ret;
}
