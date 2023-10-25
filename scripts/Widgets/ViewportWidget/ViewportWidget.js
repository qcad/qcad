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

include("scripts/library.js");
include("scripts/sprintf.js");

if (exists("scripts/Navigation/DefaultNavigation/DefaultNavigation.js")) {
    include("scripts/Navigation/DefaultNavigation/DefaultNavigation.js");
}

ViewportWidget.templateDir = autoPath("scripts/Widgets/ViewportWidget/Templates");

/**
 * A viewport widget encapsulates one graphics view and might provide means to navigate
 * (scroll bars) and other widgets that are available for every graphics view.
 *
 * \param vpNumber Number of viewport. There can be up to four viewports
 * available for example in an MDI child (tab). This number is used to identify
 * the viewport settings in configuration files and document settings.
 * \param vpWidget Viewport widget that will contain the viewport
 * after initialization.
 */
function ViewportWidget(vpNumber, vpWidget, documentInterface) {
    this.vpNumber = vpNumber;
    this.vpWidget = vpWidget;
    this.documentInterface = documentInterface;
    this.eventHandler = undefined;
}

/**
 * \return Array of ViewportWidget objects, one for each child of widget that
 * is called "ViewportXX".
 */
ViewportWidget.getViewports = function(widget, documentInterface) {
    var vpWidget;
    var c = 0;
    var vps = [];
    do {
        var vpName = sprintf("Viewport%02d", c);
        vpWidget = widget.findChild(vpName);
        if (isNull(vpWidget)) {
            break;
        }
        var viewport = new ViewportWidget(c, vpWidget, documentInterface);
        vps.push(viewport);
        ++c;
    } while (!isNull(vpWidget));
    return vps;
};

ViewportWidget.initEventHandler = function(viewports) {
    for ( var i = 0; i < viewports.length; ++i) {
        viewports[i].initEventHandler();
    }
};

ViewportWidget.initializeViewports = function(viewports, uiFile, graphicsSceneClass) {
    for ( var i = 0; i < viewports.length; ++i) {
        var vp = viewports[i];
        vp.init(uiFile, graphicsSceneClass);
    }
};

ViewportWidget.updateViewports = function(viewports) {
    // TODO auto zoom for each graphics view works only for the first viewport
    for (var i = 0; i < viewports.length; ++i) {
        var vp = viewports[i];
        vp.getEventHandler().viewportChanged();
        var view = vp.getGraphicsView();

        if (RSettings.getAutoZoomOnLoad() || i>0) {
            view.autoZoom(-1, true);
        }
        else {
            // restore first viewport (zoom / pan):
            var di = vp.getDocumentInterface();
            var doc = di.getDocument();
            var c = doc.getVariable("ViewportCenter", undefined);
            var w = doc.getVariable("ViewportWidth", undefined);
            var h = doc.getVariable("ViewportHeight", undefined);
            if (!isNull(c) && !isNull(w) && !isNull(h)) {
                view.zoomTo(new RBox(c, w, h));
            }
        }
    }
};

ViewportWidget.initMdiChild = function(mdiChild, uiFileName) {
    var w = WidgetFactory.createWidget("", ViewportWidget.templateDir + QDir.separator + uiFileName, mdiChild);
    w.setWindowTitle("");
    mdiChild.setWidget(w);
};

ViewportWidget.prototype.initEventHandler = function() {
    var self = this;

    this.eventHandler = new EventHandler(this, this.documentInterface);
    if (isOfType(this.graphicsView, RGraphicsViewQt)) {
        this.graphicsView.drop.connect(function(e) { self.eventHandler.drop(e); });
        this.graphicsView.dragEnter.connect(function(e) { self.eventHandler.dragEnter(e); });

        this.graphicsView.getImageView().viewportChanged.connect(function() { self.eventHandler.viewportChanged(); });
        this.graphicsView.getImageView().updateSnapInfo.connect(
            function(worker, snap, restriction) {
                self.eventHandler.updateSnapInfo(worker, snap, restriction);
            }
        );
        this.graphicsView.getImageView().updateTextLabel.connect(function(painter, textLabel) { self.eventHandler.updateTextLabel(painter, textLabel); });
    }

    if (!isNull(this.hsb)) {
        this.hsb.valueChanged.connect(function(value) { self.eventHandler.horizontalScrolled(value); } );
        this.vsb.valueChanged.connect(function(value) { self.eventHandler.verticalScrolled(value); } );
    }
};

