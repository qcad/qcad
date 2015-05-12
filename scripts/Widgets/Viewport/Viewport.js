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

if (new QFileInfo("scripts/Navigation/DefaultNavigation/DefaultNavigation.js").exists()) {
    include("scripts/Navigation/DefaultNavigation/DefaultNavigation.js");
}

Viewport.templateDir = "scripts/Widgets/Viewport/Templates";

/**
 * A viewport encapsulates one graphics view and might provide means to navigate
 * (scroll bars) and other widgets that are available for every graphics view.
 *
 * \param vpNumber Number of viewport. There can be up to four viewports
 * available for example in an MDI child (tab). This number is used to identify
 * the viewport settings in configuration files and document settings.
 * \param vpWidget Viewport widget that will contain the viewport
 * after initialization.
 */
function Viewport(vpNumber, vpWidget, documentInterface) {
    this.vpNumber = vpNumber;
    this.vpWidget = vpWidget;
    this.documentInterface = documentInterface;
    this.eventHandler = undefined;
}

/**
 * \return Array of Viewport objects, one for each child of widget that
 * is called "ViewportXX".
 */
Viewport.getViewports = function(widget, documentInterface) {
    var vpWidget;
    var c = 0;
    var vps = [];
    do {
        var vpName = sprintf("Viewport%02d", c);
        vpWidget = widget.findChild(vpName);
        if (isNull(vpWidget)) {
            break;
        }
        var viewport = new Viewport(c, vpWidget, documentInterface);
        vps.push(viewport);
        ++c;
    } while (!isNull(vpWidget));
    return vps;
};

Viewport.initEventHandler = function(viewports) {
    for ( var i = 0; i < viewports.length; ++i) {
        viewports[i].initEventHandler();
    }
};

Viewport.initializeViewports = function(viewports) {
    for ( var i = 0; i < viewports.length; ++i) {
        var vp = viewports[i];
        vp.init();
    }
};

Viewport.updateViewports = function(viewports) {
    // TODO auto zoom for each graphics view works only for the first viewport
    for (var i = 0; i < viewports.length; ++i) {
        var vp = viewports[i];
        vp.getEventHandler().viewportChanged();
        var gv = vp.getGraphicsView();
        gv.autoZoom(-1, true);
        //gv.setAntialiasing(RSettings.getBoolValue("GraphicsView/Antialiasing", false));
    }
};

Viewport.initMdiChild = function(mdiChild, uiFileName) {
    var w = WidgetFactory.createWidget("", Viewport.templateDir + QDir.separator + uiFileName, mdiChild);
    w.setWindowTitle("");
    mdiChild.setWidget(w);
};

Viewport.prototype.initEventHandler = function() {
    this.eventHandler = new EventHandler(this, this.documentInterface);
    if (isOfType(this.graphicsView, RGraphicsViewQt)) {
        this.graphicsView.drop.connect(this.eventHandler, "drop");
        this.graphicsView.dragEnter.connect(this.eventHandler, "dragEnter");
        this.graphicsView.viewportChanged.connect(this.eventHandler, "viewportChanged");
        this.graphicsView.updateSnapInfo.connect(this.eventHandler, "updateSnapInfo");
        this.graphicsView.updateTextLabel.connect(this.eventHandler, "updateTextLabel");
    }

    if (!isNull(this.hsb)) {
        this.hsb.valueChanged.connect(this.eventHandler, "horizontalScrolled");
        this.vsb.valueChanged.connect(this.eventHandler, "verticalScrolled");
    }
};

/**
 * Initializes this viewport.
 */
