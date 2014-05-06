/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("EAction.js");
include("Select/Select.js");
include("Widgets/CadToolBar/CadToolBar.js");

/**
 * \class DefaultAction
 * \brief Default action which is active when no other tool
 * or action is active. Implements basic entity selection 
 * and drag and drop.
 */
function DefaultAction(guiAction) {
    EAction.call(this, guiAction);
}

DefaultAction.prototype = new EAction();

DefaultAction.State = {
    Neutral : 0,
    Dragging : 1,
    SettingCorner2 : 2,
    MovingEntity : 3,
    MovingEntityInBlock : 4,
    SettingEntity : 5,
    MovingReference : 6,
    SettingReference : 7
};

DefaultAction.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.rangePixels = RSettings.getSnapRange();
    this.d1Model = RVector.invalid;
    this.d1Screen = RVector.invalid;
    this.d2Model = RVector.invalid;
    this.d2Screen = RVector.invalid;
    this.di = this.getDocumentInterface();
    this.document = this.getDocument();
    this.setState(DefaultAction.State.Neutral);
    this.blockRefId = RObject.INVALID_ID;
    this.entityInBlockId = RObject.INVALID_ID;
};

DefaultAction.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    var appWin = EAction.getMainWindow();

    if (this.state === DefaultAction.State.MovingReference
            || this.state === DefaultAction.State.SettingReference
            || this.state === DefaultAction.State.MovingEntity
            || this.state === DefaultAction.State.MovingEntityInBlock
            || this.state === DefaultAction.State.SettingEntity) {
        this.di.setClickMode(RAction.PickCoordinate);
        this.setCrosshairCursor();
        EAction.showSnapTools();
    } else {
        this.di.setClickMode(RAction.PickingDisabled);
        this.setArrowCursor();
    }

    switch (this.state) {
    case DefaultAction.State.Neutral:
        this.d1Model = RVector.invalid;
        this.d1Screen = RVector.invalid;
        this.d2Model = RVector.invalid;
        this.d2Screen = RVector.invalid;
        var ltip = qsTr("Select entity or region");
        if (this.di.hasSelection()) {
            ltip += "\n" + qsTr("Move entity or reference");
        }
        this.setLeftMouseTip(ltip);
        this.setRightMouseTip("");
        this.setCommandPrompt();
        break;
    case DefaultAction.State.Dragging:
        this.d2Model = RVector.invalid;
        this.d2Screen = RVector.invalid;
        break;
    case DefaultAction.State.SettingCorner2:
        this.setLeftMouseTip(qsTr("Set second corner"));
        this.setRightMouseTip("");
        break;
    case DefaultAction.State.MovingReference:
    case DefaultAction.State.SettingReference:
        this.setLeftMouseTip(
                qsTr("Specify target point of reference point")
        );
        this.setRightMouseTip("");
        break;
    case DefaultAction.State.MovingEntity:
    case DefaultAction.State.SettingEntity:
        this.setLeftMouseTip(
                qsTr("Specify target point of selection")
        );
        this.setRightMouseTip("");
        break;
    case DefaultAction.State.MovingEntityInBlock:
        this.setLeftMouseTip(
                qsTr("Move entity to desired location")
        );
        this.di.setSnap(new RSnapFree());
        break;
    default:
        break;
    }
};

DefaultAction.prototype.suspendEvent = function() {
    if (!isNull(this.getGuiAction())) {
        this.getGuiAction().setChecked(false);
    }
};

DefaultAction.prototype.resumeEvent = function() {
    EAction.prototype.resumeEvent.call(this);
};

