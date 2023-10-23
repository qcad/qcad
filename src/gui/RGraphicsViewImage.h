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

#ifndef RGRAPHICSVIEWIMAGE_H
#define RGRAPHICSVIEWIMAGE_H

#include "gui_global.h"

#include <QtCore>
#include <QPinchGesture>
#include <QTransform>
#include <QPainter>

#include "RGraphicsView.h"
#include "RPainterPath.h"

class RAction;
class RDocument;
class RDocumentInterface;
class RGraphicsSceneQt;
class RGraphicsSceneDrawable;
class RLine;
class RSnap;
class RSnapRestriction;
class RGraphicsViewImage;



class QCADGUI_EXPORT RGraphicsViewWorker : public QThread {
    Q_OBJECT

public:
    RGraphicsViewWorker(RGraphicsViewImage& imageView, int threadId) : imageView(imageView), threadId(threadId), list(nullptr), startIndex(-1), endIndex(-1) {}
    virtual ~RGraphicsViewWorker();

    enum ClearMode {
        NoClear = 0,
        ClearToTransparent = 1,
        ClearToBackground = 2
    };

    void run();

    virtual void init(QList<REntity::Id>& list, int start, int end);

    void setClearMode(ClearMode m) {
        clearMode = m;
    }

    ClearMode getClearMode() const {
        return clearMode;
    }

    QImage getImage() const {
        return image;
    }
    virtual void setImage(const QImage& img) {
        image = img;
    }

    bool hasTransforms() const {
        return !entityTransformStack.isEmpty();
    }

    QStack<RTransform> getEntityTransformStack() const {
        return entityTransformStack;
    }

    void pushTransform(const RTransform& t) {
        entityTransformStack.push(t);
    }

    void popTransform() {
        entityTransformStack.pop();
    }

    virtual void paint();

    virtual void begin() = 0;
    virtual void end() = 0;

    virtual void clear() = 0;

    virtual void setAntialiasing(bool on) = 0;
    virtual void setBackground(const QColor& col) = 0;
    virtual void setCompositionMode(QPainter::CompositionMode mode) = 0;
    virtual void setFont(const QFont& font) = 0;

    virtual void eraseRect(const QRectF& rect) = 0;

    virtual void setClipRect(const QRectF& rect) = 0;
    virtual void setClipping(bool on) = 0;
    virtual void setOpacity(double opacity) = 0;
    virtual void save() = 0;
    virtual void restore() = 0;

    virtual QTransform getTransform() = 0;
    virtual void setTransform(const QTransform& t, bool combine = false) = 0;

    virtual void translate(double x, double y) = 0;
    virtual void scale(double x, double y) = 0;

    virtual QTransform getWorldTransform() const = 0;
    virtual void setWorldTransform(const QTransform& t, bool combine = false) = 0;

    virtual void setBrush(const QBrush& brush) = 0;
    virtual QPen getPen() const = 0;
    virtual void setPen(const QPen& pen) = 0;

    virtual void drawPoint(const QPointF& p) = 0;

    virtual void paintImage(const RImageData& img, bool workingSet);
    virtual void drawImage(int x, int y, const QImage& image) = 0;

    virtual void paintText(const RTextBasedData& text, bool workingSet);
    virtual void drawText(const QRectF& rectangle, int flags, const QString& text) = 0;
    virtual void drawTextLayout(const QTextLayout& textLayout) = 0;

    virtual void fillPath(const RPainterPath& path, const QBrush& brush) = 0;
    virtual void drawPath(const RPainterPath& path) = 0;
    virtual void drawLine(const QPointF& p1, const QPointF& p2) {
        drawLine(QLineF(p1, p2));
    }
    virtual void drawLine(const QLineF& line) = 0;
    virtual void strokePath(const QPainterPath& path, const QPen& pen) = 0;

    virtual void drawEllipse(const QPointF& center, double rx, double ry) {
        drawEllipse(QRectF(center.x()-rx, center.y()-ry, rx*2, ry*2));
    }
    virtual void drawEllipse(const QRectF& rectangle) = 0;

