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

#include <QSet>

#include "RArc.h"
#include "RArcExporter.h"
#include "RBlockReferenceEntity.h"
#include "RCircle.h"
#include "RDebug.h"
#include "RDocument.h"
#include "REllipse.h"
#include "REntity.h"
#include "RExporter.h"
#include "RLine.h"
#include "RLinetype.h"
#include "RMainWindow.h"
#include "RPainterPathSource.h"
#include "RPolyline.h"
#include "RSettings.h"
#include "RShapesExporter.h"
#include "RSpline.h"
#include "RStorage.h"
#include "RTriangle.h"
#include "RUnit.h"
#include "RView.h"
#include "RViewportEntity.h"
#include "RXLine.h"

class RImageData;

RExporter::RExporter()
    : document(NULL),
      currentLayer(NULL),
      layerSource(NULL),
      blockSource(NULL),
      draftMode(false),
      twoColorSelectedMode(false),
      screenBasedLinetypes(false),
      visualExporter(false),
      pixelSizeHint(0.5),
      pixelUnit(false),
      clipping(false),
      pixelWidth(false),
      penCapStyle(Qt::RoundCap),
      //combineTransforms(true),
      projectionRenderingHint(RS::RenderThreeD) {

    init();
}

RExporter::RExporter(RDocument& document, RMessageHandler *messageHandler, RProgressHandler *progressHandler)
    : document(&document),
      currentLayer(NULL),
      layerSource(NULL),
      blockSource(NULL),
      draftMode(false),
      twoColorSelectedMode(false),
      screenBasedLinetypes(false),
      visualExporter(false),
      pixelSizeHint(0.5),
      pixelUnit(false),
      clipping(false),
      pixelWidth(false),
      penCapStyle(Qt::RoundCap),
      //combineTransforms(true),
      projectionRenderingHint(RS::RenderThreeD) {

    Q_UNUSED(messageHandler)
    Q_UNUSED(progressHandler)

    init();
}



RExporter::~RExporter() {
}

void RExporter::init() {
    currentPen.setColor(Qt::white);
    currentPen.setWidth(3);
    currentPen.setStyle(Qt::SolidLine);

    currentBrush.setColor(Qt::white);
    currentBrush.setStyle(Qt::SolidPattern);

    // init pen cap style (usually round):
    //int v = RSettings::getIntValue("GraphicsView/PenCapStyle", Qt::RoundCap);
    //penCapStyle = (Qt::PenCapStyle)v;
    currentPen.setCapStyle(penCapStyle);
    // needed when exporting polyline to bitmap:
    currentPen.setJoinStyle(Qt::RoundJoin);
}

QString RExporter::getErrorMessage() const {
    return errorMessage;
}

void RExporter::setLayerSource(RDocument* ls) {
    layerSource = ls;
}

void RExporter::setBlockSource(RDocument* bs) {
    blockSource = bs;
}

/**
 * \return The document that is currently being exported.
 */
RDocument& RExporter::getDocument() const {
    Q_ASSERT(document!=NULL);
    return *document;
}

/**
 * \return Block reference that is currently being exported or
 *      if no block reference is being exported, the current entity
 *      that is being exported.
 */
REntity* RExporter::getBlockRefOrEntity() {
    if (blockRefViewportStack.isEmpty()) {
        return getEntity();
    }

    // return the top block reference in the hierarchy. this is the
    // first in the stack, NOT the stack top:
    return blockRefViewportStack.first();
}

REntity::Id RExporter::getBlockRefOrEntityId() {
    REntity* entity = getBlockRefOrEntity();
    if (entity==NULL) {
        return REntity::INVALID_ID;
    }
    else {
        return entity->getId();
    }
}

/**
 * \return Pointer to the entity that is currently being exported.
 */
const REntity* RExporter::getEntity() const {
    if (entityStack.isEmpty()) {
        return NULL;
    }
    return entityStack.top();
}

/**
 * Sets a rendering hint for the current projection used for exports.
 *
 * This is a rendering hint for the exporting entity to decide how
 * its geometry should be rendered. For example a wall with a window
 * exports itself differently when viewed from top than when viewed
 * from the front or side. Note that the rendering difference is not
 * only in the projection in a mathematical sense, but also in what
 * edges are exported, how they are visualized and what types of
 * shapes are exported (lines and arcs or triangles).
 *
 * This rendering hint may also be used to determine what grid is
 * appropriate to display for exporters that export to a graphics
 * scene.
 *
 * The mathematical projection is defined separately by \ref setProjection().
 */
void RExporter::setProjectionRenderingHint(RS::ProjectionRenderingHint p) {
    projectionRenderingHint = p;
}

/**
 * \return The current projection for exports.
 */
RS::ProjectionRenderingHint RExporter::getProjectionRenderingHint() {
    return projectionRenderingHint;
}

/**
 * \return Clip rectangle due to current viewport being exported.
 */
//RBox RExporter::getClipRectangle() const {
//    if (!clipping) {
//        return RBox();
//    }

//    RViewportEntity* viewport = getCurrentViewport();
//    if (viewport!=NULL) {
//        return viewport->getBoundingBox();
//    }

//    return RBox();
//}

void RExporter::setClipping(bool on) {
    clipping = on;
}

bool RExporter::getClipping() const {
    return clipping;
}

/**
 * Sets the current pen (currentPen).
 */
void RExporter::setPen(const QPen& pen) {
    currentPen = pen;
    currentPen.setCapStyle(penCapStyle);
    currentPen.setJoinStyle(Qt::RoundJoin);
}

QPen RExporter::getPen(const RPainterPath& path) {
    QPen pen = currentPen;

    // required for text widths in screen based linetype mode:
    if (draftMode || getScreenBasedLinetypes()) {
        pen.setWidth(0);
    }

    if (path.isFixedPenColor()) {
        // pen is fixed color (text color given):
        pen.setColor(path.getPen().color());
        return pen;
    }

    else {
        // pen is current pen or no pen:
        if (path.getPen().style()!=Qt::NoPen) {
            // pen is current pen:
            return pen;
        }

        return QPen(Qt::NoPen);
    }
}

/**
 * \return Current pen.
 */
QPen RExporter::getPen() {
    return currentPen;
}

void RExporter::setBrush(const QBrush& brush) {
    currentBrush = brush;
}

