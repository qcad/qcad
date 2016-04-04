/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
#include "RViewportEntity.h"


RGraphicsSceneQt::RGraphicsSceneQt(RDocumentInterface& documentInterface)
    : RGraphicsScene(documentInterface), decorating(false) {

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
    deleteDrawables();
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
    currentPainterPath.setNoClipping(!getClipping());

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
        if (entity!=NULL && entity->getCustomBoolProperty("QCAD", "ScreenWeight", false)==true) {
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
    currentPainterPath.setPixelUnit(pixelUnit);

    // experimental: allow entity display in pixel units:
    // this would probably need an additional property to define the center of the entity...
//    if (entity!=NULL && entity->getCustomBoolProperty("QCAD", "ScreenSize", false)==true) {
//        currentPainterPath.setPixelUnit(true);
//    }

    if (!exportToPreview) {
        if (entity!=NULL && entity->isSelected()) {
            currentPainterPath.setSelected(true);
        }
    }
//    else {
//        if (entity!=NULL && entity->getCustomProperty("QCADCAM", "simulation", false)==true) {
//            currentPainterPath.setHighlighted(true);
//        }
//    }

    return true;
}

void RGraphicsSceneQt::endPath() {
    if (!exportToPreview) {
        if (!currentPainterPath.isEmpty()) {
            // entities which are part of a block and have attributes ByBlock are exported to block ref ID:
            addPath(getBlockRefOrEntityId(), currentPainterPath, false);
        }
    } else {
        addToPreview(getBlockRefOrEntityId(), currentPainterPath);
    }

    currentPainterPath.setValid(false);

    if (!decorating) {
        // give entity export listeners a chance to decorate entity:
        REntity* entity = getEntity();
        if (entity!=NULL && entity->hasCustomProperties()) {
            if (RMainWindow::hasMainWindow()) {
                RMainWindow* appWin = RMainWindow::getMainWindow();
                // start separate path for entity decoration:
                decorating = true;
                appWin->notifyEntityExportListeners(this, entity);
                decorating = false;
            }
        }
    }
}

void RGraphicsSceneQt::exportPoint(const RPoint& point) {
    bool created = beginPath();

    currentPainterPath.addPoint(point.position);

    if (created) {
        endPath();
    }
}

double RGraphicsSceneQt::exportLine(const RLine& line, double offset) {
    bool created = beginPath();

    bool ret = RGraphicsScene::exportLine(line, offset);

    if (created) {
        endPath();
    }

    return ret;
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

void RGraphicsSceneQt::exportThickPolyline(const RPolyline& polyline) {
    if (RPolyline::hasProxy()) {
        QList<RPolyline> pls  = polyline.getOutline();

        RPainterPath pp;
        for (int i=0; i<pls.length(); i++) {
            if (pls[i].isClosed()) {
                pp.addPath(pls[i].toPainterPath());
            }
            else {
                currentPainterPath.addPath(pls[i].toPainterPath());
            }
        }

        endPath();

        beginPath();
        currentPainterPath.addPath(pp);
        currentPainterPath.setFillRule(Qt::WindingFill);
        currentPainterPath.setBrush(currentPen.color());
        currentPainterPath.setPen(QPen(Qt::NoPen));
        endPath();
    }
    else {
        RPolyline pl = polyline;
        pl.stripWidths();
        exportPolyline(pl);
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

    if (twoColorSelectedMode || screenBasedLinetypes) {
        // QPainterPath with pattern shown as solid (when clipped?)
        // bug workaround:
        currentPainterPath.moveTo(arc.getStartPoint());
        if (twoColorSelectedMode && qAbs(arc.getSweep())<0.05) {
            // Qt bug workaround: arcs with large radius / small angle are off:
            currentPainterPath.lineTo(arc.getEndPoint());
        }
        else {
            currentPainterPath.arcTo(
                arc.getCenter().x-arc.getRadius(),
                arc.getCenter().y-arc.getRadius(),
                arc.getRadius()*2, arc.getRadius()*2,
                RMath::rad2deg(-arc.getStartAngle()),
                RMath::rad2deg(-arc.getSweep())
            );
        }
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
        addPath(getBlockRefOrEntityId(), p, draftMode);
    } else {
        addToPreview(getBlockRefOrEntityId(), p);
    }
}

void RGraphicsSceneQt::exportRectangle(const RVector& p1, const RVector& p2) {
    if (getEntity() == NULL && !exportToPreview) {
        qWarning("RGraphicsSceneQt::exportRectangle: entity is NULL");
        return;
    }

    RPainterPath p;
    p.setZLevel(0);
    p.setPen(currentPen);
    p.setBrush(currentBrush);
    RVector vMin = RVector::getMinimum(p1, p2);
    RVector vMax = RVector::getMaximum(p1, p2);
    p.addRect(vMin.x, vMin.y, vMax.x, vMax.y);
    p.setNoClipping(!getClipping());

    if (!exportToPreview) {
        if (draftMode) {
            addPath(getBlockRefOrEntityId(), p, true);
        }
        else {
            addPath(getBlockRefOrEntityId(), p, false);
        }
    } else {
        addToPreview(getBlockRefOrEntityId(), p);
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
                addPath(getBlockRefOrEntityId(), path, draftMode);
            }
        }
        else {
            addToPreview(getBlockRefOrEntityId(), path);
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
        addToPreview(getBlockRefOrEntityId(), path);
    }
    else {
        REntity::Id id = getBlockRefOrEntityId();
        if (drawables.contains(id)) {
            //images[getBlockRefOrEntityId()].append(image);
            drawables[id].append(image);
        }
        else {
            //images.insert(getBlockRefOrEntityId(), QList<RImageData>() << image);
            drawables.insert(id, QList<RGraphicsSceneDrawable>() << image);
        }
    }
}

QList<RPainterPath> RGraphicsSceneQt::exportText(const RTextBasedData& text, bool forceSelected) {
    RTextBasedData textCopy = text;

    // resolve line type, color by layer, by block:
    textCopy.setLineweight(text.getLineweight(true, blockRefViewportStack));
    RColor col = text.getColor(true, blockRefViewportStack);
    textCopy.setColor(col);
    if (forceSelected) {
        textCopy.setSelected(true);
    }
    //qDebug() << "text color resolved to: " << textCopy.getColor();
    //textCopy.setLinetypeId(text.getLinetypeId(true, blockRefStack));

    // generate cached text layouts:
    QList<RTextLayout> textLayouts = textCopy.getTextLayouts();

    if (exportToPreview) {
        addTextToPreview(textCopy);
    }
    else {
        REntity::Id id = getBlockRefOrEntityId();
        if (drawables.contains(id)) {
            //texts[getBlockRefOrEntityId()].append(textCopy);
            drawables[id].append(textCopy);
        }
        else {
            //texts.insert(getBlockRefOrEntityId(), QList<RTextBasedData>() << textCopy);
            drawables.insert(id, QList<RGraphicsSceneDrawable>() << textCopy);
        }
    }

    QList<RPainterPath> ret;
    for (int t=0; t<textLayouts.length(); t++) {
        for (int k=0; k<textLayouts[t].painterPaths.length(); k++) {
            RPainterPath pp = textLayouts[t].painterPaths[k];
            pp.transform(textLayouts[t].transform);
            if (text.isSelected() || forceSelected) {
                pp.setSelected(true);
                pp.setPen(RSettings::getSelectionColor());
            }
            ret.append(pp);
        }
    }

    return ret;
}

void RGraphicsSceneQt::exportClipRectangle(const RBox& clipRectangle, bool forceSelected) {
    Q_UNUSED(forceSelected)

    if (exportToPreview) {
        previewClipRectangles.insert(getBlockRefOrEntityId(), clipRectangle);
    }
    else {
        clipRectangles.insert(getBlockRefOrEntityId(), clipRectangle);
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
        drawables.remove(entityId);
        //images.remove(entityId);
        //texts.remove(entityId);
        clipRectangles.remove(entityId);
    }
}

void RGraphicsSceneQt::deleteDrawables() {
    drawables.clear();
    //images.clear();
    //texts.clear();
    clipRectangles.clear();

    previewDrawables.clear();
    //previewTexts.clear();
    //previewImages.clear();
    previewClipRectangles.clear();
}

/**
 * \return A list of all painter paths that represent the entity with the
 * given ID.
 */
QList<RGraphicsSceneDrawable> RGraphicsSceneQt::getDrawables(REntity::Id entityId) {
    if (drawables.contains(entityId)) {
        return drawables[entityId];
    }

    return QList<RGraphicsSceneDrawable>();
}

/*
bool RGraphicsSceneQt::hasImageFor(REntity::Id entityId) {
    //return images.contains(entityId);

    if (!painterPaths.contains(entityId)) {
        return false;
    }

    for (int i=0; i<painterPaths[entityId].length(); i++) {
        if (painterPaths[entityId][i].type==RGraphicsSceneDrawable::Image) {
            return true;
        }
    }

    return false;
}

QList<RImageData> RGraphicsSceneQt::getImages(REntity::Id entityId) {
//    if (images.contains(entityId)) {
//        return images.value(entityId);
//    }

//    return QList<RImageData>();
    QList<RImageData> ret;

    if (!painterPaths.contains(entityId)) {
        return false;
    }

    for (int i=0; i<painterPaths[entityId].length(); i++) {
        if (painterPaths[entityId][i].type==RGraphicsSceneDrawable::Image) {
            ret.append(painterPaths[entityId][i].image);
        }
    }

    return ret;
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
*/

bool RGraphicsSceneQt::hasClipRectangleFor(REntity::Id entityId) {
    return clipRectangles.contains(entityId);
}

RBox RGraphicsSceneQt::getClipRectangle(REntity::Id entityId) {
    if (clipRectangles.contains(entityId)) {
        return clipRectangles.value(entityId);
    }

    return RBox();
}

void RGraphicsSceneQt::addPath(REntity::Id entityId, const RGraphicsSceneDrawable& path, bool draft) {
    Q_UNUSED(draft)
    if (drawables.contains(entityId)) {
        drawables[entityId].append(path);
    }
    else {
        drawables.insert(entityId, QList<RGraphicsSceneDrawable>() << path);
    }
}

bool RGraphicsSceneQt::hasPreview() const {
    return !previewDrawables.isEmpty() /*|| !previewTexts.isEmpty() || !previewImages.isEmpty()*/;
}

QList<REntity::Id> RGraphicsSceneQt::getPreviewEntityIds() {
    QList<REntity::Id> ret = previewDrawables.keys();
    //ret.append(previewTexts.keys());
    //ret.append(previewImages.keys());
    ret.append(previewClipRectangles.keys());
    ret = ret.toSet().toList();
    return ret;
}

QList<RGraphicsSceneDrawable> RGraphicsSceneQt::getPreviewDrawables(RObject::Id entityId) {
    if (previewDrawables.contains(entityId)) {
        return previewDrawables[entityId];
    }
    return QList<RGraphicsSceneDrawable>();
}

//QList<RTextBasedData> RGraphicsSceneQt::getPreviewTexts(REntity::Id entityId) {
//    if (previewTexts.contains(entityId)) {
//        return previewTexts[entityId];
//    }
//    return QList<RTextBasedData>();
//}

void RGraphicsSceneQt::clearPreview() {
    RGraphicsScene::clearPreview();
    previewDrawables.clear();
    //previewTexts.clear();
}
    
void RGraphicsSceneQt::addToPreview(REntity::Id entityId, const RGraphicsSceneDrawable& drawable) {
    if (previewDrawables.contains(entityId)) {
        previewDrawables[entityId].append(drawable);
    }
    else {
        previewDrawables.insert(entityId, QList<RGraphicsSceneDrawable>() << drawable);
    }
}

void RGraphicsSceneQt::addToPreview(REntity::Id entityId, const QList<RGraphicsSceneDrawable>& drawables) {
    if (previewDrawables.contains(entityId)) {
        previewDrawables[entityId].append(drawables);
    }
    else {
        previewDrawables.insert(entityId, drawables);
    }
}

void RGraphicsSceneQt::addTextToPreview(const RTextBasedData& text) {
    REntity::Id entityId = getBlockRefOrEntityId();
    if (previewDrawables.contains(entityId)) {
        //previewTexts[entityId].append(text);
        previewDrawables[entityId].append(text);
    }
    else {
        //previewTexts.insert(entityId, QList<RTextBasedData>() << text);
        previewDrawables.insert(entityId, QList<RGraphicsSceneDrawable>() << text);
    }
}

void RGraphicsSceneQt::highlightEntity(REntity& entity) {
    beginPreview();
    // get painter paths for closest entity:
    QList<RGraphicsSceneDrawable> drawables = getDrawables(entity.getId());
    for (int i = 0; i < drawables.size(); ++i) {
        drawables[i].setSelected(entity.isSelected());
        drawables[i].setHighlighted(true);
    }
    // highlighted entities are previews on top of original entities:
    addToPreview(entity.getId(), drawables);
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
            drawables.remove(getEntity()->getId());
            //images.remove(getEntity()->getId());
            //texts.remove(getEntity()->getId());
        }
    }
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RGraphicsSceneQt& gs) {
    dbg.nospace() << "RGraphicsSceneQt(" << QString("%1").arg((long int)&gs, 0, 16) << ")";
    QMap<REntity::Id, QList<RGraphicsSceneDrawable> >::iterator it;
    for (it=gs.drawables.begin(); it!=gs.drawables.end(); it++) {
        //dbg.nospace() << "\n" << it.key() << "\n  " << it.value() << "\n";
    }
    return dbg.space();
}