    virtual void drawRect(const QRectF& rectangle) = 0;
    virtual void fillRect(const QRectF& rectangle, const QBrush& brush) = 0;


signals:
    void finished();

protected:
    int threadId;
    QList<REntity::Id>* list;
    int startIndex;
    int endIndex;
    ClearMode clearMode;

    QImage image;
    RGraphicsViewImage& imageView;
    QStack<RTransform> entityTransformStack;
};




class QCADGUI_EXPORT RGraphicsViewWorkerPainter : public RGraphicsViewWorker {
    Q_OBJECT

public:
    RGraphicsViewWorkerPainter(RGraphicsViewImage& imageView, int threadId) : RGraphicsViewWorker(imageView, threadId), painter(NULL) {}
    virtual ~RGraphicsViewWorkerPainter();

    virtual void begin();
    virtual void end();

    virtual void setImage(const QImage& img);

    virtual void paint();

    virtual void clear();

    virtual void setAntialiasing(bool on);
    virtual void setBackground(const QColor& col);
    virtual void setCompositionMode(QPainter::CompositionMode mode);
    virtual void setFont(const QFont& font);

    virtual void eraseRect(const QRectF& rect);

    virtual void setClipRect(const QRectF& rect);
    virtual void setClipping(bool on);
    virtual void setOpacity(double opacity);
    virtual void save();
    virtual void restore();

    virtual QTransform getTransform();
    virtual void setTransform(const QTransform& t, bool combine = false);

    virtual void translate(double x, double y);
    virtual void scale(double x, double y);

    virtual QTransform getWorldTransform() const;
    virtual void setWorldTransform(const QTransform& t, bool combine = false);


    virtual void setBrush(const QBrush& brush);
    virtual QPen getPen() const;
    virtual void setPen(const QPen& pen);

    virtual void drawPoint(const QPointF& p);

    //virtual void paintImage(const RImageData& img, bool workingSet);
    virtual void drawImage(int x, int y, const QImage& image);

    //virtual void paintText(const RTextBasedData& text, bool workingSet);
    virtual void drawText(const QRectF& rectangle, int flags, const QString& text);
    virtual void drawTextLayout(const QTextLayout& textLayout);

    virtual void fillPath(const RPainterPath& path, const QBrush& brush);
    virtual void drawPath(const RPainterPath& path);
    virtual void drawLine(const QLineF& line);
    virtual void strokePath(const QPainterPath& path, const QPen& pen);

    virtual void drawEllipse(const QRectF& rectangle);

    virtual void drawRect(const QRectF& rectangle);
    virtual void fillRect(const QRectF& rectangle, const QBrush& brush);

protected:
    QPainter* painter;
};



/**
 * \brief QImage based 2d graphics view.
 *
 * This graphics view renders a rectangular area of a RGraphicsSceneQt into a QImage.
 *
 * \ingroup gui
 * \scriptable
 * \generateScriptShell
 */
class QCADGUI_EXPORT RGraphicsViewImage : public QObject, public RGraphicsView {
    Q_OBJECT

public:
    RGraphicsViewImage(QObject* parent=NULL);
    virtual ~RGraphicsViewImage();

    int getNumThreads() const {
        return numThreads;
    }
    void setNumThreads(int n);

    void clear();

