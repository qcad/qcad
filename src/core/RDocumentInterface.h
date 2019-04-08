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

#ifndef RDOCUMENTINTERFACE_H
#define RDOCUMENTINTERFACE_H

#include "core_global.h"

#include <QKeyEvent>
#include <QList>
#include <QMap>
#include <QMutex>
#include <QSharedPointer>
#include <QStack>
#include <QQueue>
#include <QSwipeGesture>
#include <QPanGesture>
#include <QPinchGesture>

#include "RAction.h"
#include "RCommandEvent.h"
#include "RCoordinateEvent.h"
#include "RCoordinateListener.h"
#include "RDocument.h"
#include "RExporter.h"
#include "RLayerListener.h"
#include "RStorage.h"
#include "RTerminateEvent.h"
#include "RTextLabel.h"
#include "RTransactionListener.h"
#include "RUcs.h"

#define RDEFAULT_QLIST_QREAL QList<qreal>()
#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

class RGraphicsScene;
class RGraphicsSceneDrawable;
class RGraphicsView;
class RMouseEvent;
class ROperation;
class RPropertyEvent;
class RSnap;
class RSnapRestriction;
class RScriptHandler;
class RTransaction;
class RWheelEvent;



/**
 * \brief Interface for interaction between a graphics document
 * and a user.
 *
 * Typically one document interface exists for every document that
 * is open in an MDI application. The document interface owns and
 * links the various scenes, views and the currently active action.
 *
 * A document interface can own multiple graphics scenes, each of
 * which can have multiple views attached to it. The views forward
 * all user events (mouse moves, mouse clicks, etc.) to the document
 * interface for processing. The document interface dispatches the
 * events to the currently active action object.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RDocumentInterface {
public:
    enum IoErrorCode {
        /**
         * No error occurred during import or export.
         */
        IoErrorNoError,
        /**
         * No suitable importer was found.
         */
        IoErrorNoImporterFound,
        /**
         * File size is zero bytes.
         */
        IoErrorZeroSize,
        /**
         * File not found.
         */
        IoErrorNotFound,
        /**
         * No permissions to read file.
         */
        IoErrorPermission,
        /**
         * General import error, i.e. non of the errors above.
         */
        IoErrorGeneralImportError,
        /**
         * General import error if an URL was given, i.e. non of the errors above.
         */
        IoErrorGeneralImportUrlError
    };

