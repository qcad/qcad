/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

#include "RBlockReferenceEntity.h"
#include "RDebug.h"
#include "RDocumentInterface.h"
#include "REntity.h"
#include "RGraphicsSceneQt.h"
#include "RGraphicsViewImage.h"
#include "RMainWindow.h"
#include "RPainterPathExporter.h"
#include "RPainterPathSource.h"
#include "RSettings.h"
#include "RSpline.h"
#include "RTextLabel.h"
#include "RUnit.h"


RGraphicsSceneQt::RGraphicsSceneQt(RDocumentInterface& documentInterface)
    : RGraphicsScene(documentInterface) /*, patternFactor(-1.0)*/ {

    setProjectionRenderingHint(RS::RenderTop);

    currentPainterPath.setValid(false);
}

RGraphicsSceneQt::~RGraphicsSceneQt() {
}

RGraphicsViewImage* RGraphicsSceneQt::getGraphicsView() const {
    QList<RGraphicsView*> views = getGraphicsViews();

    if (views.count()>=1) {
        return dynamic_cast<RGraphicsViewImage*>(views.at(0));
    }

    return NULL;
}

//const RGraphicsViewImage* RGraphicsSceneQt::getGraphicsView() const {
//    if (views.count()>=1) {
//        return dynamic_cast<const RGraphicsViewImage*>(views.at(0));
//    }

//    return NULL;
//}

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

    if (screenBasedLinetypes && currentPen.style()==Qt::SolidLine) {
        QVector<qreal> pat = currentLinetypePattern.getScreenBasedLinetype();
        if (!pat.isEmpty()) {
            currentPen.setDashPattern(pat);
        }
    }

    REntity* entity = getEntity();

    if (draftMode || screenBasedLinetypes || twoColorSelectedMode) {
        QPen localPen = currentPen;
        if (twoColorSelectedMode) {
            // fixed width for selected entities in two color selected mode:
            localPen.setCosmetic(true);
            localPen.setWidth(3);
        }
        else {
            if (draftMode) {
                localPen.setWidth(0);
            }
            else {
                // screen based line weights:
                localPen.setCosmetic(true);
                // magic number 4.25 to scale approximately, so 1mm width is 1mm on screen:
                localPen.setWidth(currentPen.widthF()*4.25);
            }
        }
        currentPainterPath.setPen(localPen);
    }
    else {
        if (entity!=NULL && entity->getCustomProperty("QCAD", "ScreenWeight", false)==true) {
            QPen localPen = currentPen;
            localPen.setCosmetic(true);
            localPen.setWidthF(entity->getLineweight()/10);
            currentPainterPath.setPen(localPen);
        }
        else {
            currentPainterPath.setPen(currentPen);
        }
    }

    currentPainterPath.setBrush(QBrush(Qt::NoBrush));
    currentPainterPath.setPixelSizeHint(pixelSizeHint);

    if (!exportToPreview) {
        if (entity!=NULL && entity->isSelected()) {
            currentPainterPath.setSelected(true);
        }
    }
    else {
        if (entity!=NULL && entity->getCustomProperty("QCADCAM", "simulation", false)==true) {
            currentPainterPath.setHighlighted(true);
        }
    }

    return true;
}

void RGraphicsSceneQt::endPath() {
    // give entity export listeners a chance to decorate entity:
//    REntity* entity = getEntity();
//    if (entity!=NULL && entity->hasCustomProperties()) {
//        if (RMainWindow::hasMainWindow()) {
//            RMainWindow* appWin = RMainWindow::getMainWindow();
//            // TODO: start separate path:
//            appWin->notifyEntityExportListeners(this, entity);
//        }
//    }

    if (!exportToPreview) {
        if (!currentPainterPath.isEmpty()) {
//            REntity* entity = getEntity();
//            if (entity->getColor().isByBlock() ||
//                entity->getLinetypeId()==document->getLinetypeByBlockId() ||
//                entity->getLineweight()==RLineweight::WeightByBlock) {

                // entities which are part of a block and have attributes ByBlock are exported to block ref ID:
                addPath(getBlockRefOrEntity()->getId(), currentPainterPath, false);
//            }
//            else {
//                // entities which are part of a block and have NO attributes ByBlock are exported to entity ID:
//                if (!painterPaths.contains(getEntity()->getId())) {
//                    addPath(getEntity()->getId(), currentPainterPath, false);
//                }
//            }
        }
    } else {
        addToPreview(currentPainterPath);
    }

    currentPainterPath.setValid(false);
    //setSelectedMode(false);
}

