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

#ifndef RGRAPHICSSCENEQT_H
#define RGRAPHICSSCENEQT_H

#include "gui_global.h"

#include <QPen>
#include <QList>
#include <QMultiMap>

#include "RArc.h"
#include "RCircle.h"
#include "RDocumentInterface.h"
#include "REllipse.h"
#include "RGraphicsScene.h"
#include "RImageData.h"
#include "RLine.h"
#include "RPainterPath.h"
#include "RPainterPathSource.h"
#include "RPoint.h"
#include "RPolyline.h"
#include "RRay.h"
#include "RXLine.h"

class RGraphicsViewImage;

/**
 * \brief Qt based 2d graphics scene.
 *
 * This graphics scene is an exporter that exports entities into
 * QPainterPaths (2d). 
 * 
 * \ref RGraphicView "graphics views". 
 *
 * \ingroup gui
 * \scriptable
 */
class QCADGUI_EXPORT RGraphicsSceneQt : public RGraphicsScene {
public:
    RGraphicsSceneQt(RDocumentInterface& documentInterface);
    virtual ~RGraphicsSceneQt();

    RGraphicsViewImage* getGraphicsView() const;
    //RGraphicsViewImage* const getGraphicsView() const;

    virtual void clear();

    virtual void updateSelectionStatus(QSet<REntity::Id>& affectedEntities, bool updateViews);

    virtual void clearPreview();

    bool beginPath();
    void endPath();
    
    virtual void unexportEntity(REntity::Id entityId);

    virtual void exportPoint(const RPoint& point);
    virtual double exportLine(const RLine& line, double offset = RNANDOUBLE, double w1 = -1.0, double w2 = -1.0);
    virtual void exportArc(const RArc& arc, double offset = RNANDOUBLE, double w1 = -1.0, double w2 = -1.0);
    virtual void exportEllipse(const REllipse& ellipse, double offset = RNANDOUBLE);
    //virtual void exportQuad(const RVector& p1, const RVector& p2, const RVector& p3, const RVector& p4);
    virtual void exportThickLine(const RLine& line, double w1, double w2);
    virtual void exportThickArc(const RArc& arc, double w1, double w2);
    virtual void exportPolyline(const RPolyline& polyline, bool polylineGen = true, double offset = RNANDOUBLE);
    void exportPolylineFill(const RPolyline& polyline);
    virtual void exportSpline(const RSpline& spline, double offset = RNANDOUBLE);

    virtual void exportArcSegment(const RArc& arc, bool allowForZeroLength = false);
    virtual void exportLineSegment(const RLine& line, double angle = RNANDOUBLE);
    virtual void exportXLine(const RXLine& xLine);
    virtual void exportRay(const RRay& ray);
    virtual void exportTriangle(const RTriangle& triangle);
    virtual void exportRectangle(const RVector& p1, const RVector& p2);

    //virtual void exportPainterPathSource(const RPainterPathSource& pathSource);
    virtual void exportPainterPaths(const QList<RPainterPath>& paths);
    virtual void exportImage(const RImageData& image, bool forceSelected = false);
    virtual void exportText(const RTextBasedData& text, bool forceSelected = false);

    virtual double getLineTypePatternScale(const RLinetypePattern& p) const;
    
    virtual void highlightEntity(REntity& entity);

    void deletePainterPaths();
    QList<RPainterPath> getPainterPaths(REntity::Id entityId);
    QList<RPainterPath> getPreviewPainterPaths();
    bool hasPreviewPainterPaths() const;
    QList<RTextBasedData> getPreviewTexts();
    bool hasPreviewTexts() const;
    bool hasImageFor(REntity::Id entityId);
    QList<RImageData> getImages(REntity::Id entityId);
    bool hasTextsFor(REntity::Id entityId);
    QList<RTextBasedData> getTexts(REntity::Id entityId);

    void addPath(REntity::Id entityId, const RPainterPath& path, bool draft);

    void addToPreview(const QList<RPainterPath>& painterPaths);
    void addToPreview(const RPainterPath& painterPath);
    void addTextToPreview(const RTextBasedData& text);

    virtual void startEntity(bool topLevelEntity);

    virtual void dump() {
        qDebug() << *this;
    }

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, RGraphicsSceneQt& gs);

private:
    RPainterPath currentPainterPath;
    QMap<REntity::Id, QList<RPainterPath> > painterPaths;

    QMap<REntity::Id, QList<RImageData> > images;
    QMap<REntity::Id, QList<RTextBasedData> > texts;

    QList<RPainterPath> previewPainterPaths;
    QList<RTextBasedData> previewTexts;
};

Q_DECLARE_METATYPE(RGraphicsSceneQt*)

#endif
