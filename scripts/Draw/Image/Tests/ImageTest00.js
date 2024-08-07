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
// Auto generated by Testing Dashboard
// File        : scripts/Draw/Image/Tests/ImageTest00.js
// Timestamp   : 2011-08-16 12:01:35
// Description : disabled (needs native open file dialog)

include('scripts/Developer/TestingDashboard/TdbTest.js');

function ImageTest00() {
    TdbTest.call(this, 'scripts/Draw/Image/Tests/ImageTest00.js');
}

ImageTest00.prototype = new TdbTest();

ImageTest00.prototype.test00 = function() {
    return;
    
    qDebug('running ImageTest00.test00()...');
    this.setUp();
    var w = objectFromPath('MainWindow::CadToolBar::MainToolsPanel');
    this.sendMouseEvent(w, QEvent.MouseButtonRelease, new QPoint(35, 418), Qt.LeftButton, 0, 0);
    var w = objectFromPath('MainWindow::CadToolBar::MainToolsPanel');
    this.sendMouseEvent(w, QEvent.MouseButtonPress, new QPoint(35, 418), Qt.LeftButton, 1, 0);
    this.triggerCommand('bitmap');
    this.setToolOption('Image/Width',  [ 262, 0 ] );
    this.setToolOption('Image/KeepProportions', 'true');
    this.setToolOption('Image/Height',  [ 320, 0 ] );
    this.setToolOption('Image/Angle',  [ 0, 0 ] );
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(6.3, 9.5);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(11.2, 7.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.tearDown();
    qDebug('finished ImageTest00.test00()');
};

