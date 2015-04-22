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

include("Draw.js");

/**
 * \class DrawBasedOnRectangle
 * 
 * \brief Base class for drawing tools that draw something based on 
 * a rectangular shape with given width, height and angle. The tool
 * also supports reference points at the corners, top, left, right, 
 * bottom and middle.
 * 
 * \ingroup ecma_draw
 */
function DrawBasedOnRectangle(guiAction) {
    EAction.call(this, guiAction);

    this.dialogUiFile = undefined;
    this.useDialog = RSettings.getBoolValue("DrawBasedOnRectangle/UseDialog", false);
    this.dialog = undefined;
    this.pos = undefined;
    this.width = 1;
    this.height = 1;
    this.angle = 0;
    this.corners = [];
    
    // [ObjectName], [Shown Text], offset vector
    this.referencePoints = [
        [ "TopLeft",     qsTr("Top Left"),     new RVector(-1,  1) ],
        [ "Top",         qsTr("Top"),          new RVector( 0,  1) ],
        [ "TopRight",    qsTr("Top Right"),    new RVector( 1,  1) ],
        [ "Left",        qsTr("Left"),         new RVector(-1,  0) ],
        [ "Middle",      qsTr("Middle"),       new RVector( 0,  0) ],
        [ "Right",       qsTr("Right"),        new RVector( 1,  0) ],
        [ "BottomLeft",  qsTr("Bottom Left"),  new RVector(-1, -1) ],
        [ "Bottom",      qsTr("Bottom"),       new RVector( 0, -1) ],
        [ "BottomRight", qsTr("Bottom Right"), new RVector( 1, -1) ]
    ];
    this.referencePointIndex = undefined;
}

DrawBasedOnRectangle.prototype = new EAction();
DrawBasedOnRectangle.includeBasePath = includeBasePath;

DrawBasedOnRectangle.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(0);
    this.simulateMouseMoveEvent();

    if (this.useDialog) {
        if (!this.showDialog()) {
            this.terminate();
            return;
        }
    }
};

DrawBasedOnRectangle.prototype.finishEvent = function() {
    if (!isNull(this.dialog)) {
        this.dialog.destroy();
    }
    EAction.prototype.finishEvent.call(this);
};

DrawBasedOnRectangle.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var trPosition = qsTr("Position");
    this.setCommandPrompt(trPosition);
    this.setLeftMouseTip(trPosition);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

/**
 * Show dialog to enter some of the options.
 * This might move to EAction at one point.
 */
