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

#ifndef RACTION_H
#define RACTION_H

#include "core_global.h"

#include <QKeyEvent>
#include <QList>
#include <QMap>
#include <QObject>
#include <QString>
#include <QSwipeGesture>
#include <QPanGesture>
#include <QPinchGesture>

#include "RDebug.h"
#include "REntity.h"
#include "RVector.h"

class RPropertyEvent;
class RGraphicsScene;
class RGraphicsView;
class RDocumentInterface;
class RCommandEvent;
class RCoordinateEvent;
class RDocument;
class REntityPickEvent;
class RMouseEvent;
class RWheelEvent;
class RGuiAction;
class RStorage;
class RTabletEvent;
class ROperation;

/**
 * \brief Abstract base class for all action classes.
 *
 * Action classes handle user interaction with a document. A menu,
 * toolbar button or command usually triggers an action.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RAction {
public:
    /**
     * Current mouse click mode.
     */
    enum ClickMode {
        /**
         * Mouse click will pick a coordinate and trigger \ref coordinateEvent.
         * This is the default mode.
         */
        PickCoordinate,
        PickCoordinateNoSnap,
        /**
         * Mouse click will pick an entity and trigger \ref entityPickEvent.
         */
        PickEntity,
        /**
         * Mouse click will not trigger any events except for \ref mousePressEvent
         * and \ref mouseReleaseEvent.
         */
        PickingDisabled
    };

public:
    RAction(RGuiAction* guiAction = NULL);
    virtual ~RAction();

    void terminate();
    bool isTerminated();

    void setOverride();
    bool isOverride();

    void setNoState(bool on = true);
    bool hasNoState();

    void setUniqueGroup(const QString& ug);
    QString getUniqueGroup();

    void setOverrideBase(RAction* base);
    RAction* getOverrideBase();

    virtual RGuiAction* getGuiAction();

    void setGuiAction(RGuiAction* guiAction);

    QList<RGraphicsScene*> getGraphicsScenes();
    RDocument* getDocument();
    RDocumentInterface* getDocumentInterface();
    RStorage* getStorage();

    void setDocumentInterface(RDocumentInterface* di) {
        documentInterface = di;
    }

    void setClickMode(RAction::ClickMode m);

    /**
     * \return The current click mode of this action as previously
     *      requested by the action.
     */
    RAction::ClickMode getClickMode() {
        return clickMode;
    }

    /**
     * Called as soon as the action is created (menu chosen, toolbutton activated, etc).
     */
    virtual void beginEvent() = 0;
    /**
     * Called if this action is set as a navigation action of a graphics view.
     */
    virtual void setGraphicsView(RGraphicsView* view) = 0;
    /**
     * Called just before the action is deleted.
     */
    virtual void finishEvent() = 0;
    /**
     * Called when user presses enter (e.g. to show action dialog with options).
     */
    virtual void enterEvent() = 0;
    /**
     * Called when the action is suspended, for example when another action
     * becomes active or the mouse cursor leaves the view.
     */
    virtual void suspendEvent() = 0;
    /**
     * Resumes the action (for example when another action became active and
     * then terminated or if the mouse cursor enters the view).
     */
    virtual void resumeEvent() = 0;
    /**
     * Escape events are triggered if the user clicks the right mouse button or
     * hits the Escape key. The action is expected to go one step back, to the
     * last state or terminate itself.
     */
    virtual void escapeEvent() = 0;

    virtual void keyPressEvent(QKeyEvent& event) = 0;

    virtual void keyReleaseEvent(QKeyEvent& event) = 0;

    /**
     * Called on mouse press events.
     */
    virtual void mousePressEvent(RMouseEvent& event) = 0;

    /**
     * Called on mouse move events.
     */
    virtual void mouseMoveEvent(RMouseEvent& event) = 0;

    /**
     * Called on mouse release events.
     */
    virtual void mouseReleaseEvent(RMouseEvent& event) = 0;

    /**
     * Called on mouse double click events.
     */
    virtual void mouseDoubleClickEvent(RMouseEvent& event) = 0;

    /**
     * Called on mouse wheel events.
     */
    virtual void wheelEvent(RWheelEvent& event) = 0;

    /**
     * Called on tablet events.
     */
    virtual void tabletEvent(RTabletEvent& event) = 0;

    /**
     * Called on swipe gesture events.
     */
    virtual void swipeGestureEvent(QSwipeGesture& gesture) = 0;

    /**
     * Called on pan gesture events.
     */
    virtual void panGestureEvent(QPanGesture& gesture) = 0;

    /**
     * Called on pinch gesture events.
     */
    virtual void pinchGestureEvent(QPinchGesture& gesture) = 0;

    /**
     * Called when a command is entered in the command line.
     */
    virtual void commandEvent(RCommandEvent& event) = 0;

    /**
     * Called when a command is being edited in the command line.
     */
    virtual void commandEventPreview(RCommandEvent& event) = 0;

    /**
     * Called for every coordinate event.
     * Coordinate events can be the result of a mouse click or an entered
     * coordinate from the command line.
     * These events are fired after mouse click events in mode "PickCoordinate".
     */
    virtual void coordinateEvent(RCoordinateEvent& event) = 0;

    /**
     * Called if the action is in \c PickCoordinate mode and the mouse is moved
     * around. Typically, some sort of preview is shown to the user to indicate
     * what would happen if that coordinate would be picked.
     */
    virtual void coordinateEventPreview(RCoordinateEvent& event) = 0;

    virtual void entityPickEvent(REntityPickEvent& event) = 0;

    virtual void entityPickEventPreview(REntityPickEvent& event) = 0;

    /**
     * Called when the value of a property is modified while this action is active.
     */
    virtual void propertyChangeEvent(RPropertyEvent& event) = 0;

    /**
     * Called when the zoom factor or offset changed in the given view.
     */
    virtual void zoomChangeEvent(RGraphicsView& view) = 0;

    //virtual void setMultiSnapPoints(const QList<RVector>& points) = 0;
    //virtual void setMultiSnapAngles(const QList<double>& angles) = 0;

    virtual void updatePreview() = 0;
    virtual void applyOperation() = 0;

    RVector snap(RMouseEvent& event);

protected:
    bool terminated;
    bool override;

    /**
     * Indicates whether this action is stateless
     * (i.e. terminates in beginEvent).
     */
    bool noState;

    QString uniqueGroup;
    RAction::ClickMode clickMode;
    RGuiAction* guiAction;
    RAction* overrideBase;
    RDocumentInterface* documentInterface;
};

Q_DECLARE_METATYPE(RAction*)
Q_DECLARE_METATYPE(RAction::ClickMode)

#endif
