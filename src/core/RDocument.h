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

#ifndef RDOCUMENT_H
#define RDOCUMENT_H

#include "core_global.h"

#include <QString>
#include <QSharedPointer>

#include "RNonCopyable.h"
#include "RRequireHeap.h"
#include "RTransactionStack.h"
#include "RBox.h"
#include "RMath.h"
#include "RLineweight.h"

class RBlock;
class RColor;
class RDimStyle;
class RDocumentVariables;
class REntity;
class RLayer;
class RLayerState;
class RLayout;
class RLinetype;
class RLinetypePattern;
class RVector;
class RSpatialIndex;
class RStorage;
class RUcs;
class RView;

#ifndef RDEFAULT_QVARIANT
#define RDEFAULT_QVARIANT QVariant()
#endif

#ifndef RDEFAULT_QLIST_RBOX
#define RDEFAULT_QLIST_RBOX QList<RBox>()
#endif

#ifndef RDEFAULT_QSTRINGLIST
#define RDEFAULT_QSTRINGLIST QStringList()
#endif

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

#define RDEFAULT_QLIST_RS_ENTITYTYPE QList<RS::EntityType>()


/**
 * A graphics document contains and owns entities, layers, user coordinate
 * systems, variables, block definitions, etc.
 *
 * Every document maintains a spatial index for fast entity lookups.
 * Documents also handle transactions through a \ref RTransactionStack.
 * A document is backed by an \ref RStorage implementation to
 * store the document for the duration of the document's lifetime.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RDocument : public RRequireHeap, RNonCopyable {
public:
    RDocument(RStorage& storage, RSpatialIndex& spatialIndex, bool beforeLoad = false);
    virtual ~RDocument();

    void init(bool beforeLoad=false);
    void initLinetypes(RTransaction* transaction=NULL);
    QList<QSharedPointer<RObject> > getDefaultLinetypes();

    RStorage& getStorage();
    const RStorage& getStorage() const;
    RSpatialIndex& getSpatialIndex();
    const RSpatialIndex& getSpatialIndex() const;
    RSpatialIndex* getSpatialIndexForBlock(RObject::Id blockId) const;
    RSpatialIndex* getSpatialIndexForCurrentBlock() const;
    RTransactionStack& getTransactionStack();

    void clear(bool beforeLoad=false);

    RObject::Id queryClosestXY(
        const RVector& wcsPosition,
        double range,
        bool draft,
        double strictRange = RMAXDOUBLE,
        bool includeLockedLayers = true,
        bool selectedOnly = false
    );
    QPair<RObject::Id, QSet<int> > queryClosestXYWithIndices(
        const RVector& wcsPosition,
        double range,
        bool draft,
        double strictRange = RMAXDOUBLE,
        bool includeLockedLayers = true,
        bool selectedOnly = false
    );

    RObject::Id queryClosestXY(
        QSet<RObject::Id>& candidates,
        const RVector& wcsPosition,
        double range,
        bool draft,
        double strictRange = RMAXDOUBLE
    );
    QPair<RObject::Id, QSet<int> > queryClosestXYWithIndices(
            QMap<RObject::Id, QSet<int> >& candidates,
            const RVector& wcsPosition,
            double range,
            bool draft,
            double strictRange = RMAXDOUBLE);

    QSet<RObject::Id> queryAllObjects() const;
    QSet<RObject::Id> querySelectedLayers() const;
    QSet<RObject::Id> queryAllVisibleEntities() const;
    QSet<RObject::Id> queryAllEntities(bool undone = false, bool allBlocks = false, RS::EntityType type = RS::EntityAll) const;
    QSet<RObject::Id> queryAllEntities(bool undone, bool allBlocks, QList<RS::EntityType> types) const;
    QSet<RObject::Id> queryWorkingSetEntities() const;
    QSet<RObject::Id> queryAllUcs() const;
    QSet<RObject::Id> queryAllLayers() const;
    QSet<RObject::Id> queryAllLayerStates() const;
    QSet<RObject::Id> queryAllBlocks() const;
    QSet<RObject::Id> queryAllLayoutBlocks(bool includeModelSpace = false) const;
    QSet<RObject::Id> queryAllLayouts() const;
    QSet<RObject::Id> queryAllViews() const;
    QSet<RObject::Id> queryAllLinetypes() const;

    QSet<RObject::Id> queryLayerEntities(RObject::Id layerId, bool allBlocks = false) const;
    QSet<RObject::Id> querySelectedLayerEntities(RObject::Id layerId, bool allBlocks = false) const;
    bool hasBlockEntities(RObject::Id blockId) const;
    QSet<RObject::Id> queryBlockEntities(RObject::Id blockId) const;
    QSet<RObject::Id> queryLayerBlockEntities(RObject::Id layerId, RObject::Id blockId) const;
    QSet<RObject::Id> queryChildEntities(RObject::Id parentId, RS::EntityType type = RS::EntityAll) const;
    bool hasChildEntities(RObject::Id parentId) const;
    QSet<RObject::Id> queryBlockReferences(RObject::Id blockId) const;
    QSet<RObject::Id> queryAllBlockReferences() const;
    QSet<RObject::Id> queryAllViewports() const;

    QSet<RObject::Id> queryContainedEntities(const RBox& box) const;

    QSet<RObject::Id> queryInfiniteEntities() const;

    QSet<RObject::Id> queryIntersectedEntitiesXYFast(const RBox& box);
    QSet<RObject::Id> queryIntersectedShapesXYFast(const RBox& box, bool noInfiniteEntities = false);

    QSet<RObject::Id> queryIntersectedEntitiesXY(const RBox& box,
        bool checkBoundingBoxOnly=false,
        bool includeLockedLayers=true,
        RObject::Id blockId = RObject::INVALID_ID,
        const QList<RS::EntityType>& filter = RDEFAULT_QLIST_RS_ENTITYTYPE,
        bool selectedOnly = false,
        RObject::Id layerId = RObject::INVALID_ID) const;

    QMap<RObject::Id, QSet<int> > queryIntersectedEntitiesXYWithIndex(const RBox& box,
         bool checkBoundingBoxOnly=false,
         bool includeLockedLayers=true,
         RObject::Id blockId = RObject::INVALID_ID,
         const QList<RS::EntityType>& filter = RDEFAULT_QLIST_RS_ENTITYTYPE,
         bool selectedOnly = false,
         RObject::Id layerId = RObject::INVALID_ID) const;

    QMap<RObject::Id, QSet<int> > queryIntersectedShapesXY(const RBox& box,
        bool checkBoundingBoxOnly=false,
        bool includeLockedLayers=true,
        RObject::Id blockId = RObject::INVALID_ID,
        const QList<RS::EntityType>& filter = RDEFAULT_QLIST_RS_ENTITYTYPE,
        bool selectedOnly = false,
        RObject::Id layerId = RObject::INVALID_ID) const;

    QSet<RObject::Id> queryContainedEntitiesXY(const RBox& box) const;

    QSet<RObject::Id> querySelectedEntities() const;

    QSet<RObject::Id> queryConnectedEntities(RObject::Id entityId, double tolerance = RS::PointTolerance, RObject::Id layerId = RObject::INVALID_ID);

    QSet<RObject::Id> queryPropertyEditorObjects();

    QSharedPointer<RDocumentVariables> queryDocumentVariables() const;
    QSharedPointer<RDocumentVariables> queryDocumentVariablesDirect() const;
    QSharedPointer<RDimStyle> queryDimStyle() const;
    QSharedPointer<RDimStyle> queryDimStyleDirect() const;
    QSharedPointer<RObject> queryObject(RObject::Id objectId) const;
    QSharedPointer<RObject> queryObjectDirect(RObject::Id objectId) const;
    RObject* queryObjectCC(RObject::Id objectId) const;
    QSharedPointer<RObject> queryObjectByHandle(RObject::Handle objectHandle) const;
    QSharedPointer<REntity> queryEntity(RObject::Id entityId) const;
    QSharedPointer<REntity> queryEntityDirect(RObject::Id entityId) const;
    QSharedPointer<REntity> queryVisibleEntityDirect(RObject::Id entityId) const;
    QSharedPointer<RUcs> queryUcs(RObject::Id ucsId) const;
    QSharedPointer<RUcs> queryUcs(const QString& ucsName) const;
    QSharedPointer<RLayer> queryLayer(RObject::Id layerId) const;
    QSharedPointer<RLayer> queryLayerDirect(RObject::Id layerId) const;
    QSharedPointer<RLayer> queryLayer(const QString& layerName) const;
    QSharedPointer<RLayerState> queryLayerState(RObject::Id layerStateId) const;
    QSharedPointer<RLayerState> queryLayerStateDirect(RObject::Id layerStateId) const;
    QSharedPointer<RLayerState> queryLayerState(const QString& layerStateName) const;
    QSharedPointer<RLayout> queryLayout(RObject::Id layoutId) const;
    QSharedPointer<RLayout> queryLayoutDirect(RObject::Id layoutId) const;
    QSharedPointer<RLayout> queryLayout(const QString& layoutName) const;
    QSharedPointer<RBlock> queryBlock(RObject::Id blockId) const;
    QSharedPointer<RBlock> queryBlockDirect(RObject::Id blockId) const;
    QSharedPointer<RBlock> queryBlockDirect(const QString& blockName) const;
    QSharedPointer<RBlock> queryBlock(const QString& blockName) const;
    QSharedPointer<RView> queryView(RObject::Id viewId) const;
    QSharedPointer<RView> queryView(const QString& viewName) const;
    QSharedPointer<RLinetype> queryLinetype(RObject::Id linetypeId) const;
    QSharedPointer<RLinetype> queryLinetype(const QString& linetypeName) const;

    int countSelectedEntities() const;

    void clearSelection(
        QSet<RObject::Id>* affectedEntities=NULL
    );

    void selectAllEntities(QSet<RObject::Id>* affectedEntities = NULL);

    void selectEntity(
        RObject::Id entityId,
        bool add=false,
        QSet<RObject::Id>* affectedEntities=NULL
    );
    void deselectEntity(
        RObject::Id entityId,
        QSet<RObject::Id>* affectedEntities=NULL
    );
    int selectEntities(
        const QSet<RObject::Id>& entityId,
        bool add=false,
        QSet<RObject::Id>* affectedEntities=NULL
    );
    int deselectEntities(
        const QSet<RObject::Id>& entityId,
        QSet<RObject::Id>* affectedEntities=NULL
    );
    bool isSelected(RObject::Id entityId);
    bool isSelectedWorkingSet(RObject::Id entityId);
    bool isLayerLocked(RObject::Id layerId) const;
    bool isLayerLocked(const RLayer& layer) const;
    bool isParentLayerLocked(RObject::Id layerId) const;
    bool isParentLayerLocked(const RLayer& layer) const;

    bool isEntity(RObject::Id objectId) const;
    bool isEntityEditable(RObject::Id entityId) const;
    //bool isEntityLayerLocked(RObject::Id entityId) const;

    bool isLayerOff(RObject::Id layerId) const;
    bool isLayerOff(const RLayer& layer) const;

    bool isLayerOffOrFrozen(RObject::Id layerId) const;
    bool isLayerOffOrFrozen(const RLayer& layer) const;

    bool isLayerFrozen(RObject::Id layerId) const;
    bool isLayerFrozen(const RLayer& layer) const;
    bool isLayerPlottable(RObject::Id layerId) const;
    bool isLayerPlottable(const RLayer& layer) const;
    bool isLayerSnappable(RObject::Id layerId) const;
    bool isLayerSnappable(const RLayer& layer) const;
    bool isParentLayerFrozen(RObject::Id layerId) const;
    bool isParentLayerFrozen(const RLayer& layer) const;
    bool isBlockFrozen(RObject::Id blockId) const;
    bool isLayoutBlock(RObject::Id blockId) const;
    bool isEntityLayerFrozen(RObject::Id entityId) const;

    bool isEntityVisible(const REntity& entity, RObject::Id blockId = RObject::INVALID_ID) const;

    bool isParentLayerSnappable(RObject::Id layerId) const;
    bool isParentLayerSnappable(const RLayer& layer) const;

    bool isParentLayerPlottable(RObject::Id layerId) const;
    bool isParentLayerPlottable(const RLayer& layer) const;

    bool hasSelection() const;

    RBox getBoundingBox(bool ignoreHiddenLayers = true, bool ignoreEmpty = false) const;
    RBox getSelectionBox() const;
    RBox getEntitiesBox(QSet<RObject::Id>& ids) const;

    //void addToSpatialIndex(RObject& object, bool isNew = false);
    void clearSpatialIndices();
    virtual void rebuildSpatialIndex();
    //void addToSpatialIndex(QSharedPointer<REntity> entity);
    void addToSpatialIndex(QSharedPointer<REntity> entity);

    bool blockContainsReferences(RObject::Id blockId, RObject::Id referencedBlockId);

    void removeBlockFromSpatialIndex(RObject::Id blockId);
    bool addBlockToSpatialIndex(RObject::Id blockId, RObject::Id ignoreBlockId);
    virtual void removeFromSpatialIndex(QSharedPointer<REntity> entity, const QList<RBox>& boundingBoxes = RDEFAULT_QLIST_RBOX);
    //virtual void removeFromSpatialIndex2(QSharedPointer<REntity> entity);

    void updateAllEntities();

    QList<RTransaction> undo();
    QList<RTransaction> redo();
    bool isUndoAvailable() const;
    bool isRedoAvailable() const;

    void startTransactionGroup();
    int getTransactionGroup() const;

    /**
     * True: add all operations to the current transaction group
     */
    void setAutoTransactionGroup(bool on) {
        autoTransactionGroup = on;
    }
    bool getAutoTransactionGroup() const {
        return autoTransactionGroup;
    }

    void resetTransactionStack();

    void setFileName(const QString& fn);
    QString getFileName() const;

    void setFileVersion(const QString& fv);
    QString getFileVersion() const;

    QSharedPointer<RLayer> queryCurrentLayer();