QBrush RExporter::getBrush(const RPainterPath& path) {
    if (path.isFixedBrushColor()) {
        // brush is fixed color (text color given):
        QBrush brush = currentBrush;
        QColor color = path.getBrush().color();
        // color fixed to "by layer":
        if (color==RColor::CompatByLayer) {
            if (currentLayer!=NULL) {
                color = currentLayer->getColor();
            }
            else {
                qWarning("color by layer but current layer is NULL");
                Q_ASSERT(false);
            }
        }
        // color fixed to "by block" (which really means by block reference):
        if (color==RColor::CompatByBlock) {
            if (!blockRefViewportStack.isEmpty()) {
                QStack<REntity*> newBlockRefStack;
                newBlockRefStack = blockRefViewportStack;
                newBlockRefStack.pop();
                color = blockRefViewportStack.top()->getColor(true, newBlockRefStack);
            }
            else {
                // this can happen (by block at top level):
                color = RColor(Qt::white);
                //qWarning("color by block but current block reference is NULL");
                //Q_ASSERT(false);
            }
        }
        REntity* e = getEntity();
        if (e!=NULL && (e->isSelected() || e->isSelectedWorkingSet())) {
            brush.setColor(RSettings::getSelectionColor());
        }
        else {
            brush.setColor(color);
        }
        return brush;
    }
    else {
        // brush is current brush or no brush:
        if (path.getBrush().style()!=Qt::NoBrush) {
            // brush is current brush:
            return currentBrush;
        }
        else {
            return path.getBrush();
        }
    }
}

QBrush RExporter::getBrush() {
    return currentBrush;
}

RColor RExporter::getColor(const RColor& unresolvedColor) {
    REntity* currentEntity = getEntity();
    if (currentEntity == NULL) {
        qWarning() << "no current entity";
        return RColor();
    }

    return currentEntity->getColor(unresolvedColor, blockRefViewportStack);
}

RColor RExporter::getColor(bool resolve) {
    REntity* currentEntity = getEntity();
    if (currentEntity == NULL) {
        qWarning() << "no current entity";
        return RColor();
    }

    return currentEntity->getColor(resolve, blockRefViewportStack);
}

void RExporter::setEntityAttributes(bool forceSelected) {
    REntity* currentEntity = getEntity();
    if (currentEntity == NULL) {
        return;
    }

    if (forceSelected || (currentEntity->isSelected() || currentEntity->isSelectedWorkingSet())) {
        setColor(RSettings::getSelectionColor());
    }
    else {
        setColor(currentEntity->getColor(true, blockRefViewportStack));
    }
    setLineweight(currentEntity->getLineweight(true, blockRefViewportStack));
    setLinetypeId(currentEntity->getLinetypeId(true, blockRefViewportStack));

    setStyle(Qt::SolidLine);
    setBrushStyle(Qt::SolidPattern);
}

void RExporter::setStyle(Qt::PenStyle penStyle) {
    currentPen.setStyle(penStyle);
}

void RExporter::setBrushStyle(Qt::BrushStyle brushStyle) {
    currentBrush.setStyle(brushStyle);
}

void RExporter::setDashPattern(const QVector<qreal>& dashes) {
    currentPen.setDashPattern(dashes);
}

/**
 * \return Pointer to the entity that is currently being exported.
 */
REntity* RExporter::getEntity() {
    if (entityStack.size()>0) {
        return entityStack.top();
    }
    return NULL;
}

REntity* RExporter::getCurrentBlockRef() const {
    for (int i=blockRefViewportStack.size()-1; i>=0; i--) {
        REntity* e = blockRefViewportStack.at(i);
        RBlockReferenceEntity* v = dynamic_cast<RBlockReferenceEntity*>(e);
        if (v!=NULL) {
            return v;
        }
    }
    return NULL;
}

RViewportEntity* RExporter::getCurrentViewport() const {
    for (int i=blockRefViewportStack.size()-1; i>=0; i--) {
        REntity* e = blockRefViewportStack.at(i);
        RViewportEntity* v = dynamic_cast<RViewportEntity*>(e);
        if (v!=NULL) {
            return v;
        }
    }
    return NULL;
}

QStack<REntity*> RExporter::getBlockRefViewportStack() const {
    return blockRefViewportStack;
}

/**
 * Sets the current export color in RGB and Alpha.
 * All components are in the range of 0.0 <= component <= 1.0.
 * If \ref isColorFixed is true, this function does nothing.
 */
void RExporter::setColor(float r, float g, float b, float a) {
    QColor clr;
    clr.setRgbF(r, g, b, a);
    setColor(clr);
}

void RExporter::setColor(const RColor& color) {
    currentPen.setColor(color);
    currentBrush.setColor(color);
}

void RExporter::setLinetypeId(RLinetype::Id ltId) {
    RDocument* doc = NULL;
    if (getEntity()!=NULL) {
        doc = getEntity()->getDocument();
    }
    if (doc == NULL) {
        doc = document;
    }

    QSharedPointer<RLinetype> lt = doc->queryLinetype(ltId);

    if (!lt.isNull()) {
        currentLinetypePattern = lt->getPattern();
    }
}

void RExporter::setLinetypePattern(const RLinetypePattern& ltPattern) {
    Q_ASSERT(ltPattern.isValid());
    currentLinetypePattern = ltPattern;
}

void RExporter::setLineweight(RLineweight::Lineweight weight) {
    Q_ASSERT(weight>=0);

    if (document==NULL) {
        currentPen.setWidthF(weight);
        return;
    }

    currentPen.setWidthF(
        RUnit::convert(weight / 100.0, RS::Millimeter, document->getUnit())
    );
}

/**
 * Called to start a new, complete export.
 * Implementors can for example clear any stored exported entities or caches.
 * The default implementation does nothing.
 */
void RExporter::startExport() {
}

/**
 * Called at the end of a completed export.
 * The default implementation notifies listeners.
 */
void RExporter::endExport() {
    RMainWindow* mainWindow = RMainWindow::getMainWindow();

    if (mainWindow!=NULL) {
        mainWindow->notifyExportListenersEnd(this);
    }
}

/**
 * Exports the visual representation of all objects (including entities) of the document.
 */
bool RExporter::exportDocument() {
    startExport();
    if (!exportDocumentSettings()) {
        return false;
    }
    //qDebug() << "exporting linetypes";
    exportLinetypes();
    //qDebug() << "exporting layers";
    exportLayers();
    //qDebug() << "exporting layer states";
    exportLayerStates();
    //qDebug() << "exporting blocks";
    exportBlocks();
    //qDebug() << "exporting views";
    exportViews();
    //qDebug() << "exporting entities";
    if (isVisualExporter()) {
        exportEntities(false);
    }
    else {
        exportEntities(true);
    }
    endExport();

    return true;
}

bool RExporter::exportDocumentSettings() {
    exportDocumentSetting("QCADVersion", RSettings::getVersionString());

    // export all QCAD specific document variables:
    QStringList variables = document->getVariables();
    variables.sort();
    for (int i=0; i<variables.size(); i++) {
        QString key = variables[i];
        QVariant value = document->getVariable(key);
        exportDocumentSetting(key, value);
    }

    return true;
}

