function MyRectangle() {
}

MyRectangle.prototype.toString = function() {
	print("MyRectangle.js:", "toString(): ");
}

MyRectangle.init = function(formWidget) {
    if (!isNull(formWidget)) {
        MyRectangle.widgets = getWidgets(formWidget);
    }
};

MyRectangle.generate = function(di, file) {
    var w = InsertScriptItem.getWidget(file);
    var mleWidth = MyRectangle.widgets["mleWidth"];
    var mleHeight = MyRectangle.widgets["mleHeight"];
	if (!mleWidth.isValid() || !mleHeight.isValid()) {
		return undefined;
	}
    return MyRectangle.getOperation(di, mleWidth.getValue(), mleHeight.getValue());
}

MyRectangle.generatePreview = function(di, iconSize) {
	return MyRectangle.getOperation(di, 100, 50);
}

MyRectangle.getOperation = function(di, width, height) {
    // the dots:
	var va = new Array(new RVector(0, 0), new RVector(0, height),
			new RVector(width, height), new RVector(width, 0));	

    // the dot connection pairs:
    //
    //    1 +----------------+ 2
    //      |                |
    //      |                |
    //    0 +----------------+ 3
    //
    var linePairs = [[0,1], [1,2], [2,3], [3,0], [1,3], [0,2]];
	
    // connect the dots:
    var operation = new RAddObjectsOperation(false);
    for (var i = 0; i < linePairs.length; ++i) {
        var lineData = new RLineData(va[linePairs[i][0]], va[linePairs[i][1]]);
		var line = new RLineEntity(di.getDocument(), lineData);
		operation.addObject(line);
	}
	return operation;
}
