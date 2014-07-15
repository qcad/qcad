/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include "RBox.h"
#include "RDebug.h"
#include "RDocument.h"
#include "RLinkedStorage.h"
#include "RMath.h"
#include "RMemoryStorage.h"
#include "RSettings.h"
#include "RSpatialIndexSimple.h"
#include "RStorage.h"
#include "RUcs.h"
#include "RPolyline.h"


RDocument* RDocument::clipboard = NULL;


/**
 * Creates a new document with the given storage as back-end.
 * The document takes ownership of the storage and spatial index.
 * A new document contains one layer ("0") and a number of default
 * line types. The default unit is Millimeter.
 */
RDocument::RDocument(
    RStorage& storage,
    RSpatialIndex& spatialIndex)
    : storage(storage),
      spatialIndex(spatialIndex),
      transactionStack(*this) {

    init();
}


void RDocument::init() {
    RTransaction t(storage, "", false);

    RLinkedStorage* ls = dynamic_cast<RLinkedStorage*>(&storage);
    bool storageIsLinked = (ls!=NULL);

    // add default line types if not already added (RLinkedStorage):
    if (!storageIsLinked && queryLinetype("BYLAYER").isNull()) {
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "BYLAYER")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "BYBLOCK")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "CONTINUOUS")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "BORDER")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "BORDER2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "BORDERX2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "CENTER")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "CENTER2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "CENTERX2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DASHDOT")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DASHDOT2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DASHDOTX2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DASHED")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DASHED2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DASHEDX2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DIVIDE")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DIVIDE2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DIVIDEX2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DOT")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DOT2")));
        t.addObject(QSharedPointer<RObject>(new RLinetype(this, "DOTX2")));
    }

    // add default layer:
    if (!storageIsLinked && queryLayer("0").isNull()) {
        QSharedPointer<RLayer> layer(
            new RLayer(
                this, "0", false, false,
                RColor(Qt::white), getLinetypeId("CONTINUOUS"),
                RLineweight::Weight025
            )
        );
        t.addObject(layer);
    }

    // add default block:
    if (!storageIsLinked && queryBlock(RBlock::modelSpaceName).isNull()) {
        QSharedPointer<RBlock> modelSpace(
            new RBlock(
                this, RBlock::modelSpaceName, RVector()
            )
        );
        t.addObject(modelSpace);
    }

    modelSpaceBlockId = getBlockId(RBlock::modelSpaceName);

    t.end(this);

    // caching for faster operations:
    linetypeByLayerId = queryLinetype("BYLAYER")->getId();
    linetypeByBlockId = queryLinetype("BYBLOCK")->getId();

    if (!storageIsLinked) {
        setCurrentLayer("0");

        setCurrentBlock(RBlock::modelSpaceName);

        // default variables:
        setUnit((RS::Unit)RSettings::getValue("UnitSettings/Unit", RS::None).toInt());
        setLinetypeScale(RSettings::getDoubleValue("LinetypeSettings/Scale", 1.0));

        setKnownVariable(RS::DIMTXT, RSettings::getDoubleValue("DimensionSettings/DIMTXT", 2.5));
        setKnownVariable(RS::DIMEXE, RSettings::getDoubleValue("DimensionSettings/DIMEXE", 1.25));
        setKnownVariable(RS::DIMEXO, RSettings::getDoubleValue("DimensionSettings/DIMEXO", 0.625));
        setKnownVariable(RS::DIMGAP, RSettings::getDoubleValue("DimensionSettings/DIMGAP", 0.625));
        setKnownVariable(RS::DIMASZ, RSettings::getDoubleValue("DimensionSettings/DIMASZ", 2.5));
        setKnownVariable(RS::DIMSCALE, RSettings::getDoubleValue("DimensionSettings/DIMSCALE", 1.0));

        // arch tick head:
        if (RSettings::getStringValue("DimensionSettings/ArrowStyle", "Arrow")=="Arrow") {
            setKnownVariable(RS::DIMTSZ, 0.0);
        }

        // arrow head:
        else {
            setKnownVariable(RS::DIMTSZ, getKnownVariable(RS::DIMASZ));
        }

        setKnownVariable(RS::DIMLUNIT, RSettings::getIntValue("DimensionSettings/LinearFormat", RS::Decimal));
        setKnownVariable(RS::DIMDEC, RSettings::getIntValue("DimensionSettings/LinearPrecision", 4));

        // show trailing zeroes:
        if (RSettings::getBoolValue("DimensionSettings/LinearShowTrailingZeros", false)) {
            setKnownVariable(RS::DIMZIN, 0);
        }

        // suppress trailing zeroes:
        else {
            setKnownVariable(RS::DIMZIN, 8);
        }

        setKnownVariable(RS::DIMAUNIT, RSettings::getIntValue("DimensionSettings/AngularFormat", RS::DegreesDecimal));
        setKnownVariable(RS::DIMADEC, RSettings::getIntValue("DimensionSettings/AngularPrecision", 0));

        // show trailing zeroes:
        if (RSettings::getBoolValue("DimensionSettings/AngularShowTrailingZeros", false)) {
            setKnownVariable(RS::DIMAZIN, 0);
        }

        // suppress trailing zeroes:
        else {
            setKnownVariable(RS::DIMAZIN, 2);
        }

        //  multi page printing settings:
        setVariable("MultiPageSettings/Columns", RSettings::getIntValue("MultiPageSettings/Columns", 1));
        setVariable("MultiPageSettings/Rows", RSettings::getIntValue("MultiPageSettings/Rows", 1));
        setVariable("MultiPageSettings/GlueMarginsLeft", RSettings::getDoubleValue("MultiPageSettings/GlueMarginsLeft", 0));
        setVariable("MultiPageSettings/GlueMarginsTop", RSettings::getDoubleValue("MultiPageSettings/GlueMarginsTop", 0));
        setVariable("MultiPageSettings/GlueMarginsRight", RSettings::getDoubleValue("MultiPageSettings/GlueMarginsRight", 0));
        setVariable("MultiPageSettings/GlueMarginsBottom", RSettings::getDoubleValue("MultiPageSettings/GlueMarginsBottom", 0));
        setVariable("MultiPageSettings/PrintCropMarks", RSettings::getBoolValue("MultiPageSettings/PrintCropMarks", false));

        // printer page settings:
        QString vs;
        double vd;

        // paper size:
        vd = RSettings::getDoubleValue("PageSettings/PaperWidth", 0);
        if (vd<1.0e-4) {
            vd = 210;
        }
        setVariable("PageSettings/PaperWidth", vd);

        vd = RSettings::getDoubleValue("PageSettings/PaperHeight", 0);
        if (vd<1.0e-4) {
            vd = 297;
        }
        setVariable("PageSettings/PaperHeight", vd);

        // orientation:
        vs = RSettings::getStringValue("PageSettings/PageOrientation", "");
        if (vs.isEmpty()) {
            vs = "Portrait";
        }
        setVariable("PageSettings/PageOrientation", vs);

        // paper unit:
        setVariable("UnitSettings/PaperUnit", RSettings::getIntValue("UnitSettings/PaperUnit", RS::Millimeter));

        // offset:
        setVariable("PageSettings/OffsetX", RSettings::getDoubleValue("PageSettings/OffsetX", 0));
        setVariable("PageSettings/OffsetY", RSettings::getDoubleValue("PageSettings/OffsetY", 0));

        // scale:
        vs = RSettings::getStringValue("PageSettings/Scale", "1:1");
        if (vs.isEmpty()) {
            vs = "1:1";
        }
        setVariable("PageSettings/Scale", vs);

        setVariable("PageSettings/ShowPaperBorders", RSettings::getBoolValue("PageSettings/ShowPaperBorders", true));
        //setVariable("PageSettings/ShowBoundingBox", RSettings::getBoolValue("PageSettings/ShowBoundingBox", false));

        // grid settings:
        QString s;
        for (int i=0; i<4; i++) {
            s = QString("Grid/DisplayGrid0%1").arg(i);
            setVariable(s, RSettings::getBoolValue(s, true));
            s = QString("Grid/IsometricGrid0%1").arg(i);
            setVariable(s, RSettings::getBoolValue(s, false));
            s = QString("Grid/IsometricProjection0%1").arg(i);
            setVariable(s, RSettings::getIntValue(s, (int)RS::IsoTop));
            s = QString("Grid/GridSpacingX0%1").arg(i);
            setVariable(s, RSettings::getStringValue(s, "auto"));
            s = QString("Grid/GridSpacingY0%1").arg(i);
            setVariable(s, RSettings::getStringValue(s, "auto"));
            s = QString("Grid/MetaGridSpacingX0%1").arg(i);
            setVariable(s, RSettings::getStringValue(s, "auto"));
            s = QString("Grid/MetaGridSpacingY0%1").arg(i);
            setVariable(s, RSettings::getStringValue(s, "auto"));
        }

        setDimensionFont(RSettings::getStringValue("DimensionSettings/DimensionFont", "Standard"));

        storage.setModified(false);
    }
}