void RExporter::exportDocumentSetting(const QString& key, const QVariant& value, const QString& dictionaryName) {
    Q_UNUSED(key)
    Q_UNUSED(value)
    Q_UNUSED(dictionaryName)
}

void RExporter::exportIntListWithName(const QString& dictionaryName, const QString& name, const QString& listName, QList<int64_t>& values) {
    Q_UNUSED(dictionaryName)
    Q_UNUSED(name)
    Q_UNUSED(listName)
    Q_UNUSED(values)
}

void RExporter::exportEntities(bool allBlocks, bool undone) {
    QSet<REntity::Id> ids = document->queryAllEntities(undone, allBlocks);

    // 20110815: ordered export (TODO: optional?):
    // needed for order of block contents (DXF export tests)
    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);

    QList<REntity::Id>::iterator it;
    for (it=list.begin(); it!=list.end(); it++) {
        QSharedPointer<REntity> e = document->queryEntityDirect(*it);
        if (!e.isNull()) {
            exportEntity(*e, false);
        }
    }
}

void RExporter::exportLayers() {
    QSet<RLayer::Id> ids = document->queryAllLayers();
    QSet<RLayer::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        // 20110715: queryLayer -> queryLayerDirect
        QSharedPointer<RLayer> e = document->queryLayerDirect(*it);
        if (!e.isNull()) {
            exportLayer(*e);
        }
    }
}

void RExporter::exportLayerStates() {
    QSet<RLayerState::Id> ids = document->queryAllLayerStates();
    QSet<RLayerState::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<RLayerState> ls = document->queryLayerStateDirect(*it);
        if (!ls.isNull()) {
            exportLayerState(*ls);
        }
    }
}

void RExporter::exportBlocks() {
    QSet<RBlock::Id> ids = document->queryAllBlocks();
    QList<RBlock::Id> idsSorted = document->sortBlocks(ids.toList());
    QList<RBlock::Id>::iterator it;
    for (it = idsSorted.begin(); it != idsSorted.end(); it++) {
        QSharedPointer<RBlock> e = document->queryBlock(*it);
        if (!e.isNull()) {
            exportBlock(*e);
        }
    }
}

void RExporter::exportViews() {
    QSet<RView::Id> ids = document->queryAllViews();
    QSet<RView::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<RView> e = document->queryView(*it);
        if (!e.isNull()) {
            exportView(*e);
        }
    }
}

void RExporter::exportLinetypes() {
    QSet<RLinetype::Id> ids = document->queryAllLinetypes();
    QSet<RLinetype::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        QSharedPointer<RLinetype> e = document->queryLinetype(*it);
        if (!e.isNull()) {
            exportLinetype(*e);
        }
    }
}


/**
 * Exports the visual representation of all entities that are completely
 * or partly inside the given area.
 */
void RExporter::exportEntities(const RBox& box) {
    QSet<REntity::Id> ids = document->queryIntersectedEntitiesXY(box);
    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        exportEntity(*it);
    }
}


void RExporter::exportLayer(RLayer::Id layerId) {
    QSharedPointer<RLayer> layer = getDocument().queryLayer(layerId);
    if (layer.isNull() || !layer->isOffOrFrozen()) {
        exportLayer(*layer);
    }
}

void RExporter::exportBlock(RBlock::Id blockId) {
    QSharedPointer<RBlock> block = getDocument().queryBlock(blockId);
    if (block.isNull() || !block->isFrozen()) {
        exportBlock(*block);
    }
}

void RExporter::exportView(RView::Id viewId) {
    QSharedPointer<RView> view = getDocument().queryView(viewId);
    if (view.isNull()) {
        exportView(*view);
    }
}

/**
 * Exports the given entity as part of a block definition to be reused by block references.
 * This is called for entities which have no attributes ByBlock.
 */
//void RExporter::exportBlockEntity(REntity& entity, bool preview, bool allBlocks, bool forceSelected) {
//    RExporter::exportEntity(entity, preview, allBlocks, forceSelected);
//}

/**
 * Sets the current entity to the given entity and calls \ref exportEntity().
 * Note that entity is a temporary clone.
 *
 * \forceSelected Force selection, used to export entities as part of a selected block reference.
 */
void RExporter::exportEntity(REntity& entity, bool preview, bool allBlocks, bool forceSelected) {
    RDocument* doc = entity.getDocument();
    if (doc==NULL) {
        doc = document;
    }

    // entity not on current block and allBlocks==false, break:
    if (!allBlocks && doc->getCurrentBlockId()!=entity.getBlockId()) {
        qDebug() << "entity on block " << entity.getBlockId() << "[" << entity.getBlockName() << "]" << " (not on current block" << doc->getCurrentBlockId() << "[" << doc->getCurrentBlockName() <<  "])";
        //unexportEntity(entity.getId());
        return;
    }

    entityStack.push(&entity);

    // find layer of the current entity
    QSharedPointer<RLayer> layer = getEntityLayer(entity);
    if (!layer.isNull()) {
        currentLayer = layer.data();
    }

    // find block reference of the current entity, ignore this entity:
    bool blockRefOrViewportSet = false;
    // check if this entity is a block reference, viewport or leader
    // (which can all serve as container for other entities):
    if (entity.getType()==RS::EntityBlockRef || entity.getType()==RS::EntityViewport || entity.getType()==RS::EntityLeader) {
        blockRefViewportStack.push(&entity);
        blockRefOrViewportSet = true;
    }

    bool skip = false;

    // if this exporter exports a visual
    // representation of the drawing (scene, view, print)...
    if (isVisualExporter()) {
        skip = !isVisible(entity);
    }

    if (!skip) {
        setEntityAttributes(forceSelected);

        if ((forceSelected || (entity.isSelected() || entity.isSelectedWorkingSet())) && RSettings::getUseSecondarySelectionColor()) {
            // first part of two color selection:
            twoColorSelectedMode = true;
        }

        startEntity(/* topLevelEntity = */ blockRefOrViewportSet || blockRefViewportStack.isEmpty());
        exportCurrentEntity(preview, forceSelected);
        endEntity();

        // export again, with secondary selection color:
        if (visualExporter) {
            if ((forceSelected || (entity.isSelected() || entity.isSelectedWorkingSet())) &&
                RSettings::getUseSecondarySelectionColor() &&
                entity.getType()!=RS::EntityBlockRef &&
                entity.getType()!=RS::EntityText &&
                entity.getType()!=RS::EntityAttribute &&
                entity.getType()!=RS::EntityAttributeDefinition) {

                RColor secondarySelectionColor = RSettings::getColor("GraphicsViewColors/SecondarySelectionColor", RColor(Qt::white));
                setColor(secondarySelectionColor);
                //setStyle(Qt::CustomDashLine);
                setDashPattern(QVector<qreal>() << 2 << 3);
                entity.exportEntity(*this, preview, forceSelected);
            }
        }
        twoColorSelectedMode = false;
    }
//    }

    if (blockRefOrViewportSet) {
        blockRefViewportStack.pop();
        //blockRefBS.clear();
    }
    currentLayer = NULL;

    entityStack.pop();
}