DrawBasedOnRectangle.prototype.showDialog = function() {
    var i;
    var children;

    if (isNull(this.dialog)) {
        // collect widgets which are tagged to be moved to the dialog:
        var c;
        var widgets = [];
        var optionsToolBar = EAction.getOptionsToolBar();
        children = optionsToolBar.children();
        for (i = 0; i < children.length; ++i) {
            c = children[i];
            if (c["MoveToDialog"]===true) {
                widgets.push(c);
            }
        }

        if (widgets.length===0) {
            // no widgets to show in dialog, return to normal operation without dialog:
            return true;
        }

        // show dialog and move tool bar widgets to its layout:
        var formLayout = undefined;
        if (isNull(this.dialogUiFile)) {
            // auto create dialog:
            this.dialog = WidgetFactory.createDialog(DrawBasedOnRectangle.includeBasePath, "DrawBasedOnRectangleDialog.ui");
            formLayout = this.dialog.findChild("FormLayout");
        }
        else {
            this.dialog = WidgetFactory.createDialog(this.includeBasePath, this.dialogUiFile);
            WidgetFactory.restoreState(this.dialog, this.settingsGroup, this);
        }
        this.dialog.windowTitle = this.getToolTitle();
        var guiAction = this.getGuiAction();
        if (!isNull(guiAction)) {
            this.dialog.windowIcon = guiAction.icon;
        }
        else {
            this.dialog.windowIcon = new QIcon();
        }

        for (i = 0; i < widgets.length; i++) {
            if (isNull(this.dialogUiFile) && !isNull(formLayout)) {
                if (isOfType(widgets[i], QCheckBox)) {
                    formLayout.addRow(new QWidget(formLayout), widgets[i]);
                    this.moveWidget(widgets[i], this.dialog);
                    continue;
                }

                // other widgets are moved to the dialog:
                if (i<widgets.length-1) {
                    formLayout.addRow(widgets[i], widgets[i+1]);
                    this.moveWidget(widgets[i], this.dialog);
                    this.moveWidget(widgets[i+1], this.dialog);
                    i++;
                }
            }
            else {
                widgets[i].destroy();
            }
        }

        // remove double separators:
        children = optionsToolBar.children();
        var previousWidgetWasSeparator = false;
        for (i = 0; i < children.length; ++i) {
            c = children[i];
            if (isFunction(c.isSeparator) && c.isSeparator()===true) {
                if (previousWidgetWasSeparator) {
                    var idx = this.optionWidgetActions.indexOf(c);
                    if (idx!==-1) {
                        // make sure the action is also removed from the list of added actions:
                        this.optionWidgetActions.splice(idx, 1);
                    }
                    c.destroy();
                }

                previousWidgetWasSeparator = true;
            }
            else if (isQWidget(c) && c.objectName.length!==0) {
                previousWidgetWasSeparator = false;
            }
        }
    }

    // give focus to control with custom property 'DefaultFocus':
    children = this.dialog.children();
    for (i=0; i<children.length; i++) {
        if (children[i].property("DefaultFocus")===true) {
            children[i].setFocus();
            if (isFunction(children[i].selectAll)) {
                // select all text in line edits:
                children[i].selectAll();
            }
            break;
        }
    }

    var ret = this.dialog.exec();

    WidgetFactory.saveState(this.dialog, "Shape");
    WidgetFactory.saveState(this.dialog, this.settingsGroup);

    //this.dialog.destroy();
    //this.dialog = undefined;

    //var appWin = EAction.getMainWindow();
    //appWin.setFocus();
    var view = EAction.getGraphicsView();
//    if (!isNull(view)) {
//        view.setFocus();
//    }

    //this.updatePreview();
    //this.simulateMouseMoveEvent();
    qDebug("view.hasFocus: ", view.hasFocus());
    qDebug("view.mouseTracking: ", view.mouseTracking);
    qDebug("focus widget: ", QApplication.focusWidget());
    qDebug("focus widget name: ", QApplication.focusWidget().objectName);

    var appWin = RMainWindowQt.getMainWindow();
    var event = new QFocusEvent(QEvent.FocusIn);
    QCoreApplication.sendEvent(appWin, event);

    return ret;
};

DrawBasedOnRectangle.prototype.validateNumber = function(n) {
    this.enableOk(!isNaN(n));
};

DrawBasedOnRectangle.prototype.validatePositiveNumber = function(n) {
    this.enableOk(!isNaN(n) && n>=0);
};

DrawBasedOnRectangle.prototype.validateNumberGreaterZero = function(n) {
    this.enableOk(!isNaN(n) && n>0);
};

DrawBasedOnRectangle.prototype.enableOk = function(onOff) {
    if (!isNull(this.dialog)) {
        var buttonBox = this.dialog.findChild("ButtonBox");
        buttonBox.button(QDialogButtonBox.Ok).enabled = onOff;
    }
};

DrawBasedOnRectangle.prototype.moveWidget = function(widget, dialog) {
    widget.setParent(dialog);
    //widget.sizePolicy = new QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed);
    widget.sizePolicy = new QSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Fixed);
    widget.minimumWidth = 50;
    //widget.minimumHeight = 10;
    widget.maximumWidth = 32000;
    widget.visible = true;
};

DrawBasedOnRectangle.prototype.initUiOptions = function(resume, restoreFromSettings) {
    EAction.prototype.initUiOptions.call(this, resume, restoreFromSettings);

    this.referencePointIndex = RSettings.getIntValue(this.settingsGroup + "/ReferencePoint", 4);
    
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");

    if (isNull(refPointCombo)) {
        return;
    }

    refPointCombo.blockSignals(true);
    refPointCombo.clear();
    if (isNull(this.shortcuts)) {
        this.shortcuts = [];
    }

    for (var i=0; i<this.referencePoints.length; i++) {
        var str = "%1".arg(i+1);
        refPointCombo.addItem(
            "[" + str + "] " + this.referencePoints[i][1],
            this.referencePoints[i][2]
        );
        if (isNull(this.shortcuts[i])) {
            this.shortcuts[i] = new QShortcut(new QKeySequence(str), refPointCombo, 0, 0, Qt.WindowShortcut);
            this.shortcuts[i].activated.connect(new KeyReactor(i), "activated");
        }
    }

    if (isNull(this.referencePointIndex) ||
        this.referencePointIndex<0 ||
        this.referencePointIndex>this.referencePoints.length-1) {

        this.referencePointIndex = 4;
    }

    refPointCombo.blockSignals(false);
    refPointCombo.currentIndex = this.referencePointIndex;
};

