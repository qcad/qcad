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
#include <QDragMoveEvent>
#include <QScrollBar>

#include "RDebug.h"
#include "RDocumentInterface.h"
#include "REntity.h"
#include "RGraphicsSceneQt.h"
#include "RGraphicsViewImage.h"
#include "RLine.h"
#include "RPoint.h"
#include "RSettings.h"
#include "RSpline.h"
#include "RTextLabel.h"
#include "RPainterPathSource.h"
#include "RPolyline.h"
#include "RBlockReferenceEntity.h"


RGraphicsSceneQt::RGraphicsSceneQt(RDocumentInterface& documentInterface)
    : RGraphicsScene(documentInterface) /*, patternFactor(-1.0)*/ {

    setProjectionRenderingHint(RS::RenderTop);

    currentPainterPath.setValid(false);
}

RGraphicsSceneQt::~RGraphicsSceneQt() {
}

RGraphicsViewImage* RGraphicsSceneQt::getGraphicsView() {
    QList<RGraphicsView*> views = getGraphicsViews();

    if (views.count()>=1) {
        return dynamic_cast<RGraphicsViewImage*>(views.at(0));
    }

    return NULL;
}

void RGraphicsSceneQt::clear() {
    RGraphicsScene::clear();
    deletePainterPaths();
}

void RGraphicsSceneQt::updateSelectionStatus(QSet<REntity::Id>& affectedEntities, bool updateViews) {
    RGraphicsScene::updateSelectionStatus(affectedEntities, updateViews);
    /*
    // Change painter paths directly when selecting an entity (faster).
    // Generally good idea, needs refining (blue handles not added when selecting entity):
    RDocument& doc = documentInterface.getDocument();

    QSet<REntity::Id>::iterator it;
    for (it = affectedEntities.begin(); it != affectedEntities.end(); it++) {
        QSharedPointer<REntity> entity = doc.queryEntityDirect(*it);
        if (entity.isNull()) {
            continue;
        }
        bool on = entity->isSelected();

        QList<RPainterPath> pps = getPainterPaths(*it);
        QList<RPainterPath>::iterator it2;
        for (it2 = pps.begin(); it2 != pps.end(); it2++) {
            RPainterPath& pp = *it2;
            pp.setSelected(on);
        }
    }

    if (updateViews) {
        regenerateViews(false);
    }
    */
}

/**
 * Starts a new painter path to export geometry into.
 * \return True if a path has been created, false if there is already a
 *      valid path.
 */
bool RGraphicsSceneQt::beginPath() {
    if (!exportToPreview) {
        Q_ASSERT(getEntity() != NULL);
    }

    if (currentPainterPath.isValid()) {
        return false;
    }

    currentPainterPath = RPainterPath();
    currentPainterPath.setZLevel(0);

    if (screenBasedLinetypes) {
        QVector<qreal> pat = currentLinetypePattern.getScreenBasedLinetype();
        if (!pat.isEmpty()) {
            currentPen.setDashPattern(pat);
        }
    }

    if (draftMode || screenBasedLinetypes) {
        QPen draftPen = currentPen;
        draftPen.setWidth(0);
        currentPainterPath.setPen(draftPen);
    }
    else {
        currentPainterPath.setPen(currentPen);
    }

    currentPainterPath.setBrush(QBrush(Qt::NoBrush));
    currentPainterPath.setPixelSizeHint(pixelSizeHint);

    if (!exportToPreview) {
        if (getEntity()->isSelected()) {
            currentPainterPath.setSelected(true);
        }
    }
    else {
        if (getEntity()!=NULL) {
            if (getEntity()->getCustomProperty("QCADCAM", "simulation", false)==true) {
                currentPainterPath.setHighlighted(true);
            }
        }
    }

    return true;
}

void RGraphicsSceneQt::endPath() {
    if (!exportToPreview) {
        if (!currentPainterPath.isEmpty()) {
            addPath(getBlockRefOrEntity()->getId(), currentPainterPath, false);
        }
    } else {
        addToPreview(currentPainterPath);
    }

    currentPainterPath.setValid(false);
}

void RGraphicsSceneQt::exportPoint(const RPoint& point) {
    bool created = beginPath();

    currentPainterPath.addPoint(point.position);

    if (created) {
        endPath();
    }
}

void RGraphicsSceneQt::exportLine(const RLine& line, double offset) {
    bool created = beginPath();

    RGraphicsScene::exportLine(line, offset);

    if (created) {
        endPath();
    }
}

void RGraphicsSceneQt::exportArc(const RArc& arc, double offset) {
    bool created = beginPath();

    RGraphicsScene::exportArc(arc, offset);

    if (created) {
        endPath();
    }
}

void RGraphicsSceneQt::exportEllipse(const REllipse& ellipse, double offset) {
    bool created = beginPath();

    RGraphicsScene::exportEllipse(ellipse, offset);

    if (created) {
        endPath();
    }
}

