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

#include <QSet>

#include "RArc.h"
#include "RBlockReferenceEntity.h"
#include "RCircle.h"
#include "RDebug.h"
#include "RDocument.h"
#include "REllipse.h"
#include "REntity.h"
#include "RExporter.h"
#include "RLine.h"
#include "RLinetype.h"
#include "RLinetypePatternMap.h"
#include "RPolyline.h"
#include "RSpline.h"
#include "RStorage.h"
#include "RTriangle.h"
#include "RUnit.h"
#include "RView.h"

class RImageData;

RExporter::RExporter()
    : document(NULL),
      currentLayer(NULL),
      layerSource(NULL),
      blockSource(NULL),
      draftMode(false),
      visualExporter(false),
      projectionRenderingHint(RS::RenderThreeD),
      pixelSizeHint(0.5) {

    currentPen.setColor(Qt::white);
    currentPen.setWidth(3);
    currentPen.setCapStyle(Qt::RoundCap);
    currentPen.setJoinStyle(Qt::RoundJoin);
    currentPen.setStyle(Qt::SolidLine);

    currentBrush.setColor(Qt::white);
    currentBrush.setStyle(Qt::SolidPattern);
}

RExporter::RExporter(RDocument& document, RMessageHandler *messageHandler, RProgressHandler *progressHandler)
    : document(&document),
      currentLayer(NULL),
      layerSource(NULL),
      blockSource(NULL),
      draftMode(false),
      visualExporter(false),
      projectionRenderingHint(RS::RenderThreeD),
      pixelSizeHint(0.5) {

    currentPen.setColor(Qt::white);
    currentPen.setWidth(3);
    currentPen.setCapStyle(Qt::RoundCap);
    currentPen.setJoinStyle(Qt::RoundJoin);

    currentBrush.setColor(Qt::white);
    currentBrush.setStyle(Qt::SolidPattern);
}



