/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("../Screencast.js");


/**
 * Focus listener. Re-installes event filters if focus has changed
 * (e.g. new document).
 */
/*
function ScInputInfoFocusListener(ef) {
    RFocusListenerAdapter.call(this);
    this.eventFilter = ef;
}

ScInputInfoFocusListener.prototype = new RFocusListenerAdapter();

ScInputInfoFocusListener.prototype.updateFocus = function(di) {
    var appWin = RMainWindowQt.getMainWindow();
    var mdiArea = appWin.findChild("MdiArea");
    this.eventFilter.install(mdiArea);
};
*/



/**
 * Event filter installed for all widgets, tracks mouse, keys, etc.
 */
function ScInputInfoEventFilter() {
    QObject.call(this);
    this.stopped = false;
    this.quit = false;
    this.buttons = undefined;
    this.button = undefined;
    this.key = undefined;
}

ScInputInfoEventFilter.prototype = new QObject();

ScInputInfoEventFilter.prototype.install = function(w) {
    if (this.quit) {
        return;
    }
    this.stopped = false;

    var kids = w.children();
    for (var i=0; i<kids.length; i++) {
        var k = kids[i];
        if (isNull(k.gotEventFilter)) {
            k.installEventFilter(this);
            //k.mouseTracking = true;
            k.setProperty("gotEventFilter", true);
        }
        this.install(k);
    }
};

ScInputInfoEventFilter.prototype.uninstall = function(w) {
    //qDebug("UNINSTALLING EVENT FILTERS");
    var kids = w.children();
    for (var i=0; i<kids.length; i++) {
        var k = kids[i];
        if (isNull(k.gotEventFilter)) {
            k.removeEventFilter(this);
            k.setProperty("gotEventFilter", undefined);
        }
        this.uninstall(k);
    }
};

ScInputInfoEventFilter.prototype.eventFilter = function(watched, e) {
    if (this.stopped || this.quit) {
        return false;
    }

    var appWin = RMainWindowQt.getMainWindow();
    e = e.cast();
    var type = e.type().toString();
    var objectName = watched.objectName;

    if (type==="DeferredDelete") {
        return true;
    }

    //qDebug("type: ", type);
    //qDebug("objectName: ", objectName);

    if (type.contains("Close") && objectName.contains("Untitled")) {
        //qDebug("type: ", type);
        //qDebug("objectName: ", objectName);
        this.uninstall(appWin);
        this.stopped = true;
        return false;
    }

    if (!type.contains("Mouse") &&
        !type.contains("Key") &&
        !type.contains("Focus") &&
        !type.contains("Enter") &&
        !type.contains("Leave")) {

        return false;

        //qDebug("object: ", watched.objectName);
        //qDebug("type: ", type);
    }

    var installFilter = false;
    var updatePos = false;

    switch (type) {
        case "MouseButtonRelease":
        case "MouseButtonPress":
        case "MouseMove":
            this.button = e.button().valueOf();
            this.buttons = e.buttons().valueOf();
            break;
    }

//    if (this.button===Qt.LeftButton.valueOf() || this.buttons===Qt.LeftButton.valueOf()) {
//        this.mouseLabel.pixmap = this.leftButtonPixmap;
//    }
//    else if (this.button===Qt.MidButton.valueOf() || this.buttons===Qt.MidButton.valueOf()) {
//        this.mouseLabel.pixmap = this.middleButtonPixmap;
//    }
//    else if (this.button===Qt.RightButton.valueOf() || this.buttons===Qt.RightButton.valueOf()) {
//        this.mouseLabel.pixmap = this.rightButtonPixmap;
//    }

    switch (type) {
        case "ContextMenu":
            installFilter = true;
            break;

        case "MouseButtonRelease":
            //updatePos = true;
            //this.hideMouseLabel();
            break;

        case "MouseButtonPress":
            //this.showMouseLabel();
            if (this.buttons!==Qt.RightButton.valueOf()) {
                installFilter = true;
            }
            //updatePos = true;
            break;

        case "MouseMove":
            //updatePos = true;
            break;

        case "KeyPress":
            this.key = e.key().valueOf();
            this.modifiers = e.modifiers().valueOf();
            break;

        case "KeyRelease":
            this.key = undefined;
            this.modifiers = undefined;
            break;
    }

    if (installFilter) {
        if (objectName!=="GraphicsView" &&
            objectName!=="MdiArea" &&
            objectName!=="Form" &&
            !objectName.startsWith("Viewport") &&
            objectName!=="Single") {

            var self = this;
            for (var i=0; i<2; i++) {
                var singleShot = new QTimer();
                singleShot.singleShot = true;
                singleShot.timeout.connect(function() {
                    //self.mouseLabel.raise();
                    self.install(appWin);
                });
                singleShot.start(20 + i*200);
            }
        }
    }

//    if (updatePos) {
//        var pos = QCursor.pos();
//        this.mouseLabel.move(pos.x()+10, pos.y()+10);
//    }

    return false;
};




/**
 * This action creates a Qt main window.
 */
function ScMirrored(guiAction) {
    EAction.call(this, guiAction);
}

ScMirrored.prototype = new EAction();
ScMirrored.includeBasePath = includeBasePath;