//    RTransaction setCurrentLayer(RObject::Id layerId);
//    RTransaction setCurrentLayer(const QString& layerName);
//    void setCurrentLayer(RTransaction& transaction, RObject::Id layerId);
//    void setCurrentLayer(RTransaction& transaction, const QString& layerName);
    void setCurrentLayer(RObject::Id layerId, RTransaction* transaction=NULL);
    void setCurrentLayer(const QString& layerName, RTransaction* transaction=NULL);
    RObject::Id getCurrentLayerId() const;
    QString getCurrentLayerName() const;

    void setCurrentColor(const RColor& color);
    RColor getCurrentColor() const;

    void setCurrentLineweight(RLineweight::Lineweight lw);
    RLineweight::Lineweight getCurrentLineweight() const;

    void setCurrentLinetype(RObject::Id ltId);
    void setCurrentLinetype(const QString& name);
    void setCurrentLinetypePattern(const RLinetypePattern& p);
    RObject::Id getCurrentLinetypeId() const;
    RLinetypePattern getCurrentLinetypePattern() const;

    QSharedPointer<RBlock> queryCurrentBlock();
    void setCurrentBlock(RObject::Id blockId);
    void setCurrentBlock(const QString& blockName);
    RObject::Id getCurrentBlockId() const;
    QString getCurrentBlockName() const;

    void setCurrentViewport(RObject::Id viewportId);
    RObject::Id getCurrentViewportId();
    bool hasCurrentViewport();
    void unsetCurrentViewport();

