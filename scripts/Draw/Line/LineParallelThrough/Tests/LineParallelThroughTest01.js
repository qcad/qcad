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
// File        : scripts/Draw/Line/LineParallelThrough/Tests/LineParallelThroughTest01.js
// Timestamp   : 2011-03-08 11:57:22
// Description : Draw parallels to polyline segments

include('scripts/Developer/TestingDashboard/TdbTest.js');

function LineParallelThroughTest01() {
    TdbTest.call(this, 'scripts/Draw/Line/LineParallelThrough/Tests/LineParallelThroughTest01.js');
}

LineParallelThroughTest01.prototype = new TdbTest();

LineParallelThroughTest01.prototype.test00 = function() {
    qDebug('running LineParallelThroughTest01.test00()...');
    this.setUp();
    this.importFile('scripts/Draw/Line/LineParallelThrough/Tests/data/polyline.dxf');
    this.clickOnWidget('MainWindow::MainToolsPanel::LineToolsPanelButton');
    this.clickOnWidget('MainWindow::LineToolsPanel::LineParallelThroughButton');
    this.setToolOption('LineParallelThrough/Number', '1');
    this.updateToolOptions();
    this.setZoom(23.258377425044095, new RVector(8.42069, 4.50195, 0) );
    var p = new RVector(-0.036611, 6.63382);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(23.258377425044095, new RVector(8.42069, 4.50195, 0) );
    var p = new RVector(-1.928403, 7.020777);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(4.778858, 8.052664);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.setZoom(23.258377425044095, new RVector(8.42069, 4.50195, 0) );
    var p = new RVector(4.563882, 9.90146);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(23.258377425044095, new RVector(8.42069, 4.50195, 0) );
    var p = new RVector(4.950839, 11.922237);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(7.960507, 10.030445);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.setZoom(23.258377425044095, new RVector(8.42069, 4.50195, 0) );
    var p = new RVector(13.678877, 8.35363);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(23.258377425044095, new RVector(8.42069, 4.50195, 0) );
    var p = new RVector(17.075502, 4.914009);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(15.742649, 3.065213);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.setZoom(23.258377425044095, new RVector(8.42069, 4.50195, 0) );
    var p = new RVector(14.925739, 2.334294);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(23.258377425044095, new RVector(8.42069, 4.50195, 0) );
    var p = new RVector(17.032507, 2.033327);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(15.441682, 2.592265);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(15.312697, 2.592265);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('LineParallelThroughTest01_000.dxf');
    this.tearDown();
    qDebug('finished LineParallelThroughTest01.test00()');
};