/**
 * Initializes this viewport widget.
 *
 * \param uiFile UI file to use for view port (defaults to ViewportWidgetQt.ui).
 * \param graphicsSceneClass Class to use for graphics scene (defaults to "RGraphicsSceneQt")
 */
ViewportWidget.prototype.init = function(uiFile, graphicsSceneClass) {
    // delete placeholder children if there are any (clear out parent window):
    var chs = this.vpWidget.children();
    for (var i = 0; i < chs.length; ++i) {
        var ch = chs[i];
        if (isNull(ch)) {
            continue;
        }

        if (RSettings.getQtVersion()>=0x060000) {
            //if (ch.isOfObjectType(RJSType.QLayout_Type) || ch.isOfObjectType(RJSType.QWidget_Type)) {
            if (ch.isOfObjectType(RJSType_QLayout.id) || ch.isOfObjectType(RJSType_QWidget.id)) {
                destr(ch);
            }
        }
        else {
            destr(ch);
        }
    }

    if (isNull(uiFile)) {
        uiFile = "scripts/Widgets/ViewportWidget/ViewportWidgetQt.ui";
    }

    // use ViewportWidgetQt.ui or given UI file:
    var vpw = WidgetFactory.createWidget("", uiFile, this.vpWidget);

    var layout = new QVBoxLayout();
    if (RSettings.isQt(6)) {
        layout.addWidget(vpw);
    }
    else {
        layout.addWidget(vpw, 0, Qt.AlignTop | Qt.AlignLeft);
    }

    layout.setStretch(0, 1);
    layout.setContentsMargins(0,0,0,0);
    if (!isNull(this.vpWidget.layout())) {
        // destroy existing layout manager
        destr(this.vpWidget.layout());
    }
    this.vpWidget.setLayout(layout);
    // clear style sheet
    this.vpWidget.styleSheet = "";

    this.graphicsView = this.vpWidget.findChild("GraphicsView");

    if (isNull(this.graphicsView)) {
        qWarning("graphics view not found");
        return;
    }

    var imageView;

    if (false && !isNull(RGraphicsViewSkia)) {
    //if (!isNull(RGraphicsViewSkia)) {
        // skia view:
        imageView = new RGraphicsViewSkia();
        this.graphicsView.setImageView(imageView);
    }
    else {
        imageView = this.graphicsView.getImageView();
    }

    imageView.setViewportNumber(this.vpNumber);
    if (isFunction(imageView.setFocusFrameWidget)) {
        imageView.setFocusFrameWidget(this.vpWidget);
    }

    imageView.setAntialiasing(RSettings.getBoolValue("GraphicsView/Antialiasing", false));

    // enable multithreaded graphics view:
    //if (RSettings.getBoolValue("GraphicsView/Multithreading", true)) {
    var numThreads = RSettings.getIntValue("GraphicsView/Threads", Math.min(RS.getIdealThreadCount(), 6));
    if (numThreads!==1) {
        imageView.setNumThreads(numThreads);
        //EAction.handleUserMessage(qsTr("Threads:") + " " + numThreads);
    }
    //}

    // create custom graphics scene (e.g. OpenGL, ...):
    var scene = undefined;
    if (!isNull(graphicsSceneClass)) {
        if (!isNull(global[graphicsSceneClass])) {
            scene = new global[graphicsSceneClass](this.documentInterface);
        }
    }

    if (isNull(scene)) {
        scene = new RGraphicsSceneQt(this.documentInterface);
    }

    if (RSettings.getBoolValue("GraphicsView/AutoSwitchLinetypes", false)===true) {
        scene.setScreenBasedLinetypes(true);
    }

    imageView.setScene(scene);
    if (typeof(DefaultNavigation)!=="undefined") {
        var navigationAction = new DefaultNavigation(this.vpWidget);
        imageView.setNavigationAction(navigationAction);
    }

    var grid = new ROrthoGrid(getRGraphicsView(imageView));

    imageView.setGrid(grid);

    if (RSettings.isQt(6)) {
        this.graphicsView.setFocus(Qt.OtherFocusReason);
    }
    else {
        this.graphicsView.setFocus();
    }

    this.hsb = this.vpWidget.findChild("HorizontalScrollBar");
    if (!isNull(this.hsb)) {
        this.hsb.singleStep = 50;
    }
    this.vsb = this.vpWidget.findChild("VerticalScrollBar");
    if (!isNull(this.vsb)) {
        this.vsb.singleStep = 50;
    }
    if (RSettings.getBoolValue("GraphicsView/ShowScrollBars", true)===false) {
        var infoLabel = this.vpWidget.findChild("InfoLabel");
        infoLabel.hide();
        if (!isNull(this.hsb)) {
            this.hsb.hide();
        }
        if (!isNull(this.vsb)) {
            this.vsb.hide();
        }
    }

    var hruler = this.vpWidget.findChild("HorizontalRuler");
    var vruler = this.vpWidget.findChild("VerticalRuler");

    // moved to RRulerQt:
    //var appWin = RMainWindowQt.getMainWindow();
    //appWin.addPaletteListener(hruler);
    //appWin.addPaletteListener(vruler);

    if (RSettings.getBoolValue("GraphicsView/ShowRulers", true)) {
        this.hruler = hruler;
        if (!isNull(this.hruler)) {
            this.hruler.setGraphicsView(imageView);
            this.documentInterface.addCoordinateListener(this.hruler);
        }
        this.vruler = vruler;
        if (!isNull(this.vruler)) {
            this.vruler.setGraphicsView(imageView);
            this.documentInterface.addCoordinateListener(this.vruler);
        }
    } else {
        if (!isNull(hruler)) {
            hruler.hide();
        }
        if (!isNull(vruler)) {
            vruler.hide();
        }
        var cf = this.vpWidget.findChild("cornerFrame");
        if (!isNull(cf)) {
            cf.hide();
        }
    }
};

