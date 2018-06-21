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

#ifndef RGRAPHICSVIEW_H
#define RGRAPHICSVIEW_H

#include "core_global.h"

#include <QKeyEvent>
#include <QCursor>
#include <QSwipeGesture>
#include <QPanGesture>
#include <QPinchGesture>

#include "RExporter.h"
#include "RGrid.h"
#include "RNonCopyable.h"
#include "RTextLabel.h"
#include "RTerminateEvent.h"

class RAction;
class RDocumentInterface;
class RGraphicsScene;
class RLine;
class RMouseEvent;
class RTabletEvent;
class RWheelEvent;

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif


/**
 * \brief Graphics view.
 *
 * A graphics view displays a (part of a) graphics scene.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RGraphicsView : RNonCopyable {
public:
    enum ColorMode {
        FullColor,
        GrayScale,
        BlackWhite
    };

public:
    RGraphicsView(RGraphicsScene* scene = NULL);
    virtual ~RGraphicsView();

    void setViewportNumber(int n);
    int getViewportNumber() const {
        return viewportNumber;
    }

    void clear() {}
    void clearCaches();

    void setDisplayOnlyCurrentUcs(bool on);

    virtual void setScene(RGraphicsScene* scene, bool regen=true);
    RGraphicsScene* getScene() const;
    RDocument* getDocument() const;
    RDocumentInterface* getDocumentInterface() const;

    /**
     * Maps the given view coordinate in pixels to a model coordinate.
     *
     * \param v view coordinate in pixels, v.z is always 0
     * \param z known z coordinate in model units
     */
    virtual RVector mapFromView(const RVector& v, double z=0.0) const = 0;

    /**
     * Maps the given model coordinate to a view coordinate in pixels.
     */
    virtual RVector mapToView(const RVector& v) const = 0;
    virtual RBox mapToView(const RBox& box) const;

    /**
     * Maps the given view distance in pixels to a model distance.
     * If the view projection is not orthogonal the result is undefined.
     */
    virtual double mapDistanceFromView(double d) const = 0;

    /**
     * Maps the given model distance to a screen distance in pixels.
     * If the view projection is not orthogonal the result is undefined.
     */
    virtual double mapDistanceToView(double d) const = 0;

    virtual QList<RVector> mapCornersFromView() const;

    virtual RBox getBox() const;
    virtual RVector getMinimum() const;
    virtual RVector getMaximum() const;

    virtual void handleTerminateEvent(RTerminateEvent& event);

    virtual void handleKeyPressEvent(QKeyEvent& event);
    virtual void handleKeyReleaseEvent(QKeyEvent& event);
    virtual void simulateMouseMoveEvent();
    virtual void handleMouseMoveEvent(RMouseEvent& event);
    virtual void handleMousePressEvent(RMouseEvent& event);
    virtual void handleMouseReleaseEvent(RMouseEvent& event);
    virtual void handleMouseDoubleClickEvent(RMouseEvent& event);
    virtual void handleWheelEvent(RWheelEvent& event);
    virtual void handleTabletEvent(RTabletEvent& event);
    virtual void handleSwipeGestureEvent(QSwipeGesture& gesture);
    virtual void handlePanGestureEvent(QPanGesture& gesture);
    virtual void handlePinchGestureEvent(QPinchGesture& gesture);
    virtual void giveFocus() = 0;
    /**
     * \return True if this view currently has the focus.
     */
    virtual bool hasFocus() = 0;
    virtual void removeFocus() = 0;

    virtual void viewportChangeEvent();

    void saveViewport();
    void restoreViewport();
    void zoomIn();
    void zoomOut();
    void zoomIn(const RVector& center, double factor=1.2);
    void zoomOut(const RVector& center, double factor=1.2);
    virtual void zoom(const RVector& center, double factor);
    virtual void zoomTo(const RBox& window, int margin = 0);
    void zoomPrevious();
    void autoZoom(int margin = RDEFAULT_MIN1, bool ignoreEmpty=false, bool ignoreLineweight=false);
    bool zoomToSelection(int margin = RDEFAULT_MIN1);
    bool zoomToEntities(const QSet<REntity::Id>& ids, int margin = RDEFAULT_MIN1);

    virtual void centerToPoint(const RVector& point);
    virtual void centerToBox(const RBox& box);
    virtual void pan(const RVector& delta, bool regen=true);
    void startPan();

    double getFactor(bool includeStepFactor=true) const;
    void setFactor(double f, bool regen=true);

    RVector getOffset(bool includeStepOffset=true) const;
    void setOffset(const RVector& offset, bool regen=true);

    /**
     * Regenerates the view to show the visible parts of the underlying scene.
     * This function is called after the entities have been modified or
     * the view port changed after a zoom or pan or after the window
     * has been resized.
     *
     * \param force True if scene has changed, don't use any optimizations, force regeneration.
     */
    virtual void regenerate(bool force=false) = 0;
    virtual void regenerate(QSet<REntity::Id>& affectedEntities) {
        Q_UNUSED(affectedEntities)

        regenerate(true);
    }

    /**
     * Repaints the view (widget, etc..). This differs from regenerate in that
     * it does not require the view to iterate through the scene elements. Instead
     * for example a buffered bitmap might be drawn.
     * This is for example called when the preview changes to restore the view
     * before painting the preview on top of it.
     */
    virtual void repaintView() = 0;

    /**
     * \return Width of the view in pixels.
     */
    virtual int getWidth() const = 0;

    /**
     * \return Height of the view in pixels.
     */
    virtual int getHeight() const = 0;

    /**
     * \return True if this view is considered to be active and needs updates
     * (for example if a view is visible).
     */
    virtual int isActive() const {
        return true;
    }

    virtual bool getSignalsBlocked() const {
        return false;
    }
    virtual void setSignalsBlocked(bool on) {
        Q_UNUSED(on)
        return;
    }

    void setNavigationAction(RAction* action);

    /**
     * \return Current grid or NULL if no grid is set.
     */
    RGrid* getGrid() {
        return grid;
    }

    /**
     * Sets the current grid. This graphics view takes ownership
     * of the grid. The previous grid is deleted. Setting the grid
     * to NULL disables the grid.
     */
    void setGrid(RGrid* g) {
        if (grid!=NULL) {
            delete grid;
            grid = NULL;
        }
        grid = g;
    }

    void setGridVisible(bool on);
    bool isGridVisible() const;

    virtual void paintGridPoint(const RVector& /*ucsPosition*/) {}
    virtual void paintGridLine(const RLine& /*ucsPosition*/) {}

    virtual QCursor getCursor() { return QCursor(Qt::ArrowCursor); }
    virtual void setCursor(Qt::CursorShape /*cursorShape*/) {}
    virtual void setCursor(const QCursor& /*cursor*/) {}

    RRefPoint getClosestReferencePoint(const RVector& screenPosition, int range);
    RRefPoint getClosestReferencePoint(REntity::Id entityId, const RVector& screenPosition);
    REntity::Id getClosestEntity(const RVector& screenPosition, int range, int strictRange, bool includeLockedLayers=true, bool selectedOnly = false);
    //REntity::Id getClosestEntityInUcs(const RVector& screenPosition, int range);

    virtual void setBackgroundColor(const QColor& col);
    QColor getBackgroundColor();

    int getMargin();
    void setMargin(int m);

    void setExporting(bool on);
    bool isExporting() const;

    bool isPrintingOrExporting() const;

    void setPrinting(bool on);
    bool isPrinting() const;
    void setPrintPreview(bool on);
    bool isPrintPreview() const;
    void setPrintPointSize(const RVector& s);

    void setColorMode(RGraphicsView::ColorMode cm);
    RGraphicsView::ColorMode getColorMode();

    void setHairlineMode(bool on);
    bool getHairlineMode();

    void setHairlineMinimumMode(bool on);
    bool getHairlineMinimumMode();

    QList<RTextLabel> getTextLabels();
    void clearTextLabels();
    void addTextLabel(const RTextLabel &textLabel);

    RVector getLastKnownMousePosition() const {
        return lastKnownModelPosition;
    }

    double getCurrentStepScaleFactor() const {
        return currentStepScaleFactor;
    }

    void setCurrentStepScaleFactor(double f) {
        currentStepScaleFactor = f;
    }

    RVector getCurrentStepOffset() const {
        return currentStepOffset;
    }

    void setCurrentStepOffset(const RVector& s) {
        currentStepOffset = s;
    }

    void setTextHeightThresholdOverride(int v) {
        textHeightThresholdOverride = v;
    }

    int getTextHeightThresholdOverride() const {
        return textHeightThresholdOverride;
    }

    void updateTextHeightThreshold();

    bool isPathVisible(const RPainterPath& path) const;

    void setAntialiasing(bool val);
    bool getAntialiasing() const;

    virtual double getDevicePixelRatio() const {
        return 1.0;
    }

    /**
     * Reimplementations may return true to prevent this view from being deleted.
     */
    virtual bool isShared() const {
        return false;
    }

    /**
     * Reimplementations may return true to register this view and allow it
     * to be returned by RDocumentInterface::getLastKnownViewWithFocus.
     */
    virtual bool registerForFocus() const {
        return false;
    }