    // TODO: these methods are not found in RGraphicsViewQt, due to the
    // multiple inheritance of RGraphicsViewQt (QWidget and RGraphicsViewImage)
    // unless they are re-declared here again:
//    void setViewportNumber(int n) {
//        RGraphicsView::setViewportNumber(n);
//    }

//    int getViewportNumber() const {
//        return RGraphicsView::getViewportNumber();
//    }

//    void setNavigationAction(RAction* action) {
//        RGraphicsView::setNavigationAction(action);
//    }

//    RBox getBox() const {
//        return RGraphicsView::getBox();
//    }

//    void autoZoom(int margin = RDEFAULT_MIN1, bool ignoreEmpty=false, bool ignoreLineweight=false) {
//        RGraphicsView::autoZoom(margin, ignoreEmpty, ignoreLineweight);
//    }

//    void zoomTo(const RBox &window, int margin = 0) {
//        RGraphicsView::zoomTo(window, margin);
//    }

//    void zoom(const RVector& center, double factor) {
//        RGraphicsView::zoom(center, factor);
//    }

//    void pan(const RVector& delta, bool regen=true) {
//        RGraphicsView::pan(delta, regen);
//    }

//    void centerToBox(const RBox& box) {
//        RGraphicsView::centerToBox(box);
//    }

//    void centerToPoint(const RVector& point) {
//        RGraphicsView::centerToPoint(point);
//    }

//    void setGrid(RGrid* grid) {
//        RGraphicsView::setGrid(grid);
//    }

//    RGrid* getGrid() {
//        return RGraphicsView::getGrid();
//    }

//    double getFactor(bool includeStepFactor=true) const {
//        return RGraphicsView::getFactor(includeStepFactor);
//    }

//    void setFactor(double f, bool regen=true) {
//        RGraphicsView::setFactor(f, regen);
//    }

//    RVector getOffset(bool includeStepOffset=true) const {
//        return RGraphicsView::getOffset(includeStepOffset);
//    }

//    void setOffset(const RVector& offset, bool regen=true) {
//        RGraphicsView::setOffset(offset, regen);
//    }

//    QColor getBackgroundColor() {
//        return RGraphicsView::getBackgroundColor();
//    }

//    void setMargin(int m) {
//        RGraphicsView::setMargin(m);
//    }

//    void setColorMode(RGraphicsView::ColorMode cm) {
//        RGraphicsView::setColorMode(cm);
//    }

//    void setHairlineMode(bool on) {
//        RGraphicsView::setHairlineMode(on);
//    }

//    bool getHairlineMode() {
//        return RGraphicsView::getHairlineMode();
//    }

//    void setHairlineMinimumMode(bool on) {
//        RGraphicsView::setHairlineMinimumMode(on);
//    }

//    bool getHairlineMinimumMode() {
//        return RGraphicsView::getHairlineMinimumMode();
//    }

//    void setAntialiasing(bool on) {
//        RGraphicsView::setAntialiasing(on);
//    }

//    bool getAntialiasing() const {
//        return RGraphicsView::getAntialiasing();
//    }

//    RGraphicsScene* getScene() const {
//        return RGraphicsView::getScene();
//    }

//    RDocument* getDocument() const {
//        return RGraphicsView::getDocument();
//    }

//    RDocumentInterface* getDocumentInterface() const {
//        return RGraphicsView::getDocumentInterface();
//    }

//    void setExporting(bool on) {
//        RGraphicsView::setExporting(on);
//    }

//    bool isExporting() const {
//        return RGraphicsView::isExporting();
//    }

//    bool isPrintingOrExporting() const {
//        return RGraphicsView::isPrintingOrExporting();
//    }

//    void setPrinting(bool on) {
//        RGraphicsView::setPrinting(on);
//    }

//    bool isPrinting() const {
//        return RGraphicsView::isPrinting();
//    }

//    void setPrintPreview(bool on) {
//        RGraphicsView::setPrintPreview(on);
//    }

//    bool isPrintPreview() const {
//        return RGraphicsView::isPrintPreview();
//    }

//    void setPrintPointSize(const RVector& s) {
//        RGraphicsView::setPrintPointSize(s);
//    }

    virtual void simulateMouseMoveEvent();

//    void setTextHeightThresholdOverride(int v) {
//        RGraphicsView::setTextHeightThresholdOverride(v);
//    }

//    int getTextHeightThresholdOverride() const {
//        return RGraphicsView::getTextHeightThresholdOverride();
//    }

//    bool isGridVisible() const {
//        return RGraphicsView::isGridVisible();
//    }

//    void setGridVisible(bool on) {
//        RGraphicsView::setGridVisible(on);
//    }
    
    virtual void setScene(RGraphicsSceneQt* scene, bool regen=true);

    virtual void setBackgroundColor(const QColor& col);

