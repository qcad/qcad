// Auto generated by Testing Dashboard
// File        : scripts/Modify/BreakOut/Tests/BreakOutTest06.js
// Timestamp   : 2015-11-04 21:41:14
// Description : 

include('scripts/Developer/TestingDashboard/TdbTest.js');

function BreakOutTest06() {
    TdbTest.call(this, 'scripts/Modify/BreakOut/Tests/BreakOutTest06.js');
}

BreakOutTest06.prototype = new TdbTest();

BreakOutTest06.prototype.test00 = function() {
    qDebug('running BreakOutTest06.test00()...');
    this.setUp();
    this.importFile('scripts/Modify/BreakOut/Tests/data/line_xline_ray2.dxf');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::ModifyToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::ModifyToolsPanel::BreakOutProButton');
    this.setToolOption('BreakOutPro/RemoveSegment', 'true');
    this.setToolOption('BreakOutPro/LineMode', 'false');
    this.setZoom(11.120567375886525, new RVector(-3.74235, 2.37309, 0, true));
    var p = new RVector(23.52551, 24.693878);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(11.120567375886525, new RVector(-3.74235, 2.37309, 0, true));
    var p = new RVector(23.52551, 20.017857);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(11.120567375886525, new RVector(-3.74235, 2.37309, 0, true));
    var p = new RVector(23.25574, 10.216199);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(11.120567375886525, new RVector(-3.74235, 2.37309, 0, true));
    var p = new RVector(23.075893, 6.799107);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(15.792092, 14.532526);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(15.792092, 14.532526);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    var p = new RVector(15.882015, 14.982143);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('BreakOutTest06_000.dxf');
    this.tearDown();
    qDebug('finished BreakOutTest06.test00()');
};