DefaultAction.prototype.mouseMoveEvent = function(event) {
    // we're in the middle of panning: don't do anything:
    if (event.buttons().valueOf() === Qt.MidButton.valueOf() ||
        (event.buttons().valueOf() === Qt.LeftButton.valueOf() &&
         event.modifiers().valueOf() === Qt.ControlModifier.valueOf())) {
         return;
    }

    var view, referencePoint, entityId;
    
    if (isNull(this.rangePixels)) {
        return;
    }

    view = event.getGraphicsView();

    var range = view.mapDistanceFromView(this.rangePixels);
    switch (this.state) {
    case DefaultAction.State.Neutral:
        var screenPosition = event.getScreenPosition();
        referencePoint = view.getClosestReferencePoint(screenPosition, this.rangePixels / 2);
        if (referencePoint.isValid()) {
            this.highlightReferencePoint(referencePoint);
        } else {
            entityId = this.di.getClosestEntity(event.getModelPosition(), range, false);
            if (entityId !== RObject.INVALID_ID && this.document.isEntityEditable(entityId)) {
                this.highlightEntity(entityId);
            }
        }
        break;

    case DefaultAction.State.Dragging:
        this.d2Model = event.getModelPosition();
        this.d2Screen = event.getScreenPosition();
        view = event.getGraphicsView();
        if (!this.d1Screen.equalsFuzzy(this.d2Screen, this.rangePixels / 2)) {
            // if the dragging started on top of a reference point,
            // start moving the reference point:
            referencePoint = view.getClosestReferencePoint(this.d1Screen, this.rangePixels / 2);
            if (referencePoint.isValid()) {
                this.d1Model = referencePoint;
                this.di.setRelativeZero(this.d1Model);
                this.setState(DefaultAction.State.MovingReference);
            } else {
                // if the dragging started on top of an entity,
                // start moving the entity:
                entityId = view.getClosestEntity(this.d1Screen, this.rangePixels, false);

                // in block easy drag and drop:
                if (entityId !== RObject.INVALID_ID) {
                    var doc = this.getDocument();
                    if (!isNull(doc)) {
                        var entity = doc.queryEntityDirect(entityId);
                        if (isBlockReferenceEntity(entity)) {
                            var blockId = entity.getReferencedBlockId();
                            var block = doc.queryBlock(blockId);
                            if (!isNull(block)) {
                                // cursor, mapped to block coordinates:
                                var pBlock = entity.mapToBlock(this.d1Model);
                                var box = new RBox(
                                    pBlock.operator_subtract(new RVector(range,range)),
                                    pBlock.operator_add(new RVector(range,range))
                                );
                                var res = doc.queryIntersectedEntitiesXY(box, true, false, blockId);
                                this.entityInBlockId = doc.queryClosestXY(res, pBlock, range, false);
                                var entityInBlock = doc.queryEntityDirect(this.entityInBlockId);
                                if (!isNull(entityInBlock) && getInBlockEasyDragAndDrop(entityInBlock)) {
                                    this.d1Model = pBlock;
                                    this.blockRefId = entityId;
                                    this.setState(DefaultAction.State.MovingEntityInBlock);
                                    break;
                                }
                            }
                        }
                    }
                }

                if (entityId !== RObject.INVALID_ID && this.document.hasSelection()) {
                    // move start point of dragging operation to closest
                    // reference point:
                    // TODO: use auto snap instead here (optional?):
                    this.d1Model = view.getClosestReferencePoint(entityId, this.d1Screen);
                    this.di.setRelativeZero(this.d1Model);
                    this.setState(DefaultAction.State.MovingEntity);
                } else {
                    // if the dragging started in an empty space,
                    // start box selection:
                    this.setState(DefaultAction.State.SettingCorner2);
                    // make sure one mouse move is enough to get a visible preview 
                    // (for testing, one mouse move event has to be enough):
                    this.mouseMoveEvent(event);
                }
            }
        }
        break;

    case DefaultAction.State.SettingCorner2:
        this.d2Model = event.getModelPosition();
        Select.previewSelectionBox(
            this.getDocumentInterface(),
            new RBox(this.d1Model, this.d2Model),
            this.d1Model.x > this.d2Model.x
        );
        break;

    default:
        break;
    }
};