RExporter::~RExporter() {
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
    if (blockRefStack.isEmpty()) {
        return getEntity();
    }

    // return the top block reference in the hierarchy. this is the
    // first in the stack, NOT the stack top:
    return blockRefStack.first();
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
 * Sets the current pen (currentPen).
 */
void RExporter::setPen(const QPen& pen) {
    currentPen = pen;
    currentPen.setCapStyle(Qt::RoundCap);
    currentPen.setJoinStyle(Qt::RoundJoin);
}

QPen RExporter::getPen(const RPainterPath& path) {
    QPen pen = currentPen;

    if (draftMode) {
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
            if (!blockRefStack.isEmpty()) {
                QStack<RBlockReferenceEntity*> newBlockRefStack;
                newBlockRefStack = blockRefStack;
                newBlockRefStack.pop();
                color = blockRefStack.top()->getColor(true, newBlockRefStack);
            }
            else {
                // this can happen (by block at top level):
                color = RColor(Qt::white);
                //qWarning("color by block but current block reference is NULL");
                //Q_ASSERT(false);
            }
        }
        brush.setColor(color);
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

void RExporter::setEntityAttributes() {
    REntity* currentEntity = getEntity();
    if (currentEntity == NULL) {
        return;
    }

    setColor(currentEntity->getColor(true, blockRefStack));
    setLineweight(currentEntity->getLineweight(true, blockRefStack));
    setLinetypeId(currentEntity->getLinetypeId(true, blockRefStack));

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
 * Sets the current export color for entities. The default implementation
 * calls \ref setColor. Exporter implementations may choose to re-implement
 * this method for example to display entities in a different color when
 * they are selected.
 */
/*
void RExporter::setEntityColor(float r, float g, float b, float a) {
    QColor clr;
    clr.setRgbF(r, g, b, a);
    setEntityColor(clr);
}

void RExporter::setEntityColor(const RColor& color) {
    setColor(color);
}
*/

/**
 * \todo remove or refactor
 *
 * Overrides any calls to \ref setColor or \ref setEntityColor. All color
 * changes that are made between a call to this function and a call
 * to \ref unsetOverrideColor have no effect.
 */
/*
void RExporter::setFixedColor(float r, float g, float b, float a) {
    QColor clr;
    clr.setRgbF(r, g, b, a);
    setFixedColor(clr);
}

void RExporter::setFixedColor(const QColor& clr) {
    setColor(clr);
    fixedColor = true;
}
*/

/**
 * \todo remove or refactor
 *
 * Allows setting of colors after a section of exports with a fixed color.
void RExporter::unsetFixedColor() {
    fixedColor = false;
}
 */

/**
 * \return True if this exporter is currently using a fixed export color
 * (\ref setFixedColor has been called), false otherwise.
bool RExporter::isColorFixed() {
    return fixedColor;
}
 */

/**
 * \return Pointer to the entity that is currently being exported.
 */
REntity* RExporter::getEntity() {
    if (entityStack.size()>0) {
        return entityStack.top();
    }
    return NULL;
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

    currentLinetypePattern =
        RLinetypePatternMap::getPattern(doc->getLinetypeName(ltId));
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
 * The default implementation does nothing.
 */
void RExporter::endExport() {
}

/**
 * Exports the visual representation of all objects (including entities) of the document->
 */
bool RExporter::exportDocument() {
    startExport();
    if (!exportDocumentSettings()) {
        return false;
    }
    exportLinetypes();
    exportLayers();
    exportBlocks();
    exportViews();
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
    // export all QCAD specific document variables:
    QListIterator<QString> it(document->getVariables());
    while (it.hasNext()) {
        QString key = it.next();
        QVariant value = document->getVariable(key);
        exportDocumentSetting(key, value);
    }

    return true;
}

void RExporter::exportEntities(bool allBlocks, bool undone) {
    QSet<REntity::Id> ids = document->queryAllEntities(undone, allBlocks);

    // 20110815: ordered export (TODO: optional?):
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

void RExporter::exportBlocks() {
    QSet<RBlock::Id> ids = document->queryAllBlocks();
    QSet<RBlock::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
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
    if (layer.isNull() || !layer->isFrozen()) {
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
 * Sets the current entity to the given entity and calls \ref exportEntity().
 * Note that entity is a temporary clone.
 */
void RExporter::exportEntity(REntity& entity, bool preview, bool allBlocks) {

    RDocument* doc = entity.getDocument();
    if (doc==NULL) {
        doc = document;
    }

    // entity not on current block and allBlocks==false, break:
    if (!allBlocks && doc->getCurrentBlockId()!=entity.getBlockId()) {
        return;
    }

    entityStack.push(&entity);

    // find layer of the current entity
    QSharedPointer<RLayer> layer;
    if (layerSource!=NULL) {
        RLayer::Id layerId = entity.getLayerId();
        layer = layerSource->queryLayer(layerId);
        Q_ASSERT(!layer.isNull());
    }
    else {
        layer = doc->queryLayer(entity.getLayerId());
        if (layer.isNull()) {
            qDebug() << "Document: " << *doc;
            qDebug() << "Layer ID: " << entity.getLayerId();
            Q_ASSERT_X(false, "RExporter::exportEntity", "layer is NULL");
        }
    }
    if (!layer.isNull()) {
        currentLayer = layer.data();
    }

    // find block reference of the current entity, ignore this entity:
    bool blockRefSet = false;
    // check if this entity is a block reference:
    RBlockReferenceEntity* blockRef = dynamic_cast<RBlockReferenceEntity*>(&entity);
    if (blockRef!=NULL) {
        blockRefStack.push(blockRef);
        blockRefSet = true;
    }

    startEntity(/* topLevelEntity = */ blockRefSet || blockRefStack.isEmpty());
    exportCurrentEntity(preview);
    endEntity();

    if (blockRefSet) {
        blockRefStack.pop();
        //blockRefBS.clear();
    }
    currentLayer = NULL;

    entityStack.pop();
}

/**
 * Calls \ref exportEntity(REntity*) for the entity with the given ID.
 */
void RExporter::exportEntity(REntity::Id entityId, bool allBlocks) {
    QSharedPointer<REntity> e = document->queryEntityDirect(entityId);
    if (!e.isNull()) {
        exportEntity(*e, false, allBlocks);
    }
    else {
        unexportEntity(entityId);
    }
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
void RExporter::exportCurrentEntity(bool preview) {
    REntity* entity = getEntity();
    if (entity==NULL) {
        return;
    }

    // if this exporter exports a visual
    // representation of the drawing (scene, view, print)...
    if (isVisualExporter()) {
        // ... only export entities on visible layers:
        if (currentLayer!=NULL && currentLayer->isFrozen()) {
            return;
        }

        // ... only export entities in visible blocks:
        RBlockReferenceEntity* blockRef = dynamic_cast<RBlockReferenceEntity*>(entity);
        if (blockRef!=NULL) {
            RBlock::Id blockId = blockRef->getReferencedBlockId();
            if (blockId!=RBlock::INVALID_ID) {
                QSharedPointer<RBlock> block = document->queryBlockDirect(blockId);
                if (!block.isNull() && block->isFrozen()) {
                    return;
                }
            }
        }
    }

    setEntityAttributes();
    entity->exportEntity(*this, preview);
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

void RExporter::exportLine(const RLine& line, double offset) {
    if (!line.isValid()) {
        return;
    }

    double length = line.getLength();

    if (length>1e100) {
        return;
    }

    RLinetypePattern p = getLinetypePattern();

    if (!p.isValid() || p.getNumDashes() == 1 || draftMode) {
        exportLineSegment(line);
        return;
    }

    p.scale(getPatternFactor());

    // avoid exporting a huge number of small segments that overlap anyway:
    if (p.getLargestGap() < currentPen.widthF()) {
        exportLineSegment(line);
        return;
    }

    // avoid huge number of small segments due to very fine 
    // pattern or long lines:
    if (length / p.getPatternLength() > 5000) {
        exportLineSegment(line);
        return;
    }

    double angle = line.getAngle();
    RVector* vp = NULL;
    vp = new RVector[p.getNumDashes()];
    for (int i = 0; i < p.getNumDashes(); ++i) {
        vp[i] = RVector(cos(angle) * fabs(p.getDashLengthAt(i)),
                        sin(angle) * fabs(p.getDashLengthAt(i)));
    }

    bool optimizeEnds = false;
    if (RMath::isNaN(offset)) {
        offset = getPatternOffset(length, p);
        optimizeEnds = true;
    }
    else {
        double num = ceil(offset / p.getPatternLength());
        offset -= num * p.getPatternLength();
    }

    bool done = false;
    int i = 0;
    RVector cursor(line.getStartPoint() + RVector::createPolar(offset, angle));
    double total = offset;
    bool dashFound = false;
    bool gapFound = false;
    RVector p1 = line.getStartPoint();
    RVector p2 = p1;

    do {
        if (dashFound && !gapFound) {
            // don't shoot over end of line:
            if (total + fabs(p.getDashLengthAt(i)) >= length - 1.0e-6) {
                if (optimizeEnds) {
                    exportLineSegment(RLine(p1, line.endPoint));
                }
                else {
                    exportLineSegment(RLine(p1, p2));
                }
                break;
            }
            exportLineSegment(RLine(p1, p2));
        }

        // dash, no gap. note that a dash can have a length of 0.0 (point):
        if (p.getDashLengthAt(i) > -RS::PointTolerance) {
            // check if we're on the line already:
            if (total + p.getDashLengthAt(i) > 0) {
                p1 = cursor;

                // no gap at the beginning of the line:
                if (total < 0 || (!dashFound && optimizeEnds)) {
                    p1 = line.startPoint;
                }

                p2 = cursor + vp[i];
                if (p2.getDistanceTo(line.startPoint) > 1.0e-6) {
                    dashFound = true;
                }
            }
            gapFound = false;
        }

        // gap:
        else {
            gapFound = true;
        }

        cursor += vp[i];
        total += fabs(p.getDashLengthAt(i));

        done = total > length;

        ++i;
        if (i >= p.getNumDashes()) {
            i = 0;
        }
    } while (!done);

    if (!gapFound || !dashFound) {
        if (total + fabs(p.getDashLengthAt(i)) >= length - 1.0e-6) {
            if (optimizeEnds || (total>length && !gapFound)) {
                exportLineSegment(RLine(p1, line.endPoint));
            }
            else {
                exportLineSegment(RLine(p1, p2));
            }
        } else {
            exportLineSegment(RLine(p1, p2));
        }
    }

    delete[] vp;
}

void RExporter::exportArc(const RArc& arc, double offset) {
    if (!arc.isValid()) {
        return;
    }

    RLinetypePattern p = getLinetypePattern();

    if (getEntity() == NULL || !p.isValid() || p.getNumDashes() == 1 || draftMode) {
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

    p.scale(getPatternFactor());

    double length = normalArc.getLength();

    // avoid huge number of small segments due to very fine 
    // pattern or long lines:
    if (length / p.getPatternLength() > 5000) {
        exportArcSegment(arc);
        return;
    }

    double* vp = NULL;
    vp = new double[p.getNumDashes()];
    for (int i = 0; i < p.getNumDashes(); ++i) {
        vp[i] = fabs(p.getDashLengthAt(i)) / normalArc.radius;
    }

    if (RMath::isNaN(offset)) {
        offset = getPatternOffset(length, p);
    }

    QList<RArc> arcSegments;
    bool done = false;
    int i = 0;
    double cursor = normalArc.getStartAngle() + offset / normalArc.radius;
    double total = offset;
    bool dashFound = false;
    bool gapFound = false;
    double a1 = normalArc.getStartAngle();
    double a2;
    do {
        if (dashFound && !gapFound) {
            if (total + fabs(p.getDashLengthAt(i)) >= length - 1.0e-6) {
                arcSegments.append(RArc(normalArc.getCenter(), normalArc.getRadius(), a1, normalArc.getEndAngle()));
                break;
            }
            arcSegments.append(RArc(normalArc.getCenter(), normalArc.getRadius(), a1, a2));
        }
        if (p.getDashLengthAt(i) > 0) {
            // dash, no gap
            if (total + p.getDashLengthAt(i) > 0) {
                a1 = cursor;
                if (total < 0 || !dashFound) {
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
            exportArcSegment(arcSegments[i]);
        }
    }
    else {
        for (int i=0; i<arcSegments.length(); i++) {
            exportArcSegment(arcSegments[i]);
        }
    }

    delete[] vp;
}

void RExporter::exportArcSegment(const RArc& arc) {
    double segmentLength;
    if (pixelSizeHint>0.0) {
        // approximate arc with segments with the length of 2 pixels:
        segmentLength = pixelSizeHint * 2;
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
    // avoid huge radius and slow down to almost stand-still:
    if (radius>1.0e6) {
        return;
    }

    double aStep;
    if (radius<1.0e-3) {
        aStep = 0.1;
    }
    else {
        aStep = segmentLength / radius;
        if (aStep>1.0) {
            aStep = 1.0;
        }
        if (aStep<0.001) {
            aStep = 0.001;
        }
    }
    RVector prev = arc.getStartPoint();
    RVector ci;
    double a;

    if(!arc.isReversed()) {
        // Arc Counterclockwise:
        if(a1>a2-RS::AngleTolerance) {
            a2+=2*M_PI;
        }
        for(a=a1+aStep; a<=a2; a+=aStep) {
            ci.x = center.x + cos(a) * radius;
            ci.y = center.y + sin(a) * radius;
            //path.lineTo(RVector(ci.x, ci.y));
            this->exportLineSegment(RLine(prev, ci));
            prev = ci;
        }
    } else {
        // Arc Clockwise:
        if(a1<a2+RS::AngleTolerance) {
            a2-=2*M_PI;
        }
        for(a=a1-aStep; a>=a2; a-=aStep) {
            ci.x = center.x + cos(a) * radius;
            ci.y = center.y + sin(a) * radius;
            this->exportLineSegment(RLine(prev, ci));
            //path.lineTo(RVector(cix, ciy));
            prev = ci;
        }
    }
    this->exportLineSegment(RLine(prev, arc.getEndPoint()));
    //path.lineTo(arc.getEndPoint());
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

    aStep=0.05;
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
        for(a=a1+aStep; a<=a2; a+=aStep) {
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
        for(a=a1-aStep; a>=a2; a-=aStep) {
            vp.set(cp.x+cos(a)*radius1,
                   cp.y+sin(a)*radius2);
            vp.rotate(angle, vc);
            polyline.appendVertex(vp);
        }
    }
    vp.set(cp.x+cos(a2)*radius1,
           cp.y+sin(a2)*radius2);
    vp.rotate(angle, vc);
    polyline.appendVertex(vp);

    exportPolyline(polyline, offset);
}

void RExporter::exportPolyline(const RPolyline& polyline, double offset) {
    RLinetypePattern p = getLinetypePattern();

    bool continuous = false;
    if (getEntity() == NULL || !p.isValid() || p.getNumDashes() == 1 || draftMode) {
        continuous = true;
    }

    if (!continuous) {
        p.scale(getPatternFactor());

        if (RMath::isNaN(offset)) {
            double length = polyline.getLength();
            offset = getPatternOffset(length, p);
        }
    }

    exportExplodable(polyline, offset);
}

void RExporter::exportSpline(const RSpline& spline, double offset) {
    RLinetypePattern p = getLinetypePattern();

    bool continuous = false;
    if (getEntity() == NULL || !p.isValid() || p.getNumDashes() == 1 || draftMode) {
        continuous = true;
    }

    if (!continuous) {
        p.scale(getPatternFactor());

        if (RMath::isNaN(offset)) {
            double length = spline.getLength();
            offset = getPatternOffset(length, p);
        }
        exportExplodable(spline, offset);
    }
    else {
        // version <= 3.0.0 was (line interpolation):
        //exportExplodable(spline, offset);

        // performance improvement (using real splines):
        RPainterPath pp;
        pp.setPen(QPen(Qt::SolidLine));
        pp.addSpline(spline);
        exportPainterPaths(QList<RPainterPath>() << pp);
    }


    /*
    RLinetypePattern p = getLinetypePattern();
    p.scale(getPatternFactor());

    if (RMath::isNaN(offset)) {
        double length = spline.getLength();
        offset = getPatternOffset(length, p);
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
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        QSharedPointer<RLine> line = (*it).dynamicCast<RLine>();
        if (!line.isNull()) {
            exportLine(*line.data(), offset);
            offset -= line->getLength();
        }

        QSharedPointer<RArc> arc = (*it).dynamicCast<RArc>();
        if (!arc.isNull()) {
            exportArc(*arc.data(), offset);
            offset -= arc->getLength();
        }
    }
}

void RExporter::exportPainterPathSource(const RPainterPathSource& pathSource) {
    exportPainterPaths(pathSource.getPainterPaths());
}

void RExporter::exportPainterPaths(const QList<RPainterPath>& paths) {
    Q_UNUSED(paths)
    // TODO: split up painter paths into line semgents, splines (?), arcs...
}

void RExporter::exportBoundingBoxPaths(const QList<RPainterPath>& paths) {
    Q_UNUSED(paths)
}

void RExporter::exportImage(const RImageData& image) {
    Q_UNUSED(image)
}

/**
 * \return Offset to use to apply the given pattern to an entity of the
 *      given length that the pattern is symmetrical.
 */
double RExporter::getPatternOffset(double length,
        const RLinetypePattern& pattern) {
    double optOffset = 0.0;
    double gap = 0.0;
    double maxGap = RMINDOUBLE;
    for (int i = 0; i < pattern.getNumDashes(); ++i) {
        if (!pattern.isSymmetrical(i)) {
            continue;
        }
        double offset = getPatternOffset(length, pattern, i, &gap);
        if (gap > maxGap) {
            maxGap = gap;
            optOffset = offset;
//          qDebug(QString("RExporter::getPatternOffset: i=%1").arg(i));
        }
    }
    return optOffset;
}

double RExporter::getPatternOffset(double length,
        const RLinetypePattern& pattern, int index, double* gap) {
    double po = fabs(pattern.getDashLengthAt(index)) / 2;
    for (int i = index - 1; i >= 0; --i) {
        po += fabs(pattern.getDashLengthAt(i));
    }
    double offset = length / 2 - po;
    int m = (int) RMath::trunc(offset / (pattern.getPatternLength()));
    offset -= (m + 1) * pattern.getPatternLength();
    if (gap != NULL) {
        *gap = pattern.getDelta(-offset);
    }
    return offset;
}

double RExporter::getPatternFactor() {
    if (document==NULL) {
        return 1.0;
    }

    // note: pen width is in current drawing unit:
    double factor = currentPen.widthF();

    double ltscale = document->getKnownVariable(RS::LTSCALE).toDouble();

    if (factor < 1e-6) {
        return RUnit::convert(1.0, RS::Millimeter, document->getUnit()) * ltscale;
    }

    // LTSCALE might be zero:
    if (ltscale>1e-6) {
        factor *= ltscale;
    }

    return factor;
}

QStack<REntity*> RExporter::getEntityStack() {
    return entityStack;
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

    QSharedPointer<RLine> line = shape.dynamicCast<RLine>();
    if (!line.isNull()) {
        exportLine(*line.data());
    }

    QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
    if (!arc.isNull()) {
        exportArc(*arc.data());
    }

    QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
    if (!circle.isNull()) {
        exportCircle(*circle.data());
    }

    QSharedPointer<RTriangle> triangle = shape.dynamicCast<RTriangle>();
    if (!triangle.isNull()) {
        exportTriangle(*triangle.data());
    }
}

