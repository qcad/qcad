include('scripts/Developer/TestingDashboard/TdbTest.js');

function EllipseArcCPPATest10() {
    TdbTest.call(this, 'scripts/Draw/Ellipse/EllipseArcCPPA/Tests/EllipseArcCPPATest10.js');
}

EllipseArcCPPATest10.prototype = new TdbTest();

EllipseArcCPPATest10.prototype.test00 = function() {
    qDebug('running EllipseArcCPPATest10.test00()...');
    this.setUp();

    var TWO_PI = Math.PI * 2;

    var axisAngles = [
                0,                   // horizontal
                Math.PI / 4,         // 45
                Math.PI / 2,         // vertical
                (3 * Math.PI) / 4,   // 135
                Math.PI,             // 180
                (7 * Math.PI) / 4    // 315
            ];

    var ratios = [
                1,      // circle
                0.8,
                0.5,
                0.2,
                0.05    // extremely flat
            ];

    // Semi-major axis lengths (<= 5 so each ellipse stays in its 10x10 cell)
    //var lengthOptions = [2, 3.5, 5];

    var startParams = [
                0,
                0.001,          // almost 0
                -0.5,           // negative
                Math.PI / 4,
                1.0,
                TWO_PI - 0.1    // near 2 PI
            ];

    var spans = [
                TWO_PI,           // full ellipse
                TWO_PI - 0.001,   // almost full
                Math.PI,          // half
                Math.PI / 2,      // quarter
                0.1,              // small arc
                0.01,             // tiny arc
                3 * TWO_PI        // >1 full revolution
            ];

    var x = -200;
    var y = 200;

    for (var i=0; i<axisAngles.length; i++) {
        var axisAngle = axisAngles[i];
        for (var j=0; j<ratios.length; j++) {
            var ratio = ratios[j];
            var majorLength = 4.0;
            for (var m=0; m<startParams.length; m++) {
                var startParam = startParams[m];
                for (var n=0; n<spans.length; n++) {
                    var span = spans[n];

                    var cp = new RVector(x, y);
                    var mp = RVector.createPolar(majorLength, axisAngle);

                    addEllipse(cp, mp, ratio, startParam, startParam + span, false);

                    x+=10;
                    if (x > 200) {
                        x = -200;
                        y -= 10;
                    }
                }
            }
        }
    }

    this.selectAll();
    this.triggerCommand('boundingbox');

    //this.verifyDrawing('EllipseArcCPPATest10_000.dxf');
    this.tearDown();
    qDebug('finished EllipseArcCPPATest10.test00()');
};

