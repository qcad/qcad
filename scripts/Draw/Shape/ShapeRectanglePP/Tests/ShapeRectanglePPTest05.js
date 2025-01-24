// Auto generated by Testing Dashboard
// File        : scripts/Draw/Shape/ShapeRectanglePP/Tests/ShapeRectanglePPTest05.js
// Timestamp   : 2025-01-22 14:16:55
// Description : 

include('scripts/Developer/TestingDashboard/TdbTest.js');

function ShapeRectanglePPTest05() {
    TdbTest.call(this, 'scripts/Draw/Shape/ShapeRectanglePP/Tests/ShapeRectanglePPTest05.js');
}

ShapeRectanglePPTest05.prototype = new TdbTest();

ShapeRectanglePPTest05.prototype.test00 = function() {
    qDebug('running ShapeRectanglePPTest05.test00()...');
    this.setUp();
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::ShapeToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::ShapeToolsPanel::ShapeRectanglePPButton');
    this.setToolOption('Shape/CreatePolyline', 'true');
    this.setToolOption('Shape/Fill', 'true');
    this.setToolOption('Shape/RoundCorners', 'false');
    this.setToolOption('Shape/Radius', '1');
    this.setToolOption('ShapeRectanglePP/Rotate', 'false');
    this.setToolOption('ShapeRectanglePP/Rotation', '0');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5,5));
    var p = new RVector(10.1, 9.8);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(39.9, 29.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(51.5, 40);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('ShapeRectanglePPTest05_000.dxf');
    this.tearDown();
    qDebug('finished ShapeRectanglePPTest05.test00()');
};

