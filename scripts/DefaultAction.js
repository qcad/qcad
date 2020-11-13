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

include("scripts/EAction.js");
include("scripts/Select/Select.js");
include("scripts/Widgets/CadToolBar/CadToolBar.js");

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
    Dragging : 1,               //*< Started dragging, minor distance, could be simple click at this stage
    SettingCorner2 : 2,         //*< Setting 2nd corner of selection rectangle.
    MovingEntity : 3,           //*< Dragging entity, mouse button is down.
    MovingEntityInBlock : 4,    //*< Dragging entity inside block, mouse button is down.
    SettingEntity : 5,          //*< Setting position of previously dragged entity, mouse button is up.
    MovingReference : 6,        //*< Dragging reference point, mouse button is down.
    SettingReference : 7        //*< Setting position of previously dragged reference point, mouse button is up.
};

DefaultAction.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    //this.snapRangePixels = RSettings.getSnapRange();
    //this.minSnapRangePixels = Math.min(this.snapRangePixels / 2, 10);
    this.pickRangePixels = RSettings.getPickRange();
    this.minPickRangePixels = Math.min(this.pickRangePixels / 2, 10);
    this.d1Model = RVector.invalid;
    this.d1Screen = RVector.invalid;
    this.d2Model = RVector.invalid;
    this.d2Screen = RVector.invalid;
    this.di = this.getDocumentInterface();
    this.document = this.di.getDocument();
    this.setState(DefaultAction.State.Neutral);
    this.blockRefId = RObject.INVALID_ID;
    this.entityInBlockId = RObject.INVALID_ID;

    this.optOutRelativeZeroResume = true;
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

    var tr;
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
        tr = qsTr("Second corner");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip("");
        break;
    case DefaultAction.State.MovingReference:
    case DefaultAction.State.SettingReference:
        tr = qsTr("Target point of reference point");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip("");
        break;
    case DefaultAction.State.MovingEntity:
    case DefaultAction.State.SettingEntity:
        tr = qsTr("Target point of selection");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip("");
        break;
    case DefaultAction.State.MovingEntityInBlock:
        this.setLeftMouseTip(
                qsTr("Move entity to desired location")
        );
        break;
    default:
        break;
    }
};

DefaultAction.prototype.suspendEvent = function() {
    if (!isNull(this.getGuiAction())) {
        this.getGuiAction().setChecked(false);
    }

    EAction.prototype.suspendEvent.call(this);
};

DefaultAction.prototype.resumeEvent = function() {
    EAction.prototype.resumeEvent.call(this);
};

