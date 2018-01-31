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

include("../Screencast.js");


/**
 * This action resizes the application window for screencasts.
 */
function ScPrepare(guiAction) {
    EAction.call(this, guiAction);
}

ScPrepare.prototype = new EAction();
ScPrepare.includeBasePath = includeBasePath;

ScPrepare.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.titleBarHeight = 22;

    this.x = 0;
    if (RS.getSystemId()==="osx") {
        this.x = 50;
    }
    this.y = 22;

    this.w = 1280;
    this.targetHeight = 720;
    this.h = this.targetHeight - this.y - this.titleBarHeight;

    this.iconSize = 32;

    var appWin = RMainWindowQt.getMainWindow();
    appWin.resize(this.w,this.h);
    appWin.move(this.x,this.y);

    this.terminate();
};