/**
 * Resets this document to its initial, empty state.
 */
void RDocument::clear() {
    fileName = "";
    storage.clear();
    spatialIndex.clear();
    transactionStack.reset();
    RS::Unit u = getUnit();
    init();
    setUnit(u);
}


RDocument::~RDocument() {
    storage.doDelete();
    spatialIndex.doDelete();
}

void RDocument::setUnit(RS::Unit unit) {
    storage.setUnit(unit);
}

RS::Unit RDocument::getUnit() const {
    return storage.getUnit();
}

void RDocument::setDimensionFont(const QString& f) {
    storage.setDimensionFont(f);
}

QString RDocument::getDimensionFont() const {
    return storage.getDimensionFont();
}

void RDocument::setLinetypeScale(double v) {
    storage.setLinetypeScale(v);
}

double RDocument::getLinetypeScale() const {
    return storage.getLinetypeScale();
}

/**
 * \return The linear format type for this document.
 * This is determined by the variable "$DIMLUNIT".
 */
RS::LinearFormat RDocument::getLinearFormat() {
    return (RS::LinearFormat)getKnownVariable(RS::DIMLUNIT, 2).toInt();
}



/**
 * \return The linear precision for this document.
 * This is determined by the variable "$DIMDEC".
 */
int RDocument::getLinearPrecision() {
    return getKnownVariable(RS::DIMDEC, 4).toInt();
}



bool RDocument::showLeadingZeroes() {
    return !(getKnownVariable(RS::DIMZIN, 8).toInt() & 4);
}


bool RDocument::showTrailingZeroes() {
    return !(getKnownVariable(RS::DIMZIN, 8).toInt() & 8);
}

bool RDocument::showLeadingZeroesAngle() {
    return !(getKnownVariable(RS::DIMAZIN, 3).toInt() & 1);
}


bool RDocument::showTrailingZeroesAngle() {
    return !(getKnownVariable(RS::DIMAZIN, 3).toInt() & 2);
}


/**
 * \return The angle format type for this document.
 * This is determined by the variable "$DIMAUNIT".
 */