/**
 * Calls \ref exportEntity(REntity*) for the entity with the given ID.
 */
void RExporter::exportEntity(REntity::Id entityId, bool allBlocks, bool forceSelected) {
    QSharedPointer<REntity> e = document->queryEntityDirect(entityId);
    if (!e.isNull() && !e->isUndone()) {
        exportEntity(*e, false, allBlocks, forceSelected);
    }
    else {
        unexportEntity(entityId);
    }
}

QSharedPointer<RLayer> RExporter::getEntityLayer(REntity& entity) {
    RDocument* doc = entity.getDocument();
    if (doc==NULL) {
        doc = document;
    }

    QSharedPointer<RLayer> layer;
    if (layerSource!=NULL) {
        RLayer::Id layerId = entity.getLayerId();
        layer = layerSource->queryLayerDirect(layerId);
        Q_ASSERT(!layer.isNull());
    }
    else {
        layer = doc->queryLayerDirect(entity.getLayerId());
        if (layer.isNull()) {
            qDebug() << "Document: " << *doc;
            qDebug() << "Layer ID: " << entity.getLayerId();
            Q_ASSERT_X(false, "RExporter::getEntityLayer", "layer is NULL");
        }
    }

    return layer;
}

bool RExporter::isVisible(REntity& entity) {
    return entity.isVisible();

    /*
    // only export entities on visible layers:
    if (currentLayer!=NULL && currentLayer->isOffOrFrozen()) {
        // viewports are exported even if layer is hidden (but without border):
        if (entity.getType()!=RS::EntityViewport) {
            return false;
        }
    }

    // only export entities in visible blocks:
    {
        RBlockReferenceEntity* blockRef = dynamic_cast<RBlockReferenceEntity*>(&entity);
        if (blockRef!=NULL) {
            RBlock::Id blockId = blockRef->getReferencedBlockId();
            if (blockId!=RBlock::INVALID_ID) {
                QSharedPointer<RBlock> block = document->queryBlockDirect(blockId);
                if (!block.isNull() && block->isFrozen()) {
                    return false;
                }
            }
        }
    }

    // only export block attributes of visible blocks:
    if (RSettings::getHideAttributeWithBlock()) {
        if (entity.getType()==RS::EntityAttribute) {
            RDocument* doc = entity.getDocument();
            if (doc==NULL) {
                doc = document;
            }

            REntity::Id blockRefId = entity.getParentId();
            QSharedPointer<REntity> parentEntity = doc->queryEntityDirect(blockRefId);
            QSharedPointer<RBlockReferenceEntity> blockRef = parentEntity.dynamicCast<RBlockReferenceEntity>();
            if (!blockRef.isNull()) {
                RLayer* currentLayerBak = currentLayer;
                QSharedPointer<RLayer> layer = getEntityLayer(*blockRef);
                if (!layer.isNull()) {
                    currentLayer = layer.data();
                }
                //bool ret = isVisible(*blockRef);
                bool ret = !doc->isLayerOffOrFrozen(blockRef->getLayerId());
                currentLayer = currentLayerBak;
                return ret;
            }
        }
    }

    return true;
    */
}

/**
 * The default implementation calls the \ref REntity::exportEntity() function
 * of the entity.
 * This method may use the \c currentEntity stack to access the
 * entity that is currently being exported.
 * Exporters can choose to reimplement this function to export an entity
 * in a target platform specific manner (e.g. to optimize things for
 * a specific platform).
 */
void RExporter::exportCurrentEntity(bool preview, bool forceSelected) {
    REntity* entity = getEntity();
    if (entity==NULL) {
        return;
    }

    entity->exportEntity(*this, preview, forceSelected);
}



/**
 * \return True if there is a current entity and it is selected, false
 *      otherwise.
 */
bool RExporter::isEntitySelected() {
    const REntity* entity = getEntity();
    if (entity!=NULL) {
        return entity->isSelected();
    }
    else {
        return false;
    }
}

bool RExporter::isPatternContinuous(const RLinetypePattern& p) {
    return !p.isValid() || p.getNumDashes()<=1 ||
           draftMode || getScreenBasedLinetypes() || twoColorSelectedMode;
}

/**
 * This is called for entities for which an export was requested
 * but which cannot be instantiated because they either do not exist
 * (anymore) in the DB or they are currently undone.
 */
void RExporter::unexportEntity(REntity::Id /*entityId*/) {}



/**
 * Calls \ref exportEntity() for all given entities.
 */
void RExporter::exportEntities(QSet<REntity::Id>& entityIds, bool allBlocks) {
    QSet<REntity::Id>::iterator it;
    for (it=entityIds.begin(); it!=entityIds.end(); ++it) {
        exportEntity(*it, allBlocks);
    }
}



/**
 * Exports a quadrilateral with the current attributes.
 * This is a convenience function that exports two triangles but may
 * also be re-implemented to do something else.
 */
void RExporter::exportQuad(
    const RVector& p1, const RVector& p2,
    const RVector& p3, const RVector& p4) {

    exportTriangle(RTriangle(p1, p2, p3));
    exportTriangle(RTriangle(p3, p4, p1));
}

/**
 * Exports a rectangle with the current attributes.
 * This is a convenience function that exports two triangles but may
 * also be re-implemented to do something else.
 */
void RExporter::exportRectangle(const RVector& p1, const RVector& p2) {
    exportQuad(p1, RVector(p2.x, p1.y), p2, RVector(p1.x, p2.y));
}

/**
 * Exports a vertical quadrilateral with the two given
 * base points and the given height.
 */
void RExporter::exportVerticalQuad(
        const RVector& p1,
        const RVector& p2,
        double height) {

    exportQuad(p1, p2, p2+RVector(0,0,height), p1+RVector(0,0,height));
}



/**
 * Exports the surfaces of the given box.
 * This is a convenience function that exports 12 triangles but may
 * also be re-implemented to do something else.
 */
void RExporter::exportBox(const RBox& box) {
    QList<RTriangle> triangles = box.getTriangles();
    QList<RTriangle>::iterator it;
    for (it=triangles.begin(); it!=triangles.end(); ++it) {
        exportTriangle(*it);
    }
}

RLinetypePattern RExporter::getLinetypePattern() {
    return currentLinetypePattern;
}

