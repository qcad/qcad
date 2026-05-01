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

include("../../EAction.js");

function DefaultNavigation(widget) {
    RActionAdapter.call(this);
    this.lastCursor = undefined;
    this.view = undefined;
    this.panning = false;
    this.savedCursor = undefined;
    this.panOrigin = new RVector();
    this.panFirstOrigin = new RVector();
    if (!isNull(widget)) {
        this.hruler = widget.findChild("HorizontalRuler");
        this.vruler = widget.findChild("VerticalRuler");
    }

    // make sure wheel behavior / pan gesture is initialized:
    DefaultNavigation.applyPreferences();
}

DefaultNavigation.prototype = new RActionAdapter();

DefaultNavigation.WheelBehavior = {
    Zoom : 0,
    Pan : 1
};

DefaultNavigation.getPreferencesCategory = function() {
    return [qsTr("Graphics View"), qsTr("Navigation")];
};

DefaultNavigation.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var wheelCombo = pageWidget.findChild("Wheel");
    wheelCombo.addItem(qsTr("Zoom (Wheel Mouse)"), DefaultNavigation.WheelBehavior.Zoom);
    wheelCombo.addItem(qsTr("Scroll (Trackpad, Multi-Touch Mouse)"), DefaultNavigation.WheelBehavior.Pan);
};

DefaultNavigation.applyPreferences = function(doc) {
    DefaultNavigation.wheelBehavior = RSettings.getIntValue("GraphicsViewNavigation/Wheel", DefaultNavigation.WheelBehavior.Zoom);
    DefaultNavigation.reverseMouseWheelZoom = RSettings.getBoolValue("GraphicsViewNavigation/ReverseMouseWheelZoom", false);
    DefaultNavigation.mouseWheelZoomFactor = RSettings.getDoubleValue("GraphicsViewNavigation/MouseWheelZoomFactor", 1.2);
    if (RMath.fuzzyCompare(DefaultNavigation.mouseWheelZoomFactor, 0.0, 0.001)) {
        DefaultNavigation.mouseWheelZoomFactor = 1.2;
    }
    DefaultNavigation.mouseWheelScrollFactor = RSettings.getDoubleValue("GraphicsViewNavigation/MouseWheelScrollFactor", 1.0);
    if (RMath.fuzzyCompare(DefaultNavigation.mouseWheelScrollFactor, 0.0, 0.001)) {
        DefaultNavigation.mouseWheelScrollFactor = 1.0;
    }
    DefaultNavigation.panGesture = RSettings.getBoolValue("GraphicsViewNavigation/PanGesture", false);
    DefaultNavigation.middleMouseButtonZoomFactor = RSettings.getDoubleValue("GraphicsViewNavigation/MiddleMouseButtonZoomFactor", 1.2);
    DefaultNavigation.panThreshold = RSettings.getDoubleValue("GraphicsViewNavigation/PanThreshold", 4);
    DefaultNavigation.panSpeed = RSettings.getDoubleValue("GraphicsViewNavigation/PanSpeed", 0.5);
    DefaultNavigation.scrollHorVer = RSettings.getBoolValue("GraphicsViewNavigation/ScrollHorVer", false);
};

DefaultNavigation.prototype.beginEvent = function() {
};

DefaultNavigation.prototype.setGraphicsView = function(v) {
    this.view = v;
};

DefaultNavigation.prototype.finishEvent = function() {
};

/**
 * Implement panning with arrow keys.
 * Only has an effect if no actions are triggered using arrows as shortcuts.
 */
//DefaultNavigation.prototype.keyPressEvent = function(event) {
//    var v = undefined;

//    if (event.isAccepted()) {
//        return;
//    }

//    if (event.key()===Qt.Key_Left.valueOf()) {
//        v = new RVector(50, 0);
//    } else if (event.key()===Qt.Key_Right.valueOf()) {
//        v = new RVector(-50, 0);
//    } else if (event.key()===Qt.Key_Up.valueOf()) {
//        v = new RVector(0, 50);
//    } else if (event.key()===Qt.Key_Down.valueOf()) {
//        v = new RVector(0, -50);
//    }

//    if (!isNull(v)) {
//        this.view.pan(v);
//        event.accept();
//    }
//};