//    void setSelectedBlock(RObject::Id blockId);
//    void setSelectedBlock(const QString& blockName);
//    RObject::Id getSelectedBlockId() const;

    QSharedPointer<RView> queryCurrentView();
    void setCurrentView(RObject::Id viewId);
    void setCurrentView(const QString& viewName);
    RObject::Id getCurrentViewId() const;

    QString getTempBlockName() const;
    QString getUniqueBlockName(const QString& currentName, const QStringList& usedBlockNames = RDEFAULT_QSTRINGLIST) const;
    QString getBlockName(RObject::Id blockId) const;
    QString getBlockNameFromHandle(RObject::Handle blockHandle) const;
    QString getBlockNameFromLayout(const QString& layoutName) const;
    QString getBlockNameFromLayout(RObject::Id layoutId) const;
    QSet<QString> getBlockNames(const QString& rxStr = RDEFAULT_QSTRING, bool undone = false) const;
    QList<RObject::Id> sortBlocks(const QList<RObject::Id>& blockIds) const;
    QList<RObject::Id> sortLayers(const QList<RObject::Id>& layerIds) const;
    QString getLayerName(RObject::Id layerId) const;
    QSet<QString> getLayerNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    QString getLayerStateName(RObject::Id layerStateId) const;
    QSet<QString> getLayerStateNames(const QString& rxStr = RDEFAULT_QSTRING) const;
    QString getLayoutName(RObject::Id layoutId) const;
    QSet<QString> getViewNames() const;

    bool hasLayer(const QString& layerName) const;
    bool hasLayerStates() const;
    bool hasLayerState(const QString& layerStateName) const;
    bool hasBlock(const QString& blockName) const;
    bool hasLayout(const QString& layoutName) const;
    bool hasView(const QString& viewName) const;
    bool hasLinetype(const QString& linetypeName) const;

    RObject::Id getLayerId(const QString& layerName) const;
    RObject::Id getLayer0Id() const;

    RObject::Id getLayerStateId(const QString& layerStateName) const;

    RObject::Id getBlockId(const QString& blockName) const;
    RObject::Id getBlockIdAuto(const QString& blockLayoutName) const;
    RObject::Id getModelSpaceBlockId() const;

    RObject::Id getLinetypeId(const QString& linetypeName) const;
    RObject::Id getLinetypeByLayerId() const {
        return linetypeByLayerId;
    }
    RObject::Id getLinetypeByBlockId() const {
        return linetypeByBlockId;
    }
    QString getLinetypeName(RObject::Id linetypeId) const;
    QString getLinetypeDescription(RObject::Id linetypeId) const;
    QString getLinetypeLabel(RObject::Id linetypeId) const;
    QSet<QString> getLinetypeNames() const;
    QList<RLinetypePattern> getLinetypePatterns() const;
    bool isByLayer(RObject::Id linetypeId) const;
    bool isByBlock(RObject::Id linetypeId) const;

    RLineweight::Lineweight getMaxLineweight() const;

    QStringList getVariables() const;
    void setVariable(const QString& key, const QVariant& value, bool overwrite=true);
    QVariant getVariable(const QString& key, const QVariant& defaultValue = RDEFAULT_QVARIANT, bool useSettings = false) const;
    bool hasVariable(const QString& key) const;
    void removeVariable(const QString& key);

    void setKnownVariable(RS::KnownVariable key, const QVariant& value, RTransaction* transaction = NULL);
    void setKnownVariable(RS::KnownVariable key, const RVector& value, RTransaction* transaction = NULL);
    QVariant getKnownVariable(RS::KnownVariable key, const QVariant& defaultValue = RDEFAULT_QVARIANT) const;

    void setUnit(RS::Unit unit, RTransaction* transaction = NULL);
    RS::Unit getUnit() const;

    void setMeasurement(RS::Measurement m,  RTransaction* transaction = NULL);
    RS::Measurement getMeasurement() const;

    bool isMetric() const;

    void setDimensionFont(const QString& f, RTransaction* transaction = NULL);
    QString getDimensionFont() const;

    void setLinetypeScale(double v, RTransaction* transaction = NULL);
    double getLinetypeScale() const;

    QString formatLinear(double value);
    QString formatAngle(double value);

    void setLinearFormat(RS::LinearFormat f);
    RS::LinearFormat getLinearFormat() const;
    int getLinearPrecision();
    bool showLeadingZeroes();
    bool showTrailingZeroes();
    bool showLeadingZeroesAngle();
    bool showTrailingZeroesAngle();
    RS::AngleFormat getAngleFormat();
    int getAnglePrecision();
    char getDecimalSeparator();

    bool isModified() const;
    QDateTime getLastModifiedDateTime() const;
    QString getLastModified() const;
    void setModified(bool m);

    void copyVariablesFrom(const RDocument& other);

    QString addAutoVariable(double value);
    QStringList getAutoVariables() const;
    QString substituteAutoVariables(const QString& expression);
    double eval(const QString& expression, bool* ok = NULL);

    bool isEditingWorkingSet() const;
    void setIgnoreWorkingSet(bool on);

    void setNotifyListeners(bool on);
    bool getNotifyListeners() const;