double RExporter::exportLine(const RLine& line, double offset) {
    double ret = RNANDOUBLE;

    if (!line.isValid()) {
        return ret;
    }

    double length = line.getLength();

    if (length>1e100 || !RMath::isSane(length)) {
        return ret;
    }

    if (length<RS::PointTolerance) {
        exportLineSegment(line, 0.0);
        return ret;
    }

    double angle = line.getAngle();

    // continuous line or
    // we are in draft mode or
    // QCAD is configured to show screen based line patterns
    if (draftMode || getScreenBasedLinetypes() || twoColorSelectedMode) {
        exportLineSegment(line, angle);
        return ret;
    }

    RLinetypePattern p = getLinetypePattern();
    if (!p.isValid() || p.getNumDashes() <= 1) {
        exportLineSegment(line, angle);
        return ret;
    }

    p.scale(getLineTypePatternScale(p));
    double patternLength = p.getPatternLength();

    // avoid huge number of small segments due to very fine 
    // pattern or long lines:
    if (patternLength<RS::PointTolerance || length / patternLength > RSettings::getDashThreshold()) {
        exportLineSegment(line, angle);
        return ret;
    }

    RVector dv = (line.getEndPoint() - line.getStartPoint()).getNormalized();

    RVector* vp = NULL;
    vp = new RVector[p.getNumDashes()];
    for (int i = 0; i < p.getNumDashes(); ++i) {
//        vp[i] = RVector(cos(angle) * fabs(p.getDashLengthAt(i)),
//                        sin(angle) * fabs(p.getDashLengthAt(i)));
        vp[i] = dv * fabs(p.getDashLengthAt(i));
    }

    if (RMath::isNaN(offset)) {
        offset = p.getPatternOffset(length);
    }
    else {
        double num = ceil(offset / patternLength);
        offset -= num * patternLength;
    }

    bool done = false;
    int i = 0;
    //RVector cursor(line.getStartPoint() + RVector::createPolar(offset, angle));
    RVector cursor(line.getStartPoint() + dv*offset);
    double total = offset;
    double nextTotal;
    bool isGap = false;
    RLine dash;

    do {
        double dashLength = p.getDashLengthAt(i);
        nextTotal = total + fabs(dashLength);

        // dash, no gap. note that a dash can have a length of 0.0 (point):
        if (dashLength > -RS::PointTolerance) {
            isGap = false;
        }

        // gap:
        else {
            isGap = true;
        }

        // check if we're on the line already
        // (since we might start before the line due to pattern offset):
        if (nextTotal > -RS::PointTolerance) {
            dash = RLine(cursor, cursor + vp[i]);

            if (!isGap) {
                // fist part is gap, then dash
                ret = -nextTotal;
            }
            else {
                // fist part is dash, then gap
                ret = nextTotal;
            }

            // shorten at start of line:
            if (total < 0.0 /*&& nextTotal > 0.0*/) {
                dash.startPoint = line.startPoint;
                ret = RNANDOUBLE;
            }

            // shorten at end of line:
            if (/*total < length &&*/ nextTotal >= length - 1.0e-6) {
                dash.endPoint = line.endPoint;
                ret = RINFDOUBLE;
            }

            if (!isGap) {
                exportLineSegment(dash, angle);
                ret = nextTotal;
            }
        }

        cursor += vp[i];
        total = nextTotal;

        done = (total > length) || RMath::isNaN(total);

        // export shape (zigzag, text, etc.) at end of dash / gap:
        if (p.hasShapeAt(i)) {
            QList<RPainterPath> pps = p.getShapeAt(i);
            exportLinetypeShape(pps, line, total, length, angle, cursor);
        }

        ++i;
        if (i >= p.getNumDashes()) {
            i = 0;
        }
    } while (!done);

    delete[] vp;

    return ret;
}

bool RExporter::exportLinetypeShape(QList<RPainterPath>& pps, const RLine& line, double total, double length, double angle, const RVector& cursor) {
    RVector min = RPainterPath::getMinList(pps);
    RVector max = RPainterPath::getMaxList(pps);
    bool isCursorOnLine = line.isOnShape(cursor);
    double diffBefore = total+min.x;
    double diffAfter = total+max.x-length;
    bool shapeOutsideBefore = diffBefore < -RS::PointTolerance;
    bool shapeOutsideAfter = diffAfter > RS::PointTolerance;
    if (isCursorOnLine && (!shapeOutsideBefore && !shapeOutsideAfter)) {
        exportPainterPaths(pps, angle, cursor);
        return true;
    }
    else {
        if (shapeOutsideBefore) {
            // check if first shape is not entirely before the start point of the line:
            if (total + max.x < 0.0) {
                return false;
            }
            RLine l = line;
            if (fabs(total+max.x)<length) {
                RVector p = RVector(
                            cos(angle) * fabs(total+max.x),
                            sin(angle) * fabs(total+max.x)
                            );
                l.endPoint = l.startPoint + p;
            }
            exportLineSegment(l, angle);
            return true;
        }
        if (shapeOutsideAfter) {
            // check if last shape is not entirely after the end point of the line:
            if (total + min.x > length) {
                return false;
            }
            RLine l = line;
            if (fabs(total+min.x)>0.0) {
                RVector p = RVector(
                            cos(angle) * fabs(total+min.x),
                            sin(angle) * fabs(total+min.x)
                            );
                l.startPoint = l.startPoint + p;
            }
            exportLineSegment(l, angle);
            return true;
        }

        return false;
    }
}

