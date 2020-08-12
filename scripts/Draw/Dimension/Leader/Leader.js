/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("scripts/Draw/Dimension/Dimension.js");

/**
 * \class Leader
 * \brief Draw leader, segment by segment.
 * \ingroup ecma_draw_dimension
 */
function Leader(guiAction) {
    Dimension.call(this, guiAction);

    this.arrowHead = true;
    this.leaderEntity = undefined;
    this.segment = undefined;
    this.arrowBlockId = RBlock.INVALID_ID;

    this.setUiOptions("Leader.ui");
}

Leader.prototype = new Dimension();

Leader.State = {
    SettingFirstVertex : 0,
    SettingNextVertex : 1
};

Leader.prototype.beginEvent = function() {
    Dimension.prototype.beginEvent.call(this);

    this.setState(Leader.State.SettingFirstVertex);
    this.updateButtonStates();
};

Leader.prototype.setState = function(state) {
    Dimension.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Leader.State.SettingFirstVertex:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        var trFirstVertex = qsTr("Arrow position");
        this.setCommandPrompt(trFirstVertex);
        this.setLeftMouseTip(trFirstVertex);
        this.setRightMouseTip(EAction.trCancel);
        this.segment = undefined;
        EAction.showSnapTools();
        break;

    case Leader.State.SettingNextVertex:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        var trNextVertex = qsTr("Next vertex");
        this.setCommandPrompt(trNextVertex);
        this.setLeftMouseTip(trNextVertex);
        this.setRightMouseTip(EAction.trDone);
        EAction.showSnapTools();
        break;
    }
};

Leader.prototype.showUiOptions = function(resume) {
    Draw.prototype.showUiOptions.call(this, resume);
    this.updateButtonStates();
};

Leader.prototype.escapeEvent = function() {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Leader.State.SettingFirstVertex:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Leader.State.SettingNextVertex:
        if (!isNull(this.leaderEntity)) {
            // remove leader with one or zero vertices:
            if (this.leaderEntity.countVertices()<=1) {
                var op = new RDeleteObjectOperation(this.leaderEntity, false);
                this.applyOperation(op);
            }
        }

        this.setState(Leader.State.SettingFirstVertex);
        this.updateButtonStates();
        break;
    }
};

Leader.prototype.pickCoordinate = function(event, preview) {
    var point, op;
    
    var di = this.getDocumentInterface();
    var document = this.getDocument();

    switch (this.state) {
    // set first vertex, create leader entity:
    case Leader.State.SettingFirstVertex:
        if (!preview) {
            point = event.getModelPosition();

            var leader = new RLeaderEntity(document, new RLeaderData());
            leader.appendVertex(point);
            op = new RAddObjectOperation(leader, this.getToolTitle());
            this.applyOperation(op);
            di.setRelativeZero(point);
            if (!isNull(this.leaderEntity)) {
                this.setState(Leader.State.SettingNextVertex);
            }
        }
        break;

    // set next vertex:
    case Leader.State.SettingNextVertex:
        point = event.getModelPosition();

        // if we have at least one vertex:
        if (!isNull(this.leaderEntity) && this.leaderEntity.countVertices()>0) {
            var appendPoint = this.leaderEntity.getEndPoint();
            this.segment = new RLine(appendPoint, point);

            // append vertex:
            if (!preview) {
                this.leaderEntity.appendVertex(point);
                this.leaderEntity.setArrowHead(this.arrowHead);
            }
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            if (!isNull(op)) {
                this.applyOperation(op);
                di.setRelativeZero(point);
                //this.uncheckArcSegment();
            }
        }
        break;
    }

    if (!preview) {
        this.updateButtonStates();
    }
};

Leader.prototype.getOperation = function(preview) {
    if (isNull(this.leaderEntity)) {
        return undefined;
    }

    // for preview, only add current segment:
    if (preview) {
        if (isNull(this.segment)) {
            return undefined;
        }

        if (this.leaderEntity.countVertices()>1) {
            var entity = new RLineEntity(this.getDocument(), new RLineData(this.segment));
            entity.copyAttributesFrom(this.leaderEntity.data());
            return new RAddObjectOperation(entity, false);
        }
        else {
            // for the first segment, we preview a real leader for the sake
            // of displaying the arrow correctly:
            if (this.arrowBlockId!==RBlock.INVALID_ID) {
                this.leaderEntity.setDimLeaderBlockId(this.arrowBlockId);
            }
            var ld = this.leaderEntity.clone();
            ld.appendVertex(this.segment.getEndPoint());
            ld.setArrowHead(this.arrowHead);
            return new RAddObjectOperation(ld, true, false);
        }
    }
    else {
        return new RAddObjectOperation(this.leaderEntity, this.getToolTitle(), true, false);
    }
};

/**
 * Updates the leader in storage and makes sure that this.leaderEntity
 * points to new new clone of the original entity.
 */
Leader.prototype.applyOperation = function(op) {
    this.leaderEntity = undefined;

    var di = this.getDocumentInterface();
    var document = this.getDocument();
    var transaction = di.applyOperation(op);

    // find out ID of leader, that was added to the document:
    var ids = transaction.getAffectedObjects();
    for (var i=0; i<ids.length; ++i) {
        var id = ids[i];
        var entity = document.queryEntity(id);
        if (isLeaderEntity(entity)) {
            this.leaderEntity = entity;
            break;
        }
    }
};

/**
 * Called when user clicks the 'Undo' button to remove the last added vertex.
 */
Leader.prototype.slotUndo = function() {
    if (isNull(this.leaderEntity)) {
        return;
    }

    var di = this.getDocumentInterface();

    if (this.leaderEntity.countVertices() >= 2) {
        this.leaderEntity.removeLastVertex();
        di.clearPreview();
        var op = this.getOperation(false);
        if (!isNull(op)) {
            this.applyOperation(op);
        }
    }

    this.updateButtonStates();
};

Leader.prototype.slotArrowHeadChanged = function(v) {
    var di = this.getDocumentInterface();
    this.arrowHead = v;

    if (!isNull(this.leaderEntity)) {
        this.leaderEntity.setArrowHead(this.arrowHead);
    }

    di.clearPreview();
    var op = this.getOperation(false);
    if (!isNull(op)) {
        if (this.leaderEntity.countVertices() >= 2) {
            this.applyOperation(op);
        }
    }
    this.updatePreview();
};

/**
 * Updates the state (enabled / disabled) of the undo button
 * depending on the current progress.
 */
Leader.prototype.updateButtonStates = function() {
    if (isNull(this.leaderEntity)) {
        return;
    }

    var w = objectFromPath("MainWindow::Options::Undo");
    if (this.leaderEntity.countVertices() > 1) {
        w.enabled = true;
    } else {
        w.enabled = false;
    }
};

