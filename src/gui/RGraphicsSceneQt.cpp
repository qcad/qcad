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

#if QT_VERSION >= 0x050000
#include <QtConcurrent>
#else
#include <qtconcurrentrun.h>
#endif

#include "RBlockReferenceEntity.h"
#include "RDocument.h"
#include "REntity.h"
#include "RGraphicsSceneQt.h"
#include "RGraphicsViewImage.h"
#include "RMainWindow.h"
#include "RPainterPathExporter.h"
#include "RSettings.h"
#include "RShapesExporter.h"
#include "RTriangle.h"
#include "RUnit.h"
#include "RViewportEntity.h"


RGraphicsSceneQt::RGraphicsSceneQt(RDocumentInterface& documentInterface) :
    RGraphicsScene(documentInterface),
    decorating(false),
    screenBasedLinetypesOverride(false) {

    setProjectionRenderingHint(RS::RenderTop);

    currentPainterPath.setValid(false);

    // line type patterns are done on the view level,
    // by applying dashes on painter paths
    // this is to account for (non-uniform) block scales:
    setEnablePatterns(false);
}

RGraphicsSceneQt::~RGraphicsSceneQt() {
    clear();
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

        QList<RGraphicsSceneDrawable>* pps = getDrawables(*it);
        QList<RGraphicsSceneDrawable>::iterator it2;
        for (it2 = pps->begin(); it2 != pps->end(); it2++) {
            RGraphicsSceneDrawable& pp = *it2;
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
    currentPainterPath.setNoColorMode(getNoColorMode());
    currentPainterPath.setWipeout(getWipeout());
    currentPainterPath.setFrameless(getFrameless());

    QSharedPointer<REntity> entity = getEntity();
    QSharedPointer<RLayer> layer;
    if (entity!=NULL) {
        layer = document->queryLayerDirect(entity->getLayerId());
    }
    if (!layer.isNull()) {
        if (layer->getCustomBoolProperty("QCAD", "ScreenBasedLinetypes", false)==true) {
            screenBasedLinetypesOverride = true;
            currentPainterPath.setScreenBasedLinetype(screenBasedLinetypesOverride);
        }
        // TODO: handle layer opacity:
//        if (!layer->isPlottable()) {
//            currentPainterPath.setNoPlot(true);
//        }
    }

    if (getScreenBasedLinetypes() && currentPen.style()==Qt::SolidLine) {
        QVector<qreal> pat = currentLinetypePattern.getScreenBasedLinetype();
        if (!pat.isEmpty()) {
            currentPen.setDashPattern(pat);
        }
    }

    if (draftMode || getScreenBasedLinetypes() || twoColorSelectedMode) {
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

                if (!pixelWidth) {
                    // magic number 4.25 to scale approximately, so 1mm width is 1mm on screen:
                    localPen.setWidth(RUnit::convert(currentPen.widthF(), document->getUnit(), RS::Millimeter)*4.25);
                }
            }
        }
        currentPainterPath.setPen(localPen);
    }
    else {
        if ((entity!=NULL && entity->getCustomBoolProperty("QCAD", "ScreenWeight", false)==true) ||
            (!layer.isNull() && layer->getCustomBoolProperty("QCAD", "ScreenWeight", false)==true)) {
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
    currentPainterPath.setPixelWidth(pixelWidth);

    // experimental: allow entity display in pixel units:
    // this would probably need an additional property to define the center of the entity...
//    if (entity!=NULL && entity->getCustomBoolProperty("QCAD", "ScreenSize", false)==true) {
//        currentPainterPath.setPixelUnit(true);
//    }

    if (!exportToPreview) {
        if (entity!=NULL && (entity->isSelected() || entity->isSelectedWorkingSet())) {
            //qDebug() << "painter path selected for entity:" << entity->getId();
            currentPainterPath.setSelected(true);
        }
    }

    return true;
}

void RGraphicsSceneQt::endPath() {
    QSharedPointer<REntity> entity = getEntity();

    if (!currentPainterPath.isEmpty()) {
        transformAndApplyPatternPath(currentPainterPath);

        // entities which are part of a block and have attributes ByBlock are exported to block ref ID:
        RGraphicsSceneDrawable d(currentPainterPath);
        addDrawable(getBlockRefOrEntityId(), d, false, exportToPreview);
    }

    currentPainterPath.setValid(false);

    if (!decorating) {
        // give entity export listeners a chance to decorate entity:
        if (entity!=NULL && entity->hasCustomProperties()) {
            if (RMainWindow::hasMainWindow()) {
                RMainWindow* appWin = RMainWindow::getMainWindow();
                // start separate path for entity decoration:
                decorating = true;
                appWin->notifyEntityExportListeners(this, entity.data());
                decorating = false;
            }
        }
    }

    screenBasedLinetypesOverride = false;
}

/**
 * Transform the given paths according to current block reference scales.
 */
void RGraphicsSceneQt::transformAndApplyPatternPath(RPainterPath& path) const {
    // apply transforms (for paths inside block references):
    if (!transformStack.isEmpty()) {
        for (int k=transformStack.size()-1; k>=0; k--) {
            // TODO: move to place where path is generated:
            path.transform(transformStack[k]);
        }
    }

    if (getScreenBasedLinetypes()) {
        // screen based line types:
        // pattern applied elsewhere:
        return;
    }

    if (path.getNoPattern()) {
        // path has no pattern (e.g. polyline with segment widths):
        return;
    }

    if (path.getPen().style()==Qt::NoPen) {
        // solid fills without pen
        return;
    }

    // apply line type pattern to path:
    RLinetypePattern lp = currentLinetypePattern;
    if (lp.isValid() && lp.getNumDashes() > 1) {
        // path shapes as lines and splines:
        // may contain polylines for CAD font texts:
        QList<QSharedPointer<RShape> > pathShapes = path.getShapes();

        lp.scale(getLineTypePatternScale(lp));

        // detect viewport context:
        double scaleHint = 1.0;
        QSharedPointer<RViewportEntity> vp = getCurrentViewport();
        if (!vp.isNull()) {
            scaleHint = vp->getScale();
        }

        QPainterPath pathWithPattern;
        RPainterPathExporter ppe(getDocument());
        ppe.setPixelSizeHint(getPixelSizeHint());
        ppe.setExportZeroLinesAsPoints(false);
        ppe.setLinetypePattern(lp);
        ppe.setIgnoreLineTypePatternScale(true);
        ppe.setScaleHint(scaleHint);

        if (path.getPolylineGen()) {

            double length = 0.0;
            for (int i=0; i<pathShapes.length(); i++) {
                length += pathShapes[i]->getLength();
            }
            //qDebug() << "pattern offset:" << lp.getPatternOffset(length);
            RShapesExporter(ppe, pathShapes, lp.getPatternOffset(length));
            RPainterPath p = ppe.getPainterPath();
            //qDebug() << "path with dashes:" << p;
            pathWithPattern.addPath(p);
        }
        else {
            //RPainterPathExporter ppe(getDocument());
            //ppe.setPixelSizeHint(getPixelSizeHint());
            //ppe.setExportZeroLinesAsPoints(false);
            //ppe.setLinetypePattern(lp);
            //ppe.setIgnoreLineTypePatternScale(true);
            //ppe.setScaleHint(scaleHint);

            for (int i=0; i<pathShapes.length(); i++) {
                //double length = 0.0;
                //qDebug() << "shape:" << *pathShapes[i];

                double offset = RNANDOUBLE;
                QList<QSharedPointer<RShape> > shapes;
                if (RShape::isPolylineShape(*pathShapes[i])) {
                    // only used for polylines in CAD fonts (original shapes of glyphs):
                    QSharedPointer<RPolyline> pl = pathShapes[i].dynamicCast<RPolyline>();
                    shapes << pl->getExploded();
                    //length = pl->getLength();
                    //offset = lp.getPatternOffset(pl->getLength());
                }
                else {
                    shapes << pathShapes[i];
                    //length = pathShapes[i]->getLength();
                }

                //qDebug() << "pattern offset:" << lp.getPatternOffset(length);
                RShapesExporter(ppe, shapes, offset);
                //lp.getPatternOffset(length));
                RPainterPath p = ppe.getPainterPath();
                pathWithPattern.addPath(p);
            }
        }

        //qDebug() << "auto 1" << path.getAutoRegen();
        path.setPath(pathWithPattern);
        //qDebug() << "auto 2" << path.getAutoRegen();
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

void RGraphicsSceneQt::exportThickPolyline(const RPolyline& polyline) {
    if (RPolyline::hasProxy()) {
        QList<RPolyline> pls  = polyline.getOutline();

        RPainterPath pp;
        for (int i=0; i<pls.length(); i++) {
            if (pls[i].isClosed()) {
                pp.addPath(pls[i].toPainterPath());
            }
            else {
                // add open polylines directly to currentPainterPath:
                currentPainterPath.addPath(pls[i].toPainterPath());
            }
        }

        endPath();

        beginPath();
        currentPainterPath.addPath(pp);
        currentPainterPath.setFillRule(Qt::WindingFill);
        currentPainterPath.setBrush(currentPen.color());
        //currentPainterPath.setPen(QPen(Qt::NoPen));

        QPen p(Qt::SolidLine);
        p.setCosmetic(true);
        if (RSettings::getRenderThinPolylines1px()) {
            RGraphicsViewImage* view = getGraphicsView();
            if (view!=NULL && view->isPrintingOrExporting()) {
                p.setWidthF(0.001);
            }
            else {
                p.setWidth(0);
                currentPainterPath.setPixelWidth(true);
            }
        }
        else {
            p.setWidthF(0.001);
        }
        p.setColor(currentPen.color());
        currentPainterPath.setPen(p);

        currentPainterPath.setNoPattern(true);

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

    // let path remember if path uses pattern along whole polyline:
    // used to apply the line pattern on regen:
    currentPainterPath.setPolylineGen(polylineGen);

    if (!polylineGen) {
        for (int i=0; i<polyline.countSegments(); i++) {
            // add original shapes of polyline:
            // needed for correct rendering of polylines with individual segment patterns:
            currentPainterPath.addOriginalShape(polyline.getSegmentAt(i));
        }
    }

    if (created) {
        if (!polyline.hasWidths()) {
            // if polyline has widths, this is called by exportThickPolyline:
            endPath();
        }
    }
}

void RGraphicsSceneQt::exportPolylineFill(const RPolyline& polyline) {
    if (currentBrush!=Qt::NoBrush) {
        bool created = beginPath();

        RPolyline pl = polyline;
        pl.setClosed(true);

//         TODO: support arc segments for filling:
//        QPolygonF qpolygon;
//        QList<RVector> points = polyline.getVertices();
//        for (int i = 0; i < points.size(); ++i) {
//            RVector v = points.at(i);
//            qpolygon << QPointF(v.x, v.y);
//        }

        currentPainterPath.setBrush(currentBrush);

        currentPainterPath.moveTo(pl.getStartPoint());
        currentPainterPath.addPolyline(pl);
        //currentPainterPath.addPolygon(qpolygon);

        if (created) {
            endPath();
        }
    }
}

void RGraphicsSceneQt::exportSpline(const RSpline& spline, double offset) {
    bool created = beginPath();

    RGraphicsScene::exportSpline(spline, offset);
    currentPainterPath.setPolylineGen(true);

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

    if (twoColorSelectedMode || getScreenBasedLinetypes()) {
        // QPainterPath with pattern shown as solid (when clipped?)
        // bug workaround:
        currentPainterPath.moveTo(arc.getStartPoint());
        if (twoColorSelectedMode && qAbs(arc.getSweep())<0.05) {
            // Qt bug workaround: arcs with large radius / small angle are off:
            currentPainterPath.lineTo(arc.getEndPoint());
        }
        else {
            // this is faster for continuous arcs:
            // 20210903: also use this for arcs with patterns for screen-based linetypes:
            currentPainterPath.setAutoRegen(true);
            RGraphicsScene::exportArcSegment(arc, allowForZeroLength);

//            if (getLinetypePattern().getNumDashes()<=1) {
//            }
//            else {
//                // slower:
//                currentPainterPath.setAutoRegen(true);
//                QList<RSpline> splines = RSpline::createSplinesFromArc(arc);
//                for (int i=0; i<splines.length(); i++) {
//                    currentPainterPath.addSpline(splines[i]);
//                }

                // this is not precise enough:
//                currentPainterPath.arcTo(
//                    arc.getCenter().x-arc.getRadius(),
//                    arc.getCenter().y-arc.getRadius(),
//                    arc.getRadius()*2, arc.getRadius()*2,
//                    RMath::rad2deg(-arc.getStartAngle()),
//                    RMath::rad2deg(-arc.getSweep())
//                );
//            }
        }
    }
    else {
        currentPainterPath.setAutoRegen(true);
        currentPainterPath.setPolylineGen(true);
        RGraphicsScene::exportArcSegment(arc, allowForZeroLength);

        // TODO: this might be worth considering:
//        QList<RSpline> splines = RSpline::createSplinesFromArc(arc);
//        for (int i=0; i<splines.length(); i++) {
//            currentPainterPath.addSpline(splines[i]);
//        }
    }
}

void RGraphicsSceneQt::exportLineSegment(const RLine& line, double angle) {
    Q_ASSERT(currentPainterPath.isValid());

    if (line.getLength()<RS::PointTolerance && !RMath::isNaN(angle)) {
        // Qt won't export a zero length line as point:
        // note: QPainterPath compares points as floats with lower precision,
        // 1e-1 should work, even for extreme coordinates
        // see FS#2053
        RVector startPoint = line.startPoint - RVector::createPolar(1e-4, angle);
        RVector endPoint = line.endPoint + RVector::createPolar(1e-4, angle);

        currentPainterPath.moveTo(startPoint);
        currentPainterPath.lineTo(endPoint);
        return;
    }

    if ((currentPainterPath.currentPosition() - QPointF(line.startPoint.x, line.startPoint.y)).manhattanLength() > RS::PointTolerance) {
        currentPainterPath.moveTo(line.startPoint);
    }

    currentPainterPath.lineTo(line.endPoint);

    //currentPainterPath.setPixelWidth(true);
    //currentPainterPath.setPen(QPen(QBrush("white"), 10));
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

    // transform view box in inverted way as entities:
    if (!transformStack.isEmpty()) {
        for (int k=0; k<transformStack.size(); k++) {
            bool ok;
            QTransform t = transformStack[k].inverted(&ok);
            if (!ok) {
                qDebug() << "transform not invertable";
            }
            box.transform(t);
        }
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

    // transform view box in inverted way as entities:
    if (!transformStack.isEmpty()) {
        for (int k=0; k<transformStack.size(); k++) {
            bool ok;
            QTransform t = transformStack[k].inverted(&ok);
            if (!ok) {
                qDebug() << "transform not invertable";
            }
            box.transform(t);
        }
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
    if (draftMode || getScreenBasedLinetypes()) {
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

    transformAndApplyPatternPath(p);

    RGraphicsSceneDrawable d(p);
    addDrawable(getBlockRefOrEntityId(), d, draftMode, exportToPreview);
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

    RGraphicsSceneDrawable d(p);
    addDrawable(getBlockRefOrEntityId(), d, draftMode, exportToPreview);
}

void RGraphicsSceneQt::exportPainterPaths(const QList<RPainterPath>& paths, double z) {
    Q_UNUSED(z)

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

        // export into current path (used for complex linetypes):
        if (currentPainterPath.isValid()) {
            currentPainterPath.addPath(path);
        }
        else {
            transformAndApplyPatternPath(path);

            RGraphicsSceneDrawable d(path);
            addDrawable(getBlockRefOrEntityId(), d, draftMode, exportToPreview);
        }
    }
}

void RGraphicsSceneQt::exportImage(const RImageData& image, bool forceSelected) {
    REntity::Id id = getBlockRefOrEntityId();

    if (exportToPreview) {
        RImageData img = image;
        img.setFade(qMax(img.getFade(), 50));
        img.setDocument(&getDocument());
        RGraphicsSceneDrawable d(img);
        addDrawable(id, d, draftMode, true);
//        RPainterPath path;
//        path.setPen(currentPen);
//        path.setBrush(Qt::NoBrush);
//        if (forceSelected) {
//            path.setSelected(true);
//        }
//        QList<RLine> edges = image.getEdges();
//        for (int i=0; i<=edges.count(); i++) {
//            if (i==0) {
//                path.moveTo(edges.at(i).getStartPoint());
//            }
//            else {
//                path.lineTo(edges.at(i % edges.count()).getStartPoint());
//            }
//        }
//        RGraphicsSceneDrawable d(path);
//        addDrawable(id, d, draftMode, true);
    }
    else {
        RGraphicsSceneDrawable d(image);
        addDrawable(id, d, draftMode, false);
    }
}

QList<RPainterPath> RGraphicsSceneQt::exportText(const RTextBasedData& text, bool forceSelected) {
    RTextBasedData textCopy = text;

    // make sure we render the correct text (tag) for attribute definitions:
    textCopy.setText(text.getRenderedText());

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
        RGraphicsSceneDrawable d(textCopy);
        addDrawable(id, d, draftMode);
//        if (drawables.contains(id)) {
//            drawables[id].append(textCopy);
//        }
//        else {
//            drawables.insert(id, QList<RGraphicsSceneDrawable>() << textCopy);
//        }
    }

    // painter paths for CAD line text:
    QList<RPainterPath> ret;
    for (int t=0; t<textLayouts.length(); t++) {
        for (int k=0; k<textLayouts[t].painterPaths.length(); k++) {
            RPainterPath pp = textLayouts[t].painterPaths[k];
            pp.transform(textLayouts[t].transform);
            if (text.isSelected() || text.isSelectedWorkingSet() || forceSelected) {
                pp.setSelected(true);
                pp.setPen(RSettings::getSelectionColor());
            }
            else {
                // use fixed color from given text data instead of current entity
                // used (only) for dimension text labels if dimension text color is configured:
                if (!col.isByBlock() && !col.isByLayer() && !pp.getPen().color().isValid()) {
                    pp.setPen(col);
                    pp.setFixedPenColor(true);
                }
            }

            pp.setAutoRegen(true);
            pp.setPixelSizeHint(pixelSizeHint);
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

void RGraphicsSceneQt::clearClipRectangles() {
    previewClipRectangles.clear();
    clipRectangles.clear();
}

void RGraphicsSceneQt::exportTransform(const RTransform& t) {
    RExporter::exportTransform(t);

    REntity::Id id = getBlockRefOrEntityId();
    RGraphicsSceneDrawable d(t);
    addDrawable(id, d, draftMode, exportToPreview);

    // remember transformation stack for XLine / Ray transforms:
    transformStack.push(t);
}

void RGraphicsSceneQt::exportEndTransform() {
    RExporter::exportEndTransform();

    REntity::Id id = getBlockRefOrEntityId();
    RGraphicsSceneDrawable d(RGraphicsSceneDrawable::EndTransform);
    addDrawable(id, d, draftMode, exportToPreview);

    // remember transformation stack for XLine / Ray transforms:
    if (!transformStack.isEmpty()) {
        transformStack.pop();
    }
    else {
        qWarning() << "transformStack empty";
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
        // 20200225: only apply global scale for model space, not for viewports or other blocks:
        if (document->getCurrentBlockId()==document->getModelSpaceBlockId()) {
            QVariant scaleVariant = getDocument().getVariable("PageSettings/Scale", QVariant(), true);
            if (!scaleVariant.isValid() || !scaleVariant.canConvert(QVariant::String)) {
                return factor;
            }
            factor /= RMath::parseScale(scaleVariant.toString());
        }
    }

    //qDebug() << "scene factor: " << factor;

    return factor;
}

void RGraphicsSceneQt::unexportEntity(REntity::Id entityId) {
    RGraphicsScene::unexportEntity(entityId);
    if (!exportToPreview) {
        drawables.remove(entityId);
        clipRectangles.remove(entityId);
    }
}

void RGraphicsSceneQt::deleteDrawables() {
    drawables.clear();
    clipRectangles.clear();

    previewDrawables.clear();
    previewClipRectangles.clear();
}

QList<RGraphicsSceneDrawable> RGraphicsSceneQt::getDrawablesList(REntity::Id entityId) {
    if (drawables.contains(entityId)) {
        return drawables[entityId];
    }
    return QList<RGraphicsSceneDrawable>();
}

/**
 * \return A list of all drawables (painter path, text, image) that represent the entity with the
 * given ID.
 */
QList<RGraphicsSceneDrawable>* RGraphicsSceneQt::getDrawables(REntity::Id entityId) {
    // TODO: check should not be necessary:
    if (drawables.contains(entityId)) {
        return &drawables[entityId];
    }

    return NULL;
}

bool RGraphicsSceneQt::hasClipRectangleFor(REntity::Id entityId, bool preview) const {
    if (preview) {
        return previewClipRectangles.contains(entityId);
    }
    else {
        return clipRectangles.contains(entityId);
    }
}

RBox RGraphicsSceneQt::getClipRectangle(REntity::Id entityId, bool preview) const {
    if (preview) {
        if (previewClipRectangles.contains(entityId)) {
            return previewClipRectangles.value(entityId);
        }
    }
    else {
        if (clipRectangles.contains(entityId)) {
            return clipRectangles.value(entityId);
        }
    }

    return RBox();
}

void RGraphicsSceneQt::addDrawable(REntity::Id entityId, RGraphicsSceneDrawable& drawable, bool draft, bool preview) {
    Q_UNUSED(draft)

    // entityId: ID of entity for which the drawbale represents a part (e.g. line, block reference, viewport, etc)

    // this is the current entity being exported:
    // this might be in the context of the block reference or viewport indicated by entityId:
    QSharedPointer<REntity> entity = getEntity();
    if (entity!=NULL) {
        QSharedPointer<RLayer> layer = getEntityLayer(entity);
        if (!layer.isNull()) {
            if (!layer->isPlottable()) {
                drawable.setNoPlot(true);
            }
        }
    }

    // check block ref stack for non-plottable layer:
    if (drawable.getNoPlot()==false) {
        for (int i=blockRefViewportStack.size()-1; i>=0; i--) {
            QSharedPointer<REntity> e = blockRefViewportStack[i];
            if (e.isNull()) {
                continue;
            }
            if (e->getType()==RS::EntityViewport) {
                // entities in non-plottable viewports are plottable:
                continue;
            }
            QSharedPointer<RLayer> layer = getEntityLayer(e);
            if (!layer.isNull()) {
                if (!layer->isPlottable()) {
                    drawable.setNoPlot(true);
                    break;
                }
            }
        }
    }

    QSharedPointer<REntity> blockRefEntity = getBlockRefOrEntity();
    if (blockRefEntity!=NULL && blockRefEntity->getType()==RS::EntityBlockRef) {
        QSharedPointer<RBlockReferenceEntity> blockRef = blockRefEntity.dynamicCast<RBlockReferenceEntity>();
        if (blockRef!=NULL) {
            //qDebug() << "exporting entity in blockref:" << blockRef->getId();
            RBlock::Id blockId = blockRef->getReferencedBlockId();

            // retrieve document from entity (could be a preview document):
            RDocument* doc = blockRefEntity->getDocument();
            if (doc!=NULL) {
                QSharedPointer<RBlock> block = doc->queryBlockDirect(blockId);
                if (block!=NULL && block->isPixelUnit()) {
                    drawable.setPixelUnit(true);
                }
            }
        }
    }

    if (document->isEditingWorkingSet()) {
        if (entity!=NULL) {
            for (int i=entityStack.size()-1; i>=0; i--) {
                if (entityStack[i]->isWorkingSet()) {
//                    qDebug() << "working set";
                    drawable.setWorkingSet(true);
                    break;
                }
            }
//            if (entity->isWorkingSet()) {
//                drawable.setWorkingSet(true);
//            }
        }
    }

    QMap<REntity::Id, QList<RGraphicsSceneDrawable> >* dwb;
    if (preview) {
        dwb = &previewDrawables;
    }
    else {
        dwb = &drawables;
    }

    if (dwb->contains(entityId)) {
        (*dwb)[entityId].append(drawable);
    }
    else {
        dwb->insert(entityId, QList<RGraphicsSceneDrawable>() << drawable);
    }
}

bool RGraphicsSceneQt::hasPreview() const {
    return !previewDrawables.isEmpty();
}

QList<REntity::Id> RGraphicsSceneQt::getPreviewEntityIds() {
    QList<REntity::Id> retWithDuplicates = previewDrawables.keys();
    retWithDuplicates.append(previewClipRectangles.keys());

    // remove duplicate without changing order:
    QSet<REntity::Id> set;
    QList<REntity::Id> ret;
    for (int i=0; i<retWithDuplicates.length(); i++) {
        if (!set.contains(retWithDuplicates[i])) {
            ret.append(retWithDuplicates[i]);
            set.insert(retWithDuplicates[i]);
        }
    }

    return ret;
}

QList<RGraphicsSceneDrawable>* RGraphicsSceneQt::getPreviewDrawables(RObject::Id entityId) {
    if (previewDrawables.contains(entityId)) {
        return &previewDrawables[entityId];
    }
    return NULL;
}

void RGraphicsSceneQt::clearPreview() {
    RGraphicsScene::clearPreview();
    previewDrawables.clear();
}

void RGraphicsSceneQt::exportEntities(bool allBlocks, bool undone, bool invisible) {
    //RDebug::startTimer(100);
    RGraphicsScene::exportEntities(allBlocks, undone, invisible);
    //RDebug::stopTimer(100, "exportEntities");

    /*
    return;

    QSet<REntity::Id> ids = document->queryAllEntities(undone, allBlocks);
    if (ids.isEmpty()) {
        return;
    }

    RDebug::startTimer(100);
    RDocumentInterface& di = getDocumentInterface();
    di.disableUpdates();

    //QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);
    QList<REntity::Id> list = ids.toList();

    for (int i=0; i<8; i++) {
        RGraphicsSceneQt* s  = new RGraphicsSceneQt(di);
        // TODO: init scenes based on this scene:
        //s->
        threadScenes.append(s);
    }

    // render into multiple scenes using threads:
    int slice = int(floor(double(list.length())/threadScenes.length()));

    QList<QFuture<void> > futureThread;
    for (int threadId=0; threadId<threadScenes.length(); threadId++) {
        int start = threadId*slice;
        int end = (threadId+1)*slice;
        if (threadId==threadScenes.length()-1) {
            end = list.length();
        }
        qDebug() << "slice:" << start << end;
        futureThread.append(QtConcurrent::run(this, &RGraphicsSceneQt::exportEntitiesThread, threadId, list, start, end));
    }
    //RDebug::stopTimer(100, "launch threads");

    for (int i=0; i<futureThread.length(); i++) {
        futureThread[i].waitForFinished();
    }

    // merge result into this scene:
    // TODO:
    for (int i=0; i<threadScenes.length(); i++) {
        //qDebug() << "thread " << i << " has " << threadScenes[i]->drawables.size() << " drawables";
        drawables.insert(threadScenes[i]->drawables);

//        QMap<REntity::Id, QList<RGraphicsSceneDrawable> >::iterator it;
//        for (it=threadScenes[i]->drawables.begin(); it!=threadScenes[i]->drawables.end(); it++) {
//            QList<RGraphicsSceneDrawable> list;
//            for (int k=0; k<it->length(); k++) {
//                list.append((*it).at(k).clone());
//            }
//            drawables.insert(it.key(), list);
//        }

        clipRectangles.insert(threadScenes[i]->clipRectangles);
        referencePoints.insert(threadScenes[i]->referencePoints);

        //threadScenes[i]->drawables.clear();
        //threadScenes[i]->clipRectangles.clear();
        //threadScenes[i]->referencePoints.clear();
    }

    //qDebug() << "got drawables:" << drawables.size();

    for (int i=0; i<threadScenes.length(); i++) {
        di.unregisterScene(*threadScenes[i]);
        delete threadScenes[i];
    }
    threadScenes.clear();

    di.enableUpdates();

    RDebug::stopTimer(100, "exportEntitiesThread");

    */
}

void RGraphicsSceneQt::exportEntitiesThread(int threadId, QList<REntity::Id>& list, int start, int end) {
    qDebug() << "threadId:" << threadId;
    qDebug() << "start:" << start;
    qDebug() << "end:" << end;

    for (int i=start; i<end; i++) {
        exportEntityThread(threadId, list[i]);
    }
}

void RGraphicsSceneQt::exportEntityThread(int threadId, REntity::Id id) {
    //qDebug() << "export:" << id;
    QSharedPointer<REntity> e = document->queryEntityDirect(id);
    if (!e.isNull()) {
        threadScenes[threadId]->exportEntity(e, false);
    }
}
    
void RGraphicsSceneQt::addToPreview(REntity::Id entityId, RGraphicsSceneDrawable& drawable) {
    addDrawable(entityId, drawable, draftMode, true);
}

void RGraphicsSceneQt::addToPreview(REntity::Id entityId, QList<RGraphicsSceneDrawable>& drawables) {
    for (int i=0; i<drawables.length(); i++) {
        addDrawable(entityId, drawables[i], draftMode, true);
    }
}

void RGraphicsSceneQt::addTextToPreview(const RTextBasedData& text) {
    REntity::Id entityId = getBlockRefOrEntityId();
    RGraphicsSceneDrawable d(text);
    addDrawable(entityId, d, draftMode, true);
}

void RGraphicsSceneQt::highlightEntity(REntity& entity) {
    // get painter paths for closest entity:
    QList<RGraphicsSceneDrawable>* drawables = getDrawables(entity.getId());
    if (drawables==NULL) {
        return;
    }

    // avoid changing the original painter paths
    // (avoid entities that keep being highlighted):
    QList<RGraphicsSceneDrawable> drawablesCopy = *drawables;

    beginPreview();
    RBox clipRectangle = getClipRectangle(entity.getId());
    for (int i = 0; i < drawablesCopy.size(); ++i) {
        drawablesCopy[i].setSelected(entity.isSelected() || entity.isSelectedWorkingSet());
        drawablesCopy[i].setHighlighted(true);
    }
    if (clipRectangle.isValid()) {
        previewClipRectangles.insert(entity.getId(), clipRectangle);
        //exportClipRectangle(clipRect);
    }
    // highlighted entities are previews on top of original entities:
    addToPreview(entity.getId(), drawablesCopy);
    endPreview();
}

void RGraphicsSceneQt::startEntity(bool topLevelEntity) {
    if (getEntity() == NULL) {
        return;
    }

    RGraphicsScene::startEntity(topLevelEntity);

    if (!exportToPreview) {
        if (topLevelEntity) {
            // top level entity (i.e. not entity in block ref):
            // remove previous graphical representations:
            drawables.remove(getEntity()->getId());
        }
    }
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RGraphicsSceneQt& gs) {
    dbg.nospace() << "RGraphicsSceneQt(" << QString("%1").arg((unsigned long long int)&gs, 0, 16) << ")";
    //QMap<REntity::Id, QList<RGraphicsSceneDrawable> >::iterator it;
    //for (it=gs.drawables.begin(); it!=gs.drawables.end(); it++) {
        //dbg.nospace() << "\n" << it.key() << "\n  " << it.value() << "\n";
    //}
    return dbg.space();
}