Viewport.prototype.init = function() {
    // delete placeholder children if there are any (clear out parent window):
    var chs = this.vpWidget.children();
    for (var i = 0; i < chs.length; ++i) {
        var ch = chs[i];
        ch.destroy();
    }
    
    var vpw = WidgetFactory.createWidget("", "scripts/Widgets/Viewport/Viewport.ui", this.vpWidget);
//    var vpw = WidgetFactory.createWidget("", "scripts/Widgets/Viewport/ViewportGl.ui", this.vpWidget);
    var layout = new QVBoxLayout();
    layout.addWidget(vpw, 0, Qt.AlignTop | Qt.AlignLeft);
    layout.setStretch(0, 1);
    layout.setContentsMargins(0,0,0,0);
    if (!isNull(this.vpWidget.layout())) {
        // destroy existing layout manager
        this.vpWidget.layout().destroy();
    }
    this.vpWidget.setLayout(layout);
    // clear style sheet
    this.vpWidget.styleSheet = "";

    this.graphicsView = this.vpWidget.findChild("GraphicsView");
    if (isNull(this.graphicsView)) {
        qWarning("graphics view not found");
        return;
    }
    this.graphicsView.setViewportNumber(this.vpNumber);
    if (isFunction(this.graphicsView.setFocusFrameWidget)) {
        this.graphicsView.setFocusFrameWidget(this.vpWidget);
    }

    this.graphicsView.setAntialiasing(RSettings.getBoolValue("GraphicsView/Antialiasing", false));

    var scene = new RGraphicsSceneQt(this.documentInterface);
    // var scene = new RGraphicsSceneGl(this.documentInterface);
    if (RSettings.getBoolValue("GraphicsView/AutoSwitchLinetypes", false)===true) {
        scene.setScreenBasedLinetypes(true);
    }

    this.graphicsView.setScene(scene);
    if (!isNull(DefaultNavigation)) {
        var navigationAction = new DefaultNavigation(this.vpWidget);
        this.graphicsView.setNavigationAction(navigationAction);
    }

    var grid = new ROrthoGrid(this.graphicsView.getRGraphicsView());
    this.graphicsView.setGrid(grid);

    this.graphicsView.setFocus();

    this.hsb = this.vpWidget.findChild("HorizontalScrollBar");
    if (!isNull(this.hsb)) {
        this.hsb.singleStep = 50;
    }
    this.vsb = this.vpWidget.findChild("VerticalScrollBar");
    if (!isNull(this.vsb)) {
        this.vsb.singleStep = 50;
    }
    if (RSettings.getBoolValue("GraphicsView/ShowScrollbars", true)===false) {
        var infoLabel = this.vpWidget.findChild("InfoLabel");
        infoLabel.hide();
        if (!isNull(this.hsb)) {
            this.hsb.hide();
        }
        if (!isNull(this.vsb)) {
            this.vsb.hide();
        }
    }

    if (RSettings.getBoolValue("GraphicsView/ShowRulers", true)) {
        this.hruler = this.vpWidget.findChild("HorizontalRuler");
        this.hruler.setGraphicsView(this.graphicsView);
        this.vruler = this.vpWidget.findChild("VerticalRuler");
        this.vruler.setGraphicsView(this.graphicsView);

        this.documentInterface.addCoordinateListener(this.hruler);
        this.documentInterface.addCoordinateListener(this.vruler);
    } else {
        var hruler = this.vpWidget.findChild("HorizontalRuler");
        hruler.hide();
        var vruler = this.vpWidget.findChild("VerticalRuler");
        vruler.hide();
        var cf = this.vpWidget.findChild("cornerFrame");
        cf.hide();
    }
};

Viewport.prototype.getVpWidget = function() {
    return this.vpWidget;
};

Viewport.prototype.getGraphicsView = function() {
    return this.graphicsView;
};

Viewport.prototype.getEventHandler = function() {
    return this.eventHandler;
};

/**
 * Event handler class. For each new document that is created or
 * opened, an event handler is created to handle various events
 * for the life time of the document.
 */
function EventHandler(viewport, documentInterface) {
    //this.mdiChild = mdiChild;
    this.document = documentInterface.getDocument();
    this.documentInterface = documentInterface;

    this.vpWidget = viewport.getVpWidget();
    this.hsb = this.vpWidget.findChild("HorizontalScrollBar");
    this.vsb = this.vpWidget.findChild("VerticalScrollBar");
    this.graphicsView = this.vpWidget.findChild("GraphicsView");
    this.hruler = this.vpWidget.findChild("HorizontalRuler");
    this.vruler = this.vpWidget.findChild("VerticalRuler");
}

EventHandler.prototype.dragEnter = function(event) {
    event.acceptProposedAction();
};

/**
 * Handles drop into the drawing area
 * \param event QDropEvent
 */
