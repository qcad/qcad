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

#ifndef REXPORTER_H
#define REXPORTER_H

#include <stdint.h>

#include "core_global.h"

#include <QBrush>
#include <QColor>
#include <QPen>
#include <QStack>
#include <QTextLayout>
#include <QTransform>

#include "REntity.h"
#include "RImageData.h"
#include "RMatrix.h"
#include "RPainterPath.h"
#include "RTextBasedData.h"
#include "RView.h"
#include "RViewportEntity.h"

class RArc;
class RCircle;
class RDocument;
class REllipse;
class RLine;
class RLinetype;
class RLinetypePattern;
class RMessageHandler;
class RPainterPathSource;
class RPoint;
class RPolyline;
class RProgressHandler;
class RRay;
class RSpline;
class RTriangle;
class RVector;
class RXLine;

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Abstract base class for exporters.
 *
 * Exporters export documents into files, views, etc.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RExporter {

public:
    RExporter();
    RExporter(RDocument& document, RMessageHandler* messageHandler = NULL, RProgressHandler* progressHandler = NULL);
    virtual ~RExporter();

private:
    void init();

public:

    QString getErrorMessage() const;

    void setLayerSource(RDocument* ls);
    void setBlockSource(RDocument* bs);

    /**
     * \nonscriptoverwritable
     */
    RDocument& getDocument() const;

    void setProjectionRenderingHint(RS::ProjectionRenderingHint p);
    RS::ProjectionRenderingHint getProjectionRenderingHint();

    //virtual RBox getClipRectangle() const;
    void setClipping(bool on);
    bool getClipping() const;

    virtual void setPen(const QPen& pen);
    virtual QPen getPen(const RPainterPath& path);
    virtual QPen getPen();
    virtual void setBrush(const QBrush& brush);
    virtual QBrush getBrush(const RPainterPath& path);
    virtual QBrush getBrush();

    virtual RColor getColor(const RColor& unresolvedColor);
    virtual RColor getColor(bool resolve);

    virtual void setEntityAttributes(bool forceSelected=false);

    virtual void setStyle(Qt::PenStyle penStyle);
    virtual void setBrushStyle(Qt::BrushStyle brushStyle);
    virtual void setDashPattern(const QVector<qreal>& dashes);

    virtual void setColor(float r, float g, float b, float a = 1.0f);
    virtual void setColor(const RColor& color);

    virtual void setLineweight(RLineweight::Lineweight weight);

    virtual void setLinetypeId(RLinetype::Id ltId);
    virtual void setLinetypePattern(const RLinetypePattern& ltPattern);
    virtual RLinetypePattern getLinetypePattern();

    virtual REntity* getBlockRefOrEntity();
    virtual REntity::Id getBlockRefOrEntityId();
    virtual REntity* getEntity();
    virtual REntity* getCurrentBlockRef() const;
    virtual RViewportEntity* getCurrentViewport() const;
    virtual QStack<REntity*> getBlockRefViewportStack() const;

    /**
     * \nonscriptable
     */
    virtual const REntity* getEntity() const;

    virtual bool isEntitySelected();
    virtual bool isPatternContinuous(const RLinetypePattern& p);

    virtual void startExport();
    virtual void endExport();

    virtual bool exportDocument();
    virtual bool exportDocumentSettings();
    virtual void exportDocumentSetting(const QString& key, const QVariant& value, const QString& dictionaryName = "QCAD_OBJECTS");

    virtual void exportIntListWithName(const QString& dictionaryName, const QString& name, const QString& listName, QList<int64_t>& values);

    virtual void exportLayers();
    virtual void exportLayerStates();
    virtual void exportBlocks();
    virtual void exportViews();
    virtual void exportLinetypes();

    virtual void exportLayer(RLayer& /*layer*/) {}
    virtual void exportLayer(RLayer::Id layerId);
    virtual void exportLayerState(RLayerState& /*layerState*/) {}
    virtual void exportBlock(RBlock& /*block*/) {}
    virtual void exportBlock(RBlock::Id blockId);
    virtual void exportView(RView& /*view*/) {}
    virtual void exportView(RView::Id viewId);
    virtual void exportLinetype(RLinetype& /*linetype*/) {}

    virtual void exportEntities(bool allBlocks = true, bool undone = false);
    virtual void exportEntities(const RBox& box);
    virtual void exportEntities(QSet<REntity::Id>& entityIds, bool allBlocks = true);
    virtual void exportEntity(REntity& entity, bool preview = false, bool allBlocks = true, bool forceSelected = false);
    virtual void exportEntity(REntity::Id entityId, bool allBlocks = true, bool forceSelected = false);
    virtual QSharedPointer<RLayer> getEntityLayer(REntity& entity);
    virtual bool isVisible(REntity& entity);
    virtual void startEntity(bool /*topLevelEntity*/) {}
    virtual void endEntity() {}
    virtual void exportCurrentEntity(bool preview = false, bool forceSelected = false);
    virtual void unexportEntity(REntity::Id entityId);

    virtual void exportShapes(const QList<QSharedPointer<RShape> >& shapes);
    virtual void exportShape(QSharedPointer<RShape> shape);
    virtual void exportShapeSegment(QSharedPointer<RShape> shape, double angle);

    /**
     * Exports a line with the current attributes.
     */
    virtual double exportLine(const RLine& line, double offset = RNANDOUBLE);

    /**
     * \nonscriptable
     */
    virtual bool exportLinetypeShape(QList<RPainterPath>& pps, const RLine& line, double total, double length, double angle, const RVector& cursor);

    /**
     * Exports a line segment (a line without pattern). This is called
     * from the standard implementation of exportLine for every dash in a
     * dashed line.
     */
    virtual void exportLineSegment(const RLine& line, double angle = RNANDOUBLE) = 0;

    /**
     * Exports an infinite line. Used for xlines (construction lines).
     */
    virtual void exportXLine(const RXLine& xLine) = 0;

    /**
     * Exports an infinite ray. Used for rays.
     */
    virtual void exportRay(const RRay& ray) = 0;

    /**
     * Exports a point with the current attributes.
     */
    virtual void exportPoint(const RPoint& point) = 0;

    virtual void exportCircle(const RCircle& circle);

    virtual void exportArc(const RArc& arc, double offset = RNANDOUBLE);

    virtual void exportArcSegment(const RArc& arc, bool allowForZeroLength = false);

    virtual void exportEllipse(const REllipse& ellipse, double offset = RNANDOUBLE);

    virtual void exportPolyline(const RPolyline& polyline, bool polylineGen = true, double offset = RNANDOUBLE);

    virtual void exportSpline(const RSpline& spline, double offset = RNANDOUBLE);

    virtual void exportSplineSegment(const RSpline& spline);

    /**
     * \nonscriptable
     */
    virtual void exportExplodable(const RExplodable& explodable, double offset = RNANDOUBLE);

    /**
     * \nonscriptable
     */
    virtual void exportPainterPathSource(const RPainterPathSource& pathSource, double z = 0.0);

    virtual void exportPainterPaths(const QList<RPainterPath>& paths, double z = 0.0);
    virtual void exportPainterPaths(const QList<RPainterPath>& paths, double angle, const RVector& pos);

    virtual void exportBoundingBoxPaths(const QList<RPainterPath>& paths);

    virtual void exportImage(const RImageData& image, bool forceSelected = false);
    virtual QList<RPainterPath> exportText(const RTextBasedData& text, bool forceSelected = false);
    virtual void exportClipRectangle(const RBox& clipRectangle, bool forceSelected = false);
    virtual void exportTransform(const RTransform& t);
    virtual void exportEndTransform();

    virtual void exportThickPolyline(const RPolyline& polyline) {
        RPolyline pl = polyline;
        pl.stripWidths();
        exportPolyline(pl);
    }

//    virtual void exportThickLine(const RLine& line, double w1, double w2) {
//        Q_UNUSED(w1)
//        Q_UNUSED(w2)
//        exportLineSegment(line);
//    }

//    virtual void exportThickArc(const RArc& arc, double w1, double w2) {
//        Q_UNUSED(w1)
//        Q_UNUSED(w2)
//        exportArcSegment(arc);
//    }

    virtual void exportQuad(
        const RVector& p1,
        const RVector& p2,
        const RVector& p3,
        const RVector& p4
    );

    virtual void exportVerticalQuad(
        const RVector& p1,
        const RVector& p2,
        double height
    );

    virtual void exportBox(const RBox& box);

    /**
     * Exports a triangle with the current attributes.
     */
    virtual void exportTriangle(const RTriangle& triangle) = 0;

    virtual void exportRectangle(const RVector& p1, const RVector& p2);

    virtual double getLineTypePatternScale(const RLinetypePattern& p) const;

    /**
     * Override to force text rendering mode.
     */
    virtual bool isTextRenderedAsText() {
        return RSettings::isTextRenderedAsText();
    }

    QStack<REntity*> getEntityStack();

    void pushEntity(REntity* e);
    void popEntity();

    void setDraftMode(bool on);

    void toggleDraftMode() {
        setDraftMode(!draftMode);
    }

    bool getDraftMode() const {
        return draftMode;
    }

    void setTwoColorSelectedMode(bool on) {
        twoColorSelectedMode = on;
    }

    bool getTwoColorSelectedMode() const {
        return twoColorSelectedMode;
    }

    void setScreenBasedLinetypes(bool on);

    void toggleScreenBasedLinetypes() {
        setScreenBasedLinetypes(!screenBasedLinetypes);
    }

    virtual bool getScreenBasedLinetypes() const {
        return screenBasedLinetypes;
    }

    /**
     * \return True if this exporter exports only visible entities
     * (on visible layers).
     */
    bool isVisualExporter() const {
        return visualExporter;
    }

    void setVisualExporter(bool on) {
        visualExporter = on;
    }

    double getPixelSizeHint() const {
        return pixelSizeHint;
    }

    virtual double getCurrentPixelSizeHint() const;

    void setPixelSizeHint(double v) {
        pixelSizeHint = v;
    }

    bool getPixelUnit() const {
        return pixelUnit;
    }

    void setPixelUnit(bool on) {
        pixelUnit = on;
    }

    bool getPixelWidth() const {
        return pixelWidth;
    }

    void setPixelWidth(bool on) {
        pixelWidth = on;
    }

//    bool getCombineTransforms() const {
//        return combineTransforms;
//    }

//    void setCombineTransforms(bool on) {
//        combineTransforms = on;
//    }

protected:
    RDocument* document;
    QTransform transform;
    QPen currentPen;
    RLinetypePattern currentLinetypePattern;
    QBrush currentBrush;
    QStack<REntity*> entityStack;
    RLayer* currentLayer;
    QStack<REntity*> blockRefViewportStack;
    RDocument* layerSource;
    RDocument* blockSource;
    bool draftMode;
    bool twoColorSelectedMode;
    bool screenBasedLinetypes;
    bool visualExporter;
    QString errorMessage;
    double pixelSizeHint;
    bool pixelUnit;
    bool clipping;
    bool pixelWidth;
    Qt::PenCapStyle penCapStyle;
    //bool combineTransforms;

private:
    RS::ProjectionRenderingHint projectionRenderingHint;
};

Q_DECLARE_METATYPE(RExporter*)

#endif
