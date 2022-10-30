// Auto generated by Testing Dashboard
// File        : scripts/Edit/CopyWithReference/Tests/CopyWithReferenceTest01.js
// Timestamp   : 2022-04-29 22:31:39
// Description : 

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function CopyWithReferenceTest01() {
    TdbTest.call(this, 'scripts/Edit/CopyWithReference/Tests/CopyWithReferenceTest01.js');
}

CopyWithReferenceTest01.prototype = new TdbTest();

CopyWithReferenceTest01.prototype.test00 = function() {
    qDebug('running CopyWithReferenceTest01.test00()...');
    this.setUp();
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::LineToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::LineToolsPanel::Line2PButton');
    this.setZoom(10, new RVector(5,5));
    var p = new RVector(10, 39.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5,5));
    var p = new RVector(20.2, 39.8);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(5,5));
    var p = new RVector(20.1, 29.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(31.6, 33);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(31.7, 33.8);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(31.3, 34);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.selectAll();
    TdbTest.clickOnWidget('MainWindow::EditToolBar::ToolButtonCopyWithReference');
    this.setZoom(10, new RVector(5,5));
    var p = new RVector(20.1, 40.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    TdbTest.clickOnWidget('MainWindow::EditToolBar::ToolButtonPaste');
    this.setToolOption('Paste/Rotation', '0');
    this.setToolOption('Paste/Scale', '1');
    this.setToolOption('Paste/FlipHorizontal', 'false');
    this.setToolOption('Paste/FlipVertical', 'true');
    this.setToolOption('Paste/ToCurrentLayer', 'false');
    this.setToolOption('Paste/OverwriteLayers', 'false');
    this.setToolOption('Paste/OverwriteBlocks', 'false');
    this.updateToolOptions();
    this.setToolOption('Paste/Rotation', '0');
    this.setToolOption('Paste/Scale', '1');
    this.setToolOption('Paste/FlipHorizontal', 'false');
    this.setToolOption('Paste/FlipVertical', 'true');
    this.setToolOption('Paste/ToCurrentLayer', 'false');
    this.setToolOption('Paste/OverwriteLayers', 'false');
    this.setToolOption('Paste/OverwriteBlocks', 'false');
    this.updateToolOptions();
    this.setZoom(10, new RVector(5,5));
    var p = new RVector(19.5, 50.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(37.4, 51.2);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('CopyWithReferenceTest01_000.dxf');
    this.tearDown();
    qDebug('finished CopyWithReferenceTest01.test00()');
};