void RGraphicsSceneQt::exportPolyline(const RPolyline& polyline, double offset) {
    // filling:
    bool created = beginPath();

    exportPolylineFill(polyline);

    if (created) {
        endPath();
    }

    // outline:
    created = beginPath();

    RGraphicsScene::exportPolyline(polyline, offset);

    if (created) {
        endPath();
    }
}

void RGraphicsSceneQt::exportPolylineFill(const RPolyline& polyline) {
    if (currentBrush!=Qt::NoBrush) {
        bool created = beginPath();

        // TODO: support arc segments for filling:
        QPolygonF qpolygon;
        QList<RVector> points = polyline.getVertices();
        for (int i = 0; i < points.size(); ++i) {
            RVector v = points.at(i);
            qpolygon << QPointF(v.x, v.y);
        }
        currentPainterPath.setBrush(currentBrush);
        currentPainterPath.addPolygon(qpolygon);

        if (created) {
            endPath();
        }
    }
}

void RGraphicsSceneQt::exportSpline(const RSpline& spline, double offset) {
    bool created = beginPath();

    RGraphicsScene::exportSpline(spline, offset);

    if (created) {
        endPath();
    }
}

void RGraphicsSceneQt::exportArcSegment(const RArc& arc) {
    Q_ASSERT(currentPainterPath.isValid());

    if (arc.getRadius()<RS::PointTolerance) {
        currentPainterPath.addPoint(arc.getCenter());
        return;
    }

    // arc threshold is configurable (FS#1012):
    if (arc.getAngleLength()<RSettings::getArcAngleLengthThreshold()) {
        currentPainterPath.moveTo(arc.getStartPoint());
        currentPainterPath.lineTo(arc.getEndPoint());
        return;
    }

    // arc approximation with splines: faster but not precise enough:
    // RPainterPath p;
    // p.addArc(arc);
    // path.addPath(p);

    currentPainterPath.setAutoRegen(true);
    RGraphicsScene::exportArcSegment(arc);
}

void RGraphicsSceneQt::exportLineSegment(const RLine& line) {
    Q_ASSERT(currentPainterPath.isValid());

    // add new painter path with current entity ID:
    if ((currentPainterPath.currentPosition() - QPointF(line.startPoint.x, line.startPoint.y)).manhattanLength() > RS::PointTolerance) {
        currentPainterPath.moveTo(line.startPoint);
    }

    currentPainterPath.lineTo(line.endPoint);
}

void RGraphicsSceneQt::exportXLine(const RLine& line) {
    bool created = beginPath();

    Q_ASSERT(currentPainterPath.isValid());

    // find largest view box over all attached views:
    RBox box;
    QList<RGraphicsView*>::iterator it;
    for (it=views.begin(); it!=views.end(); it++) {
        RBox b = (*it)->getBox();
        box.growToIncludeBox(b);
    }

    // trim line to view box:
    RLine clippedLine = line;
    clippedLine.clipToXY(box, true);

    exportLineSegment(clippedLine);

    currentPainterPath.setAlwaysRegen(true);

    if (created) {
        endPath();
    }
}

void RGraphicsSceneQt::exportTriangle(const RTriangle& triangle) {
    if (getEntity() == NULL && !exportToPreview) {
        qWarning("RGraphicsSceneQt::exportTriangle: entity is NULL");
        return;
    }

    // add new painter path with current entity ID:
    RPainterPath p;
    p.setZLevel(0);
    if (draftMode || screenBasedLinetypes) {
        QPen draftPen = currentPen;
        draftPen.setWidth(0);
        p.setPen(draftPen);
    }
    else {
        p.setPen(currentPen);
    }
    p.setBrush(currentBrush);
    p.moveTo(triangle.corner[0]);
    p.lineTo(triangle.corner[1]);
    p.lineTo(triangle.corner[2]);
    p.lineTo(triangle.corner[0]);

    if (!exportToPreview) {
        addPath(getBlockRefOrEntity()->getId(), p, draftMode);
    } else {
        addToPreview(p);
    }
}

void RGraphicsSceneQt::exportRectangle(const RVector& p1,
        const RVector& p2) {
    if (getEntity() == NULL && !exportToPreview) {
        qWarning("RGraphicsSceneQt::exportRectangle: entity is NULL");
        return;
    }

    RPainterPath p;
    p.setZLevel(0);
    p.setPen(currentPen);
    p.setBrush(currentBrush);
    RVector v = RVector::getMinimum(p1, p2);
    p.addRect(v.x, v.y, fabs(p2.x - p1.x), fabs(p2.y - p1.y));

    if (!exportToPreview) {
        if (draftMode) {
            addPath(getBlockRefOrEntity()->getId(), p, true);
        }
        else {
            addPath(getBlockRefOrEntity()->getId(), p, false);
        }
    } else {
        addToPreview(p);
    }
}

void RGraphicsSceneQt::exportPainterPathSource(const RPainterPathSource& pathSource) {
    exportPainterPaths(pathSource.getPainterPaths(false));
}

