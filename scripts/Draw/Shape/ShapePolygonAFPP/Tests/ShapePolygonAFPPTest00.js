// Auto generated by Testing Dashboard
// File        : scripts/Draw/Shape/ShapePolygonAFPP/Tests/ShapePolygonAFPPTest00.js
// Timestamp   : 2015-04-27 10:52:09
// Description : 

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function ShapePolygonAFPPTest00() {
    TdbTest.call(this, 'scripts/Draw/Shape/ShapePolygonAFPP/Tests/ShapePolygonAFPPTest00.js');
}

ShapePolygonAFPPTest00.prototype = new TdbTest();

ShapePolygonAFPPTest00.prototype.test00 = function() {
    qDebug('running ShapePolygonAFPPTest00.test00()...');
    this.setUp();
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::ShapeToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::ShapeToolsPanel::ShapePolygonAFPPButton');
    this.setToolOption('Shape/CreatePolyline', 'false');
    this.setToolOption('Shape/Fill', 'false');
    this.setToolOption('ShapePolygonAFPP/Corners', '3');
    this.setToolOption('ShapePolygonAFPP/CornerToCorner', 'false');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0, true));
    var p = new RVector(5, 14.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0, true));
    var p = new RVector(4.8, 25);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Shape/CreatePolyline', 'false');
    this.setToolOption('Shape/Fill', 'false');
    this.setToolOption('ShapePolygonAFPP/Corners', '4');
    this.setToolOption('ShapePolygonAFPP/CornerToCorner', 'false');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0, true));
    var p = new RVector(19.8, 15.2);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5, 5, 0, true));
    var p = new RVector(20.1, 24.8);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Shape/CreatePolyline', 'false');
    this.setToolOption('Shape/Fill', 'false');
    this.setToolOption('ShapePolygonAFPP/Corners', '4');
    this.setToolOption('ShapePolygonAFPP/CornerToCorner', 'true');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0, true));
    var p = new RVector(34.7, 14.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Shape/CreatePolyline', 'true');
    this.setToolOption('Shape/Fill', 'false');
    this.setToolOption('ShapePolygonAFPP/Corners', '4');
    this.setToolOption('ShapePolygonAFPP/CornerToCorner', 'true');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5, 5, 0, true));
    var p = new RVector(34.8, 24.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.verifyDrawing('ShapePolygonAFPPTest00_000.dxf');
    var p = new RVector(25.6, 11.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(25.4, 11.6);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.tearDown();
    qDebug('finished ShapePolygonAFPPTest00.test00()');
};