public:
    RDocumentInterface(RDocument& document);
    ~RDocumentInterface();

    void clearCaches();

    RDocument& getDocument();
    RStorage& getStorage();
    QList<RGraphicsScene*> getGraphicsScenes();
    RGraphicsView* getGraphicsViewWithFocus();
    RGraphicsScene* getGraphicsSceneWithFocus();

    void addCoordinateListener(RCoordinateListener* l);
    void notifyCoordinateListeners();

    void addLayerListener(RLayerListener* l);
    void removeLayerListener(RLayerListener* l);
    void notifyLayerListeners(QList<RLayer::Id>& layerIds);

    int addTransactionListener(RTransactionListener* l);
    void removeTransactionListener(int key);
    void removeTransactionListener(RTransactionListener* l);
    void notifyTransactionListeners(RTransaction* t);

    void clear(bool beforeLoad=false);

    RScriptHandler* getScriptHandler(const QString& extension);
    bool isScriptRunning();

    void setDefaultAction(RAction* action);
    RAction* getDefaultAction() const;
    void setCurrentAction(RAction* action);
    void terminateCurrentAction();
    void queueAction(RAction* action);
    void killAllActions();

    RAction* getCurrentAction();
    bool hasCurrentAction() const;
    RAction* getCurrentStatefulAction();
    bool hasCurrentStatefulAction() const;

    void suspend();
    void resume();

    void setClickMode(RAction::ClickMode m);
    RAction::ClickMode getClickMode();

    void terminateEvent(RTerminateEvent& event);

    void keyPressEvent(QKeyEvent& event);
    void keyReleaseEvent(QKeyEvent& event);
    void mouseMoveEvent(RMouseEvent& event);
    void mousePressEvent(RMouseEvent& event);
    void mouseReleaseEvent(RMouseEvent& event);
    void mouseDoubleClickEvent(RMouseEvent& event);
    void coordinateEvent(RCoordinateEvent& event);
    void coordinateEventPreview(RCoordinateEvent& event);
    void commandEvent(RCommandEvent& event);
    void commandEventPreview(RCommandEvent& event);
    void wheelEvent(RWheelEvent& event);
    void tabletEvent(RTabletEvent& event);
    void swipeGestureEvent(QSwipeGesture& gesture);
    void panGestureEvent(QPanGesture& gesture);
    void pinchGestureEvent(QPinchGesture& gesture);

    void propertyChangeEvent(RPropertyEvent& event);
    void ucsSetEvent(const QString& ucsName);
    void zoomChangeEvent(RGraphicsView& view);

    void enableUpdates();
    void disableUpdates();

    void enableRegeneration();
    void disableRegeneration();

    void enableMouseTracking();
    void disableMouseTracking();

    void updateAllEntities();

    void regenerateScenes(bool undone = false);
    void regenerateScenes(QSet<REntity::Id>& entityIds, bool updateViews);
    void regenerateScenes(REntity::Id entityId, bool updateViews);

    void updateSelectionStatus(QSet<REntity::Id>& entityIds, bool updateViews);
    void updateSelectionStatus(REntity::Id entityId, bool updateViews);

    void regenerateViews(bool force=false);
    void regenerateViews(QSet<REntity::Id>& entityIds);
    void repaintViews();

    void registerScene(RGraphicsScene& scene);
    void unregisterScene(RGraphicsScene& scene);

    void setCursor(const QCursor& cursor, bool global = true);

    RDocumentInterface::IoErrorCode importUrl(
        const QUrl& url, const QString& nameFilter = "", bool notify = true);
    RDocumentInterface::IoErrorCode importFile(
        const QString& fileName, const QString& nameFilter = "", bool notify = true);

    QString getCorrectedFileName(const QString& fileName, const QString& fileVersion);
    bool exportFile(const QString& fileName, const QString& fileVersion = "", bool resetModified = true);

    void tagState(const QString& tag = "");
    void undoToTag(const QString& tag = "");
    void undo();
    void redo();
    void flushTransactions();
    void flushRedo();

    void setSnap(RSnap* snap);
    RSnap* getSnap();

    void setSnapRestriction(RSnapRestriction* snapRestriction);
    RSnapRestriction* getSnapRestriction();

    RVector snap(RMouseEvent& event, bool preview = false);
    RVector restrictOrtho(const RVector& position, const RVector& relativeZero, RS::OrthoMode mode = RS::Orthogonal);

    REntity::Id getClosestEntity(RInputEvent& event);
    REntity::Id getClosestEntity(const RVector& position,
        double range, double strictRange = RMAXDOUBLE,
        bool includeLockedLayers = true,
        bool selectedOnly = false);
    void highlightEntity(REntity::Id entityId);
    void highlightReferencePoint(const RRefPoint& position);
    int selectEntities(const QSet<REntity::Id>& entityIds, bool add = false);
    void selectEntity(REntity::Id entityId, bool add = false);
    int deselectEntities(const QSet<REntity::Id>& entityIds);
    void deselectEntity(REntity::Id entityId);
    void selectBoxXY(const RBox& box, bool add = false);
    void selectAll();
    void deselectAll();
    void clearSelection();
    bool hasSelection();

    void addZoomBoxToPreview(const RBox& box);
    void addShapeToPreview(RShape& shape, const RColor& color,
            const QBrush& brush, RLineweight::Lineweight lineweight,
            Qt::PenStyle style, const QList<qreal>& dashValues = RDEFAULT_QLIST_QREAL);
    void addAuxShapeToPreview(RShape& shape);
    void addEntityToPreview(REntity& entity);
    void addDrawableToPreview(RGraphicsSceneDrawable& drawable);
    void beginPreview();
    void endPreview();
    void clearPreview();
    bool isPreviewEmpty();
    void keepPreview();

    void showPropertiesOf(REntity& entity);
    void clearProperties();

    void zoomIn();
    void zoomOut();
    void autoZoom(int margin = RDEFAULT_MIN1);
    bool zoomToSelection();
    void zoomTo(const RBox& region, int margin = 0);
    void zoomPrevious();

    void previewOperation(ROperation* operation);
    RTransaction applyOperation(ROperation* operation);

    void objectChangeEvent(RTransaction& transaction);

    RVector getRelativeZero() const;
    RVector getLastPosition() const;
    void setRelativeZero(const RVector& p);

    void lockRelativeZero();
    void unlockRelativeZero();
    bool isRelativeZeroLocked() const;

    void lockSnap();
    void unlockSnap();
    void toggleSnapLock();
    bool isSnapLocked() const;

    RVector getCursorPosition() const;
    void setCursorPosition(const RVector& p);
    void setCursorOverride(bool on);
    bool getCursorOverride() const;

    void deleteTerminatedActions();

    void setCurrentColor(const RColor& color);
    RColor getCurrentColor();

    void setCurrentLineweight(RLineweight::Lineweight lw);
    RLineweight::Lineweight getCurrentLineweight();

    void setCurrentLinetype(RLinetype::Id ltId);
    void setCurrentLinetypePattern(const RLinetypePattern& p);
    RLinetype::Id getCurrentLinetypeId();
    RLinetypePattern getCurrentLinetypePattern();

    void setCurrentLayer(RLayer::Id layerId);
    void setCurrentLayer(const RLayer& layer);
    void setCurrentLayer(const QString& layerName);

    void setCurrentBlock(RBlock::Id blockId);
    void setCurrentBlock(const RBlock& block);
    void setCurrentBlock(const QString& blockName);

    void setCurrentViewport(const RViewportEntity& viewport);
    void unsetCurrentViewport();

    void setCurrentView(const QString& viewName);

    void setCurrentUcs(const RUcs& ucs);
    void setCurrentUcs(const QString& ucsName);
    RUcs getCurrentUcs();
    QString getCurrentUcsName();

    RGraphicsView* getLastKnownViewWithFocus();
    void setLastKnownViewWithFocus(RGraphicsView* view);

    static RDocumentInterface& getClipboard();
    static void deleteClipboard();
    bool isClipboard() {
        return this==clipboard;
    }
    bool isSuspended() {
        return suspended;
    }
    void setNotifyListeners(bool on) {
        notifyGlobalListeners = on;
    }
    bool getNotifyListeners() const {
        return notifyGlobalListeners;
    }

    bool isDeleting() const {
        return deleting;
    }

    QVariant eval(const QString& ext, const QString& script);

