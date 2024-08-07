// Auto generated by Testing Dashboard
// File        : scripts/Draw/Text/Tests/Text33.js
// Timestamp   : 2021-02-03
// Description : 

include('scripts/Developer/TestingDashboard/TdbTest.js');

function Text33() {
    TdbTest.call(this, 'scripts/Draw/Text/Tests/Text33.js');
}

Text33.prototype = new TdbTest();

Text33.prototype.test00 = function() {
    qDebug('running Text33.test00()...');
    this.setUp();
    this.importFile('scripts/Draw/Text/Tests/data/text33.dxf');
    this.selectAll();
    this.triggerCommand('explode');
    this.verifyDrawing('Text33_000.dxf');
    this.triggerCommand('explode');
    this.deselectAll();
    this.verifyDrawing('Text33_001.dxf');
    this.tearDown();
    qDebug('finished Text33.test00()');
};

