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



function ScInputInfoFocusListener(ef) {
    RFocusListenerAdapter.call(this);
    this.eventFilter = ef;
}

ScInputInfoFocusListener.prototype = new RFocusListenerAdapter();

ScInputInfoFocusListener.prototype.updateFocus = function(di) {
    qDebug("updateFocus");
    var appWin = RMainWindowQt.getMainWindow();
    var mdiArea = appWin.findChild("MdiArea");
    this.eventFilter.install(mdiArea);
};




function ScInputInfoEventFilter() {
    QObject.call(this);
    this.mouseLabel = ScInputInfoEventFilter.createLabel("mouse_l", "mouse_mask", 32, 32);
}

ScInputInfoEventFilter.prototype = new QObject();

ScInputInfoEventFilter.createLabel = function(file, maskFile, w, h) {
    var appWin = RMainWindowQt.getMainWindow();
    var label = new QLabel(appWin);
    label.focusPolicy = Qt.NoFocus;
    var flags = new Qt.WindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool);
    label.setWindowFlags(flags);
    label.setAttribute(Qt.WA_MacNoShadow);
    label.setAttribute(Qt.WA_DeleteOnClose);
    label.setAttribute(Qt.WA_ShowWithoutActivating);
    label.resize(w,h);
    label.move(0,0);
    label.scaledContents = true;

    var pixmap = ScInputInfoEventFilter.createPixmap(ScInputInfo.includeBasePath + "/" + file + ".svg", w, h);
    var mask = ScInputInfoEventFilter.createPixmap(ScInputInfo.includeBasePath + "/" + maskFile + ".svg", w, h);
    label.pixmap = pixmap;
    label.setMask(new QBitmap(mask));
    label.setMask(mask.mask());
    label.visible = false;
    return label;
};