RS::AngleFormat RDocument::getAngleFormat() {
    return (RS::AngleFormat)getKnownVariable(RS::DIMAUNIT, 0).toInt();
}

/**
 * \return The angular precision for this document.
 * This is determined by the variable "$DIMADEC".
 */
int RDocument::getAnglePrecision() {
    return getKnownVariable(RS::DIMADEC, 2).toInt();
}


QStringList RDocument::getVariables() const {
    return storage.getVariables();
}

bool RDocument::hasVariable(const QString& key) const {
    return storage.hasVariable(key);
}

void RDocument::setVariable(const QString& key, const QVariant& value, bool overwrite) {
    storage.setVariable(key, value, overwrite);
}

QVariant RDocument::getVariable(const QString& key, const QVariant& defaultValue, bool useSettings) {
    QVariant ret = storage.getVariable(key);
    if (!ret.isValid()) {
        if (useSettings) {
            return RSettings::getValue(key, defaultValue);
        }
        ret = defaultValue;
    }
    return ret;
}

void RDocument::setKnownVariable(RS::KnownVariable key, const QVariant& value) {
    storage.setKnownVariable(key, value);
}

void RDocument::setKnownVariable(RS::KnownVariable key, const RVector& value) {
    QVariant v;
    v.setValue(value);
    storage.setKnownVariable(key, v);
}

QVariant RDocument::getKnownVariable(RS::KnownVariable key, const QVariant& defaultValue) {
    QVariant ret = storage.getKnownVariable(key);
    if (!ret.isValid()) {
        ret = defaultValue;
    }
    return ret;
}

QSharedPointer<RLayer> RDocument::queryCurrentLayer() {
    return storage.queryCurrentLayer();
}

RLayer::Id RDocument::getCurrentLayerId() {
    return storage.getCurrentLayerId();
}

void RDocument::setCurrentColor(const RColor& color) {
    storage.setCurrentColor(color);
}

RColor RDocument::getCurrentColor() const {
    return storage.getCurrentColor();
}

void RDocument::setCurrentLineweight(RLineweight::Lineweight lw) {
    storage.setCurrentLineweight(lw);
}

RLineweight::Lineweight RDocument::getCurrentLineweight() const {
    return storage.getCurrentLineweight();
}

void RDocument::setCurrentLinetype(RLinetype lt) {
    storage.setCurrentLinetype(lt);
}

RLinetype RDocument::getCurrentLinetype() const {
    return storage.getCurrentLinetype();
}

void RDocument::setCurrentLayer(RLayer::Id layerId) {
    storage.setCurrentLayer(layerId);
}

void RDocument::setCurrentLayer(const QString& layerName) {
    storage.setCurrentLayer(layerName);
}

QSharedPointer<RBlock> RDocument::queryCurrentBlock() {
    return storage.queryCurrentBlock();
}

RBlock::Id RDocument::getCurrentBlockId() const {
    return storage.getCurrentBlockId();
}

void RDocument::setCurrentBlock(RBlock::Id blockId) {
    RBlock::Id prevBlockId = getCurrentBlockId();

    RLinkedStorage* ls = dynamic_cast<RLinkedStorage*>(&storage);

    // remove references to block we're entering from spatial index:
    if (ls==NULL) {
        //qDebug() << "RDocument::setCurrentBlock: removing block: " << blockId;
    }
    removeBlockFromSpatialIndex(blockId);
    //rebuildSpatialIndex(oldBlockId);

    storage.setCurrentBlock(blockId);

    // add references to block we're leaving to spatial index:
    if (prevBlockId!=RBlock::INVALID_ID) {
        if (ls==NULL) {
            //qDebug() << "RDocument::setCurrentBlock: adding block back on: " << prevBlockId;
        }
        addBlockToSpatialIndex(prevBlockId, blockId);
    }
}

void RDocument::setCurrentBlock(const QString& blockName) {
    //storage.setCurrentBlock(blockName);
    RBlock::Id id = getBlockId(blockName);
    if (id == RBlock::INVALID_ID) {
        return;
    }
    setCurrentBlock(id);
}

QString RDocument::getTempBlockName() const {
    do {
        int p1 = qrand() % 100000;
        int p2 = qrand() % 100000;
        QString blockName = QString("A$C%1%2").arg(p1, 5, 10, QChar('0')).arg(p2, 5, 10, QChar('0'));
        if (!hasBlock(blockName)) {
            return blockName;
        }
    } while(true);
}

QString RDocument::getBlockName(RBlock::Id blockId) const {
    return storage.getBlockName(blockId);
}

QSet<QString> RDocument::getBlockNames() const {
    return storage.getBlockNames();
}

void RDocument::setCurrentView(RView::Id viewId) {
    storage.setCurrentView(viewId);
}

void RDocument::setCurrentView(const QString& viewName) {
    storage.setCurrentView(viewName);
}

RView::Id RDocument::getCurrentViewId() const {
    return storage.getCurrentViewId();
}

QSharedPointer<RView> RDocument::queryCurrentView() {
    return storage.queryCurrentView();
}

bool RDocument::hasView(const QString& viewName) const {
    return storage.hasView(viewName);
}

QString RDocument::getLayerName(RLayer::Id layerId) const {
    return storage.getLayerName(layerId);
}

QSet<QString> RDocument::getLayerNames() const {
    return storage.getLayerNames();
}

QSet<QString> RDocument::getViewNames() const {
    return storage.getViewNames();
}

bool RDocument::hasLayer(const QString& layerName) const {
    return storage.hasLayer(layerName);
}