void RExporter::exportArc(const RArc& arc, double offset) {
    if (!arc.isValid()) {
        return;
    }

    if (getEntity() == NULL || draftMode || getScreenBasedLinetypes() || twoColorSelectedMode) {
        exportArcSegment(arc);
        return;
    }

    RLinetypePattern p = getLinetypePattern();
    if (!p.isValid() || p.getNumDashes() <= 1) {
        exportArcSegment(arc);
        return;
    }

//    if (getScreenBasedLinetypes()) {
//        p.scale(1.0/pixelSizeHint);
//    }

    p.scale(getLineTypePatternScale(p));
    double patternLength = p.getPatternLength();
    if (patternLength<RS::PointTolerance || arc.getLength() / patternLength > RSettings::getDashThreshold()) {
        exportArcSegment(arc);
        return;
    }

    RArc normalArc = arc;
    if (arc.isReversed()) {
        normalArc.reverse();
    }

    if (normalArc.radius < 1.0e-12) {
        return;
    }

    RArcExporter(*this, arc, offset);

    /*
    p.scale(getLineTypePatternScale(p));

    double length = normalArc.getLength();
    double patternLength = p.getPatternLength();

    // avoid huge number of small segments due to very fine 
    // pattern or long lines:
    if (patternLength<RS::PointTolerance || length / patternLength > 5000) {
        exportArcSegment(arc);
        return;
    }

    double* vp = NULL;
    vp = new double[p.getNumDashes()];
    for (int i = 0; i < p.getNumDashes(); ++i) {
        vp[i] = fabs(p.getDashLengthAt(i)) / normalArc.radius;
    }

    //bool optimizeEnds = false;
    if (RMath::isNaN(offset)) {
        offset = p.getPatternOffset(length);
        //optimizeEnds = true;
    }

    QList<RArc> arcSegments;
    bool done = false;
    int i = 0;
    double cursor = normalArc.getStartAngle() + offset / normalArc.radius;
    double total = offset;
    bool dashFound = false;
    bool gapFound = false;
    double a1 = normalArc.getStartAngle();
    double a2 = 0.0;
    do {
        if (dashFound && !gapFound) {
            if (total + fabs(p.getDashLengthAt(i)) >= length - 1.0e-6) {
                arcSegments.append(RArc(normalArc.getCenter(), normalArc.getRadius(), a1, normalArc.getEndAngle()));
                break;
            }
            arcSegments.append(RArc(normalArc.getCenter(), normalArc.getRadius(), a1, a2));
        }
        if (p.getDashLengthAt(i) >= 0.0) {
            // dash, no gap
            if (total + p.getDashLengthAt(i) >= 0.0) {
                a1 = cursor;
                if (total < 0.0 || !dashFound) {
                    a1 = normalArc.startAngle;
                }
                a2 = cursor + vp[i];
                if (fabs(a2 - normalArc.getStartAngle()) > 1.0e-6) {
                    dashFound = true;
                }
            }
            gapFound = false;
        } else {
            gapFound = true;
        }
        cursor += vp[i];
        total += fabs(p.getDashLengthAt(i));
        done = total > length;

        if (!done && total>0.0) {
            // handle shape at end of dash / gap:
            if (p.hasShapeAt(i)) {
                QList<RPainterPath> pps = p.getShapeAt(i);
//                RVector min = RPainterPath::getMinList(pps);
//                RVector max = RPainterPath::getMaxList(pps);
                RPainterPath::rotateList(pps, cursor+M_PI/2);
                RPainterPath::translateList(pps, normalArc.getPointAtAngle(cursor));
                exportPainterPaths(pps);
            }
        }

        ++i;
        if (i >= p.getNumDashes()) {
            i = 0;
        }
    } while (!done);

    if (!gapFound || !dashFound) {
        if (total + fabs(p.getDashLengthAt(i)) >= length - 1.0e-6) {
            arcSegments.append(RArc(normalArc.getCenter(), normalArc.getRadius(), a1, normalArc.getEndAngle()));
        } else {
            arcSegments.append(RArc(normalArc.getCenter(), normalArc.getRadius(), a1, a2));
        }
    }

    if (arc.isReversed()) {
        for (int i=arcSegments.length()-1; i>=0; i--) {
            arcSegments[i].reverse();
            exportArcSegment(arcSegments[i], true);
        }
    }
    else {
        for (int i=0; i<arcSegments.length(); i++) {
            exportArcSegment(arcSegments[i], true);
        }
    }

    delete[] vp;
    */
}

void RExporter::exportArcSegment(const RArc& arc, bool allowForZeroLength) {
    if (allowForZeroLength && arc.isFullCircle()) {
        exportLineSegment(RLine(arc.getStartPoint(), arc.getEndPoint()), arc.getDirection1());
        return;
    }

    double segmentLength;
    if (pixelSizeHint>0.0) {
        // approximate arc with segments with the length of 2 pixels:
        segmentLength = getCurrentPixelSizeHint() * 2;
    }
    else {
        segmentLength = arc.getRadius() / 40.0;
    }

    // avoid a segment length of 0:
    if (segmentLength<1.0e-4) {
        segmentLength = 1.0e-4;
    }

    double a1 = arc.getStartAngle();
    double a2 = arc.getEndAngle();
    RVector center = arc.getCenter();
    double radius = arc.getRadius();

    double aStep;
    if (radius<1.0e-3) {
        aStep = 0.1;
    }
    else {
        aStep = segmentLength / radius;
        if (aStep>1.0) {
            aStep = 1.0;
        }

        double minAStep = RSettings::getMinArcAngleStep();
        if (draftMode) {
            minAStep *= 4;
        }

        if (aStep<minAStep) {
            aStep = minAStep;
        }
    }
    RVector prev = arc.getStartPoint();
    RVector ci;
    double a;

//    RPolyline pl;
    if (!arc.isReversed()) {
        // Arc Counterclockwise:
        if(a1>a2-RS::AngleTolerance) {
            a2+=2*M_PI;
        }
        for (a=a1+aStep; a<=a2; a+=aStep) {
            ci.x = center.x + cos(a) * radius;
            ci.y = center.y + sin(a) * radius;
            ci.z = center.z;
            exportLineSegment(RLine(prev, ci), a+M_PI_2);
//            pl.appendVertex(ci);
            prev = ci;
        }
    } else {
        // Arc Clockwise:
        if (a1<a2+RS::AngleTolerance) {
            a2-=2*M_PI;
        }
        for (a=a1-aStep; a>=a2; a-=aStep) {
            ci.x = center.x + cos(a) * radius;
            ci.y = center.y + sin(a) * radius;
            ci.z = center.z;
            exportLineSegment(RLine(prev, ci), a+M_PI_2);
//            pl.appendVertex(ci);
            prev = ci;
        }
    }
    this->exportLineSegment(RLine(prev, arc.getEndPoint()), arc.getEndAngle()+M_PI_2);
    //pl.appendVertex(arc.getEndPoint());

    //this->exportPolyline(pl);
}

/**
 * Exports a circle with the current attributes.
 * The default implementation calls exportArc with a full circle arc.
 */
void RExporter::exportCircle(const RCircle& circle) {
    RArc arc(circle.center, circle.radius, 0.0, 2*M_PI, false);
    exportArc(arc);
}

/**
 * Exports an ellipse with the current attributes.
 * \todo switch from line based interpolation to arcs.
 */