DefaultAction.prototype.mouseMoveEvent = function(event) {
    // we're in the middle of panning:
    // do nothing:
    if (event.buttons().valueOf() === Qt.MidButton.valueOf() ||
        (event.buttons().valueOf() === Qt.LeftButton.valueOf() &&
         event.modifiers().valueOf() === Qt.ControlModifier.valueOf())) {
        return;
    }

    // we're in the middle of choosing something from a context menu:
    // do nothing:
    if (this.waitingForContextMenu) {
        return;
    }

    var view, referencePoint, entityId, range;
    
    if (isNull(this.pickRangePixels)) {
        return;
    }

    view = event.getGraphicsView();

    switch (this.state) {
    case DefaultAction.State.Neutral:
        var screenPosition = event.getScreenPosition();
        referencePoint = view.getClosestReferencePoint(screenPosition, this.minPickRangePixels);
        if (referencePoint.isValid()) {
            this.highlightReferencePoint(referencePoint);
        } else {
            range = view.mapDistanceFromView(this.pickRangePixels);
            var strictRange = view.mapDistanceFromView(10);
            RMouseEvent.setOriginalMousePos(event.globalPos());
            entityId = this.di.getClosestEntity(event.getModelPosition(), range, strictRange, false);
            RMouseEvent.resetOriginalMousePos();
            if (entityId !== RObject.INVALID_ID && this.document.isEntityEditable(entityId)) {
                this.highlightEntity(entityId);
            }
        }
        break;

    case DefaultAction.State.Dragging:
        this.d2Model = event.getModelPosition();
        this.d2Screen = event.getScreenPosition();
        view = event.getGraphicsView();
        if (!this.d1Screen.equalsFuzzy(this.d2Screen, 10 /*this.minPickRangePixels*/)) {
            // if the dragging started on top of a reference point,
            // start moving the reference point:
            referencePoint = view.getClosestReferencePoint(this.d1Screen, this.minPickRangePixels);
            if (referencePoint.isValid() && !referencePoint.isIgnore() && !RSettings.getIgnoreAllReferencePoints() &&
                !referencePoint.isArrow()) {
                this.d1Model = referencePoint;
                this.di.setRelativeZero(this.d1Model);
                this.setState(DefaultAction.State.MovingReference);
            } else {
                // if the dragging started on top of an entity,
                // start moving the entity:
                entityId = view.getClosestEntity(this.d1Screen, this.minPickRangePixels, 10, false);

                // in block easy drag and drop:
                if (entityId !== RObject.INVALID_ID) {
                    var doc = this.getDocument();
                    if (!isNull(doc)) {
                        var entity = doc.queryEntityDirect(entityId);
                        if (isBlockReferenceEntity(entity)) {
                            var blockId = entity.getReferencedBlockId();
                            var block = doc.queryBlock(blockId);
                            if (!isNull(block)) {
                                range = view.mapDistanceFromView(this.pickRangePixels);
                                if (Math.abs(entity.getScaleFactors().x)>0) {
                                    range /= Math.abs(entity.getScaleFactors().x);
                                }
                                // cursor, mapped to block coordinates:
                                var pBlock = entity.mapToBlock(this.d1Model);
                                var box = new RBox(pBlock, range);
                                var candidateIds = doc.queryIntersectedEntitiesXY(box, true, false, blockId);
                                var entityInBlockId;
                                if (candidateIds.length===1) {
                                    entityInBlockId = candidateIds[0];
                                }
                                else {
                                    entityInBlockId = doc.queryClosestXY(candidateIds, pBlock, range*2, false, range/2);
                                }
                                var entityInBlock = doc.queryEntityDirect(entityInBlockId);
                                if (!isNull(entityInBlock) && getInBlockEasyDragAndDrop(entityInBlock)) {
                                    var refP = entityInBlock.getReferencePoints();
                                    if (refP.length>0) {
                                        this.d1Model = refP[0]; //entity.mapToBlock(refP[0]);
                                    }
                                    else {
                                        this.d1Model = pBlock;
                                    }
                                    this.entityInBlockId = entityInBlockId;
                                    this.blockRefId = entityId;
                                    this.setState(DefaultAction.State.MovingEntityInBlock);
                                    var guiAction = RGuiAction.getByScriptFile("scripts/Snap/SnapFree/SnapFree.js");
                                    if (!isNull(guiAction)) {
                                        guiAction.slotTrigger();
                                    }
                                    this.di.setSnap(new RSnapFree());
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

    // easy in block entity drag and drop (point mark labels):
//    case DefaultAction.State.MovingEntityInBlock:
//        this.moveEntityInBlock(event.getModelPosition(), true);
//        break;

    default:
        break;
    }
};

DefaultAction.prototype.mouseReleaseEvent = function(event) {
    if (this.waitingForContextMenu) {
        return;
    }

    var persistentSelection = RSettings.getBoolValue("GraphicsView/PersistentSelection", false);
    var entityId;

    var shiftPressed = isShiftPressed(event);
    var controlPressed = isControlPressed(event);
    var addToSelection = this.getAddToSelection(shiftPressed) || controlPressed || persistentSelection===true;

    if (event.button() === Qt.LeftButton) {
        switch (this.state) {
        case DefaultAction.State.Dragging:

            // handle clicks on reference points:
            this.d2Model = event.getModelPosition();
            this.d2Screen = event.getScreenPosition();
            var view = event.getGraphicsView();
            if (this.d1Screen.equalsFuzzy(this.d2Screen, 10)) {
                // mouse press and release at same position (click):
                var referencePoint = view.getClosestReferencePoint(this.d1Screen, this.minPickRangePixels);
                if (referencePoint.isValid() && !referencePoint.isIgnore() && !RSettings.getIgnoreAllReferencePoints()) {
                    this.d1Model = referencePoint;
                    var op = new RClickReferencePointOperation(this.d1Model);
                    this.di.applyOperation(op);
                    this.setState(DefaultAction.State.Neutral);
                    return;
                }
            }

            // find selectable entity under cursor:
            entityId = this.getEntityId(event, false, true);

            //qDebug("entityId: ", entityId);

            if (entityId !== -1) {
                if (addToSelection && (this.document.isSelected(entityId) || this.document.isSelectedWorkingSet(entityId))) {
                    this.deselectEntity(entityId);
                }
                else {
                    this.selectEntity(entityId, addToSelection);
                }
            } else {
                if (!addToSelection) {
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

            // select entities:
            this.di.selectBoxXY(new RBox(this.d1Model, this.d2Model), addToSelection);

            this.setState(DefaultAction.State.Neutral);
            break;

        // easy in block entity drag and drop (point mark labels):
//        case DefaultAction.State.MovingEntityInBlock:
//            this.moveEntityInBlock(event.getModelPosition(), false);
//            break;

        default:
            break;
        }
    } else if (event.button() == Qt.RightButton) {
        var handled = false;

        if (this.state!==DefaultAction.State.Neutral && this.state!==DefaultAction.State.MovingEntityInBlock) {
            this.di.clearPreview();
            this.di.repaintViews();
            this.setState(DefaultAction.State.Neutral);
            handled = true;
        }

        else if (this.state===DefaultAction.State.Neutral) {
            var appWin = EAction.getMainWindow();
            var rightClickRange = RSettings.getIntValue("GraphicsView/RightClickRange", 10);
            entityId = EAction.getEntityIdUnderCursor(this.di, event, rightClickRange, true);

            var rightClickToDeselect = RSettings.getBoolValue("GraphicsView/RightClickToDeselect", false);

            // right-click on entity can be used to show context menu:
            if (entityId!==-1) {
                // show entity context menu:
                var rightClickEntityContextMenu = RSettings.getBoolValue("ContextMenu/RightClickEntityContextMenu", true);
                if (rightClickEntityContextMenu) {
                    event.accept();
                    appWin.showContextMenu(entityId, event.getModelPosition());
                    handled = true;
                }

                // use right-click on entity to select entity:
                else if (rightClickToDeselect) {
                    this.selectEntity(entityId, addToSelection);
                    handled = true;
                }
            }
            else {
                // use right-click into empty area to deselect everything:
                if (rightClickToDeselect) {
                    if (this.di.hasSelection()) {
                        this.di.clearSelection();
                        this.di.clearPreview();
                        this.di.repaintViews();
                        handled = true;
                    }
                }
            }
        }

        if (!handled) {
            if (CadToolBar.back()===true) {
                handled = true;
            }
        }

        if (!handled) {
            // show context menu for empty space:
            var rightClickContextMenu = RSettings.getBoolValue("ContextMenu/RightClickContextMenu", true);
            if (rightClickContextMenu===true) {
                event.accept();
                appWin.showContextMenu(RObject.INVALID_ID, event.getModelPosition());
            }
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
    if (event.button() == Qt.LeftButton && (this.state===DefaultAction.State.Neutral || this.state===DefaultAction.State.Dragging)) {
        if (this.state===DefaultAction.State.Dragging) {
            // cancel dragging (double-click):
            this.setState(DefaultAction.State.Neutral);
        }
        var view = event.getGraphicsView();
        var range = view.mapDistanceFromView(this.pickRangePixels);
        var strictRange = view.mapDistanceFromView(10);
        var entityId = this.di.getClosestEntity(event.getModelPosition(), range, strictRange, false);
        if (entityId===RObject.INVALID_ID) {
            this.emptySpaceDoubleClicked();
            return;
        }

        this.entityDoubleClicked(entityId, event);
    }
    EAction.prototype.mouseDoubleClickEvent.call(this, event);
};

DefaultAction.prototype.emptySpaceDoubleClicked = function() {
    if (this.document.getCurrentViewportId()!==RObject.INVALID_ID) {
        this.di.unsetCurrentViewport();
    }
};

DefaultAction.prototype.escapeEvent = function(event) {
    this.di.clearPreview();
    this.di.repaintViews();
    CadToolBar.back();
    this.setState(DefaultAction.State.Neutral);
};

DefaultAction.prototype.pickCoordinate = function(event, preview) {
    var op;

    var shiftPressed = isShiftPressed(event);
    var addToSelection = this.getAddToSelection(shiftPressed);
    var doc = this.getDocument();

    switch (this.state) {
    case DefaultAction.State.MovingReference:
    case DefaultAction.State.SettingReference:

        // find reference shape for lengthen, shorten when shift is pressed:
        var referenceShape = undefined;
        var d2 = event.getModelPosition();
        if (shiftPressed) {
            var view = event.getGraphicsView();
            var modelRange = view.mapDistanceFromView(this.minPickRangePixels);
            var referenceEntityId = this.di.getClosestEntity(this.d1Model, modelRange, 10, false, true);
            if (referenceEntityId!==RObject.INVALID_ID) {
                var e = doc.queryEntity(referenceEntityId);
                if (!isNull(e)) {
                    referenceShape = e.getClosestSimpleShape(this.d1Model);
                }
            }

            if (!isNull(referenceShape)) {
                d2 = referenceShape.getClosestPointOnShape(d2, false);
                this.di.addAuxShapeToPreview(new RLine(this.d2Model, event.getModelPosition()));
            }
        }

        if (preview) {
            this.d2Model = d2;
            op = new RMoveReferencePointOperation(this.d1Model, this.d2Model, event.getModifiers());
            var scene = this.di.getGraphicsSceneWithFocus();
            op.setGraphicsScene(scene);
            this.di.previewOperation(op);
        }
        else {
            if (this.state===DefaultAction.State.MovingReference) {
                this.setState(DefaultAction.State.SettingReference);
            }
            else {
                this.d2Model = d2;
                op = new RMoveReferencePointOperation(this.d1Model, this.d2Model, event.getModifiers());
                var scene = this.di.getGraphicsSceneWithFocus();
                op.setGraphicsScene(scene);
                op.setText(qsTr("Move Reference Point"));
                this.di.applyOperation(op);
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
            op = new RMoveSelectionOperation(this.d1Model, this.d2Model);
            this.di.previewOperation(op);
        }
        else {
            if (this.state===DefaultAction.State.MovingEntity) {
                this.setState(DefaultAction.State.SettingEntity);
            }
            else {
                this.d2Model = event.getModelPosition();
                op = new RMoveSelectionOperation(this.d1Model, this.d2Model);
                op.setText(qsTr("Move Selection"));
                this.di.applyOperation(op);
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
        op = new RAddObjectsOperation();
        op.setText(qsTr("Move Entity"));
        op.addObject(entityInBlock, false);
        if (preview) {
            this.di.previewOperation(op);
        }
        else {
            doc.removeFromSpatialIndex(blockRef);
            this.di.applyOperation(op);
            blockRef.update();
            doc.addToSpatialIndex(blockRef);
            this.setState(DefaultAction.State.Neutral);
            var guiAction = RGuiAction.getByScriptFile("scripts/Snap/SnapAuto/SnapAuto.js");
            if (!isNull(guiAction)) {
                guiAction.slotTrigger();
            }
            this.di.setSnap(new RSnapAuto());
        }
        break;

    default:
        break;
    }
};

/**
 * Called when the mouse cursor hovers over an entity.
 */
DefaultAction.prototype.highlightEntity = function(entityId) {
    if (RSettings.getBoolValue("GraphicsView/HighlightEntity", true)===false) {
        return;
    }

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
 * Called when the user double-clicks an entity.
 */
DefaultAction.prototype.entityDoubleClicked = function(entityId, event) {
    if (isNull(this.document) || isNull(this.di)) {
        return;
    }

    var entity = this.document.queryEntity(entityId);

    if (isTextEntity(entity) ||
        isAttributeEntity(entity) ||
        isAttributeDefinitionEntity(entity)) {

        if (RSettings.getBoolValue("GraphicsView/DoubleClickEditText", true)===true) {
            include("scripts/Modify/EditText/EditText.js");
            EditText.editText(entity);
        }
    }
    else if (isBlockReferenceEntity(entity)) {
        // in block text editing with double-click:
        /*
        var blockId = entity.getReferencedBlockId();
        var block = this.document.queryBlock(blockId);
        if (!isNull(block)) {
            var view = event.getGraphicsView();
            var range = view.mapDistanceFromView(this.pickRangePixels);
            // cursor, mapped to block coordinates:
            var pBlock = entity.mapToBlock(event.getModelPosition());
            var box = new RBox(
                pBlock.operator_subtract(new RVector(range,range)),
                pBlock.operator_add(new RVector(range,range))
            );
            var res = this.document.queryIntersectedEntitiesXY(box, true, false, blockId);
            var entityInBlockId;
            if (res.length===1) {
                entityInBlockId = res[0];
            }
            else {
                entityInBlockId = this.document.queryClosestXY(res, pBlock, range*2, false);
            }
            var entityInBlock = this.document.queryEntity(entityInBlockId);
            if (!isNull(entityInBlock) && isTextBasedEntity(entityInBlock) && getInBlockTextEdit(entityInBlock)) {
                include("scripts/Modify/EditText/EditText.js");
                EditText.editText(entityInBlock);
                return;
            }
        }
        */

        // block editing with double click might be disabled globally:
        if (RSettings.getBoolValue("GraphicsView/DoubleClickEditBlock", true)===true) {
            // block editing with double click might be disabled for this entity:
            if (entity.getCustomBoolProperty("QCAD", "DoubleClickEditBlock", true)===true) {
                include("scripts/Block/Block.js");
                EAction.handleUserMessage(qsTr("Editing block \"%1\"<br>Choose <i>Block > Return to Main Drawing</i> when done").arg(entity.getReferencedBlockName()), false);
                Block.editBlock(this.di, entity.getReferencedBlockName());
            }
        }
    }
    else if (isHatchEntity(entity)) {
        if (RSettings.getBoolValue("GraphicsView/DoubleClickEditHatch", true)===true) {
            include("scripts/Modify/EditHatch/EditHatch.js");
            EditHatch.editHatch(entity);
        }
    }
    else if (isLineEntity(entity) || 
		isArcEntity(entity) ||
		isSplineEntity(entity) ||
		isPolylineEntity(entity) ||
		isEllipseEntity(entity)) {

        if (RSettings.getBoolValue("GraphicsView/DoubleClickSelectContour", true)===true) {
            include("scripts/Select/SelectContour/SelectContour.js");
            var tol = RSettings.getDoubleValue("GraphicsView/DoubleClickSelectContourTolerance", 0.001);
            var layerId = RObject.INVALID_ID;
            if (isAltPressed(event)) {
                // Alt: restrict to same layer:
                layerId = entity.getLayerId();
            }
            var matchingEntityIds = SelectContour.getConnectedEntities(this.document, entityId, tol, layerId);
            var add = isShiftPressed(event);
            if (entity.isSelected()) {
                this.di.selectEntities(matchingEntityIds, add);
            }
            else {
                this.di.deselectEntities(matchingEntityIds);
            }
        }
    }

    // TODO:
//    else if (isViewportEntity(entity)) {
//        this.di.setCurrentViewport(entity.data());
//    }
};

/**
 * \return True to add to selection (by default this is when shiftPressed is true).
 * May be reimplemented to allow other ways to add to selection (e.g. user interface button, etc.)
 */
DefaultAction.prototype.getAddToSelection = function(shiftPressed) {
    return shiftPressed;
};

