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

#include <QList>
#include <QMultiMap>

#include "RGraphicsScene.h"
#include "RGraphicsSceneDrawable.h"
#include "RPainterPath.h"

class RArc;
class RDocumentInterface;
class RGraphicsViewImage;
class RImageData;
class RLine;
class RPoint;
class RPolyline;
class RSpline;
class RRay;
class RTriangle;
class RXLine;
class RTransform;

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

    virtual void updateSelectionStatus(QSet<RObject::Id>& affectedEntities, bool updateViews);

    virtual void clearPreview();

    virtual void exportEntities(bool allBlocks = true, bool undone = false, bool invisible = false);
    void exportEntitiesThread(int threadId, QList<RObject::Id>& list, int start, int end);
    void exportEntityThread(int threadId, RObject::Id id);

    bool beginPath();
    void endPath();

    void transformAndApplyPatternPath(RPainterPath& path) const;
    
    virtual void unexportEntity(RObject::Id entityId);

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
    virtual void clearClipRectangles();
    virtual void exportTransform(const RTransform& t);
    virtual void exportEndTransform();

    virtual double getLineTypePatternScale(const RLinetypePattern& p) const;
    
    virtual void highlightEntity(REntity& entity);

    void deleteDrawables();

    /**
     * \nonscriptable
     */
    QList<RGraphicsSceneDrawable>* getDrawables(RObject::Id entityId);

    /**
     * \nonscriptable
     */
    QList<RGraphicsSceneDrawable> getDrawablesList(RObject::Id entityId);

    bool hasPreview() const;
    QList<RObject::Id> getPreviewEntityIds();

    /**
     * \nonscriptable
     */
    QList<RGraphicsSceneDrawable>* getPreviewDrawables(RObject::Id entityId);

    virtual void addToPreview(RObject::Id entityId, QList<RGraphicsSceneDrawable>& drawables);
    virtual void addToPreview(RObject::Id entityId, RGraphicsSceneDrawable& drawable);

    virtual void addPathToPreview(RObject::Id entityId, RPainterPath& pp) {
        RGraphicsSceneDrawable drw(pp);
        addToPreview(entityId, drw);
    }

    void addTextToPreview(const RTextBasedData& text);

    bool hasClipRectangleFor(RObject::Id entityId, bool preview = false) const;
    RBox getClipRectangle(RObject::Id entityId, bool preview = false) const;

    void addDrawable(RObject::Id entityId, RGraphicsSceneDrawable& drawable, bool draft = false, bool preview = false);

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

    QMap<RObject::Id, QList<RGraphicsSceneDrawable> > drawables;
    QMap<RObject::Id, RBox> clipRectangles;

    QMap<RObject::Id, QList<RGraphicsSceneDrawable> > previewDrawables;
    QMap<RObject::Id, RBox> previewClipRectangles;

    bool decorating;
    bool screenBasedLinetypesOverride;

    QStack<QTransform> transformStack;


    QList<RGraphicsSceneQt*> threadScenes;
};

Q_DECLARE_METATYPE(RGraphicsSceneQt*)

#endif
