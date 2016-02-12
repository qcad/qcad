/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

OptionsToolBar.postInit = function(basePath) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var sh = EAction.getMainWindow().findChild("FileToolBar").sizeHint;

    // fixed height to prevent FS#652 (can happen at least on Windows and Linux):
    var h = 38;
    if (RS.getSystemId()==="osx") {
        h = 44;
    }
    optionsToolBar.setFixedHeight(h);

    var flags = new Qt.ToolBarAreas(Qt.TopToolBarArea | Qt.BottomToolBarArea);
    optionsToolBar.setAllowedAreas(flags);

    // floatable tool bar does not resize properly: prevent floating of tool bar here:
    //optionsToolBar.floatable = false;

    var iconLabel = new QLabel(optionsToolBar);
    iconLabel.objectName = "Icon";
    iconLabel.alignment = Qt.AlignCenter;
    iconLabel.setContentsMargins(6, 0, 6, 0);
    iconLabel.styleSheet =
        "QLabel {"
        + "border-radius: 6px; "
        + "background-color: "
        + "    qlineargradient(spread:pad, "
        + "        x1: 0, y1: 0, "
        + "        x2: 0, y2: 1, "
        + "        stop: 0 rgba(255,255,255,0), "
        + "        stop: 0.5 rgba(255,255,255,192), "
        + "        stop: 1 rgba(255,255,255,0) "
        + "    ); "
        + "border: 2px solid #8f8f8f;"
        + "margin: 2px 2px 2px 2px;"
        + "}";

    // avoid empty label after startup, before initializing new document:
    iconLabel.pixmap =
            new QIcon("scripts/Reset/Reset.svg").pixmap(
                optionsToolBar.iconSize
            );
    optionsToolBar.addWidget(iconLabel);
    optionsToolBar.addSeparator();
};
