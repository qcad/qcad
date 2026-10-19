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
#ifndef RPOLYMESHENTITY_H
#define RPOLYMESHENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RPolyMeshData.h"
#include "RPolyMeshEntityProxy.h"
#include "RTriangle.h"

class RDocument;
class RExporter;

/**
 * Polygon mesh entity: an indexed mesh of faces with three or more
 * vertices sharing one list of vertices (see RPolyMeshData). Stored in
 * DXF/DWG as MESH (AutoCAD 2010 and newer) or polyface mesh (older
 * formats), imported from MESH, polyface meshes and polygon meshes.
 *
 * Rendering is implemented by a proxy (see RPolyMeshEntityProxy).
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RPolyMeshEntity: public REntity {

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyProtected;
    static RPropertyTypeId PropertyWorkingSet;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLinetypeScale;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDisplayedColor;
    static RPropertyTypeId PropertyDrawOrder;

    static RPropertyTypeId PropertyVertexCount;
    static RPropertyTypeId PropertyFaceCount;

public:
    RPolyMeshEntity(RDocument* document, const RPolyMeshData& data);
    virtual ~RPolyMeshEntity();

    static void init();

    static RS::EntityType getRtti() {
        return RS::EntityPolyMesh;
    }

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(RPolyMeshEntity::getRtti());
    }

    virtual QSharedPointer<RObject> clone() const {
        return QSharedPointer<RObject>(new RPolyMeshEntity(*this));
    }

    QSharedPointer<RPolyMeshEntity> cloneToPolyMeshEntity() const {
        return QSharedPointer<RPolyMeshEntity>(new RPolyMeshEntity(*this));
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual RPolyMeshData& getData() {
        return data;
    }

    virtual const RPolyMeshData& getData() const {
        return data;
    }

    QList<RVector> getVertices() const {
        return data.getVertices();
    }

    int countVertices() const {
        return data.countVertices();
    }

    RVector getVertexAt(int index) const {
        return data.getVertexAt(index);
    }

    QList<int> getFaces() const {
        return data.getFaces();
    }

    int countFaces() const {
        return data.countFaces();
    }

    QList<int> getFace(int index) const {
        return data.getFace(index);
    }

    bool isTriangleMesh() const {
        return data.isTriangleMesh();
    }

    QList<RTriangle> getTriangles() const {
        return data.getTriangles();
    }

    static bool hasProxy() {
        return polyMeshEntityProxy!=NULL;
    }

    /**
     * \nonscriptable
     */
    static void setPolyMeshEntityProxy(RPolyMeshEntityProxy* p) {
        if (polyMeshEntityProxy!=NULL) {
            delete polyMeshEntityProxy;
        }
        polyMeshEntityProxy = p;
    }

    /**
     * \nonscriptable
     */
    static RPolyMeshEntityProxy* getPolyMeshEntityProxy() {
        return polyMeshEntityProxy;
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RPolyMeshData data;

    static RPolyMeshEntityProxy* polyMeshEntityProxy;
};

Q_DECLARE_METATYPE(RPolyMeshEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RPolyMeshEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RPolyMeshEntity>*)

#endif