RLayer::Id RDocument::getLayerId(const QString& layerName) const {
    return storage.getLayerId(layerName);
}

bool RDocument::hasBlock(const QString& blockName) const {
    return storage.hasBlock(blockName);
}

bool RDocument::hasLinetype(const QString& linetypeName) const {
    return storage.hasLinetype(linetypeName);
}

RBlock::Id RDocument::getBlockId(const QString& blockName) const {
    return storage.getBlockId(blockName);
}

RBlock::Id RDocument::getModelSpaceBlockId() const {
    return modelSpaceBlockId;
}

QString RDocument::getLinetypeName(RLinetype::Id linetypeId) const {
    return storage.getLinetypeName(linetypeId);
}

RLinetype::Id RDocument::getLinetypeId(const QString& linetypeName) const {
    return storage.getLinetypeId(linetypeName);
}

QSet<QString> RDocument::getLinetypeNames() const {
    return storage.getLinetypeNames();
}

bool RDocument::isByLayer(RLinetype::Id linetypeId) const {
    return linetypeId == linetypeByLayerId;
}

bool RDocument::isByBlock(RLinetype::Id linetypeId) const {
    return linetypeId == linetypeByBlockId;
}

RLineweight::Lineweight RDocument::getMaxLineweight() const {
    return storage.getMaxLineweight();
}

void RDocument::setFileName(const QString& fn) {
    fileName = fn;
}

QString RDocument::getFileName() const {
    return fileName;
}

void RDocument::setFileVersion(const QString& fv) {
    fileVersion = fv;
}

QString RDocument::getFileVersion() const {
    return fileVersion;
}

void RDocument::resetTransactionStack() {
    transactionStack.reset();
}

bool RDocument::isUndoAvailable() const {
    return transactionStack.isUndoAvailable();
}

bool RDocument::isRedoAvailable() const {
    return transactionStack.isRedoAvailable();
}


/**
 * \return Reference to storage that backs the document.
 */
RStorage& RDocument::getStorage() {
    return storage;
}

const RStorage& RDocument::getStorage() const {
    return storage;
}

/**
 * \return Reference to the spatial index.
 */
RSpatialIndex& RDocument::getSpatialIndex() {
    return spatialIndex;
}



/**
 * \return Reference to the transaction stack for undo/redo handling.
 */
RTransactionStack& RDocument::getTransactionStack() {
    return transactionStack;
}



/**
 * Queries all objects of this document.
 *
 * \return Set of object IDs.
 */
QSet<RObject::Id> RDocument::queryAllObjects() const {
    return storage.queryAllObjects();
}

//QSet<RObject::Id> RDocument::queryAllObjectsFromContainer() const {
//    return storage.queryAllObjects();
//}

/**
 * Queries all entities of this document. This operation can be
 * slow, depending on the total number of entities and the
 * storage type that is used for this document.
 *
 * \return Set of entity IDs.
 */
QSet<REntity::Id> RDocument::queryAllEntities(bool undone, bool allBlocks, RS::EntityType type) const {
    return storage.queryAllEntities(undone, allBlocks, type);
}



/**
 * Queries all UCSs of this document.
 *
 * \return Set of UCS IDs.
 */
QSet<RUcs::Id> RDocument::queryAllUcs() const {
    return storage.queryAllUcs();
}

/**
 * Queries all layers of this document.
 *
 * \return Set of layer IDs.
 */
QSet<RLayer::Id> RDocument::queryAllLayers() const {
    return storage.queryAllLayers();
}

/*
QList<RLayer::Id> RDocument::queryAllLayers() const {
    QSet<RLayer::Id> result;
    storage.queryAllLayers(result);
    return result.toList();
}
*/

QSet<RBlock::Id> RDocument::queryAllBlocks() const {
    return storage.queryAllBlocks();
}

/*
QList<RBlock::Id> RDocument::queryAllBlocks() const {
    QSet<RBlock::Id> result;
    storage.queryAllBlocks(result);
    return result.toList();
}
*/

QSet<RView::Id> RDocument::queryAllViews() const {
    return storage.queryAllViews();
}

QSet<RLinetype::Id> RDocument::queryAllLinetypes() const{
    return storage.queryAllLinetypes();
}

QSet<REntity::Id> RDocument::queryLayerEntities(RLayer::Id layerId, bool allBlocks) const {
    return storage.queryLayerEntities(layerId, allBlocks);
}

QSet<REntity::Id> RDocument::queryBlockEntities(RBlock::Id blockId) const {
    return storage.queryBlockEntities(blockId);
}

bool RDocument::hasChildEntities(REntity::Id parentId) const {
    return storage.hasChildEntities(parentId);
}

QSet<REntity::Id> RDocument::queryChildEntities(REntity::Id parentId, RS::EntityType type) const {
    return storage.queryChildEntities(parentId, type);
}

QSet<REntity::Id> RDocument::queryBlockReferences(RBlock::Id blockId) const {
    return storage.queryBlockReferences(blockId);
}

QSet<REntity::Id> RDocument::queryAllBlockReferences() const {
    return storage.queryAllBlockReferences();
}

/*
QSet<REntity::Id> RDocument::queryViewEntities(RView::Id viewId) const {
    return storage.queryViewEntities(viewId);
}
*/

/**
 * Queries the one entity that is closest to the given position and
 * within the given range (2d).
 *
 * \param wcsPosition The position to which the entity has to be close (2d).
 * \param range The range in which to search.
 */
