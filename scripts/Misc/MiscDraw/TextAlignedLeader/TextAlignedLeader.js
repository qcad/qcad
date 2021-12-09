include("scripts/EAction.js");
include("scripts/library.js");

function TextAlignedLeader(guiAction) {
    EAction.call(this, guiAction);

    this.doc = undefined;
    this.di = undefined;
    this.op = undefined;
    this.firstVertex = undefined;
    this.entityId = undefined;
};

TextAlignedLeader.prototype = new EAction();

TextAlignedLeader.State = {
    SettingFirstVertex: 0,
    ChoosingEntity: 1
};

// Handler for event beginEvent
TextAlignedLeader.prototype.beginEvent = function () {
    EAction.prototype.beginEvent.call(this);

    this.doc = this.getDocument();
    this.di = this.getDocumentInterface();
    this.op = new RAddObjectsOperation();
    this.setState(TextAlignedLeader.State.SettingFirstVertex);
};

// Setter for peoperty State 
TextAlignedLeader.prototype.setState = function (state) {
    EAction.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
        case TextAlignedLeader.State.SettingFirstVertex:
            this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
            var trFirstVertex = qsTr("Arrow position");
            this.setCommandPrompt(trFirstVertex);
            this.setLeftMouseTip(trFirstVertex);
            this.setRightMouseTip(EAction.trCancel);
            EAction.showSnapTools();
            break;

        case TextAlignedLeader.State.ChoosingEntity:
            this.getDocumentInterface().setClickMode(RAction.PickEntity);
            var trSelectText = qsTr("Choose text");
            this.setCommandPrompt(trSelectText);
            this.setLeftMouseTip(trSelectText);
            this.setRightMouseTip(EAction.trCancel);
            break;
    };
};

// Handler for event pickCoordinate
TextAlignedLeader.prototype.pickCoordinate = function (event, preview) {
    switch (this.state) {
        case TextAlignedLeader.State.SettingFirstVertex:
            if (!preview) {
                this.firstVertex = event.getModelPosition();
                if (!isNull(this.firstVertex)) {
                    this.setState(TextAlignedLeader.State.ChoosingEntity);
                }
            }
            break;

    };
};

// Handler for event pickEntity
TextAlignedLeader.prototype.pickEntity = function (event, preview) {
    this.entityId = this.getEntityId(event, preview);
    var pos = event.getModelPosition();
    switch (this.state) {
        case TextAlignedLeader.State.ChoosingEntity:
            if (preview) {
                this.updatePreview();
            }
            else {
                this.drawLeader(this.entityId);
            }
            break;
    };

};


TextAlignedLeader.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.doc.queryEntity(this.entityId)) && this.verifyEntity() == "ОК") {
        ret.push(this.entityId);
    }
    return ret;
};

TextAlignedLeader.prototype.verifyEntity = function () {
    if (this.entityId != -1 && isTextEntity(this.doc.queryEntity(this.entityId))) {
        return "ОК";
    }
    return "Choose text";
};

TextAlignedLeader.prototype.setLeftLeader = function (leader, vectorArr) {
    leader.appendVertex(this.firstVertex);
    leader.appendVertex(vectorArr[0]);
    leader.appendVertex(vectorArr[1]);
    return leader;
};

TextAlignedLeader.prototype.setRightLeader = function (leader, vectorArr) {
    leader.appendVertex(this.firstVertex);
    leader.appendVertex(vectorArr[1]);
    leader.appendVertex(vectorArr[0]);
    return leader;
};

TextAlignedLeader.prototype.drawLeader = function (entityId) {

    // checking the validity of an entity
    var msg = this.verifyEntity();
    if (msg != "ОК") {
        EAction.handleUserWarning(qsTr(msg));
        return;
    };

    var entity = this.doc.queryEntity(entityId);
    var td = entity.getData();

    // get the enlarged bounding box (10% of the text height)
    var box = td.getBoundingBox().grow(entity.getTextHeight() * 0.1);
    var vectorArr = box.getCorners2d();

    // delete 2 top corners
    vectorArr.pop();
    vectorArr.pop();

    // find the index of the point closest to the firstVertex
    var index = this.firstVertex.getClosestIndex2D(vectorArr);

    // choose the right or left leader depending on the firstVertex
    var leader = new RLeaderEntity(this.doc, new RLeaderData());
    if (index == 0) {
        this.op.addObject(this.setLeftLeader(leader, vectorArr));
    } else {
        this.op.addObject(this.setRightLeader(leader, vectorArr));
    }

    this.di.applyOperation(this.op);
    EAction.handleUserMessage(qsTr("Leader was created successfully"));
    this.terminate();
};
