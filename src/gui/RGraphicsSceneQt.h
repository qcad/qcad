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
#include "RGraphicsSceneDrawable.h"
#include "RImageData.h"
#include "RLine.h"
#include "RPainterPath.h"
#include "RPainterPathSource.h"
#include "RPoint.h"
#include "RPolyline.h"
#include "RRay.h"
#include "RSpline.h"
#include "RXLine.h"

class RGraphicsViewImage;

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

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

    virtual void clear();

    virtual void updateSelectionStatus(QSet<REntity::Id>& affectedEntities, bool updateViews);

    virtual void clearPreview();

    bool beginPath();
    void endPath();
    
    virtual void unexportEntity(REntity::Id entityId);

    virtual void exportPoint(const RPoint& point);
    virtual double exportLine(const RLine& line, double offset = RNANDOUBLE);
    virtual void exportArc(const RArc& arc, double offset = RNANDOUBLE);
    virtual void exportThickPolyline(const RPolyline& polyline);
    virtual void exportPolyline(const RPolyline& polyline, bool polylineGen = true, double offset = RNANDOUBLE);
    void exportPolylineFill(const RPolyline& polyline);
    virtual void exportSpline(const RSpline& spline, double offset = RNANDOUBLE);

    virtual void exportArcSegment(const RArc& arc, bool allowForZeroLength = false);
    virtual void exportLineSegment(const RLine& line, double angle = RNANDOUBLE);
    virtual void exportXLine(const RXLine& xLine);

    virtual void exportRay(const RRay& ray);
    virtual void exportTriangle(const RTriangle& triangle);
    virtual void exportRectangle(const RVector& p1, const RVector& p2);

    virtual void exportPainterPaths(const QList<RPainterPath>& paths, double z = 0.0);
    virtual void exportImage(const RImageData& image, bool forceSelected = false);
    virtual QList<RPainterPath> exportText(const RTextBasedData& text, bool forceSelected = false);
    virtual void exportClipRectangle(const RBox& clipRectangles, bool forceSelected = false);
    virtual void exportTransform(const RTransform& t);
    virtual void exportEndTransform();

    virtual double getLineTypePatternScale(const RLinetypePattern& p) const;
    
    virtual void highlightEntity(REntity& entity);

    void deleteDrawables();

    /**
     * \nonscriptable
     */
    QList<RGraphicsSceneDrawable>* getDrawables(REntity::Id entityId);

    bool hasPreview() const;
    QList<REntity::Id> getPreviewEntityIds();

    /**
     * \nonscriptable
     */
    QList<RGraphicsSceneDrawable>* getPreviewDrawables(REntity::Id entityId);

    virtual void addToPreview(REntity::Id entityId, QList<RGraphicsSceneDrawable>& drawables);
    virtual void addToPreview(REntity::Id entityId, RGraphicsSceneDrawable& drawable);
    void addTextToPreview(const RTextBasedData& text);

    bool hasClipRectangleFor(REntity::Id entityId, bool preview = false) const;
    RBox getClipRectangle(REntity::Id entityId, bool preview = false) const;

    void addDrawable(REntity::Id entityId, RGraphicsSceneDrawable& drawable, bool draft = false, bool preview = false);

    virtual void startEntity(bool topLevelEntity);

    virtual bool getScreenBasedLinetypes() const {
        if (screenBasedLinetypesOverride) {
            return true;
        }
        return RGraphicsScene::getScreenBasedLinetypes();
    }

    virtual void dump() {
        qDebug() << *this;
    }

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, RGraphicsSceneQt& gs);

private:
    RPainterPath currentPainterPath;

    QMap<REntity::Id, QList<RGraphicsSceneDrawable> > drawables;
    QMap<REntity::Id, RBox> clipRectangles;

    QMap<REntity::Id, QList<RGraphicsSceneDrawable> > previewDrawables;
    QMap<REntity::Id, RBox> previewClipRectangles;

    bool decorating;
    bool screenBasedLinetypesOverride;

    QStack<QTransform> transformStack;
};

Q_DECLARE_METATYPE(RGraphicsSceneQt*)

#endif