ScInputInfoEventFilter.createPixmap = function(file, w, h) {
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

ScInputInfoEventFilter.prototype.install = function(w) {
    var kids = w.children();
    for (var i=0; i<kids.length; i++) {
        var k = kids[i];
        if (isNull(k.gotEventFilter)) {
            k.installEventFilter(this);
            k.mouseTracking = true;
            k.setProperty("gotEventFilter", true);
        }
        this.install(k);
    }
};

ScInputInfoEventFilter.prototype.showMouseLabel = function() {
    this.mouseLabel.show();
};

ScInputInfoEventFilter.prototype.hideMouseLabel = function() {
    this.mouseLabel.hide();
};

ScInputInfoEventFilter.prototype.eventFilter = function(watched, e) {
    var appWin = RMainWindowQt.getMainWindow();
    e = e.cast();
    var type = e.type().toString();

    if (isNull(this.counter)) {
        this.counter = 0;
    }

    if (type.contains("Mouse") ||
        type.contains("Key") ||
        type.contains("Focus") ||
        type.contains("Enter") ||
        type.contains("Leave")) {

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

    switch (type) {
        case "ContextMenu":
            installFilter = true;
            break;

        case "MouseButtonRelease":
            updatePos = true;
            this.hideMouseLabel();
            break;

        case "MouseButtonPress":
            this.showMouseLabel();
            if (this.buttons!==Qt.RightButton.valueOf()) {
                installFilter = true;
            }
            updatePos = true;
            break;

        case "MouseMove":
            //this.hideMouseLabel();
            //var pos = watched.mapToGlobal(e.pos());
            this.counter++;
            if (this.counter>=2) {
                this.counter = 0;
                updatePos = true;
            }
            break;
    }

    if (installFilter) {
        var self = this;
        for (var i=0; i<2; i++) {
            var singleShot = new QTimer();
            singleShot.singleShot = true;
            singleShot.timeout.connect(function() {
                self.mouseLabel.raise();
                self.install(appWin);
            });
            singleShot.start(20 + i*200);
        }
    }

    if (updatePos) {
        var pos = QCursor.pos();
        this.mouseLabel.move(pos.x()+10, pos.y()+10);
    }

    return false;
};




/**
 * This action creates a Qt main window.
 */
function ScInputInfo(guiAction) {
    EAction.call(this, guiAction);
}

ScInputInfo.prototype = new EAction();
ScInputInfo.includeBasePath = includeBasePath;

ScInputInfo.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var w = 1280;
    var h = 680;
    var x = 50;
    var y = 20;

    var appWin = RMainWindowQt.getMainWindow();
    appWin.resize(w,h);
    appWin.move(x,y);

    //var flags = new Qt.WindowFlags(appWin.windowFlags | Qt.FramelessWindowHint);
    //var flags = new Qt.WindowFlags(appWin.windowFlags());
    //var flags = new Qt.WindowFlags(appWin.windowFlags() | Qt.Window);
    //appWin.setWindowFlags(flags);

    var pe = appWin.findChild("PropertyEditorDock");
    pe.show();
    pe.maximumWidth = 280;
    //pe.resize(300,h+5);
    //pe.move(x+w+10,y);

    var ll = appWin.findChild("LayerListDock");
    ll.show();
    ll.maximumWidth = 220;

    var bl = appWin.findChild("BlockListDock");
    bl.show();
    bl.maximumWidth = 220;

    //var ct = appWin.findChild("CamToolBar");
    //ct.hide();

    var cl = appWin.findChild("CommandLineDock");
    cl.hide();

    //this.showOverlay();

    var ef = new ScInputInfoEventFilter(this);
    ef.install(appWin);

    var fl = new ScInputInfoFocusListener(ef);
    appWin.addFocusListener(fl);

    qDebug("init running: true");
    appWin.setProperty("ScreencastRunning", true);
    //ScInputInfo.running = true;

    this.terminate();
};

//ScInputInfo.prototype.showOverlay = function() {
//    var appWin = RMainWindowQt.getMainWindow();
    //ScInputInfo.overlayWidget = new ScInputInfoOverlay(appWin);
    //ScInputInfo.overlayWidget.objectName = "ScInputInfoOverlay";
    //ScInputInfo.overlayWidget.resize(200, 200);
    //ScInputInfo.overlayWidget.move(0, 0);
    //ScInputInfo.overlayWidget.show();

//    ScInputInfo.installEventFilter(appWin);
//};


//ScInputInfo.prototype.eventFilter = function(watched, e) {
//    e = e.cast();
//    var type = e.type().toString();

////    if (watched.objectName==="ScInputInfoOverlay") {
////        return false;
////    }

//    qDebug("object: ", watched.objectName);
//    qDebug("type: ", type);

//    /*
//    switch (type) {
//        case "ContextMenu":
//            var self = this;
//            var singleShot = new QTimer();
//            singleShot.singleShot = true;
//            singleShot.timeout.connect(function() {
//                self.raise();
//            });
//            singleShot.start(20);
//            break;

//        case "KeyRelease":
//            this.raise();
////            qDebug("key: ", e.key());
////            qDebug("watched: ", watched.objectName);
////            qDebug("");
//            //this.keyLabel.text = String.fromCharCode(e.key());
//            //this.keyLabel.show();
//            //var a = new QPropertyAnimation(this.keyLabel, "anim", this.keyLabel);
//            //a.setDuration(1000);
//            //timer.start(30);
//            //this.keyLabel.start(String.fromCharCode(e.key()));

//            //this.key = e.key();
//            //this.update();
//            break;

//        case "MouseButtonPress":
//        case "MouseButtonRelease":
//        case "MouseMove":

//            this.buttons = e.buttons().valueOf();
//            qDebug("e.buttons(): ", e.buttons());

//            //qDebug("e.pos(): ", e.pos().x(), e.pos().y());

//            var appWin = RMainWindowQt.getMainWindow();
//            //var pos = watched.mapTo(appWin, e.pos());
//            var pos = watched.mapToGlobal(e.pos());
//            //pos = appWin.mapFromGlobal(pos);

//            qDebug("pos: ", pos.x(), pos.y());

//            this.move(pos.x()+20, pos.y()+20);
//            this.update();

//            //this.move(e.pos().x(), e.pos().y());
//            //this.raise();
////            if (e.buttons().valueOf()===Qt.NoButton.valueOf()) {
////                this.mouseLabel.stop();
////            }
////            else {
////                this.mouseLabel.start(watched, e);
////            }

////            qDebug("button: ", e.button());
////            qDebug("buttons: ", e.buttons());
//            qDebug("type: ", type);
////            qDebug("pos: ", e.pos());
////            qDebug("watched: ", watched.objectName);
////            qDebug("");
//            break;

//        default:
//            break;
//    }

////    if (type.contains("Key") || type.contains("Mouse")) {
////        qDebug("event: ", e.type());
////    }
//    */
//    return false;
//};

/**
 * Adds a menu for this action to Examples/Math Examples/ScInputInfo.
 */
ScInputInfo.init = function(basePath) {
    var action = new RGuiAction("&Show input info", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ScInputInfo.js");
    action.setSortOrder(20);
    action.setDefaultCommands(["screencast"]);
    EAction.addGuiActionTo(action, Screencast, true, false, false);
};
