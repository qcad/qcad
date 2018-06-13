include("scripts/EAction.js");

function ExMinimal2(guiAction) {
    EAction.call(this, guiAction);

    this.pos = undefined;
    this.radius = undefined;

    this.setUiOptions("ExMinimal2.ui");
}

ExMinimal2.prototype = new EAction();

ExMinimal2.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    di.setClickMode(RAction.PickCoordinate);
};

ExMinimal2.prototype.pickCoordinate = function(event, preview) {
    this.pos = event.getModelPosition();

    if (preview) {
        this.updatePreview();
    }
    else {
        this.applyOperation();
    }
};

ExMinimal2.prototype.getOperation = function(preview) {
    if (isNull(this.pos) || isNull(this.radius)) {
        return undefined;
    }

    var doc = this.getDocument();

    var op = new RAddObjectOperation();
    var circle = new RCircle(this.pos, this.radius);
    op.addObject(shapeToEntity(doc, circle));
    return op;
};

ExMinimal2.prototype.slotRadiusChanged = function(v) {
    this.radius = v;
    this.updatePreview();
};

ExMinimal2.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Minimal Example 2"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExMinimal2.js");
    action.setGroupSortOrder(100000);
    action.setSortOrder(0);
    action.setWidgetNames(["ExamplesMenu"]);
};