DefaultNavigation.prototype.mousePressEvent = function(event) {
    if (isNull(this.view)) {
        return;
    }

    // middle button or left button and control (command on mac) to pan:
    if (event.button() === Qt.MidButton ||
        (event.button() === Qt.LeftButton &&
         event.modifiers().valueOf() === Qt.ControlModifier.valueOf())) {

        this.panOrigin = event.getScreenPosition();
        this.panFirstOrigin = this.panOrigin;
        this.panning = true;
        this.savedCursor = this.view.getCursor();
        this.view.startPan();
        EAction.disableCoordinateWidget();
    }
};

DefaultNavigation.prototype.mouseReleaseEvent = function(event) {
    if (isNull(this.view)) {
        return;
    }

    if (this.panning === true &&
        (event.button() === Qt.MidButton ||
         event.button() === Qt.LeftButton)) {

        if (event.button() === Qt.MidButton) {
            // only middle mouse button to zoom:
            this.handleMiddleMouseButtonZoom(event);
        }

        if (!isNull(this.savedCursor)) {
            this.view.setCursor(this.savedCursor);
        }
        this.panning = false;
        this.savedCursor = undefined;
        EAction.enableCoordinateWidget();
    }
};

DefaultNavigation.prototype.handleMiddleMouseButtonZoom = function(event) {
    if (this.panFirstOrigin.getDistanceTo(event.getScreenPosition())<DefaultNavigation.panThreshold) {
        // zoom in / out:
        var position = event.getModelPosition();
        if (event.modifiers().valueOf() === Qt.ShiftModifier.valueOf()) {
            this.view.zoomOut(position, DefaultNavigation.middleMouseButtonZoomFactor);
        }
        else {
            this.view.zoomIn(position, DefaultNavigation.middleMouseButtonZoomFactor);
        }
    }
};

DefaultNavigation.prototype.mouseMoveEvent = function(event) {
    if (isNull(this.view)) {
        return;
    }

    if (event.buttons().valueOf() & Qt.MidButton.valueOf() ||
        (event.buttons().valueOf() & Qt.LeftButton.valueOf() &&
         event.modifiers().valueOf() === Qt.ControlModifier.valueOf())) {

        if (this.panning === true) {
            var panTarget = event.getScreenPosition();
            var panDelta = panTarget.operator_subtract(this.panOrigin);
            if (Math.abs(panDelta.x) > DefaultNavigation.panThreshold || Math.abs(panDelta.y) > DefaultNavigation.panThreshold) {
                this.view.setCursor(
                    new QCursor(Qt.ClosedHandCursor)
                );
                this.view.pan(panDelta);
                this.panOrigin = panTarget;
            }
        }
    }

    if (!isNull(this.hruler)) {
        this.hruler.update();
    }
    if (!isNull(this.vruler)) {
        this.vruler.update();
    }
};