ScMirrored.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.w = 1280;
    this.h = 670;
    this.x = 0;
    this.y = 20;

    var appWin = RMainWindowQt.getMainWindow();
    appWin.resize(this.w,this.h);
    appWin.move(this.x,this.y);
    //appWin.setAttribute(Qt.WA_MacAlwaysShowToolWindow);
    //appWin.setAttribute(Qt.WA_MacNoCocoaChildWindow);

    //var flags = new Qt.WindowFlags(appWin.windowFlags.valueOf() + Qt.FramelessWindowHint.valueOf());
    //var flags = new Qt.WindowFlags(appWin.windowFlags());
    //var flags = new Qt.WindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool);
    //appWin.setWindowFlags(flags);

    var pe = appWin.findChild("PropertyEditorDock");
    pe.show();
    pe.maximumWidth = 280;

    var ll = appWin.findChild("LayerListDock");
    ll.show();
    ll.maximumWidth = 220;

    var bl = appWin.findChild("BlockListDock");
    bl.show();
    bl.maximumWidth = 220;

    var ct = appWin.findChild("CamToolBar");
    ct.hide();

    var cl = appWin.findChild("CommandLineDock");
    cl.hide();

    this.mirrorWidget = new QLabel(appWin);
    this.mirrorWidget.setAttribute(Qt.WA_MacAlwaysShowToolWindow);
    this.mirrorWidget.setAttribute(Qt.WA_TransparentForMouseEvents);
    this.mirrorWidget.resize(this.w,this.y+this.h+30);
    this.mirrorWidget.move(this.x+this.w,this.y);
//    this.mirrorWidget.resize(this.w,this.h);
//    this.mirrorWidget.move(this.x,this.y);
    this.mirrorWidget.focusPolicy = Qt.NoFocus;
    var flags = new Qt.WindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool);
    this.mirrorWidget.setWindowFlags(flags);
    this.mirrorWidget.setAttribute(Qt.WA_MacNoShadow);
    this.mirrorWidget.setAttribute(Qt.WA_DeleteOnClose);
    this.mirrorWidget.setAttribute(Qt.WA_ShowWithoutActivating);

    this.mirrorWidget.show();

    this.cursors = {
        "ArrowCursor": [5,5],
        "CrossCursor": [15,15],
        "WindowZoomCursor": [12,12],
        "PrintPreviewOffsetCursor": [16,16],
        "OpenHandCursor": [16,16],
        "ClosedHandCursor": [16,16],
        "IBeamCursor": [16,16]
    };

    for (var cursorShape in this.cursors) {
        this.cursors[cursorShape].push(ScMirrored.createPixmap(
            ScMirrored.includeBasePath + "/" + cursorShape + ".svg", 32,32));
    }

    // start mirroring:
    var t = new QTimer(this.mirrorWidget);
    t.interval = 50;
    t.timeout.connect(this, "mirror");

    this.ef = new ScInputInfoEventFilter(this);
    this.ef.install(appWin);

    var self = this;
    appWin.closeRequested.connect(function() {
        qDebug("ScMirrored: closeRequested");
        self.ef.stopped = true;
        self.ef.quit = true;
        //self.ef.uninstall(appWin.findChild("MdiArea"));
        self.ef.uninstall(appWin);
        qDebug("ScMirrored: closeRequested: OK");
    });

    //var fl = new ScInputInfoFocusListener(ef);
    //appWin.addFocusListener(fl);

    //appWin.setProperty("ScreencastRunning", true);
    t.start();

    this.terminate();
};

ScMirrored.prototype.mirror = function() {
    var pm = QPixmap.grabWindow(QApplication.desktop().winId(), 0, 0, this.w, this.y+this.h+30);
    var pos = QCursor.pos();

    var widget = QApplication.widgetAt(pos);
    var shape;
    if (!isNull(widget)) {
        shape = widget.cursor.shape().toString();
    }

    if (shape==="BitmapCursor") {
        shape = widget["CursorName"];
    }

    if (isNull(shape)|| isNull(this.cursors[shape])) {
        shape = "ArrowCursor";
    }

    var p = new QPainter();
    p.begin(pm);

    //qDebug("bs: ", this.ef.buttons);
    //qDebug("b: ", this.ef.button);
    //qDebug("k: ", this.ef.key);
    //qDebug("m: ", this.ef.modifiers);

    // highlight widget under cursor:
    if (!isNull(widget) && this.ef.key===Qt.Key_Backslash.valueOf()) {
        //qDebug("widget.objectName: ", widget.objectName);
        p.setBrush(new QBrush(new QColor(255,0,0,32)));
        var pen = new QPen(new QColor(255,0,0,128));
        pen.setWidth(2);
        p.setPen(pen);
        var wpos = widget.mapToGlobal(new QPoint(0,0));
        p.drawRect(wpos.x(), wpos.y(), widget.width, widget.height);
    }

    // paint mouse cursor:
    var cursor = this.cursors[shape];
    pos.operator_add_assign(new QPoint(-cursor[0], -cursor[1]));
    p.drawPixmap(pos, cursor[2]);

    p.end();

    this.mirrorWidget.pixmap = pm;
    collectGarbage();
};

ScMirrored.createPixmap = function(file, w, h) {
    var pixmap = new QPixmap(w,h);
    pixmap.fill(new QColor(0,0,0,0));
    var p = new QPainter();
    p.begin(pixmap);
    var r = new QSvgRenderer();
    r.load(file);
    r.render(p);
    p.end();
    return pixmap;
}



/**
 * Adds a menu for this action to Examples/Math Examples/ScMirrored.
 */
ScMirrored.init = function(basePath) {
    var action = new RGuiAction("&Mirrored", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ScMirrored.js");
    action.setSortOrder(20);
    action.setDefaultCommands(["screencast"]);
    EAction.addGuiActionTo(action, Screencast, true, false, false);
};