EventHandler.prototype.drop = function(event) {
    var mimeData = event.mimeData();
    var urls = getUrlsFromMimeData(mimeData);

    if (urls.length===0) {
        EAction.handleUserMessage(qsTr("Cannot import URL(s): ") + text);
        event.acceptProposedAction();
        return;
    }

    var appWin = RMainWindowQt.getMainWindow();
    if (!isNull(appWin)) {
        appWin.raise();
        appWin.setFocus(Qt.OtherFocusReason);
    }

    var action;
    if (urls[0].isLocalFile()) {
        var file = urls[0].toLocalFile();
        EAction.handleUserMessage(qsTr("Importing file: ") + file);
        if (new QFileInfo(file).isFile()) {
            include("scripts/Block/InsertScriptItem/InsertScriptItem.js");
            if (InsertScriptItem.isScriptFile(file)) {
                action = RGuiAction.getByScriptFile("scripts/Block/InsertScriptItem/InsertScriptItem.js");
            } else {
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
    event.accept();
};

EventHandler.prototype.updateTextLabel = function(painter, textLabel) {
    this.drawInfoLabel(painter, textLabel);
};

EventHandler.prototype.drawInfoLabel = function(painter, textLabel) {
    var pos = textLabel.getPosition();
    var text = textLabel.getText();

    var p = this.graphicsView.mapToView(pos);
    // info labels might have individual colors in future
    //var color = RSettings.getColor("GraphicsViewColors/TextLabelColor", new RColor(249,198,31));
    var color = RSettings.getColor("GraphicsViewColors/MeasurementToolsColor", new RColor(155,220,112));
    painter.setPen(new QColor(color.red(), color.green(), color.blue(), color.alpha()));

    if (text!=="") {
        var font = RSettings.getInfoLabelFont();
        var fm = new QFontMetrics(font);
        var w = fm.width(text)+10;
        var h = fm.height()+10;
        fm.destroy();
        var flags = new Qt.Alignment(Qt.AlignHCenter | Qt.AlignVCenter);
        painter.setFont(font);
        painter.drawText(p.x - w - 15, p.y + h + 5, w, h, flags, text, null);
    }
};

/**
 * Called on every repaint of a view to update snap related information.
 * \param painter QPainter for the view in screen coordinates.
 * \param snap Current snap.
 */
EventHandler.prototype.updateSnapInfo = function(painter, snap, restriction) {
    if (isNull(snap)) {
        return;
    }

    var pos = snap.getLastSnap();
    if (!pos.isValid()) {
        return;
    }
    var posRestriction = undefined;
    if (!isNull(restriction)) {
        posRestriction = restriction.getLastSnap();
    }

    var text = "";
    switch (snap.getStatus()) {
//    case RSnap.Free:
//        text = qsTr("Free");
//        break;
    case RSnap.Grid:
        text = qsTr("Grid");
        break;
    case RSnap.Endpoint:
        text = qsTr("End");
        break;
    case RSnap.OnEntity:
        text = qsTr("On Entity");
        break;
    case RSnap.Perpendicular:
        text = qsTr("Perpendicular");
        break;
    case RSnap.Center:
        text = qsTr("Center");
        break;
    case RSnap.Middle:
        text = qsTr("Middle");
        break;
    case RSnap.Intersection:
        text = qsTr("Intersection");
        break;
    case RSnap.Reference:
        text = qsTr("Reference");
        break;
    }

    this.drawSnapLabel(painter, pos, posRestriction, text);
};

EventHandler.prototype.drawSnapLabel = function(painter, pos, posRestriction, text) {
    var p = this.graphicsView.mapToView(pos);
    var pr = undefined;
    if (!isNull(posRestriction)) {
        pr = this.graphicsView.mapToView(posRestriction);
    }
    var color = RSettings.getColor("GraphicsViewColors/TextLabelColor", new RColor(249,198,31));
    painter.setPen(color.toCompat());

    var font = RSettings.getSnapLabelFont();
    var fm = new QFontMetrics(font);
    painter.setFont(font);

    if (text!=="") {
        painter.drawText(
            p.x + 5, p.y + 5,
            fm.width(text)+10, fm.height()+10,
            new Qt.Alignment(Qt.AlignHCenter | Qt.AlignVCenter),
            text, null);
    }

    painter.drawEllipse(p.x-5, p.y-5, 10, 10);

    // restriction position:
    if (isValidVector(pr)) {
        painter.drawLine(pr.x, pr.y-5, pr.x+5, pr.y);
        painter.drawLine(pr.x+5, pr.y, pr.x, pr.y+5);
        painter.drawLine(pr.x, pr.y+5, pr.x-5, pr.y);
        painter.drawLine(pr.x-5, pr.y, pr.x, pr.y-5);
    }

    // display distance/angle:
    var display = RSettings.getIntValue("DisplaySettings/DisplayDistanceAngle", 0);
    if (display === 0) {
        fm.destroy();
        return;
    }

    var di = this.graphicsView.getDocumentInterface();
    var doc = this.graphicsView.getDocument();

    var relativeZero = di.getRelativeZero();

    if (isValidVector(posRestriction)) {
        var dist = relativeZero.getDistanceTo(posRestriction);
        var angle = relativeZero.getAngleTo(posRestriction);
    } else {
        dist = relativeZero.getDistanceTo(pos);
        angle = relativeZero.getAngleTo(pos);
    }

    var lp = doc.getLinearPrecision();
    var lformat = "%." + lp.toString() + "f";
    var distStr = sprintf(lformat, dist);

    angle = RMath.rad2deg(angle);
    var ap = doc.getAnglePrecision();
    var aformat = "%." + ap.toString() + "f";
    var angStr = sprintf(aformat, angle);

    var sep = RSettings.getStringValue("Input/PolarCoordinateSeparator", "<");

    color = RSettings.getColor("GraphicsViewColors/MeasurementToolsColor", new RColor(155,220,112));
    painter.setPen(color.toCompat());

    switch(display) {
    case 0:
        text = "";
        break;
    case 1:
        text = distStr + sep + angStr + "°";
        break;
    case 2:
        text = distStr;
        break;
    case 3:
        text = angStr + "°";
        break;
    default:
        text = "";
    }

    if (text !== "") {
        painter.drawText(
                    p.x + 5, p.y - 15 - fm.height(),
                    fm.width(text)+10, fm.height()+10,
                    new Qt.Alignment(Qt.AlignHCenter | Qt.AlignVCenter),
                    text, null);
    }

    fm.destroy();
};

/**
 * Called whenever the current viewport changed through panning or
 * zooming. Updates the scroll bars, rulers, etc.
 */
EventHandler.prototype.viewportChanged = function() {
    if (isNull(this.hsb) || isNull(this.vsb)) {
        return;
    }

    this.hsb.blockSignals(true);
    this.vsb.blockSignals(true);

    var box = this.document.getBoundingBox(true, true);
    var min = box.getMinimum().x * this.graphicsView.getFactor() - 800;
    var max = box.getMaximum().x * this.graphicsView.getFactor()
            - this.graphicsView.getWidth() + 800;
    this.hsb.setRange(min, max);
    this.hsb.pageStep = this.graphicsView.getWidth();
    this.hsb.value = -this.graphicsView.getOffset().x
            * this.graphicsView.getFactor();

    min = this.graphicsView.getHeight() - box.getMaximum().y
            * this.graphicsView.getFactor() - 800;
    max = 800 - box.getMinimum().y * this.graphicsView.getFactor();
    this.vsb.setRange(min, max);
    this.vsb.pageStep = this.graphicsView.getHeight();
    this.vsb.value = this.graphicsView.getOffset().y
            * this.graphicsView.getFactor();

    this.hsb.blockSignals(false);
    this.vsb.blockSignals(false);

    // rulers
    if (!isNull(this.hruler)) {
        this.hruler.updateViewport();
    }
    if (!isNull(this.vruler)) {
        this.vruler.updateViewport();
    }

    // grid info label
    var infoLabel = this.vpWidget.findChild("InfoLabel");
    var grid = this.graphicsView.getGrid();
    if (!isNull(grid)) {
        infoLabel.text = grid.getInfoText();
    }
};

EventHandler.prototype.horizontalScrolled = function(pos) {
    var blocked = this.graphicsView.signalsBlocked();
    this.graphicsView.blockSignals(true);
    var off = this.graphicsView.getOffset();
    off.x = -(pos / this.graphicsView.getFactor());
    this.graphicsView.setOffset(off);
    this.graphicsView.blockSignals(blocked);
    if (this.hruler) {
        this.hruler.updateViewport();
    }
};

EventHandler.prototype.verticalScrolled = function(pos) {
    var blocked = this.graphicsView.signalsBlocked();
    this.graphicsView.blockSignals(true);
    var off = this.graphicsView.getOffset();
    off.y = pos / this.graphicsView.getFactor();
    this.graphicsView.setOffset(off);
    this.graphicsView.blockSignals(blocked);
    if (this.vruler) {
        this.vruler.updateViewport();
    }
};