void RGraphicsSceneQt::exportPoint(const RPoint& point) {
    bool created = beginPath();

    currentPainterPath.addPoint(point.position);

    if (created) {
        endPath();
    }
}

double RGraphicsSceneQt::exportLine(const RLine& line, double offset, double w1, double w2) {
    bool created = beginPath();

    bool ret = RGraphicsScene::exportLine(line, offset, w1, w2);

    if (created) {
        endPath();
    }

    return ret;
}

void RGraphicsSceneQt::exportArc(const RArc& arc, double offset, double w1, double w2) {
    bool created = beginPath();

    RGraphicsScene::exportArc(arc, offset, w1, w2);

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

void RGraphicsSceneQt::exportThickLine(const RLine& line, double w1, double w2) {
    if (RPolyline::hasProxy()) {
        bool hasCurrentPath = false;
        if (currentPainterPath.isValid()) {
            hasCurrentPath = true;
            endPath();
        }

        beginPath();

        RPolyline::getPolylineProxy()->exportThickLine(currentPainterPath, line, w1, w2);
        currentPainterPath.setBrush(currentPen.color());
        currentPainterPath.setPen(QPen(Qt::NoPen));

        endPath();

        if (hasCurrentPath) {
            beginPath();
        }
    }
    else {
        exportLine(line);
    }
}

void RGraphicsSceneQt::exportThickArc(const RArc& arc, double w1, double w2) {
    if (RPolyline::hasProxy()) {
        bool hasCurrentPath = false;
        if (currentPainterPath.isValid()) {
            hasCurrentPath = true;
            endPath();
        }

        beginPath();

        RPolyline::getPolylineProxy()->exportThickArc(currentPainterPath, arc, w1, w2);
        currentPainterPath.setBrush(currentPen.color());
        currentPainterPath.setPen(QPen(Qt::NoPen));

        endPath();

        if (hasCurrentPath) {
            beginPath();
        }
    }
    else {
        exportArc(arc);
    }
}

void RGraphicsSceneQt::exportPolyline(const RPolyline& polyline, bool polylineGen, double offset) {
    // filling:
    bool created = beginPath();

    exportPolylineFill(polyline);

    if (created) {
        endPath();
    }

    // outline:
    created = beginPath();

    RGraphicsScene::exportPolyline(polyline, polylineGen, offset);

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

void RGraphicsSceneQt::exportArcSegment(const RArc& arc, bool allowForZeroLength) {
    Q_ASSERT(currentPainterPath.isValid());

    if (arc.getRadius()<RS::PointTolerance) {
        currentPainterPath.addPoint(arc.getCenter());
        return;
    }

    // arc threshold is configurable (FS#1012):
    if (arc.getAngleLength(allowForZeroLength)<=RSettings::getArcAngleLengthThreshold()) {
        // Qt won't export a zero length line as point:
        RVector startPoint = arc.getStartPoint() - RVector::createPolar(0.01, arc.getStartAngle()+M_PI_2);
        RVector endPoint = arc.getEndPoint() + RVector::createPolar(0.01, arc.getStartAngle()+M_PI_2);
        currentPainterPath.moveTo(startPoint);
        currentPainterPath.lineTo(endPoint);
        return;
    }

    // arc approximation with splines: faster but not precise enough:
//     RPainterPath p;
//     p.addArc(arc);
//     currentPainterPath.addPath(p);

    if (twoColorSelectedMode) {
        // QPainterPath with pattern shown as solid when clipped bug workaround:
        currentPainterPath.moveTo(arc.getStartPoint());
        currentPainterPath.arcTo(
            arc.getCenter().x-arc.getRadius(),
            arc.getCenter().y-arc.getRadius(),
            arc.getRadius()*2, arc.getRadius()*2,
            RMath::rad2deg(-arc.getStartAngle()),
            RMath::rad2deg(-arc.getSweep())
        );
    }
    else {
        currentPainterPath.setAutoRegen(true);
        RGraphicsScene::exportArcSegment(arc, allowForZeroLength);
    }
}

void RGraphicsSceneQt::exportLineSegment(const RLine& line, double angle) {
    Q_ASSERT(currentPainterPath.isValid());

    if (line.getLength()<RS::PointTolerance && !RMath::isNaN(angle)) {
        // Qt won't export a zero length line as point:
        RVector startPoint = line.startPoint - RVector::createPolar(0.01, angle);
        RVector endPoint = line.endPoint + RVector::createPolar(0.01, angle);
        currentPainterPath.moveTo(startPoint);
        currentPainterPath.lineTo(endPoint);
        return;
    }

    // add new painter path with current entity ID:
    if ((currentPainterPath.currentPosition() - QPointF(line.startPoint.x, line.startPoint.y)).manhattanLength() > RS::PointTolerance) {
        currentPainterPath.moveTo(line.startPoint);
    }

    currentPainterPath.lineTo(line.endPoint);
}

void RGraphicsSceneQt::exportXLine(const RXLine& xLine) {
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
    RLine clippedLine = xLine.getClippedLine(box);

    double offs = clippedLine.getStartPoint().getDistanceTo(xLine.getBasePoint());
    if (RMath::isSameDirection(xLine.getBasePoint().getAngleTo(clippedLine.getStartPoint()), xLine.getDirection1())) {
        offs *= -1;
    }

    exportLine(clippedLine, offs);

    currentPainterPath.setAlwaysRegen(true);

    if (created) {
        endPath();
    }
}

void RGraphicsSceneQt::exportRay(const RRay& ray) {
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
    RLine clippedLine = ray.getClippedLine(box);

    double offs = clippedLine.getStartPoint().getDistanceTo(ray.getBasePoint());
    if (RMath::isSameDirection(ray.getBasePoint().getAngleTo(clippedLine.getStartPoint()), ray.getDirection1())) {
        offs *= -1;
    }

    exportLine(clippedLine, offs);

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

//void RGraphicsSceneQt::exportPainterPathSource(const RPainterPathSource& pathSource) {
//    exportPainterPaths(pathSource.getPainterPaths(false));
//}

void RGraphicsSceneQt::exportPainterPaths(const QList<RPainterPath>& paths) {
    if (getEntity() == NULL && !exportToPreview) {
        qWarning("RGraphicsSceneQt::exportPainterPaths: entity is NULL");
        return;
    }

    RPainterPath path;
    for (int i=0; i<paths.size(); i++) {
        path = paths.at(i);
        path.setZLevel(0);

        path.setBrush(getBrush(path));
        if (path.getInheritPen()) {
            path.setPen(currentPainterPath.getPen());
        }
        else {
            path.setPen(getPen(path));
        }

        if (!exportToPreview) {
            // export into current path (used for complex linetypes):
            if (currentPainterPath.isValid()) {
                currentPainterPath.addPath(path);
            }
            else {
                addPath(getBlockRefOrEntity()->getId(), path, draftMode);
            }
        }
        else {
            addToPreview(path);
        }
    }
}

void RGraphicsSceneQt::exportImage(const RImageData& image, bool forceSelected) {
    if (exportToPreview) {
        RPainterPath path;
        path.setPen(currentPen);
        path.setBrush(Qt::NoBrush);
        if (forceSelected) {
            path.setSelected(true);
        }
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
        if (images.contains(getBlockRefOrEntity()->getId())) {
            images[getBlockRefOrEntity()->getId()].append(image);
        }
        else {
            images.insert(getBlockRefOrEntity()->getId(), QList<RImageData>() << image);
        }
    }
}

void RGraphicsSceneQt::exportText(const RTextBasedData& text, bool forceSelected) {
    RTextBasedData textCopy = text;

    // resolve line type, color by layer, by block:
    textCopy.setLineweight(text.getLineweight(true, blockRefStack));
    RColor col = text.getColor(true, blockRefStack);
    textCopy.setColor(col);
    if (forceSelected) {
        textCopy.setSelected(true);
    }
    //qDebug() << "text color resolved to: " << textCopy.getColor();
    //textCopy.setLinetypeId(text.getLinetypeId(true, blockRefStack));

    // generate cached text layouts:
    textCopy.getTextLayouts();
//    QList<RTextLayout> lts = textCopy.getTextLayouts();
//    for (int i=0; i<lts.length(); i++) {
//        for (int k=0; k<lts[i].painterPaths.length(); k++) {
//            QPen p = lts[i].painterPaths[k].getPen();
//            qDebug() << p;
//            if (!p.color().isValid()) {
//                p.setColor(col);
//                lts[i].painterPaths[k].setPen(p);
//            }
//        }
//    }

    if (exportToPreview) {
        addTextToPreview(textCopy);
    }
    else {
        if (texts.contains(getBlockRefOrEntity()->getId())) {
            texts[getBlockRefOrEntity()->getId()].append(textCopy);
        }
        else {
            texts.insert(getBlockRefOrEntity()->getId(), QList<RTextBasedData>() << textCopy);
        }
    }
}

/**
 * \return Pattern scale factor with scale applied if we are printing.
 */
double RGraphicsSceneQt::getLineTypePatternScale(const RLinetypePattern& p) const {
    double factor = RGraphicsScene::getLineTypePatternScale(p);

    const RGraphicsViewImage* view = getGraphicsView();
    if (view==NULL) {
        return factor;
    }

    // see: FS#322 - Line type scaling with print scale factor
    if (view->isPrinting() || view->isPrintPreview()) {
        QVariant scaleVariant = getDocument().getVariable("PageSettings/Scale", QVariant(), true);
        if (!scaleVariant.isValid() || !scaleVariant.canConvert(QVariant::String)) {
            return factor;
        }

        factor /= RMath::parseScale(scaleVariant.toString());
    }

    //qDebug() << "scene factor: " << factor;

    return factor;
}

void RGraphicsSceneQt::unexportEntity(REntity::Id entityId) {
    if (!exportToPreview) {
        painterPaths.remove(entityId);
        images.remove(entityId);
        texts.remove(entityId);
    }
}

void RGraphicsSceneQt::deletePainterPaths() {
    painterPaths.clear();
    images.clear();
    texts.clear();
    previewPainterPaths.clear();
    previewTexts.clear();
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

QList<RImageData> RGraphicsSceneQt::getImages(REntity::Id entityId) {
    if (images.contains(entityId)) {
        return images.value(entityId);
    }

    return QList<RImageData>();
}

bool RGraphicsSceneQt::hasTextsFor(REntity::Id entityId) {
    return texts.contains(entityId);
}

QList<RTextBasedData> RGraphicsSceneQt::getTexts(REntity::Id entityId) {
    if (texts.contains(entityId)) {
        return texts.value(entityId);
    }

    return QList<RTextBasedData>();
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

bool RGraphicsSceneQt::hasPreviewPainterPaths() const {
    return !previewPainterPaths.isEmpty();
}

QList<RTextBasedData> RGraphicsSceneQt::getPreviewTexts() {
    return previewTexts;
}

bool RGraphicsSceneQt::hasPreviewTexts() const {
    return !previewTexts.isEmpty();
}

void RGraphicsSceneQt::clearPreview() {
    RGraphicsScene::clearPreview();
    previewPainterPaths.clear();
    previewTexts.clear();
}
    
void RGraphicsSceneQt::addToPreview(const RPainterPath& painterPath) {
    previewPainterPaths << painterPath;
}

void RGraphicsSceneQt::addToPreview(const QList<RPainterPath>& painterPaths) {
    previewPainterPaths << painterPaths;
}

void RGraphicsSceneQt::addTextToPreview(const RTextBasedData& text) {
    previewTexts << text;
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
            // top level entity (i.e. not entity in block ref): remove previous graphical representations:
            painterPaths.remove(getEntity()->getId());
            images.remove(getEntity()->getId());
            texts.remove(getEntity()->getId());
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
