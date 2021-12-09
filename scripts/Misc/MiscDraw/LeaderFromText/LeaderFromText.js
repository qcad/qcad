include("scripts/EAction.js");
include("scripts/library.js");

function LeaderFromText(guiAction) {
    EAction.call(this, guiAction);
}

LeaderFromText.prototype = new EAction();

LeaderFromText.prototype.verifySelectedEntity = function (doc, entityIds) {
    // check selected one entity
    if (entityIds.length === 1) {
        
        // check selected text entity
        if (isTextEntity(doc.queryEntity(entityIds[0]))) {
            return "ОК";
        }
        return "Select text object!"
    }
    return "Select one text object!"
}

LeaderFromText.prototype.setLeftLeader = function (leader, vectorArr, offset) {
    leader.appendVertex(new RVector(vectorArr[0].getX() - offset, vectorArr[0].getY() - offset, 0));
    leader.appendVertex(vectorArr[0]);
    leader.appendVertex(vectorArr[1]);
    return leader;
}

LeaderFromText.prototype.setRightLeader = function (leader, vectorArr, offset) {
    leader.appendVertex(new RVector(vectorArr[1].getX() + offset, vectorArr[1].getY() - offset, 0));
    leader.appendVertex(vectorArr[1]);
    leader.appendVertex(vectorArr[0]);
    return leader;
}

LeaderFromText.prototype.beginEvent = function () {
    EAction.prototype.beginEvent.call(this);

    var doc = this.getDocument();
    var di = this.getDocumentInterface();
    var op = new RAddObjectsOperation();

    var ids = doc.querySelectedEntities();

    // checking the validity of an entity
    var msg = this.verifySelectedEntity(doc, ids);
    if (msg != "ОК") {
        EAction.handleUserWarning(qsTr(msg));
        this.terminate();
        return;
    }
   
    var entity = doc.queryEntity(ids[0]);
    var td = entity.getData();
    var th = entity.getTextHeight();

    // get the enlarged bounding box (10% of the text height)
    var box = td.getBoundingBox().grow(th*0.1);
    var vectorArr = box.getCorners2d();

    // delete 2 top corners
    vectorArr.pop();
    vectorArr.pop();

    // find the index of the point closest to the alignment point
    var index = entity.getAlignmentPoint().getClosestIndex2D(vectorArr);

    // choose the right or left leader depending on the alignment point
    var leader = new RLeaderEntity(doc, new RLeaderData());
    if (index == 0) {
        op.addObject(this.setLeftLeader(leader, vectorArr, th));
    } else {
        op.addObject(this.setRightLeader(leader, vectorArr, th));
    }

    di.applyOperation(op);
    EAction.handleUserMessage(qsTr("Leader was created successfully"));
    this.terminate();
};
