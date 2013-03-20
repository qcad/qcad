include("scripts/library.js");

function DiningTable() {
}

DiningTable.prototype.toString = function() {
    print("DiningTable");
};

/**
 * Initializes the UI widget for data input. The widget already exists when
 * this is called (formWidget).
 */
DiningTable.init = function(formWidget) {
    if (!isNull(formWidget)) {
        DiningTable.widgets = getWidgets(formWidget);
        var dlAngle = DiningTable.widgets["dlAngle"];
        var mleChairAngle = DiningTable.widgets["mleChairAngle"];

        DiningTable.widgets["lbNumberOfChairs"].text = DiningTable.widgets["hsNumberOfChairs"].value;

        var cb = DiningTable.widgets["rbCustomRotation"];
        if (!cb.checked) {
            DiningTable.widgets["lbChairAngle"].visible = false;
            mleChairAngle.visible = false;
            dlAngle.visible = false;
        }

        dlAngle.valueChanged.connect(function(value) {
            dlAngle.blockSignals(true);
            mleChairAngle.text = 360 - value;
            dlAngle.blockSignals(false);
        });

        mleChairAngle.textChanged .connect(function(text) {
            dlAngle.blockSignals(true);
            dlAngle.value = Math.abs(360 - text);
            dlAngle.blockSignals(false);
        });
    }
};

/**
 * Called to generate the inserted part.
 * \return operation (RAddObjectsOperation).
 */
DiningTable.generate = function(di, file) {
    var w = DiningTable.widgets["mleTableWidth"];
    var l = DiningTable.widgets["mleTableLength"];
    if (!w.isValid() || !l.isValid()) {
        return undefined;
    }
    var noOfChairs = DiningTable.widgets["hsNumberOfChairs"];
    var comboHeadFoot = DiningTable.widgets["comboHeadFoot"];
    var head = false;
    var foot = false;
    if(comboHeadFoot.currentText == "Head" || comboHeadFoot.currentText == "Both"){
        head = true;
    }
    if(comboHeadFoot.currentText == "Foot" || comboHeadFoot.currentText == "Both"){
        foot = true;
    }

    var cw = DiningTable.widgets["mleChairWidth"].getValue();
    var cl = DiningTable.widgets["mleChairLength"].getValue();

    return DiningTable.createTable(di, l.getValue(), w.getValue(),
            noOfChairs.value, head, foot, cw, cl);
};

/**
 * Called to generate an icon for this script item.
 * \return operation (RAddObjectsOperation).
 */
DiningTable.generatePreview = function(di, iconSize) {
    return DiningTable.createTable(di, 160, 100, 4, true, false, 36, 45);
};

DiningTable.createTable = function(di, length, width, numberOfChairs, head,
        foot, chairWidth, chairLength) {
//    length = DiningTable.tableLength;
//    width = DiningTable.tableWidth;

//    var pasteOperation = new RPasteOperation(DiningTable.doc);
    var addOperation = new RAddObjectsOperation(false);

//    var va = new Array(new RVector(0, 0), new RVector(0, width),
//            new RVector(length, width), new RVector(length, 0));
//    DiningTable.vectorArrayToLines(addOpertaion, va);
//    di.applyOperation(addOpertaion);

    var va = new Array(new RVector(0, 0), new RVector(0, width),
            new RVector(length, width), new RVector(length, 0));
    DiningTable.vectorArrayToLines(di, addOperation, va);

    var numOnSide = Math.ceil(numberOfChairs / 2);
    var space = (length - (numOnSide * chairWidth)) / (numOnSide + 1);
    for ( var i = 0; i < numberOfChairs; ++i) {
        var xoff = (chairWidth + space) * i / 2 + chairWidth / 2;
        DiningTable.createChair(di, addOperation, new RVector(space + xoff, 0), 0,
                chairWidth, chairLength);
        ++i;
        if (i == numberOfChairs) {
            break;
        }
        DiningTable.createChair(di, addOperation, new RVector(space + xoff, width),
                180, chairWidth, chairLength);
    }

    if (head) {
        var yoff = width / 2;
        DiningTable.createChair(di, addOperation, new RVector(0, yoff), -90,
                chairWidth, chairLength);
    }

    if (foot) {
        var yoff = width / 2;
        var xoff = length;
        DiningTable.createChair(di, addOperation, new RVector(xoff, yoff), 90,
                chairWidth, chairLength);
    }

//    DiningTable.di.applyOperation(DiningTable.addOperation);

    return addOperation;
//    return pasteOperation;
};

DiningTable.createChair = function(di, addOperation, offset, angle, width, length){
    var l2 = length / 2;
    var w2 = width / 2;
    var va = new Array(
            new RVector(-w2, -l2),
            new RVector(-w2, l2),
            new RVector(w2, l2),
            new RVector(w2, -l2),
            new RVector(-w2, -l2),
            new RVector(w2, -l2 + 8),
            new RVector(-w2, -l2 + 8),
            new RVector(w2, -l2)
    );

    if (angle == undefined) {
        angle = 0;
    }

//    var center = va[2].operator_subtract(va[0]);
//    center.operator_divide_assign(2);
//    center.move(offset);
    var center = offset;
    var randomAngle = Math.random() * 30 - 15;

    for ( var i = 0; i < va.length; ++i) {
        va[i] = va[i].move(offset);
        va[i] = va[i].rotate(RMath.deg2rad(angle), center);

        if (DiningTable.widgets == undefined) {
            continue;
        }

        var rb = DiningTable.widgets["rbRandomRotation"];
        if (!isNull(rb) && rb.checked) {
            va[i] = va[i].rotate(RMath.deg2rad(randomAngle), center);
        }

        var rb = DiningTable.widgets["rbCustomRotation"];
        if (rb != undefined && rb.checked) {
            var val = DiningTable.widgets["mleChairAngle"].getValue();
            va[i] = va[i].rotate(RMath.deg2rad(val), center);
        }

        var cb = DiningTable.widgets["cbDetailed"];
        if (cb != undefined && cb.checked && i < 4) {
            var circleData = new RCircleData(va[i], 3.5);
            var circle = new RCircleEntity(di.getDocument(), circleData);
            addOperation.addObject(circle);
        }
    }
    DiningTable.vectorArrayToLines(di, addOperation, va);
};

DiningTable.vectorArrayToLines = function(di, addOperation, va) {
    for (var i = 0; i < va.length; ++i) {
        var lineData = new RLineData(va[i], va[(i + 1) % va.length]);
        var line = new RLineEntity(di.getDocument(), lineData);
        addOperation.addObject(line);
    }
};