DefaultAction.prototype.mouseReleaseEvent = function(event) {
    var persistentSelection = RSettings.getBoolValue("GraphicsView/PersistentSelection", false);

    if (event.button() === Qt.LeftButton) {
        switch (this.state) {
        case DefaultAction.State.Dragging:
            var add = false;
            if ((event.modifiers().valueOf() === Qt.ShiftModifier.valueOf()) ||
                (event.modifiers().valueOf() === Qt.ControlModifier.valueOf()) ||
                persistentSelection===true) {

                add = true;
            }
            var view = event.getGraphicsView();
            var range = view.mapDistanceFromView(this.rangePixels);

            var entityId = this.di.getClosestEntity(event.getModelPosition(), range, false);
            //qDebug(entityId);
            if (entityId !== -1) {
                if (add && this.document.isSelected(entityId)) {
                    this.deselectEntity(entityId);
                }
                else {
                    this.selectEntity(entityId, add);
                }
            } else {
                if (!add) {
                    if (persistentSelection===false) {
                        this.di.clearSelection();
                    }
                }
            }
            this.di.clearPreview();
            this.di.repaintViews();
            this.setState(DefaultAction.State.Neutral);
            break;

        case DefaultAction.State.SettingCorner2:
            this.di.clearPreview();
            this.d2Model = event.getModelPosition();

            if ((event.modifiers().valueOf() == Qt.ShiftModifier.valueOf()) ||
                (event.modifiers().valueOf() == Qt.ControlModifier.valueOf()) ||
                persistentSelection===true) {

                // add all entities in window to the selection:
                this.di.selectBoxXY(new RBox(this.d1Model, this.d2Model), true);
            } else {
                // select entities in window only:
                this.di.selectBoxXY(new RBox(this.d1Model, this.d2Model), false);
            }
            // event.setConsumed(true);
            this.setState(DefaultAction.State.Neutral);
            break;

        default:
            break;
        }
    } else if (event.button() == Qt.RightButton) {
        if (this.state!=DefaultAction.State.Neutral) {
            this.di.clearPreview();
            this.di.repaintViews();
            this.setState(DefaultAction.State.Neutral);
        }
        else {
            CadToolBar.back();
        }
    }
};

DefaultAction.prototype.mousePressEvent = function(event) {
    if (event.button() == Qt.LeftButton
            && event.modifiers().valueOf() != Qt.ControlModifier.valueOf()) {
        if (this.state == DefaultAction.State.Neutral) {
            this.d1Model = event.getModelPosition();
            this.d1Screen = event.getScreenPosition();
            this.setState(DefaultAction.State.Dragging);
            this.di.clearPreview();
        }
    }
};

DefaultAction.prototype.mouseDoubleClickEvent = function(event) {
    if (event.button() == Qt.LeftButton && this.state==DefaultAction.State.Neutral) {
        var view = event.getGraphicsView();
        var range = view.mapDistanceFromView(this.rangePixels);
        var entityId = this.di.getClosestEntity(event.getModelPosition(), range, false);
        if (entityId===RObject.INVALID_ID) {
            return;
        }

        this.entityDoubleClicked(entityId);
    }
};

DefaultAction.prototype.escapeEvent = function(event) {
    this.di.clearPreview();
    this.di.repaintViews();
    CadToolBar.back();
    this.setState(DefaultAction.State.Neutral);
};

DefaultAction.prototype.pickCoordinate = function(event, preview) {
    var operation;

    switch (this.state) {
    case DefaultAction.State.MovingReference:
    case DefaultAction.State.SettingReference:
        if (preview) {
            this.d2Model = event.getModelPosition();
            operation = new RMoveReferencePointOperation(this.d1Model, this.d2Model);
            this.di.previewOperation(operation);
        }
        else {
            if (this.state===DefaultAction.State.MovingReference) {
                this.setState(DefaultAction.State.SettingReference);
            }
            else {
                this.d2Model = event.getModelPosition();
                operation = new RMoveReferencePointOperation(this.d1Model, this.d2Model);
                this.di.applyOperation(operation);
                this.di.clearPreview();
                this.di.repaintViews();
                CadToolBar.back();
                this.setState(DefaultAction.State.Neutral);
            }
        }
        break;

    case DefaultAction.State.MovingEntity:
    case DefaultAction.State.SettingEntity:
        if (preview) {
            this.d2Model = event.getModelPosition();
            operation = new RMoveSelectionOperation(this.d1Model, this.d2Model);
            this.di.previewOperation(operation);
        }
        else {
            if (this.state===DefaultAction.State.MovingEntity) {
                this.setState(DefaultAction.State.SettingEntity);
            }
            else {
                this.d2Model = event.getModelPosition();
                operation = new RMoveSelectionOperation(this.d1Model, this.d2Model);
                this.di.applyOperation(operation);
                this.di.clearPreview();
                this.di.repaintViews();
                CadToolBar.back();
                this.setState(DefaultAction.State.Neutral);
            }
        }
        break;

    // easy in block entity drag and drop (point mark labels):
    case DefaultAction.State.MovingEntityInBlock:
        var doc = this.getDocument();
        if (isNull(doc)) {
            break;
        }
        var blockRef = doc.queryEntity(this.blockRefId);
        if (isNull(blockRef)) {
            break;
        }
        this.d2Model = blockRef.mapToBlock(event.getModelPosition());
        var entityInBlock = doc.queryEntity(this.entityInBlockId);
        entityInBlock.move(this.d2Model.operator_subtract(this.d1Model));
        operation = new RAddObjectsOperation();
        operation.addObject(entityInBlock, false);
        if (preview) {
            this.di.previewOperation(operation);
        }
        else {
            doc.removeFromSpatialIndex(blockRef);
            this.di.applyOperation(operation);
            blockRef.update();
            doc.addToSpatialIndex(blockRef);
            this.setState(DefaultAction.State.Neutral);
        }
        break;

    default:
        break;
    }
};