REntity::Id RDocument::queryClosestXY(
    const RVector& wcsPosition,
    double range,
    bool draft,
    bool includeLockedLayers) {

    RVector rangeV(
        range,
        range
    );

    // find entities that are within given maximum distance
    //   (approximation based on bounding boxes):
    QSet<REntity::Id> candidates =
        queryIntersectedEntitiesXY(
            RBox(
                wcsPosition - rangeV,
                wcsPosition + rangeV
            ),
            true, includeLockedLayers
        );

    return queryClosestXY(candidates, wcsPosition, range, draft);
}

/**
 * Queries the entity that is closest to the given position \c wcsPosition.
 * Only entities in the given set of \c candidates are considered.
 * \c candidates is usually the result of an approximate spatial
 * index query.
 *
 * \param candidates Sets of candidates to consider.
 *
 * \param wcsPosition
 *
 * \param range Maximum distance between position and entity.
 */
REntity::Id RDocument::queryClosestXY(
    QSet<REntity::Id>& candidates,
    const RVector& wcsPosition,
    double range,
    bool draft) {

    double minDist = RMAXDOUBLE;
    REntity::Id ret = -1;

    QSet<REntity::Id>::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); it++) {
        QSharedPointer<REntity> e = queryEntityDirect(*it);
        if (e.isNull()) {
            continue;
        }
        double dist = e->getDistanceTo(wcsPosition, true, range, draft);
        if (!RMath::isNaN(dist) && dist < minDist && dist < range+RS::PointTolerance) {
            minDist = dist;
            ret = *it;
        }
    }

    return ret;
}

QSet<REntity::Id> RDocument::queryInfiniteEntities() {
    return storage.queryInfiniteEntities();
}

/**
 * Queries all entities which are completely inside the given box.
 *
 * \param box Query box.
 *
 * \param result Set of IDs of entities that are completely inside the
 *      given area.
 */
QSet<REntity::Id> RDocument::queryContainedEntities(const RBox& box) {
    QSet<REntity::Id> ret = spatialIndex.queryContained(box).keys().toSet();

    // always exclude construction lines (XLine):
    ret.subtract(queryInfiniteEntities());

    return ret;
}


QSet<REntity::Id> RDocument::queryIntersectedEntitiesXY(
        const RBox& box, bool checkBoundingBoxOnly, bool includeLockedLayers, RBlock::Id blockId,
        const QList<RS::EntityType>& filter) {

    return queryIntersectedShapesXY(box, checkBoundingBoxOnly, includeLockedLayers, blockId, filter).keys().toSet();
}

QMap<REntity::Id, QSet<int> > RDocument::queryIntersectedShapesXY(
        const RBox& box, bool checkBoundingBoxOnly, bool includeLockedLayers, RBlock::Id blockId,
        const QList<RS::EntityType>& filter) {

    RBox boxExpanded = box;
    boxExpanded.c1.z = RMINDOUBLE;
    boxExpanded.c2.z = RMAXDOUBLE;
    bool usingCurrentBlock = false;
    if (blockId==RBlock::INVALID_ID) {
        blockId = getCurrentBlockId();
    }

    usingCurrentBlock = (blockId == getCurrentBlockId());

    // always include construction lines (XLine):
    QMap<REntity::Id, QSet<int> > infinites;
    {
        QSet<REntity::Id> ids = queryInfiniteEntities();
        QSet<REntity::Id>::iterator it;
        for (it=ids.begin(); it!=ids.end(); it++) {
            infinites.insert(*it, QSet<int>());
        }
    }

    // box is completely outside the bounding box of this document:
    if (usingCurrentBlock && boxExpanded.isOutside(getBoundingBox()) && checkBoundingBoxOnly) {
        return infinites;
    }

    QMap<REntity::Id, QSet<int> > candidates;

    // box contains bounding box of this document:
    if (usingCurrentBlock && boxExpanded.contains(getBoundingBox())) {
        QSet<REntity::Id> ids = queryAllEntities(false, false);
        QSet<REntity::Id>::iterator it;
        for (it=ids.begin(); it!=ids.end(); it++) {
            candidates.insert(*it, QSet<int>());
        }
    }
    else {
        candidates = spatialIndex.queryIntersected(boxExpanded);
        candidates.unite(infinites);
    }

    RBox boxFlattened = box;
    boxFlattened.c1.z = 0.0;
    boxFlattened.c2.z = 0.0;
    RPolyline pl;
    pl.appendVertex(boxFlattened.c1);
    pl.appendVertex(RVector(boxFlattened.c2.x, boxFlattened.c1.y));
    pl.appendVertex(boxFlattened.c2);
    pl.appendVertex(RVector(boxFlattened.c1.x, boxFlattened.c2.y));
    pl.appendVertex(boxFlattened.c1);

    // filter out entities that don't intersect with the given box
    // or are not on the current block or are on a frozen layer:
    QMap<REntity::Id, QSet<int> > res;
    //QSet<REntity::Id> outsiders;
    QMap<REntity::Id, QSet<int> >::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); ++it) {
        QSharedPointer<REntity> entity = queryEntityDirect(it.key());
        if (entity.isNull()) {
            //outsiders.insert(*it);
            continue;
        }

        // undone:
        if (entity->isUndone()) {
            //outsiders.insert(*it);
            continue;
        }

        // not on current or given block:
        if (entity->getBlockId() != blockId) {
            //outsiders.insert(*it);
            continue;
        }

        // layer is off:
        if (isLayerFrozen(entity->getLayerId())) {
            //outsiders.insert(*it);
            continue;
        }

        // referenced block is off:
        QSharedPointer<RBlockReferenceEntity> blockRef = entity.dynamicCast<RBlockReferenceEntity>();
        if (!blockRef.isNull()) {
            RBlock::Id blockId = blockRef->getReferencedBlockId();
            if (blockId!=RBlock::INVALID_ID) {
                QSharedPointer<RBlock> block = queryBlockDirect(blockId);
                if (!block.isNull() && block->isFrozen()) {
                    //outsiders.insert(*it);
                    continue;
                }
            }
        }

        // layer is locked:
        if (!includeLockedLayers) {
            if (isLayerLocked(entity->getLayerId())) {
                //outsiders.insert(*it);
                continue;
            }
        }

        // apply filter:
        if (filter.contains(entity->getType())) {
            //outsiders.insert(*it);
            continue;
        }

        if (boxExpanded.contains(entity->getBoundingBox())) {
            res[it.key()] = it.value();
            continue;
        }

        if (!checkBoundingBoxOnly &&
            !entity->intersectsWith(pl)) {
            //outsiders.insert(*it);
            continue;
        }

        res[it.key()] = it.value();
    }

    return res;
    //return candidates - outsiders;
}