//    RObject::Id getWorkingSetBlockReferenceId() const;
//    void setWorkingSetBlockReferenceId(RObject::Id id, int group = RDEFAULT_MIN1, RTransaction* transaction = NULL);

    /*
    void copyToDocument(const RVector& reference, RDocument& other,
        bool selectionOnly, bool clear, RTransaction& transaction);
    void copyToDocument(REntity& entity, const RVector& reference,
        RDocument& other, RTransaction& transaction);
    */

    static RDocument& getClipboard();

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, RDocument& d);

    void dump();

protected:
    static RDocument* clipboard;

private:
    QString fileName;
    QString fileVersion;

    RStorage& storage;
    // spatial index used to spawn new spatial indices for each block:
    RSpatialIndex& spatialIndex;
    bool disableSpatialIndicesByBlock;
    // map of spatial indices (per block):
    mutable QMap<RObject::Id, RSpatialIndex*> spatialIndicesByBlock;
    RTransactionStack transactionStack;
    //RObject::Id modelSpaceBlockId;
    RObject::Id linetypeByLayerId;
    RObject::Id linetypeByBlockId;

    bool autoTransactionGroup;
};

Q_DECLARE_METATYPE(RDocument*)
Q_DECLARE_METATYPE(const RDocument*)

#endif