//DefaultAction.prototype.coordinateEvent = function(event) {
//    var operation;

//    switch (this.state) {
//    case DefaultAction.State.MovingReference:
//        this.setState(DefaultAction.State.SettingReference);
//        break;
//    case DefaultAction.State.SettingReference:
//        this.d2Model = event.getModelPosition();
//        operation = new RMoveReferencePointOperation(this.d1Model, this.d2Model);
//        this.di.applyOperation(operation);
//        this.di.clearPreview();
//        this.di.repaintViews();
//        CadToolBar.back();
//        this.setState(DefaultAction.State.Neutral);
//        break;
//    case DefaultAction.State.MovingEntity:
//        this.setState(DefaultAction.State.SettingEntity);
//        break;
//    case DefaultAction.State.MovingEntityInBlock:
//        var doc = this.getDocument();
//        if (isNull(doc)) {
//            break;
//        }
//        var blockRef = doc.queryEntityDirect(this.blockRefId);
//        if (isNull(blockRef)) {
//            break;
//        }
//        this.d2Model = blockRef.mapToBlock(event.getModelPosition());
//        qDebug("moving label from: ", this.d1Model);
//        qDebug("moving label to: ", this.d2Model);
//        var entityInBlock = doc.queryEntity(this.entityInBlockId);
//        entityInBlock.move(this.d2Model.operator_subtract(this.d1Model));
//        operation = new RAddObjectOperation(entityInBlock);
//        //operation = new RMoveSelectionOperation(this.d1Model, this.d2Model);
//        var currentBlockId = doc.getCurrentBlockId();
//        doc.setCurrentBlock(blockRef.getReferencedBlockId());
//        this.di.applyOperation(operation);
//        doc.setCurrentBlock(currentBlockId);
//        //this.di.clearPreview();
//        //this.di.repaintViews();
//        //CadToolBar.back();
//        this.setState(DefaultAction.State.Neutral);
//        break;
//    case DefaultAction.State.SettingEntity:
//        this.d2Model = event.getModelPosition();
//        operation = new RMoveSelectionOperation(this.d1Model, this.d2Model);
//        this.di.applyOperation(operation);
//        this.di.clearPreview();
//        this.di.repaintViews();
//        CadToolBar.back();
//        this.setState(DefaultAction.State.Neutral);
//        break;
//    default:
//        break;
//    }
//};

//DefaultAction.prototype.coordinateEventPreview = function(event) {

//};


/**
 * Called when the mouse cursor hovers over an entity.
 */
DefaultAction.prototype.highlightEntity = function(entityId) {
    if (isNull(this.di)) {
        return;
    }

    this.di.highlightEntity(entityId);
};

/**
 * Called when the mouse cursor hovers over a reference point.
 */
DefaultAction.prototype.highlightReferencePoint = function(referencePoint) {
    if (isNull(this.di)) {
        return;
    }

    this.di.highlightReferencePoint(referencePoint);
};

/**
 * Called when the user deselects a single entity.
 */
DefaultAction.prototype.deselectEntity = function(entityId) {
    if (isNull(this.di)) {
        return;
    }

    this.di.deselectEntity(entityId);
};

/**
 * Called when the user selects a single entity.
 */
DefaultAction.prototype.selectEntity = function(entityId, add) {
    if (isNull(this.di)) {
        return;
    }

    this.di.selectEntity(entityId, add);
};

/**
 * Called when the user selects a single entity.
 */
DefaultAction.prototype.entityDoubleClicked = function(entityId) {
    if (isNull(this.document) || isNull(this.di)) {
        return;
    }

    var entity = this.document.queryEntity(entityId);

    if (isTextEntity(entity) ||
        isAttributeEntity(entity) ||
        isAttributeDefinitionEntity(entity)) {

        include("scripts/Modify/EditText/EditText.js");
        EditText.editText(entity);
    }
    else if (isBlockReferenceEntity(entity)) {
        include("scripts/Block/Block.js");
        Block.editBlock(this.di, entity.getReferencedBlockName());
    }
};
