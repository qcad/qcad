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

#ifndef RBLOCKREFERENCEENTITY_H
#define RBLOCKREFERENCEENTITY_H

#include "core_global.h"

#include "REntity.h"
#include "RBlockReferenceData.h"

class RDocument;
class RExporter;

/**
 * Block reference entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup core
 */
class QCADCORE_EXPORT RBlockReferenceEntity: public REntity {

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

    static RPropertyTypeId PropertyReferencedBlock;
    static RPropertyTypeId PropertyPositionX;
    static RPropertyTypeId PropertyPositionY;
    static RPropertyTypeId PropertyPositionZ;
    static RPropertyTypeId PropertyScaleX;
    static RPropertyTypeId PropertyScaleY;
    static RPropertyTypeId PropertyScaleZ;
    static RPropertyTypeId PropertyRotation;
    static RPropertyTypeId PropertyColumnCount;
    static RPropertyTypeId PropertyRowCount;
    static RPropertyTypeId PropertyColumnSpacing;
    static RPropertyTypeId PropertyRowSpacing;

public:
    RBlockReferenceEntity(RDocument* document, const RBlockReferenceData& data);
    RBlockReferenceEntity(const RBlockReferenceEntity& other);
    virtual ~RBlockReferenceEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RBlockReferenceEntity));
    }

    virtual RBlockReferenceEntity* clone() const {
        return new RBlockReferenceEntity(*this);
    }

    virtual QSet<RPropertyTypeId> getPropertyTypeIds(RPropertyAttributes::Option option = RPropertyAttributes::NoOptions) const;

    virtual bool setProperty(RPropertyTypeId propertyTypeId,
            const QVariant& value, RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

//    virtual void setSelected(bool on);

    virtual void exportEntity(RExporter& e, bool preview = false, bool forceSelected=false) const;

    virtual RBlockReferenceData& getData() {
        return data;
    }

    virtual const RBlockReferenceData& getData() const {
        return data;
    }

    RVector getPosition() const {
       return data.getPosition();
    }

    void setPosition(const RVector& pos) {
        data.setPosition(pos);
    }

    RVector getScaleFactors() const {
        return data.getScaleFactors();
    }

    void setScaleFactors(const RVector sf) {
        data.setScaleFactors(sf);
    }

    double getRotation() const {
        return data.getRotation();
    }

    void setRotation(double r) {
        data.setRotation(r);
    }

    int getColumnCount() const {
        return data.getColumnCount();
    }
    void setColumnCount(int c) {
        data.setColumnCount(c);
    }

    int getRowCount() const {
        return data.getRowCount();
    }
    void setRowCount(int c) {
        data.setRowCount(c);
    }

    double getColumnSpacing() const {
        return data.getColumnSpacing();
    }
    void setColumnSpacing(double s) {
        data.setColumnSpacing(s);
    }

    double getRowSpacing() const {
        return data.getRowSpacing();
    }
    void setRowSpacing(double s) {
        data.setRowSpacing(s);
    }

    void setReferencedBlockId(RBlock::Id blockId) {
        data.setReferencedBlockId(blockId);
    }

    void setReferencedBlockName(const QString& blockName) {
        data.setReferencedBlockName(blockName);
    }

    RBlock::Id getReferencedBlockId() const {
        return data.getReferencedBlockId();
    }

    QString getReferencedBlockName() const {
        return data.getReferencedBlockName();
    }

    //virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);

    virtual void update() const {
        data.update();
    }

    void update(REntity::Id entityId) const {
        data.update(entityId);
    }

    QSharedPointer<REntity> queryEntity(REntity::Id entityId, bool transform = false, bool ignoreAttDef = true) const {
        return data.queryEntity(entityId, transform, ignoreAttDef);
    }

    bool applyTransformationTo(REntity& entity) const {
        return data.applyTransformationTo(entity);
    }

    /**
     * \nonscriptable
     */
    bool applyTransformationTo(QSharedPointer<REntity>& entity) const {
        return data.applyTransformationTo(entity);
    }

    RVector mapToBlock(const RVector& v) const {
        return data.mapToBlock(v);
    }

    /**
     * \nonscriptable
     */
    virtual void print(QDebug dbg) const;

protected:
    RBlockReferenceData data;
    mutable int recursionDepth;
};

Q_DECLARE_METATYPE(RBlockReferenceEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RBlockReferenceEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RBlockReferenceEntity>*)

#endif