ViewportWidget.prototype.getVpWidget = function() {
    return this.vpWidget;
};

ViewportWidget.prototype.getGraphicsView = function() {
    return this.graphicsView.getImageView();
};

ViewportWidget.prototype.getDocumentInterface = function() {
    return this.documentInterface;
};

ViewportWidget.prototype.getEventHandler = function() {
    return this.eventHandler;
};



/**
 * Event handler class. For each new document that is created or
 * opened, an event handler is created to handle various events
 * for the life time of the document.
 */
function EventHandler(viewport, documentInterface) {
    REventHandler.call(this, viewport.getVpWidget(), documentInterface);
}

EventHandler.prototype = new REventHandler();

/**
 * Handles drop into the drawing area
 * \param event QDropEvent
 */
EventHandler.prototype.drop = function(event) {
    var mimeData = event.mimeData();
    var urls = getUrlsFromMimeData(mimeData);

    if (urls.length===0) {
        EAction.handleUserWarning(qsTr("Dropped data not supported"));
        event.acceptProposedAction();
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();
    if (!isNull(appWin)) {
        appWin.activateWindow();
        appWin.raise();
        var view = EAction.getGraphicsView();
        if (!isNull(view)) {
            view.setFocus(Qt.OtherFocusReason);
        }
        else {
            appWin.setFocus(Qt.OtherFocusReason);
        }
    }

    var action;
    if (urls[0].isLocalFile()) {
        var filePath = urls[0].toLocalFile();
        var fi = new QFileInfo(filePath);
        if (fi.suffix().toLowerCase()==="cxf") {
            //openFiles(urls[0]);
            //event.acceptProposedAction();
            //event.ignore();
            EAction.handleUserWarning(qsTr("Cannot import file into existing drawing:") + " " + filePath);
            return;
        }

        EAction.handleUserMessage(qsTr("Importing file:") + " " + filePath);
        if (fi.isFile()) {
            include("scripts/Block/InsertScriptItem/InsertScriptItem.js");
            include("scripts/Draw/Image/Image.js");

            if (InsertScriptItem.isScriptFile(filePath)) {
                action = RGuiAction.getByScriptFile("scripts/Block/InsertScriptItem/InsertScriptItem.js");
            }
            else if (Image.isSupportedBitmapFile(filePath)) {
                action = RGuiAction.getByScriptFile("scripts/Draw/Image/Image.js");
            }
            else {
                action = RGuiAction.getByScriptFile("scripts/Block/InsertBlockItem/InsertBlockItem.js");
            }
        }
    }
    else {
        EAction.handleUserMessage(qsTr("Importing URL: ") + urls[0].toString());
        action = RGuiAction.getByScriptFile("scripts/Block/InsertBlockItem/InsertBlockItem.js");
    }

    if (isNull(action)) {
        event.acceptProposedAction();
        return;
    }

    action.setData(urls[0]);
    action.slotTrigger();
    event.acceptProposedAction();
    event.accept();
};