DefaultNavigation.prototype.wheelEvent = function(event) {
    if (isNull(this.view)) {
        return;
    }

    // if (event.source()===Qt.MouseEventNotSynthesized) {
    //     qDebug("Qt.MouseEventNotSynthesized");
    // }
    // else if (event.source()===Qt.MouseEventSynthesizedByQt) {
    //     qDebug("Qt.MouseEventSynthesizedByQt");
    // }
    // else if (event.source()===Qt.MouseEventSynthesizedByApplication) {
    //     qDebug("Qt.MouseEventSynthesizedByApplication");
    // }
    // else if (event.source()===Qt.MouseEventSynthesizedBySystem) {
    //     qDebug("Qt.MouseEventSynthesizedBySystem");
    // }

    // qDebug("pixelDelta NULL: " + event.pixelDelta.isNull());
    // qDebug("pixelDelta: X: " + event.pixelDelta.x());
    // qDebug("pixelDelta: Y: " + event.pixelDelta.y());
    // qDebug("angleDelta: X: " + event.angleDelta.x());
    // qDebug("angleDelta: Y: " + event.angleDelta.y());

    // high res device (e.g. tablet)
    // use pixel delta in X and Y for panning
    var highRes = event.phase !== Qt.NoScrollPhase;

    var wheelDelta = undefined;
    var wheelDeltaX = undefined;
    var wheelDeltaY = undefined;

    if (isFunction(event.delta)) {
        // Qt 5:
        wheelDelta = event.delta();
    }
    else {
        // Qt 6 (scroll in both directions simultaniously):
        if (highRes) {
            // high res device (e.g. tablet or magic mouse), use pixel delta:
            wheelDeltaX = event.pixelDelta.x();
            wheelDeltaY = event.pixelDelta.y();

            // apply pan speed factor to wheel delta:
            wheelDeltaX *= DefaultNavigation.panSpeed;
            wheelDeltaY *= DefaultNavigation.panSpeed;
        }

        else {
            // low res device (mouse with mouse wheel), use angle data:
            // qDebug("angleDelta: X: " + event.angleDelta.x());
            // qDebug("angleDelta: Y: " + event.angleDelta.y());

            wheelDeltaX = event.angleDelta.x() * DefaultNavigation.mouseWheelScrollFactor;
            wheelDeltaY = event.angleDelta.y() * DefaultNavigation.mouseWheelScrollFactor;
        }

        // wheelDelta is whichever delta has a value:
        wheelDelta = wheelDeltaY;
        if (wheelDelta==0) {
            // tablet with holding down command: delta in X:
            wheelDelta = wheelDeltaX;
        }

    }

    wheelDelta *= DefaultNavigation.panSpeed;

    var performZoom = false;
    var horizontalScroll = 0.0;
    var verticalScroll = 0.0;

    // Ctrl: scroll vertically or horizontally, depending on mode:
    if (isControlPressed(event)) {
        if (DefaultNavigation.wheelBehavior===DefaultNavigation.WheelBehavior.Zoom) {
            // wheel is used for zooming
            // or with Ctrl for panning vertically:
            verticalScroll = wheelDelta;
        }
        else {
            // wheel is used for scrolling, with Ctrl for horizontal scrolling:
            // this fixes scrolling with two fingers on Wacom tablets where
            // Shift + two fingers does not tirgger a wheelEvent:
            horizontalScroll = wheelDelta;
        }
    }

    // Shift: scroll horizontally (does not work for Wacom tablet, no event with Shift):
    else if (isShiftPressed(event)) {
        // qDebug("shift");
        // qDebug("wheelDelta: " + wheelDelta);
        // qDebug("wheelDeltaX: " + wheelDeltaX);
        // qDebug("wheelDeltaY: " + wheelDeltaY);
        horizontalScroll = wheelDelta;
    }

    // zooming with wheel in pan mode:
    else if (isAltPressed(event)) {
        if (DefaultNavigation.wheelBehavior===DefaultNavigation.WheelBehavior.Zoom) {
            horizontalScroll = wheelDelta;
        }
        else {
            performZoom = true;
            //zoomFactor = wheelDelta;
        }
    }

    // zoom in / out:
    else {
        // wheel behavior is "zoom":
        if (DefaultNavigation.wheelBehavior===DefaultNavigation.WheelBehavior.Zoom) {
            performZoom = true;
        }

        // wheel behavior is "pan", also for swipe gesture:
        else {
            if (isNull(this.panOffset)) {
                this.panOffset = new RVector(0,0);
            }

            // Qt 6:
            if (RSettings.getQtVersion()>=0x060000) {
                if (DefaultNavigation.scrollHorVer) {
                    // limit scrolling to horizontal / vertical:
                    if (Math.abs(wheelDeltaX)>Math.abs(wheelDeltaY)) {
                        wheelDeltaY = 0;
                    }
                    else {
                        wheelDeltaX = 0;
                    }
                }

                this.panOffset = this.panOffset.operator_add(new RVector(wheelDeltaX, wheelDeltaY));
            }

            // Qt 5:
            else {
                if (event.orientation()===Qt.Vertical) {
                    this.panOffset = this.panOffset.operator_add(new RVector(0, wheelDelta));
                }
                else {
                    this.panOffset = this.panOffset.operator_add(new RVector(wheelDelta, 0));
                }
            }

            this.view.pan(this.panOffset);
            this.panOffset = new RVector();
            this.view.simulateMouseMoveEvent();
        }
    }


    if (verticalScroll!=0 && horizontalScroll!=0) {
        this.view.pan(new RVector(horizontalScroll, verticalScroll));
        this.view.simulateMouseMoveEvent();
    }
    else if (verticalScroll!=0) {
        this.view.pan(new RVector(0, verticalScroll));
        this.view.simulateMouseMoveEvent();
    }
    else if (horizontalScroll!=0) {
        this.view.pan(new RVector(horizontalScroll, 0));
        this.view.simulateMouseMoveEvent();
    }
    else if (performZoom) {
        var zoomFactor = DefaultNavigation.mouseWheelZoomFactor;
        if (highRes) {
            zoomFactor = 1.0 + (zoomFactor-1.0) / 4.0;
        }

        var position = event.getModelPosition();
        if (wheelDelta!==0) {
            if ((wheelDelta > 0) !== DefaultNavigation.reverseMouseWheelZoom) {
                this.view.zoom(position, zoomFactor);
            }
            else {
                this.view.zoom(position, 1.0/zoomFactor);
            }
            this.view.simulateMouseMoveEvent();
        }
    }
};