void RExporter::exportEllipse(const REllipse& ellipse, double offset) {
    if (ellipse.getMajorRadius()<RS::PointTolerance ||
        ellipse.getMinorRadius()<RS::PointTolerance) {
        return;
    }

    RPolyline polyline;

    RVector cp = ellipse.getCenter();
    double radius1 = ellipse.getMajorRadius();
    double radius2 = ellipse.getMinorRadius();
    double angle = ellipse.getAngle();
    double a1 = ellipse.getStartParam();
    double a2 = ellipse.getEndParam();
    bool reversed = ellipse.isReversed();

    double aStep;         // Angle Step (rad)
    double a;             // Current Angle (rad)

    aStep=M_PI/128;
    RVector vp;
    RVector vc(cp.x, cp.y);
    vp.set(cp.x+cos(a1)*radius1,
           cp.y+sin(a1)*radius2);
    vp.rotate(angle, vc);
    polyline.appendVertex(vp);
    if (!reversed) {
        // Arc Counterclockwise:
        if (a1>a2-RS::AngleTolerance) {
            a2+=2*M_PI;
        }
        for (a=a1+aStep; a<=a2; a+=aStep) {
            vp.set(cp.x+cos(a)*radius1,
                   cp.y+sin(a)*radius2);
            vp.rotate(angle, vc);
            polyline.appendVertex(vp);
        }
    } else {
        // Arc Clockwise:
        if (a1<a2+RS::AngleTolerance) {
            a2-=2*M_PI;
        }
        for (a=a1-aStep; a>=a2; a-=aStep) {
            vp.set(cp.x+cos(a)*radius1,
                   cp.y+sin(a)*radius2);
            vp.rotate(angle, vc);
            polyline.appendVertex(vp);
        }
    }
    vp.set(cp.x+cos(a2)*radius1,
           cp.y+sin(a2)*radius2);
    vp.rotate(angle, vc);
    if (!polyline.getLastVertex().equalsFuzzy(vp)) {
        polyline.appendVertex(vp);
    }

    exportPolyline(polyline, true, offset);
}

/**
 * \param polylineGen True: use pattern along whole polyline, False: pattern per segment.
 */
void RExporter::exportPolyline(const RPolyline& polyline, bool polylineGen, double offset) {
    RLinetypePattern p = getLinetypePattern();

    bool continuous = getEntity()==NULL || isPatternContinuous(p);
    if (!continuous) {
        p.scale(getLineTypePatternScale(p));

        if (RMath::isNaN(offset)) {
            double length = polyline.getLength();
            offset = p.getPatternOffset(length);
        }
    }

    // if polyline has individual segment widths, polylineGen has no effect:
    if (!continuous && polylineGen && !polyline.hasWidths()) {
        // pattern along whole polyline:
        exportExplodable(polyline, offset);
    }
    else {
        if (polyline.hasWidths()) {
            exportThickPolyline(polyline);
        }
        else {
            // pattern for each individual segment:
            for (int i=0; i<polyline.countSegments(); i++) {
                QSharedPointer<RShape> shape = polyline.getSegmentAt(i);
                QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
                if (!line.isNull()) {
                    RExporter::exportLine(*line);
                }
                QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
                if (!arc.isNull()) {
                    RExporter::exportArc(*arc);
                }
            }
        }
    }
}

void RExporter::exportSplineSegment(const RSpline& spline) {
    RPainterPath pp;
    pp.setPen(currentPen);
    pp.setInheritPen(true);
    pp.addSpline(spline);
    exportPainterPaths(QList<RPainterPath>() << pp);
}

void RExporter::exportSpline(const RSpline& spline, double offset) {
    RLinetypePattern p = getLinetypePattern();

    bool continuous = getEntity()==NULL || isPatternContinuous(p);

    p.scale(getLineTypePatternScale(p));
    double patternLength = p.getPatternLength();
    if (patternLength<RS::PointTolerance || spline.getLength() / patternLength > RSettings::getDashThreshold()) {
        continuous = true;
    }

    if (!continuous) {
        if (getEntity()!=NULL && (getEntity()->getType()!=RS::EntitySpline || RSpline::hasProxy())) {
            // we have a spline proxy:
            RShapesExporter(*this, QList<QSharedPointer<RShape> >() << QSharedPointer<RShape>(spline.clone()), offset);
        }
        else {
            // fallback if we don't have a spline proxy:
            p.scale(getLineTypePatternScale(p));

            if (RMath::isNaN(offset)) {
                double length = spline.getLength();
                offset = p.getPatternOffset(length);
            }
            exportExplodable(spline, offset);
        }
    }
    else {
        // version <= 3.0.0 was (line interpolation):
        //exportExplodable(spline, offset);

        // performance improvement (using real splines):
        RPainterPath pp;
        pp.setPen(currentPen);
        pp.setInheritPen(true);
        pp.addSpline(spline);
        exportPainterPaths(QList<RPainterPath>() << pp);
    }

    /*
    RLinetypePattern p = getLinetypePattern();
    p.scale(getLineTypePatternScale(p));

    if (RMath::isNaN(offset)) {
        double length = spline.getLength();
        offset = p.getPatternOffset(length);
    }

    double currentOffset = offset;
    QList<QSharedPointer<RShape> > sub = spline.getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        QSharedPointer<RLine> line = (*it).dynamicCast<RLine>();
        if (!line.isNull()) {
            exportLine(*line.data(), currentOffset);
            currentOffset -= line->getLength();
        }

        QSharedPointer<RArc> arc = (*it).dynamicCast<RArc>();
        if (!arc.isNull()) {
            exportArc(*arc.data(), currentOffset);
            currentOffset -= arc->getLength();
        }
    }
    */
}

void RExporter::exportExplodable(const RExplodable& explodable, double offset) {
    QList<QSharedPointer<RShape> > sub = explodable.getExploded();

    RLinetypePattern p = getLinetypePattern();
    if (isPatternContinuous(p)) {
        for (int i=0; i<sub.length(); i++) {
            QSharedPointer<RLine> lineP = sub[i].dynamicCast<RLine>();
            if (!lineP.isNull()) {
                exportLine(*lineP.data());
                continue;
            }

            QSharedPointer<RArc> arc = sub[i].dynamicCast<RArc>();
            if (!arc.isNull()) {
                exportArc(*arc.data());
                continue;
            }
        }
        return;
    }

    if (getEntity()!=NULL && (getEntity()->getType()!=RS::EntitySpline || RSpline::hasProxy())) {
        // all explodable entities including splines if we have a spline proxy:
        RShapesExporter(*this, sub, offset);
        return;
    }

    // use alternative algorithm for splines if we don't have a spline proxy:
    for (int i=0; i<sub.length(); i++) {
        QSharedPointer<RLine> lineP = sub[i].dynamicCast<RLine>();
        if (!lineP.isNull()) {
            RLine line = *lineP.data();
            exportLine(line, offset);
            offset -= lineP->getLength();
            continue;
        }

        QSharedPointer<RArc> arc = sub[i].dynamicCast<RArc>();
        if (!arc.isNull()) {
            exportArc(*arc.data(), offset);
            offset -= arc->getLength();
            continue;
        }
    }
}

void RExporter::exportPainterPathSource(const RPainterPathSource& pathSource, double z) {
    exportPainterPaths(pathSource.getPainterPaths(false, pixelSizeHint), z);
}

void RExporter::exportPainterPaths(const QList<RPainterPath>& paths, double z) {
    Q_UNUSED(paths)
    Q_UNUSED(z)

    // TODO: split up painter paths into line semgents, splines (?), arcs...
}