void RGraphicsSceneQt::exportPainterPaths(const QList<RPainterPath>& paths) {
    if (getEntity() == NULL && !exportToPreview) {
        qWarning("RGraphicsSceneQt::exportPainterPaths: entity is NULL");
        return;
    }

    for (int i=0; i<paths.size(); i++) {
        RPainterPath path = paths.at(i);
        path.setZLevel(0);

        path.setBrush(getBrush(path));
        path.setPen(getPen(path));

        if (!exportToPreview) {
            if (draftMode) {
                addPath(getBlockRefOrEntity()->getId(), path, true);
            }
            else {
                addPath(getBlockRefOrEntity()->getId(), path, false);
            }
        }
        else {
            addToPreview(path);
        }
    }
}

void RGraphicsSceneQt::exportImage(const RImageData& image) {
    if (exportToPreview) {
        RPainterPath path;
        path.setPen(currentPen);
        path.setBrush(Qt::NoBrush);
        QList<RLine> edges = image.getEdges();
        for (int i=0; i<=edges.count(); i++) {
            if (i==0) {
                path.moveTo(edges.at(i).getStartPoint());
            }
            else {
                path.lineTo(edges.at(i % edges.count()).getStartPoint());
            }
        }
        addToPreview(path);
    }
    else {
        images.insert(getBlockRefOrEntity()->getId(), image);
    }
}

/**
 * \return Pattern scale factor with scale applied if we are printing.
 */
double RGraphicsSceneQt::getPatternFactor() {
    double ret = RGraphicsScene::getPatternFactor();
    RGraphicsViewImage* view = getGraphicsView();
    if (view==NULL) {
        return ret;
    }

    // see: FS#322 - Line type scaling with print scale factor
    if (view->isPrinting() || view->isPrintPreview()) {
        QVariant scaleVariant = getDocument().getVariable("PageSettings/Scale", QVariant(), true);
        if (!scaleVariant.isValid() || !scaleVariant.canConvert(QVariant::String)) {
            return ret;
        }

        ret /= RMath::parseScale(scaleVariant.toString());
    }

    return ret;
}

void RGraphicsSceneQt::unexportEntity(REntity::Id entityId) {
    if (!exportToPreview) {
        painterPaths.remove(entityId);
        images.remove(entityId);
    }
}

void RGraphicsSceneQt::deletePainterPaths() {
    painterPaths.clear();
    images.clear();
    previewPainterPaths.clear();
}

/**
 * \return A list of all painter paths that represent the entity with the
 * given ID.
 */
QList<RPainterPath> RGraphicsSceneQt::getPainterPaths(REntity::Id entityId) {
    if (painterPaths.contains(entityId)) {
        return painterPaths[entityId];
    }

    return QList<RPainterPath>();
}

bool RGraphicsSceneQt::hasImageFor(REntity::Id entityId) {
    return images.contains(entityId);
}

RImageData RGraphicsSceneQt::getImage(REntity::Id entityId) {
    if (images.contains(entityId)) {
        return images.value(entityId);
    }

    return RImageData();
}

void RGraphicsSceneQt::addPath(REntity::Id entityId, const RPainterPath& path, bool draft) {
    if (painterPaths.contains(entityId)) {
        painterPaths[entityId].append(path);
    }
    else {
        painterPaths.insert(entityId, QList<RPainterPath>() << path);
    }
}

QList<RPainterPath> RGraphicsSceneQt::getPreviewPainterPaths() {
    return previewPainterPaths;
}

void RGraphicsSceneQt::clearPreview() {
    RGraphicsScene::clearPreview();
    previewPainterPaths.clear();
}
    
void RGraphicsSceneQt::addToPreview(const RPainterPath& painterPath) {
    previewPainterPaths << painterPath;
}

void RGraphicsSceneQt::addToPreview(const QList<RPainterPath>& painterPaths) {
    previewPainterPaths << painterPaths;
}

void RGraphicsSceneQt::highlightEntity(REntity& entity) {
    beginPreview();
    // get painter paths for closest entity:
    QList<RPainterPath> painterPaths = getPainterPaths(entity.getId());
    for (int i = 0; i < painterPaths.size(); ++i) {
        painterPaths[i].setSelected(entity.isSelected());
        painterPaths[i].setHighlighted(true);
    }
    addToPreview(painterPaths);
    endPreview();
}

void RGraphicsSceneQt::startEntity(bool topLevelEntity) {
    if (getEntity() == NULL) {
        return;
    }

    RGraphicsScene::startEntity(topLevelEntity);

    if (!exportToPreview) {
        if (topLevelEntity) {
            painterPaths.remove(getEntity()->getId());
        }
    }
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RGraphicsSceneQt& gs) {
    dbg.nospace() << "RGraphicsSceneQt(" << QString("%1").arg((long int)&gs, 0, 16) << ")";
    QMap<REntity::Id, QList<RPainterPath> >::iterator it;
    for (it=gs.painterPaths.begin(); it!=gs.painterPaths.end(); it++) {
        dbg.nospace() << "\n" << it.key() << "\n  " << it.value() << "\n";
    }
    return dbg.space();
}
