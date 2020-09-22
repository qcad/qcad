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

/**
 * The options toolbar is created and initialized here.
 */
function OptionsToolBar() {
}

OptionsToolBar.includeBasePath = includeBasePath;

OptionsToolBar.normalizeSeparators = function(action) {
    // remove double separators:
    var optionsToolBar = EAction.getOptionsToolBar();
    var children = optionsToolBar.children();
    var previousWidgetWasSeparator = false;
    for (var i = 0; i < children.length; ++i) {
        var c = children[i];
        if (isFunction(c.isSeparator) && c.isSeparator()===true) {
            if (previousWidgetWasSeparator) {
                var idx = action.optionWidgetActions.indexOf(c);
                if (idx!==-1) {
                    // make sure the action is also removed from the list of added actions:
                    action.optionWidgetActions.splice(idx, 1);
                }
                c.destroy();
            }

            previousWidgetWasSeparator = true;
        }
        else if (isQWidget(c) && c.objectName.length!==0 && c.visible) {
            previousWidgetWasSeparator = false;
        }
    }
};

OptionsToolBar.getFirstInputWidget = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    var widgets = getWidgets(optionsToolBar);
    for (var p in widgets) {
        var w = widgets[p];
        if (isOfType(w, QLineEdit) ||
            isOfType(w, RMathLineEdit) ||
            isOfType(w, QSpinBox) ||
            isOfType(w, QComboBox)) {

            return w;
        }
    }

    return undefined;
};

OptionsToolBar.init = function(basePath) {
    // make sure that the options tool bar is initialized before 
    // positions are restored from the config file:
    var optionsToolBar = EAction.getOptionsToolBar();
};

OptionsToolBar.initStyle = function() {
    var optionsToolBar = EAction.getOptionsToolBar();

    var iconLabel = optionsToolBar.findChild("Icon");

    // style of label with current tool icon:
    if (!RSettings.hasCustomStyleSheet()) {
        var w = optionsToolBar.iconSize.width() < 20 ? 1 : 2;
        if (RSettings.hasDarkGuiBackground()) {
            iconLabel.styleSheet =
                "QLabel {"
                + "border-radius: %1px; ".arg(w*3)
                + "background-color: "
                + "    qlineargradient(spread:pad, "
                + "        x1: 0, y1: 0, "
                + "        x2: 0, y2: 1, "
                + "        stop: 0 #555555, "
                + "        stop: 0.5 #606060, "
                + "        stop: 1 #555555"
                + "    ); "
                + "border: %1px solid #a0a0a0;".arg(w)
                + "margin: %1px %1px %1px %1px;".arg(w)
                + "}";
        }
        else {
            iconLabel.styleSheet =
                "QLabel {"
                + "border-radius: %1px; ".arg(w*3)
                + "background-color: "
                + "    qlineargradient(spread:pad, "
                + "        x1: 0, y1: 0, "
                + "        x2: 0, y2: 1, "
                + "        stop: 0 rgba(255,255,255,0), "
                + "        stop: 0.5 rgba(255,255,255,192), "
                + "        stop: 1 rgba(255,255,255,0) "
                + "    ); "
                + "border: %1px solid #8f8f8f;".arg(w)
                + "margin: %1px %1px %1px %1px;".arg(w)
                + "}";
        }
    }
};

OptionsToolBar.postInit = function(basePath) {
    var optionsToolBar = EAction.getOptionsToolBar();

    // fixed height to prevent FS#652 (can happen at least on Windows and Linux):
    var ftb = EAction.getMainWindow().findChild("FileToolBar");
    if (!isNull(ftb)) {
        optionsToolBar.setFixedHeight(Math.min(ftb.sizeHint.height(), ftb.sizeHint.width()));
    }

    var flags = new Qt.ToolBarAreas(Qt.TopToolBarArea | Qt.BottomToolBarArea);
    optionsToolBar.setAllowedAreas(flags);

    // floatable tool bar does not resize properly: prevent floating of tool bar here:
    //optionsToolBar.floatable = false;

    var iconLabel = new QLabel(optionsToolBar);
    //var iconLabel = new QToolButton(optionsToolBar);
    iconLabel.objectName = "Icon";
    iconLabel.alignment = Qt.AlignCenter;
    iconLabel.setContentsMargins(6, 0, 6, 0);
    //iconLabel.setFrameStyle(QFrame.Panel | QFrame.Sunken);

    OptionsToolBar.initStyle();

    // avoid empty label after startup, before initializing new document:
    OptionsToolBar.setIcon("scripts/Reset/Reset.svg");

    optionsToolBar.addWidget(iconLabel);
    optionsToolBar.addSeparator();

    var appWin = RMainWindowQt.getMainWindow();
    var pl = new RPaletteListenerAdapter();
    appWin.addPaletteListener(pl);
    pl.paletteChanged.connect(OptionsToolBar.initStyle);
};

/**
 * Sets the icon at the left of the options toolbar, typically indicating the current tool.
 */
OptionsToolBar.setIcon = function(fileNameOrIcon) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var iconLabel = optionsToolBar.findChild("Icon");
    var f = 1.0;
    if (RS.getSystemId()==="win") {
        f = 0.8;
    }
    else if (RS.getSystemId()==="osx") {
        f = 0.9;
    }
    else if (RS.getSystemId()==="linux") {
        f = 0.8;
    }
    var w = optionsToolBar.iconSize.width()*f;
    var h = optionsToolBar.iconSize.height()*f;


//    var iconSize = RSettings.getIntValue("CadToolBar/IconSize", 32);
//    iconSize = Math.max(iconSize, RSettings.getIntValue("ToolBar/IconSize", 32));
//    iconSize = Math.max(iconSize, RSettings.getIntValue("CadToolMatrix/IconSize", 24));

//    // retina icons:
//    if (RSettings.getDevicePixelRatio()>1) {
//        iconSize*=RSettings.getDevicePixelRatio();
//    }

//    var pm = new QPixmap(iconSize,iconSize);
//    //pm.fill(Qt.transparent);
//    var p = new QPainter();
//    p.begin(pm);
//    var renderer = new QSvgRenderer(OptionsToolBar.includeBasePath + "/IconBackground.svg");
//    renderer.render(p, new QRectF(0, 0, iconSize, iconSize));

    if (isOfType(fileNameOrIcon, QIcon)) {
        iconLabel.pixmap = fileNameOrIcon.pixmap(new QSize(w, h));
        //iconLabel.icon = fileNameOrIcon;
    }
    else {
        iconLabel.pixmap = new QIcon(autoPath(fileNameOrIcon)).pixmap(new QSize(w, h));
        //iconLabel.icon = new QIcon(autoPath(fileNameOrIcon));
    }

//    p.end();


};