void RExporter::exportPainterPaths(const QList<RPainterPath>& paths, double angle, const RVector& pos) {
    QList<RPainterPath> pps = paths;
    RPainterPath::rotateList(pps, angle);
    RPainterPath::translateList(pps, pos);
    exportPainterPaths(pps);
}

void RExporter::exportBoundingBoxPaths(const QList<RPainterPath>& paths) {
    Q_UNUSED(paths)
}

void RExporter::exportImage(const RImageData& image, bool forceSelected) {
    Q_UNUSED(image)
    Q_UNUSED(forceSelected)
}

QList<RPainterPath> RExporter::exportText(const RTextBasedData& text, bool forceSelected) {
    Q_UNUSED(forceSelected)

    setBrush(getBrush());
    exportPainterPathSource(text);
    return QList<RPainterPath>();
}

void RExporter::exportClipRectangle(const RBox& clipRectangle, bool forceSelected) {
    Q_UNUSED(clipRectangle)
    Q_UNUSED(forceSelected)
}

void RExporter::exportTransform(const RTransform& t) {
    Q_UNUSED(t)
}

void RExporter::exportEndTransform() {
}

double RExporter::getLineTypePatternScale(const RLinetypePattern& p) const {
    if (document==NULL) {
        return 1.0;
    }

    double factor = 1.0;

    // document wide linetype scale:
    double docLinetypeScale = document->getKnownVariable(RS::LTSCALE).toDouble();

    // LTSCALE might be zero:
    if (docLinetypeScale>1e-6) {
        factor *= docLinetypeScale;
    }

    //qDebug() << "factor (doc): " << factor;

    // drawing unit scale:
    if (p.isMetric()) {
        // metric line type patterns are defined in mm:
        factor *= RUnit::convert(1.0, RS::Millimeter, document->getUnit());
    }
    else {
        // imperial line type patterns are defined in inches:
        factor *= RUnit::convert(1.0, RS::Inch, document->getUnit());
    }

    //qDebug() << "factor (unit): " << factor;

    // entity line type scale:
    const REntity* entity = getEntity();
    if (entity!=NULL) {
        double entityLinetypeScale = entity->getLinetypeScale();
        if (!RMath::fuzzyCompare(entityLinetypeScale, 1.0)) {
            if (entityLinetypeScale>1e-6) {
                factor *= entityLinetypeScale;
            }
        }
    }

    //qDebug() << "factor (entity): " << factor;

    // optional: automatic scaling by line weight:
    if (RSettings::getAutoScaleLinetypePatterns()) {
        if (currentPen.widthF()<1e-6) {
            // line pattern factor for lines of width 0:
            int zww = RSettings::getZeroWeightWeight()/100.0;
            if (zww<=0) {
                zww = 1.0;
            }
            //factor *= RUnit::convert(zww/100.0, RS::Millimeter, document->getUnit());
            factor *= zww;
        }
        else {
            //qDebug() << "currentPen.widthF(): " << currentPen.widthF();
            //qDebug() << "currentPen.widthF() mm: " << RUnit::convert(currentPen.widthF(), document->getUnit(), RS::Millimeter);
            factor *= RUnit::convert(currentPen.widthF(), document->getUnit(), RS::Millimeter);
        }
    }

    //qDebug() << "factor: " << factor;

    return factor;
}

void RExporter::setDraftMode(bool on) {
    draftMode = on;
    if (draftMode) {
        screenBasedLinetypes = false;
    }
}

void RExporter::setScreenBasedLinetypes(bool on) {
    screenBasedLinetypes = on;
    if (screenBasedLinetypes) {
        draftMode = false;
    }
}

QStack<REntity*> RExporter::getEntityStack() {
    return entityStack;
}

void RExporter::pushEntity(REntity* e) {
    entityStack.push(e);
}

void RExporter::popEntity() {
    entityStack.pop();
}

/**
 * Exports the given shapes as part of the geometry of the current entity.
 * \todo support more shapes.
 */
void RExporter::exportShapes(const QList<QSharedPointer<RShape> >& shapes) {
    for (int i=0; i<shapes.size(); i++) {
        QSharedPointer<RShape> s = shapes.at(i);
        if (s.isNull()) {
            continue;
        }

        exportShape(s);
    }
}

/**
 * Exports the given shapes as part of the geometry of the current entity.
 */
void RExporter::exportShape(QSharedPointer<RShape> shape) {
    if (shape.isNull()) {
        return;
    }

    QSharedPointer<RPoint> point = shape.dynamicCast<RPoint>();
    if (!point.isNull()) {
        exportPoint(*point.data());
    }

    QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
    if (!line.isNull()) {
        exportLine(*line.data());
    }

    QSharedPointer<RXLine> xline = shape.dynamicCast<RXLine>();
    if (!xline.isNull()) {
        exportXLine(*xline.data());
    }

    QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
    if (!arc.isNull()) {
        exportArc(*arc.data());
    }

    QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
    if (!circle.isNull()) {
        exportCircle(*circle.data());
    }

    QSharedPointer<REllipse> ellipse = shape.dynamicCast<REllipse>();
    if (!ellipse.isNull()) {
        exportEllipse(*ellipse.data());
    }

    QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
    if (!spline.isNull()) {
        exportSpline(*spline.data());
    }

    QSharedPointer<RPolyline> polyline = shape.dynamicCast<RPolyline>();
    if (!polyline.isNull()) {
        exportPolyline(*polyline.data());
    }

    QSharedPointer<RTriangle> triangle = shape.dynamicCast<RTriangle>();
    if (!triangle.isNull()) {
        exportTriangle(*triangle.data());
    }
}

void RExporter::exportShapeSegment(QSharedPointer<RShape> shape, double angle) {
    if (shape.isNull()) {
        return;
    }

    QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
    if (!line.isNull()) {
        exportLineSegment(*line.data(), angle);
    }

    QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
    if (!arc.isNull()) {
        exportArcSegment(*arc.data());
    }

    QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
    if (!spline.isNull()) {
        exportSplineSegment(*spline.data());
    }

    // TODO: ellipse
}

/**
 * \return pixel size hint in context of current block.
 */
double RExporter::getCurrentPixelSizeHint() const {
    double ret = pixelSizeHint;

    // adjust pixel size hint, based on block context:
    for (int i=0; i<entityStack.size(); i++) {
        REntity* e = entityStack[i];
        RBlockReferenceEntity* br = dynamic_cast<RBlockReferenceEntity*>(e);
        if (br==NULL) {
            continue;
        }
        double sf = qMax(br->getScaleFactors().x, br->getScaleFactors().y);
        if (sf>RS::PointTolerance) {
            ret /= sf;
        }
    }

    return ret;
}