protected:
    bool exporting;
    bool printing;
    bool printPreview;
    RVector printPointSize;

    ColorMode colorMode;
    bool hairlineMode;
    bool hairlineMinimumMode;

    /**
     * The scene this view is attached to.
     */
    RGraphicsScene* scene;

    /**
     * Grid that is currently displayed by this view or NULL.
     */
    RGrid* grid;

    /**
     * The navigation action of this view or NULL if no navigation action
     * has been set.
     */
    RAction* navigationAction;

    /**
     * Offset of the zero point from the lower left corner of the view in
     * model coordinates.
     */
    RVector offset;

    /**
     * Scale factor from model coordinates to view coordinates.
     */
    double factor;

    RVector previousOffset;
    double previousFactor;

    /**
     * True to only display entities within the horizontal slice that is defined
     * by the current UCS.
     */
    bool displayOnlyCurrentUcs;

    bool autoScalePatterns;

    QColor backgroundColor;
    int margin;

    /**
     * Current scale factor caused by a pinch gesture.
     */
    double currentStepScaleFactor;

    RVector currentStepOffset;
    RVector lastKnownModelPosition;
    RVector lastKnownScreenPosition;

    /**
     * Internal list of text labels that were added to this view.
     */
    QList<RTextLabel> textLabels;


    int textHeightThresholdOverride;
    int textHeightThreshold;

    int viewportNumber;

    bool antialiasing;

    // grid display flag, cached:
    mutable int gridVisible;

    //RVector mousePressScreenPosition;
    //RVector mousePressModelPosition;
};

Q_DECLARE_METATYPE(RGraphicsView::ColorMode)
Q_DECLARE_METATYPE(RGraphicsView*)
Q_DECLARE_METATYPE(QList<RGraphicsView*>)

#endif