    virtual void regenerate(bool force=false);
    virtual void repaintView();
    virtual void updateImage();

    virtual void giveFocus();
    virtual bool hasFocus();
    virtual void removeFocus();

    void saveViewport();
    void restoreViewport();

    virtual RVector mapFromView(const RVector& v, double z=0.0) const;
    virtual RVector mapToView(const RVector& v) const;
    virtual double mapDistanceFromView(double d) const;
    virtual double mapDistanceToView(double d) const;
    
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual void resizeImage(int w, int h);

    virtual void paintGridPoint(const RVector& ucsPosition);
    virtual void paintGridLine(const RLine& ucsPosition);
    virtual void paintCursorLine(const RLine& ucsPosition);

    void setPaintOrigin(bool val);

    void setPanOptimization(bool on);
    bool getPanOptimization();

    //virtual void paintEntities(QPainter* painter, const RBox& queryBox);
    void paintEntitiesMulti(const RBox& queryBox);
    //void paintEntitiesThread(int threadId, const QList<REntity::Id>& list, int start, int end);
    //void paintDrawablesThread(int threadId, const QList<RGraphicsSceneDrawable>& list, int start, int end);

    virtual void paintEntityThread(RGraphicsViewWorker* worker, REntity::Id id, bool preview = false);
    virtual void paintDrawableThread(RGraphicsViewWorker* worker, RGraphicsSceneDrawable& drawable, const RBox& clipRectangle, bool preview = false);

    virtual void paintOverlay(RGraphicsViewWorker* worker);

    QImage getBuffer() const;
    QTransform getTransform() const;

    void clearBackground();
    void addToBackground(const RGraphicsSceneDrawable& drawable);
    void setBackgroundTransform(double bgFactor, const RVector& bgOffset);

    void clearOverlay(int overlayId);
    void clearOverlay(int overlayId, RObject::Id objectId);
    void addToOverlay(int overlayId, RObject::Id objectId, const RGraphicsSceneDrawable& drawable);

    void setColorCorrectionOverride(bool on) {
        colorCorrectionOverride = (int)on;
    }

    bool getColorCorrectionOverride() const {
        return (colorCorrectionOverride!=0);
    }

    void setMinimumLineweight(double lw) {
        minimumLineweight = lw;
    }

    double getMinimumLineweight() const {
        return minimumLineweight;
    }

    void setMaximumLineweight(double lw) {
        maximumLineweight = lw;
    }

    double getMaximumLineweight() const {
        return maximumLineweight;
    }

    void setPaintOffset(const RVector& offset) {
        paintOffset = offset;
    }

    RVector getPaintOffset() const {
        return paintOffset;
    }

    bool isAlphaEnabled() const {
        return alphaEnabled;
    }

    void setAlphaEnabled(bool on) {
        alphaEnabled = on;
    }

    QImage getGraphicsBufferWithPreview() const {
        return graphicsBufferWithPreview;
    }

    RVector getLastKnownScreenPosition() const {
        return lastKnownScreenPosition;
    }

    void setLastKnownScreenPosition(const RVector& p) {
        lastKnownScreenPosition = p;
    }

    void setLastKnownModelPosition(const RVector& p) {
        lastKnownModelPosition = p;
    }

    virtual bool isShared() const {
        // never delete image view:
        // owned by creator
        return true;
    }

    virtual bool registerForFocus() const {
        return true;
    }

    virtual void viewportChangeEvent();

    virtual void emitUpdateSnapInfo(RSnap* snap, RSnapRestriction* restriction);
    virtual void emitUpdateTextLabel(const RTextLabel& textLabel);

    virtual double getDevicePixelRatio() const;