DefaultNavigation.prototype.tabletEvent = function(event) {
    /*
    qDebug("-----------------------------");
    qDebug("DefaultNavigation.tabletEvent()");
    qDebug("type: " + event.type());
    qDebug("device: " + event.device());
    qDebug("globalX: " + event.globalX());
    qDebug("globalY: " + event.globalY());
    qDebug("x: " + event.x());
    qDebug("y: " + event.y());
    qDebug("z: " + event.z());
    qDebug("hiResGlobalX: " + event.hiResGlobalX());
    qDebug("hiResGlobalY: " + event.hiResGlobalY());
    qDebug("pointerType: " + event.pointerType());
    qDebug("pointerType: " + event.pointerType());
    qDebug("pressure: " + event.pressure());
    qDebug("rotation: " + event.rotation());
    qDebug("tangentialPressure: " + event.tangentialPressure());
    qDebug("uniqueId: " + event.uniqueId());
    qDebug("xTilt: " + event.xTilt());
    qDebug("yTilt: " + event.yTilt());
    */
    event.ignore();
};

/**
 * Called for pan gestures, e.g. from a track pad.
 * Pans the current view.
 */
DefaultNavigation.prototype.panGestureEvent = function(gesture) {
    if (DefaultNavigation.panGesture===false) {
        return;
    }

    if (isNull(this.view)) {
        return;
    }

    switch (gesture.state) {
        case Qt.GestureStarted:
            this.lastCursor = this.view.getCursor();
            this.view.setCursor(new QCursor(Qt.OpenHandCursor));
            break;

        case Qt.GestureUpdated:
            this.view.setCursor(new QCursor(Qt.ClosedHandCursor));
            break;

        default:
            if (!isNull(this.lastCursor)) {
                this.view.setCursor(this.lastCursor);
            }
            break;
    }

    var delta = gesture.delta;
    this.view.pan(new RVector(delta.x(), delta.y()));
    this.view.simulateMouseMoveEvent();
};

/**
 * Called for pinch gestures, e.g. from a track pad.
 * Zooms in / out.
 */
DefaultNavigation.prototype.pinchGestureEvent = function(gesture) {
    if (isNull(this.view)) {
        return;
    }

    var changeFlags = gesture.changeFlags;
    var center = this.view.getLastKnownMousePosition();

    if (!center.isValid()) {
        return;
    }

    if (typeof(QPinchGesture)!=="undefined" && (changeFlags & QPinchGesture.RotationAngleChanged)) {
        // rotation does nothing
    }
    if (typeof(QPinchGesture)!=="undefined" && (changeFlags & QPinchGesture.ScaleFactorChanged)) {
        var value;
        if (RSettings.getQtVersion() >= 0x050000) {
            // Qt 5:
            value = gesture.totalScaleFactor;
        }
        else {
            // Qt 4:
            value = gesture.property("scaleFactor");
        }

        if (value<=0.0) {
            return;
        }
        this.view.setCurrentStepScaleFactor(value);
        var offset = this.view.getOffset(false);
        var newOffset = offset.operator_subtract(
                center.operator_multiply(
                    this.view.getCurrentStepScaleFactor()
                ).operator_subtract(center)
        );

        newOffset = newOffset.operator_divide(this.view.getCurrentStepScaleFactor());

        // avoid erratic behavior:
        if (offset.getDistanceTo(newOffset) < 10*this.view.mapDistanceFromView(this.view.getWidth())) {
            this.view.setCurrentStepOffset(newOffset.operator_subtract(this.view.getOffset(false)));
        }
    }

    if (gesture.state == Qt.GestureFinished) {
        this.view.setFactor(this.view.getFactor(true));
        this.view.setOffset(this.view.getOffset(true));

        this.view.setCurrentStepScaleFactor(1.0);
        this.view.setCurrentStepOffset(new RVector(0,0));
    }

    this.view.simulateMouseMoveEvent();
    this.view.regenerate(true);
};
