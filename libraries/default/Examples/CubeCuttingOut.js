include("scripts/library.js");

function CubeCuttingOut() {
    CubeCuttingOut.size = 10;
    CubeCuttingOut.drawPlates = true;
}

CubeCuttingOut.init = function(formWidget) {
    if (!isNull(formWidget)) {
        CubeCuttingOut.widgets = getWidgets(formWidget);
    }
};

CubeCuttingOut.generate = function(documentInterface, file) {
    CubeCuttingOut.size = parseInt(CubeCuttingOut.widgets["CubeSize"].text, 10);
    if (isNaN(CubeCuttingOut.size)) {
        // can't parse value as integer, set default size
        CubeCuttingOut.size = 10;
    }
    
    if (CubeCuttingOut.widgets["DrawPlates"].checked) {
        CubeCuttingOut.drawPlates = true;
    } else {
        CubeCuttingOut.drawPlates = false;
    }
    
    return CubeCuttingOut.createCuttingOut(documentInterface);
};

CubeCuttingOut.generatePreview = function(documentInterface, iconSize) {
    CubeCuttingOut.size = iconSize / 6;
    CubeCuttingOut.drawPlates = true;
    return CubeCuttingOut.createCuttingOut(documentInterface);
};

CubeCuttingOut.createCuttingOut = function(documentInterface) {
    var addOperation = new RAddObjectsOperation(false);
    
    // create squares
    for ( var i = 0; i < 4; ++i) {
        var pos = new RVector(i * CubeCuttingOut.size, 0);
        CubeCuttingOut.createSquare(documentInterface, addOperation, pos);
    }
    var posTop = new RVector(CubeCuttingOut.size * 2, CubeCuttingOut.size);
    CubeCuttingOut.createSquare(documentInterface, addOperation, posTop);
    var posBottom = new RVector(CubeCuttingOut.size * 2, -CubeCuttingOut.size);
    CubeCuttingOut.createSquare(documentInterface, addOperation, posBottom);
    
    // create plates
    if (CubeCuttingOut.drawPlates) {
        var plates = new Array(
                [ new RVector(4 * CubeCuttingOut.size, 0), 0 ],
                [ new RVector(2 * CubeCuttingOut.size, -3 * CubeCuttingOut.size), 90 ],
                [ new RVector(1 * CubeCuttingOut.size, -4 * CubeCuttingOut.size), 90 ],
                [ new RVector(-2 * CubeCuttingOut.size, -2 * CubeCuttingOut.size), 180 ],
                [ new RVector(-2 * CubeCuttingOut.size, 0), 180 ],
                [ new RVector(1 * CubeCuttingOut.size, 2 * CubeCuttingOut.size), 270 ],
                [ new RVector(0, 3 * CubeCuttingOut.size), 270 ]
        );
        for ( var i = 0; i < plates.length; ++i) {
            var pos = plates[i][0];
            var angle = RMath.deg2rad(plates[i][1]);
            CubeCuttingOut.createPlate(documentInterface, addOperation, pos, angle);
        }
    }
    
    return addOperation;
};

CubeCuttingOut.createSquare = function(documentInterface, addOperation, pos) {
    var va = new Array(
            new RVector(0, 0),
            new RVector(0, CubeCuttingOut.size),
            new RVector(CubeCuttingOut.size, CubeCuttingOut.size),
            new RVector(CubeCuttingOut.size, 0)
    );
    for ( var i = 0; i < va.length; ++i) {
        var v1 = va[i].operator_add(pos);
        var v2 = va[(i + 1) % va.length].operator_add(pos);
        var lineData = new RLineData(v1, v2);
        var line = new RLineEntity(documentInterface.getDocument(), lineData);
        addOperation.addObject(line);
    }
};

CubeCuttingOut.createPlate = function(documentInterface, addOperation, pos, angle) {
    var plateSize = CubeCuttingOut.size / 7;
    var off = plateSize * Math.sqrt(2);
    var va = new Array(
            new RVector(0, 0),
            new RVector(off, off),
            new RVector(off, CubeCuttingOut.size - off),
            new RVector(0, CubeCuttingOut.size)
    );
    for ( var i = 0; i < va.length; ++i) {
        var v1 = va[i].operator_add(pos);
        v1 = v1.rotate(angle);
        var v2 = va[(i + 1) % va.length].operator_add(pos);
        v2 = v2.rotate(angle);
        var lineData = new RLineData(v1, v2);
        var line = new RLineEntity(documentInterface.getDocument(), lineData);
        addOperation.addObject(line);
    }
};