QSet<REntity::Id> RDocument::queryContainedEntitiesXY(const RBox& box) {
    RBox boxExpanded = box;
    boxExpanded.c1.z = RMINDOUBLE;
    boxExpanded.c2.z = RMAXDOUBLE;
    QSet<REntity::Id> candidates = queryContainedEntities(boxExpanded);

    //spatialIndex.queryContained(boxExpanded).keys().toSet();

    // filter out entities that are not on the current block
    // or whoes entire bounding box is not inside this query box
    // (e.g. block references which add multiple bounding boxes to the index):
    QSet<REntity::Id> outsiders;
    QSet<REntity::Id>::iterator it;
    for (it=candidates.begin(); it!=candidates.end(); ++it) {
        QSharedPointer<REntity> entity = queryEntity(*it);
        if (entity.isNull()) {
            outsiders.insert(*it);
            continue;
        }

        // undone:
        if (entity->isUndone()) {
            outsiders.insert(*it);
            continue;
        }

        // not on current block:
        if (entity->getBlockId() != getCurrentBlockId()) {
            outsiders.insert(*it);
            continue;
        }

        // layer is off:
        if (isLayerFrozen(entity->getLayerId())) {
            outsiders.insert(*it);
            continue;
        }

        // block is off:
        QSharedPointer<RBlockReferenceEntity> blockRef = entity.dynamicCast<RBlockReferenceEntity>();
        if (!blockRef.isNull()) {
            if (isBlockFrozen(blockRef->getReferencedBlockId())) {
                outsiders.insert(*it);
                continue;
            }
        }

        if (!boxExpanded.contains(entity->getBoundingBox())) {
            outsiders.insert(*it);
            continue;
        }
    }

    return candidates - outsiders;
}


/* *
 * \todo refactor (3D)
 *
 * Queries all entities which are completely inside the given box in X/Y direction
 * and at least partially inside the given box in Z direction.
 * This is used for selections on the XY plane.
 *
 * \param box Query box.
 *
 * \param result Set of entity IDs.
 */
/*
QSet<REntity::Id> RDocument::queryEntitiesContainedXYIntersectedZ(const RBox& box) {
    QSet<REntity::Id> intersected =
        queryIntersectedEntities(box, true);

    QSet<REntity::Id> contained2d =
        spatialIndex.queryContained(
            box.c1.x, box.c1.y, RMINDOUBLE,
            box.c2.x, box.c2.y, RMAXDOUBLE
        );

    return intersected.intersect(contained2d);
}
*/



/**
 * Queries all selected entities.
 *
 * \return Set of IDs of all selected entities.
 */
QSet<REntity::Id> RDocument::querySelectedEntities() {
    return storage.querySelectedEntities();
}



/**
 * Queries the object with the given ID.
 *
 * \return Shared pointer to the object or a null pointer.
 */
QSharedPointer<RObject> RDocument::queryObject(RObject::Id objectId) const {
    return storage.queryObject(objectId);
}

/**
 * Queries the object with the given ID.
 * If the storage has the object instantiated, the instance is
 * returned (rather than a clone).
 *
 * \return Pointer to the object or NULL.
 */
QSharedPointer<RObject> RDocument::queryObjectDirect(RObject::Id objectId) const {
    return storage.queryObjectDirect(objectId);
}

QSharedPointer<RObject> RDocument::queryObjectByHandle(RObject::Handle objectHandle) const {
    return storage.queryObjectByHandle(objectHandle);
}

/**
 * Queries the entity with the given ID.
 *
 * \return Pointer to the entity or NULL.
 */
QSharedPointer<REntity> RDocument::queryEntity(REntity::Id entityId) const {
    return storage.queryEntity(entityId);
}

/**
 * Queries the entity with the given ID.
 * If the storage has the entity instantiated, the instance is
 * returned (rather than a clone).
 *
 * \return Pointer to the entity or NULL.
 */
QSharedPointer<REntity> RDocument::queryEntityDirect(REntity::Id entityId) const {
    return storage.queryEntityDirect(entityId);
}



/**
 * Queries the UCS with the given ID.
 *
 * \return Pointer to the UCS or NULL.
 */
QSharedPointer<RUcs> RDocument::queryUcs(RUcs::Id ucsId) const {
    return storage.queryUcs(ucsId);
}



/**
 * Queries the UCS with the given name.
 *
 * \return Pointer to the UCS or NULL.
 */
QSharedPointer<RUcs> RDocument::queryUcs(const QString& ucsName) const {
    return storage.queryUcs(ucsName);
}


