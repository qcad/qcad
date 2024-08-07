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
// File        : scripts/Draw/Line/Line2P/Tests/Lines02.js
// Timestamp   : 2011-02-09 14:15:16
// Description : 4 lines, snap to end point / start point, input mouse clicks

include('scripts/Developer/TestingDashboard/TdbTest.js');

function Lines02() {
    TdbTest.call(this, 'scripts/Draw/Line/Line2P/Tests/Lines02.js');
}

Lines02.prototype = new TdbTest();

Lines02.prototype.test00 = function() {
    qDebug('running Lines02.test00()...');
    this.setUp();
    this.clickOnWidget('MainWindow::MainToolsPanel::LineToolsPanelButton');
    this.clickOnWidget('MainWindow::LineToolsPanel::Line2PButton');
    this.zoomTo(-28.95, -21.449999999999996, 28.950000000000003, 21.450000000000006);
    var p = new RVector(-10, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(-10, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.zoomTo(-28.95, -21.449999999999996, 28.950000000000003, 21.450000000000006);
    var p = new RVector(-10, -10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonPress, new QPoint(240, 286), Qt.RightButton, 2, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonRelease, new QPoint(240, 286), Qt.RightButton, 0, 0);
    this.zoomTo(-28.95, -21.449999999999996, 28.950000000000003, 21.450000000000006);
    var p = new RVector(10, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(10, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.zoomTo(-28.95, -21.449999999999996, 28.950000000000003, 21.450000000000006);
    var p = new RVector(20, -10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonPress, new QPoint(489, 316), Qt.RightButton, 2, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonRelease, new QPoint(489, 316), Qt.RightButton, 0, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonPress, new QPoint(106, 175), Qt.RightButton, 2, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonRelease, new QPoint(106, 175), Qt.RightButton, 0, 0);
    this.clickOnWidget('MainWindow::MainToolsPanel::LineToolsPanelButton');
    this.clickOnWidget('MainWindow::LineToolsPanel::Line2PButton');
    this.clickOnWidget('MainWindow::SnapToolsPanel::SnapEndButton');
    this.zoomTo(-28.95, -21.449999999999996, 28.950000000000003, 21.450000000000006);
    var p = new RVector(-10, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(-10, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.zoomTo(-28.95, -21.449999999999996, 28.950000000000003, 21.450000000000006);
    var p = new RVector(10, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonPress, new QPoint(427, 277), Qt.RightButton, 2, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonRelease, new QPoint(427, 277), Qt.RightButton, 0, 0);
    this.zoomTo(-28.95, -21.449999999999996, 28.950000000000003, 21.450000000000006);
    var p = new RVector(20, -10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    var p = new RVector(20, -10);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.zoomTo(-28.95, -21.449999999999996, 28.950000000000003, 21.450000000000006);
    var p = new RVector(-10, -10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonPress, new QPoint(135, 312), Qt.RightButton, 2, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonRelease, new QPoint(135, 312), Qt.RightButton, 0, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonPress, new QPoint(138, 312), Qt.RightButton, 2, 0);
    this.sendMouseEventToGv(QEvent.MouseButtonRelease, new QPoint(138, 312), Qt.RightButton, 0, 0);
    this.verifyDrawing('Lines02_000.dxf');
    this.tearDown();
    qDebug('finished Lines02.test00()');
};

