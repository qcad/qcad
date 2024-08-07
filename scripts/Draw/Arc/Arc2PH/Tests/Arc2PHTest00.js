// Auto generated by Testing Dashboard
// File        : scripts/Draw/Arc/Arc2PH/Tests/Arc2PHTest00.js
// Timestamp   : 2015-09-25 12:38:50
// Description : 

include('scripts/Developer/TestingDashboard/TdbTest.js');

function Arc2PHTest00() {
    TdbTest.call(this, 'scripts/Draw/Arc/Arc2PH/Tests/Arc2PHTest00.js');
}

Arc2PHTest00.prototype = new TdbTest();

Arc2PHTest00.prototype.test00 = function() {
    qDebug('running Arc2PHTest00.test00()...');
    this.setUp();
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::ArcToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::ArcToolsPanel::Arc2PHButton');
    this.setToolOption('Arc2PH/Height', '10');
    this.setToolOption('Arc2PH/Direction', 'Clockwise');
    this.updateToolOptions();
    this.setToolOption('Arc2PH/Height', '10');
    this.setToolOption('Arc2PH/Direction', 'Clockwise');
    this.updateToolOptions();
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(0.275161, 0.605633);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(100.241848, 0.374228);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Arc2PH/Height', '20');
    this.setToolOption('Arc2PH/Direction', 'Clockwise');
    this.updateToolOptions();
    this.setToolOption('Arc2PH/Height', '20');
    this.setToolOption('Arc2PH/Direction', 'Clockwise');
    this.updateToolOptions();
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(-0.419052, 1.068442);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(100.241848, 0.142824);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Arc2PH/Height', '30');
    this.setToolOption('Arc2PH/Direction', 'Clockwise');
    this.updateToolOptions();
    this.setToolOption('Arc2PH/Height', '30');
    this.setToolOption('Arc2PH/Direction', 'Clockwise');
    this.updateToolOptions();
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(-0.187648, 0.605633);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(100.936061, 0.374228);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Arc2PH/Height', '40');
    this.setToolOption('Arc2PH/Direction', 'Clockwise');
    this.updateToolOptions();
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(0.043757, 0.837037);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(99.779039, -0.551389);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setToolOption('Arc2PH/Height', '50');
    this.setToolOption('Arc2PH/Direction', 'CounterClockwise');
    this.updateToolOptions();
    this.setToolOption('Arc2PH/Height', '50');
    this.setToolOption('Arc2PH/Direction', 'CounterClockwise');
    this.updateToolOptions();
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(100.241848, -0.319985);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(4.321439596364558, new RVector(7.59259, 12.8158, 0, true));
    var p = new RVector(-0.650457, 0.374228);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.verifyDrawing('Arc2PHTest00_000.dxf');
    this.tearDown();
    qDebug('finished Arc2PHTest00.test00()');
};

