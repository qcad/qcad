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
// File        : scripts/Modify/Rotate2/Tests/Rotate2Test05.js
// Timestamp   : 2011-08-08 15:10:01
// Description : Rotate 2 using a polyline

include('scripts/Developer/TestingDashboard/TdbTest.js');

function Rotate2Test05() {
    TdbTest.call(this, 'scripts/Modify/Rotate2/Tests/Rotate2Test05.js');
}

Rotate2Test05.prototype = new TdbTest();

Rotate2Test05.prototype.test00 = function() {
    qDebug('running Rotate2Test05.test00()...');
    this.setUp();
    var w = objectFromPath('MainWindow::CadToolBar::MainToolsPanel');
    this.sendMouseEvent(w, QEvent.MouseButtonPress, new QPoint(29, 435), Qt.LeftButton, 1, 0);
    var w = objectFromPath('MainWindow::CadToolBar::MainToolsPanel');
    this.sendMouseEvent(w, QEvent.MouseButtonRelease, new QPoint(29, 435), Qt.LeftButton, 0, 0);
    this.importFile('scripts/Modify/Rotate2/Tests/data/polyline.dxf');
    this.setZoom(9.066512021751855, new RVector(27.9049, 23.7136, 0) );
    var p = new RVector(18.419432, 3.639768);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.triggerCommand('rotate2');
    this.setToolOption('TranslateRotate/PrimaryAngle',  [ 30, 0 ] );
    this.setToolOption('TranslateRotate/SecondaryAngle',  [ 10, 0 ] );
    this.setToolOption('TranslateRotate/NumberOfCopies',  [ 8, 0 ] );
    this.updateToolOptions();
    this.setZoom(9.066512021751855, new RVector(27.9049, 23.7136, 0) );
    var p = new RVector(0.220592, -0.220592);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(9.066512021751855, new RVector(27.9049, 23.7136, 0) );
    var p = new RVector(-0.220592, 0.220592);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.dlgStart();
    this.dlgAppendCode('var map = new MapCompat()');
    this.dlgAppendCode("map.put('DialogOpenedByTdb/groupBox', 'MultipleCopies')");
    this.dlgAppendCode("map.put('DialogOpenedByTdb/NumberOfCopies',  [ 8, 0 ] )");
    this.dlgAppendCode("map.put('DialogOpenedByTdb/PrimaryAngle',  [ 30, 0 ] )");
    this.dlgAppendCode("map.put('DialogOpenedByTdb/SecondaryAngle',  [ 10, 0 ] )");
    this.dlgAppendCode("map.put('DialogOpenedByTdb/UseCurrentAttributes', false)");
    this.dlgAppendCode("WidgetFactory.restoreState(dialog, 'DialogOpenedByTdb', undefined, false, undefined, map)");
    this.dlgEnd();
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.verifyDrawing('Rotate2Test05_000.dxf');
    this.tearDown();
    qDebug('finished Rotate2Test05.test00()');
};