//    QTransform getInputTransform() const {
//        return inputTransform;
//    }

//    void setInputTransform(const QTransform& t) {
//        inputTransform = t;
//    }

private:
    void handleClickEvent(RAction& action, RMouseEvent& event);
    void previewClickEvent(RAction& action, RMouseEvent& event);

private:
    RDocument& document;
    QList<RGraphicsScene*> scenes;
    RGraphicsView* lastKnownViewWithFocus;
    QMap<QString, RScriptHandler*> scriptHandlers;

    RAction* defaultAction;
    QStack<RAction*> currentActions;
    QQueue<RAction*> queuedActions;

    QList<RCoordinateListener*> coordinateListeners;
    QList<RLayerListener*> layerListeners;
    QMap<int, RTransactionListener*> transactionListeners;

    RSnap* currentSnap;
    RSnapRestriction* currentSnapRestriction;

    RVector lastPosition;
    RVector relativeZero;
    bool relativeZeroLocked;
    bool snapLocked;
    RVector cursorPosition;
    RUcs currentUcs;
    QString currentUcsName;
    bool suspended;

    bool allowUpdate;
    bool allowRegeneration;

    bool notifyGlobalListeners;
    bool deleting;
    bool cursorOverride;

    bool keepPreviewOnce;
    bool mouseTrackingEnabled;

    QMap<QString, int> tags;

    // transform for all input coordinates:
//    QTransform inputTransform;

    static RDocumentInterface* clipboard;
};

Q_DECLARE_METATYPE(RDocumentInterface::IoErrorCode)
Q_DECLARE_METATYPE(RDocumentInterface*)

#endif
