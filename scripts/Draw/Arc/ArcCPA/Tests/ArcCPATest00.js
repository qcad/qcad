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
// File        : scripts/Draw/Arc/ArcCPA/Tests/ArcCPATest00.js
// Timestamp   : 2011-03-01 10:57:20
// Description : 3 arcs clockwise, 3 arcs counter clockwise

include('scripts/Developer/TestingDashboard/TdbTest.js');

function ArcCPATest00() {
    TdbTest.call(this, 'scripts/Draw/Arc/ArcCPA/Tests/ArcCPATest00.js');
}

ArcCPATest00.prototype = new TdbTest();

ArcCPATest00.prototype.test00 = function() {
    qDebug('running ArcCPATest00.test00()...');
    this.setUp();
    this.clickOnWidget('MainWindow::MainToolsPanel::ArcToolsPanelButton');
    this.clickOnWidget('MainWindow::ArcToolsPanel::ArcCPAButton');
    this.setToolOption('ArcCPA/Direction', 'CounterClockwise');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(9.9, 10.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(9.9, 10.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(20, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(20, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(20.2, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(20.2, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(10.1, -0.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(10.1, -0.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(10, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(10, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(18, 9.8);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(18, 9.8);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(10, 17.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(10, 17.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(10, 2);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(10, 2);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(10, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(10, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(16.1, 10.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(16.1, 10.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(4.2, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(4.2, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(10, 4);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(10, 4);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('ArcCPA/Direction', 'Clockwise');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(40.1, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(40.1, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(30.1, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(30.1, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(30.1, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(30.1, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(40, -0.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(40, -0.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(39.9, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(39.9, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(31.9, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(31.9, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(40, 17.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(40, 17.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(40, 2);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(40, 2);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(39.9, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(39.9, 9.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(34.1, 10.2);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(34.1, 10.2);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(46, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(46, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0) );
    var p = new RVector(39.9, 4.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(39.9, 4.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(24.4, 3.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    var p = new RVector(24.4, 3.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('ArcCPATest00_000.dxf');
    this.tearDown();
    qDebug('finished ArcCPATest00.test00()');
};