DrawBasedOnRectangle.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    this.pos = event.getModelPosition();

    if (preview) {
        this.updatePreview();
    }
    else {
        var op = this.getOperation(preview);
        if (!isNull(op)) {
            di.applyOperation(op);
            di.setRelativeZero(this.pos);
        }
    }
};

DrawBasedOnRectangle.prototype.keyPressEvent = function(event) {
    if (this.useDialog) {
        // enter pressed:
        if (event.key() === Qt.Key_Enter.valueOf() || event.key() === Qt.Key_Return.valueOf()) {
            // show dialog to change size and angle:
            this.showDialog();
        }
    }

    EAction.prototype.keyPressEvent(event);
};

//DrawBasedOnRectangle.prototype.keyReleaseEvent = function(event) {
//    EAction.prototype.keyReleaseEvent(event);
//    // update preview:
//    this.simulateMouseMoveEvent();
//};

DrawBasedOnRectangle.prototype.getOperation = function(preview) {
    var i;
    
    if (isNull(this.pos) || isNull(this.width) || isNull(this.height) || isNull(this.angle)) {
        return;
    }
    
    var x = this.pos.x;
    var y = this.pos.y;
    var w2 = this.width / 2;
    var h2 = this.height / 2;

    // create corners (centered)
    this.corners = [
        new RVector(x - w2, y - h2),
        new RVector(x + w2, y - h2),
        new RVector(x + w2, y + h2),
        new RVector(x - w2, y + h2)
    ];

    if (isNull(this.referencePointIndex) ||
        this.referencePointIndex<0 || this.referencePointIndex>this.referencePoints.length-1) {

        return undefined;
    }

    var referencePoint = this.referencePoints[this.referencePointIndex][2];
    // apply reference point vector
    for (i = 0; i < this.corners.length; ++i) {
        this.corners[i] = new RVector(
            this.corners[i].x - w2 * referencePoint.x,
            this.corners[i].y - h2 * referencePoint.y
        );
    }
    // apply angle:
    if (this.angle!==0.0) {
        for (i = 0; i < this.corners.length; ++i) {
            this.corners[i].rotate(this.angle, this.pos);
        }
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var shapes = this.getShapes(this.corners);
    for (i=0; i<shapes.length; ++i) {
        var e = shapeToEntity(this.getDocument(), shapes[i]);
        if (isNull(e)) {
            continue;
        }
        op.addObject(e);
    }

    return op;
};

DrawBasedOnRectangle.prototype.getShapes = function(corners) {
    return [];
};

DrawBasedOnRectangle.prototype.slotWidthChanged = function(value) {
    this.width = value;
    this.validateNumberGreaterZero(this.width);
    this.updatePreview(true);
};

DrawBasedOnRectangle.prototype.slotHeightChanged = function(value) {
    this.height = value;
    this.validateNumberGreaterZero(this.height);
    this.updatePreview(true);
};

DrawBasedOnRectangle.prototype.slotAngleChanged = function(value) {
    this.angle = value;
    this.validateNumber(this.angle);
    this.updatePreview(true);
};

DrawBasedOnRectangle.prototype.slotReferencePointChanged = function(value) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");

    this.referencePointIndex = refPointCombo.currentIndex;

    this.updatePreview(true);
};

DrawBasedOnRectangle.prototype.slotReset = function() {
    var optionsToolBar = EAction.getOptionsToolBar();

    if (isNull(optionsToolBar)) {
        return;
    }
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");
    if (!isNull(refPointCombo)) {
        refPointCombo.currentIndex = 4;
    }
    var angleEdit = optionsToolBar.findChild("Angle");
    if (!isNull(angleEdit)) {
        angleEdit.setValue(0.0);
    }
    this.updatePreview(true);
};



/**
 * Reacts to an assigned shortcut for the given index of the reference point combo box.
 */
function KeyReactor(i) {
    this.i = i;
}

KeyReactor.prototype.activated = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");
    refPointCombo.currentIndex = this.i;
};
