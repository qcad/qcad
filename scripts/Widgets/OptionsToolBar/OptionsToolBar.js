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

/**
 * The options toolbar is created and initialized here.
 */
function OptionsToolBar() {
}

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
        h = 42;
    }
    optionsToolBar.setFixedHeight(h);

    var flags = new Qt.ToolBarAreas(Qt.TopToolBarArea | Qt.BottomToolBarArea);
    optionsToolBar.setAllowedAreas(flags);

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