    virtual void paintImage(RGraphicsViewWorker* worker, const RImageData& image, bool workingSet = true);
    virtual void paintText(RGraphicsViewWorker* worker, const RTextBasedData& text, bool workingSet = true);

protected:
    QList<RPainterPath> getTextLayoutsPainterPaths(const RTextBasedData& text, const QList<RTextLayout>& textLayouts);
    void applyMinimumLineweight(QPen& pen);
    void applyColorCorrection(QPen& pen);
    void applyColorCorrection(QBrush& brush);
    void applyColorMode(QPen& pen);
    void applyColorMode(QBrush& brush);
    double getPointSize(double pSize);
    virtual void drawDot(RGraphicsViewWorker* worker, QPointF pt);
    virtual void drawPlus(RGraphicsViewWorker* worker, QPointF pt, double pSize);
    virtual void drawEx(RGraphicsViewWorker* worker, QPointF pt, double pSize);
    virtual void drawVBar(RGraphicsViewWorker* worker, QPointF pt, double pSize);
    virtual void drawCircle(RGraphicsViewWorker* worker, QPointF pt, double pSize);
    virtual void drawSquare(RGraphicsViewWorker* worker, QPointF pt, double pSize);

    virtual void paintOrigin(RGraphicsViewWorker* worker);
    virtual void paintReferencePoint(RGraphicsViewWorker* worker, const RRefPoint& pos, bool highlight);
    virtual void paintErase(RGraphicsViewWorker* worker, const QRect& rect = QRect());
    virtual void paintGrid(RGraphicsViewWorker* worker, const QRect& rect = QRect());
    virtual void paintMetaGrid(RGraphicsViewWorker* worker, const QRect& rect = QRect());
    virtual void paintCursor(RGraphicsViewWorker* worker);
    virtual void paintRelativeZero(RGraphicsViewWorker* worker);
    virtual void paintDocument(const QRect& rect = QRect());
    virtual void paintBackground(RGraphicsViewWorker* worker, const QRect& rect = QRect());

    virtual void endPaint() const;
    virtual void setBrush(const QBrush& brush) const;
    virtual void setPen(const QPen& pen) const;
    virtual void drawLine(const QLineF& line) const;

    /**
     * \nonscriptable
     */
    void initPainter(QPaintDevice& device, bool erase, bool screen = false, const QRect& rect = QRect());

    void invalidate(bool force=false);
    void initWorkers();
    void updateTransformation() const;

signals:
    void viewportChanged();
    void updateSnapInfo(RGraphicsViewWorker* worker, RSnap* snap, RSnapRestriction* restriction);
    void updateTextLabel(RGraphicsViewWorker* worker, const RTextLabel& textLabel);

protected:
    //QList<QImage> graphicsBufferThread;
    //QList<QPainter*> painterThread;

    // graphics buffer with current drawing rendered into it, without preview:
    QImage graphicsBuffer;
    // graphics buffer with current drawing rendered into it, with preview:
    QImage graphicsBufferWithPreview;

    int numThreads;

protected:
    bool panOptimization;
    QMutex mutexSi;

    RGraphicsSceneQt* sceneQt;
    double currentScale;
    QSize lastSize;
    RVector lastOffset;
    double lastFactor;
    bool graphicsBufferNeedsUpdate;
    mutable QTransform transform;
    QTransform previousView;

    QPainter* painter;
    bool doPaintOrigin;

    bool isSelected;
    QSet<RObject::Id> selectedIds;
    int bgColorLightness;

    int colorCorrectionOverride;
    bool colorCorrection;
    bool colorCorrectionDisableForPrinting;
    int colorThreshold;

    double minimumLineweight;
    double maximumLineweight;

//    int textHeightThresholdOverride;
//    int textHeightThreshold;

    double drawingScale;

    QList<RGraphicsSceneDrawable> backgroundDecoration;
    //QTransform backgroundTransform;
    double backgroundFactor;
    RVector backgroundOffset;

    QMap<int, QMap<RObject::Id, QList<RGraphicsSceneDrawable> > > overlayDrawables;

    RBox clipBox;
    //QList<QStack<RTransform> > entityTransformThread;
    RVector paintOffset;
    bool alphaEnabled;

    QString lastScaleString;

    bool showOnlyPlottable;

    QList<RGraphicsViewWorker*> workers;
    RGraphicsViewWorker* decorationWorker;
};

Q_DECLARE_METATYPE(RGraphicsViewImage*)

#endif