/**
 * Queries the layer with the given ID.
 *
 * \return Pointer to the layer or NULL.
 */
QSharedPointer<RLayer> RDocument::queryLayer(RLayer::Id layerId) const {
    return storage.queryLayer(layerId);
}

/**
 * Queries the layer with the given ID direct (no cloning).
 *
 * \return Pointer to the layer or NULL.
 */
QSharedPointer<RLayer> RDocument::queryLayerDirect(RLayer::Id layerId) const {
    return storage.queryLayerDirect(layerId);
}

/**
 * Queries the layer with the given name.
 *
 * \return Pointer to the layer or NULL.
 */
QSharedPointer<RLayer> RDocument::queryLayer(const QString& layerName) const {
    return storage.queryLayer(layerName);
}

QSharedPointer<RBlock> RDocument::queryBlockDirect(RBlock::Id blockId) const {
    return storage.queryBlockDirect(blockId);
}

QSharedPointer<RBlock> RDocument::queryBlock(RBlock::Id blockId) const {
    return storage.queryBlock(blockId);
}

QSharedPointer<RBlock> RDocument::queryBlock(const QString& blockName) const {
    return storage.queryBlock(blockName);
}

QSharedPointer<RView> RDocument::queryView(RView::Id viewId) const {
    return storage.queryView(viewId);
}

QSharedPointer<RView> RDocument::queryView(const QString& viewName) const {
    return storage.queryView(viewName);
}

QSharedPointer<RLinetype> RDocument::queryLinetype(RLinetype::Id linetypeId) const {
    return storage.queryLinetype(linetypeId);
}

QSharedPointer<RLinetype> RDocument::queryLinetype(const QString& linetypeName) const {
    return storage.queryLinetype(linetypeName);
}

bool RDocument::isSelected(REntity::Id entityId) {
    return storage.isSelected(entityId);
}

bool RDocument::isLayerLocked(RLayer::Id layerId) const {
    return storage.isLayerLocked(layerId);
}

bool RDocument::isEntityEditable(REntity::Id entityId) const {
    QSharedPointer<REntity> entity = queryEntityDirect(entityId);
    if (entity.isNull()) {
        return false;
    }

    return entity->isEditable();
}

//bool RDocument::isEntityLayerLocked(REntity::Id entityId) const {
//    QSharedPointer<REntity> entity = queryEntityDirect(entityId);
//    if (entity.isNull()) {
//        return false;
//    }

//    return isLayerLocked(entity->getLayerId());
//}

bool RDocument::isLayerFrozen(RLayer::Id layerId) const {
    return storage.isLayerFrozen(layerId);
}

bool RDocument::isBlockFrozen(RBlock::Id blockId) const {
    return storage.isBlockFrozen(blockId);
}

bool RDocument::isEntityLayerFrozen(REntity::Id entityId) const {
    QSharedPointer<REntity> entity = queryEntityDirect(entityId);
    if (entity.isNull()) {
        return false;
    }

    return storage.isLayerFrozen(entity->getLayerId());
}

/**
 * \todo refactoring to operation
 *
 * Deselectes all selected entities.
 */
void RDocument::clearSelection(QSet<REntity::Id>* affectedEntities) {
    storage.clearEntitySelection(affectedEntities);
}

/**
 * Selects all not selected entities.
 */
void RDocument::selectAllEntites(QSet<REntity::Id>* affectedEntities) {
    storage.selectAllEntites(affectedEntities);
}

/**
 * \todo refactoring to operation
 *
 * \copydoc RStorage::selectEntity
 */
void RDocument::selectEntity(
    REntity::Id entityId,
    bool add,
    QSet<REntity::Id>* affectedEntities) {

    storage.selectEntity(entityId, add, affectedEntities);
}

/**
 * \copydoc RStorage::deselectEntity
 */
void RDocument::deselectEntity(
    REntity::Id entityId,
    QSet<REntity::Id>* affectedEntities) {

    storage.deselectEntity(entityId, affectedEntities);
}

/**
 * \todo refactoring to operation
 *
 * \copydoc RStorage::selectEntities
 *
 */
void RDocument::selectEntities(
    const QSet<REntity::Id>& entityIds,
    bool add,
    QSet<REntity::Id>* affectedEntities) {

    storage.selectEntities(entityIds, add, affectedEntities);
}

/**
 * \todo refactoring to operation
 *
 * \copydoc RStorage::deselectEntities
 *
 */
void RDocument::deselectEntities(
    const QSet<REntity::Id>& entityIds,
    QSet<REntity::Id>* affectedEntities) {

    storage.deselectEntities(entityIds, affectedEntities);
}

bool RDocument::hasSelection() const {
    return storage.hasSelection();
}

/**
 * \copydoc RStorage::getBoundingBox
 */
RBox RDocument::getBoundingBox(bool includeHiddenLayer) const {
    return storage.getBoundingBox(includeHiddenLayer);
}

RBox RDocument::getSelectionBox() const {
    return storage.getSelectionBox();
}

/**
 * Rebuilds the entire spatial index from scratch (e.g. when current
 * block is changed).
 */
void RDocument::rebuildSpatialIndex() {
    spatialIndex.clear();

    QSet<REntity::Id> result = storage.queryAllEntities(false, true);

    QSetIterator<REntity::Id> i(result);
    while (i.hasNext()) {
        QSharedPointer<REntity> entity = storage.queryEntityDirect(i.next());
        if (entity.isNull()) {
            continue;
        }
        if (entity->isUndone()) {
            continue;
        }

        QList<RBox> bbs = entity->getBoundingBoxes();

        spatialIndex.addToIndex(
            entity->getId(),
            bbs
        );
    }
}

