// Auto generated by Testing Dashboard
// File        : scripts/Draw/Circle/CircleTPR/Tests/CircleTPRTest00.js
// Timestamp   : 2015-03-25 11:29:12
// Description : 

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function CircleTPRTest00() {
    TdbTest.call(this, 'scripts/Draw/Circle/CircleTPR/Tests/CircleTPRTest00.js');
}

CircleTPRTest00.prototype = new TdbTest();

CircleTPRTest00.prototype.test00 = function() {
    qDebug('running CircleTPRTest00.test00()...');
    this.setUp();
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::LineToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::LineToolsPanel::Line2PButton');
    this.setZoom(10, new RVector(18.7, 8.7, 0, true));
    var p = new RVector(9.9, 10.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(18.7, 8.7, 0, true));
    var p = new RVector(29.9, 19.8);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(26.4, 10.5);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(25.7, 10.9);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(24.5, 11);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::CircleToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::CircleToolsPanel::CircleTPRButton');
    this.setToolOption('CircleTPR/Radius', '25');
    this.updateToolOptions();
    this.setZoom(10, new RVector(18.7, 8.7, 0, true));
    var p = new RVector(19.6, 14.7);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(18.7, 8.7, 0, true));
    var p = new RVector(29.8, 10);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(10, new RVector(18.7, 8.7, 0, true));
    var p = new RVector(28.6, 16.1);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(36.3, 19.4);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('CircleTPRTest00_000.dxf');
    this.tearDown();
    qDebug('finished CircleTPRTest00.test00()');
};