void RDocument::removeBlockFromSpatialIndex(RBlock::Id blockId) {
    static int recursionDepth = 0;
    recursionDepth++;

    if (recursionDepth>16) {
        recursionDepth--;
        return;
    }

    // remove entry for block references to the block the entity belongs to:
    QSet<REntity::Id> blockRefIds = queryBlockReferences(blockId);
    QSet<REntity::Id>::iterator it;
    for (it=blockRefIds.begin(); it!=blockRefIds.end(); it++) {
        QSharedPointer<RBlockReferenceEntity> blockRef = queryEntityDirect(*it).dynamicCast<RBlockReferenceEntity>();
        if (blockRef.isNull()) {
            continue;
        }

        removeBlockFromSpatialIndex(blockRef->getBlockId());
        removeFromSpatialIndex(blockRef);
    }

    recursionDepth--;
}

bool RDocument::blockContainsReferences(RBlock::Id blockId, RBlock::Id referencedBlockId) {
    if (blockId==referencedBlockId) {
        return true;
    }

    static int recursionDepth = 0;
    if (recursionDepth++>16) {
        recursionDepth--;
        qWarning() << "RDocument::blockContainsReferences: "
            << "maximum recursion depth reached: blockId: " << blockId;
        return true;
    }

    QSet<REntity::Id> blockEntityIds = queryBlockEntities(blockId);
    QSet<REntity::Id>::iterator it;
    for (it=blockEntityIds.begin(); it!=blockEntityIds.end(); it++) {
        QSharedPointer<REntity> entity = queryEntityDirect(*it);
        QSharedPointer<RBlockReferenceEntity> blockReference = entity.dynamicCast<RBlockReferenceEntity>();
        if (blockReference.isNull()) {
            continue;
        }

        if (blockContainsReferences(blockReference->getReferencedBlockId(), referencedBlockId)) {
            recursionDepth--;
            return true;
        }
    }

    recursionDepth--;
    return false;
}

/**
 * Add block references that point to blockId, unless they also point to ignoreBlockId.
 */
bool RDocument::addBlockToSpatialIndex(RBlock::Id blockId, RBlock::Id ignoreBlockId) {
    if (blockContainsReferences(blockId, ignoreBlockId)) {
        //qDebug() << "RDocument::addBlockToSpatialIndex: block " << getBlockName(blockId) << " contains " << getBlockName(ignoreBlockId);
        return false;
    }

    // add entries for block references to the block the entity belongs to:
    QSet<REntity::Id> blockRefIds = queryBlockReferences(blockId);
    QSet<REntity::Id>::iterator it;
    QSet<RBlock::Id> added;

    for (it=blockRefIds.begin(); it!=blockRefIds.end(); it++) {
        QSharedPointer<RBlockReferenceEntity> blockRef = queryEntityDirect(*it).dynamicCast<RBlockReferenceEntity>();
        if (blockRef.isNull()) {
            continue;
        }

        if (!added.contains(blockRef->getBlockId())) {
            addBlockToSpatialIndex(blockRef->getBlockId(), ignoreBlockId);
            added.insert(blockRef->getBlockId());
        }
        //if (!addBlockToSpatialIndex(blockRef->getBlockId(), ignoreBlockId)) {
        //    return false;
        //}

        blockRef->update();
        addToSpatialIndex(blockRef);
    }

    return true;
}


void RDocument::removeFromSpatialIndex(QSharedPointer<REntity> entity /*, REntity::Id subEntityId*/) {
    QList<RBox> bbs = entity->getBoundingBoxes(/*subEntityId*/);
    bool ok = spatialIndex.removeFromIndex(entity->getId(), bbs);
    if (!ok) {
        qWarning() << "RDocument::removeFromSpatialIndex: removing entity: " << *entity;
        qWarning() << "failed to remove entity from spatial index";
    }
}

void RDocument::addToSpatialIndex(QSharedPointer<REntity> entity) {
    spatialIndex.addToIndex(entity->getId(), entity->getBoundingBoxes());
}


void RDocument::updateAllEntities() {
    QSet<REntity::Id> ids = queryAllEntities(false, false);

    QSet<REntity::Id>::iterator it;
    for (it=ids.begin(); it!=ids.end(); it++) {
        QSharedPointer<REntity> entity = queryEntityDirect(*it);
        entity->update();
    }
}

/**
 * Undoes the last transaction.
 *
 * \return The transaction that was undone. Higher level callers can use
 *   this set to update scenes, views, etc accordingly.
 */
RTransaction RDocument::undo() {
    return transactionStack.undo();
}

/**
 * Redoes a previously undone transaction.
 *
 * \return Set of affected entity IDs. Higher level callers can use
 *   this set to update scenes, views, etc accordingly.
 */
RTransaction RDocument::redo() {
    return transactionStack.redo();
}

bool RDocument::isModified() const {
    return storage.isModified();
}

void RDocument::setModified(bool m) {
    storage.setModified(m);
}

RDocument& RDocument::getClipboard() {
    if (clipboard==NULL) {
        clipboard = new RDocument(
            *(new RMemoryStorage()),
            *(new RSpatialIndexSimple())
        );
    }

    return *clipboard;
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RDocument& d) {
    dbg.nospace() << "RDocument(" << QString("0x%1").arg((long int)&d, 0, 16) << ", ";
    dbg.nospace() << d.getStorage();
    dbg.nospace() << d.getSpatialIndex();
    return dbg.space();
}

void RDocument::dump() {
    qDebug() << *this;
}
