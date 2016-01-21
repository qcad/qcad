/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

include("../Dimension.js");

/**
 * \class DimAngular
 * \brief Draw angular dimension.
 * The first entity is a line or arc. If the first entity is a line,
 * a second entity has to be chosen which is also a line.
 * \ingroup ecma_draw_dimension
 */
function DimAngular(guiAction) {
    Dimension.call(this, guiAction);

    this.data = new RDimAngularData();
    this.firstEntity = undefined;
    this.firstShape = undefined;
    this.secondEntity = undefined;
    this.secondShape = undefined;
    this.setUiOptions("../Dimension.ui");
}

DimAngular.prototype = new Dimension();

DimAngular.State = {
    SettingFirstEntity : 0,
    SettingSecondEntity : 1,
    SettingDimPos : 2
};

DimAngular.prototype.beginEvent = function() {
    Dimension.prototype.beginEvent.call(this);

    this.setState(DimAngular.State.SettingFirstEntity);
};

DimAngular.prototype.setState = function(state) {
    Dimension.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case DimAngular.State.SettingFirstEntity:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.data.setExtensionLine1Start(RVector.invalid);
        this.data.setExtensionLine1End(RVector.invalid);
        this.data.setExtensionLine2Start(RVector.invalid);
        this.data.setExtensionLine2End(RVector.invalid);
        this.data.setDimArcPosition(RVector.invalid);
        this.firstEntity = undefined;
        this.firstShape = undefined;
        this.secondEntity = undefined;
        this.secondShape = undefined;
        var trFirstEntity = qsTr("Arc or first of two lines");
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case DimAngular.State.SettingSecondEntity:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.data.setExtensionLine2Start(RVector.invalid);
        this.data.setExtensionLine2End(RVector.invalid);
        this.data.setDimArcPosition(RVector.invalid);
        this.secondEntity = undefined;
        this.secondShape = undefined;
        var trSecondEntity = qsTr("Second line");
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;

    case DimAngular.State.SettingDimPos:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.data.setDefinitionPoint(RVector.invalid);
        var trDimPos = qsTr("Dimension arc location");
        this.setCommandPrompt(trDimPos);
        this.setLeftMouseTip(trDimPos);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

DimAngular.prototype.escapeEvent = function() {
    switch (this.state) {
    case DimAngular.State.SettingFirstEntity:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DimAngular.State.SettingSecondEntity:
        this.setState(DimAngular.State.SettingFirstEntity);
        break;

    case DimAngular.State.SettingDimPos:
        if (isArcShape(this.firstShape)) {
            this.setState(DimAngular.State.SettingFirstEntity);
        }
        else {
            this.setState(DimAngular.State.SettingSecondEntity);
        }
        break;
    }
};

DimAngular.prototype.pickEntity = function(event, preview) {
    var shape, appWin;
    
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    switch (this.state) {
    case DimAngular.State.SettingFirstEntity:
        shape = entity.getClosestSimpleShape(pos);

        if (isLineBasedShape(shape)) {
            this.firstEntity = entity;
            this.firstShape = shape;
            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(DimAngular.State.SettingSecondEntity);
            }
        }
        else if (isArcShape(shape)) {
            this.firstEntity = entity;
            this.firstShape = shape;
            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(DimAngular.State.SettingDimPos);
            }
        } else {
            if (!preview) {
                EAction.warnNotLineOrArc();
                break;
            }
        }
        break;

    case DimAngular.State.SettingSecondEntity:
        shape = entity.getClosestSimpleShape(pos);

        if (isLineBasedShape(shape)) {
            this.secondEntity = entity;
            this.secondShape = shape;
            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(DimAngular.State.SettingDimPos);
            }
        }
        else {
            if (!preview) {
                EAction.warnNotLine();
                break;
            }
        }
        break;
    }
};

DimAngular.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case DimAngular.State.SettingDimPos:
        this.data.setDimArcPosition(event.getModelPosition());
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(DimAngular.State.SettingFirstEntity);
            }
        }
        break;

    }
};

DimAngular.prototype.getOperation = function(preview) {
    if (!isLineBasedShape(this.firstShape) && !isArcShape(this.firstShape)) {
        return undefined;
    }

    if (isLineBasedShape(this.firstShape) && !isLineBasedShape(this.secondShape)) {
        return undefined;
    }

    var di = this.getDocumentInterface();

    if (isLineBasedShape(this.firstShape)) {
        //this.data.setExtensionLine1Start(this.firstShape.getStartPoint());
        //this.data.setExtensionLine1End(this.firstShape.getStartPoint());

        var intersections = this.firstShape.getIntersectionPoints(this.secondShape.data(), false);

        if (intersections.length!=1) {
            return undefined;
        }

        var center = intersections[0];

        if (center.getDistanceTo(this.firstShape.getStartPoint()) <
                center.getDistanceTo(this.firstShape.getEndPoint())) {
            this.data.setExtensionLine1Start(this.firstShape.getEndPoint());
            this.data.setExtensionLine1End(this.firstShape.getStartPoint());
        } else {
            this.data.setExtensionLine1Start(this.firstShape.getStartPoint());
            this.data.setExtensionLine1End(this.firstShape.getEndPoint());
        }

        if (center.getDistanceTo(this.secondShape.getStartPoint()) <
                center.getDistanceTo(this.secondShape.getEndPoint())) {
            this.data.setExtensionLine2Start(this.secondShape.getStartPoint());
            this.data.setExtensionLine2End(this.secondShape.getEndPoint());
        } else {
            this.data.setExtensionLine2Start(this.secondShape.getEndPoint());
            this.data.setExtensionLine2End(this.secondShape.getStartPoint());
        }
        //graphicView->moveRelativeZero(center);
        if (!preview) {
            di.setRelativeZero(center);
        }
        //setStatus(SetPos);
    }
    if (isArcShape(this.firstShape)) {
        this.data.setExtensionLine1Start(this.firstShape.getCenter());
        this.data.setExtensionLine1End(this.firstShape.getStartPoint());
        this.data.setExtensionLine2Start(this.firstShape.getCenter());
        this.data.setExtensionLine2End(this.firstShape.getEndPoint());
    }

    if (!this.data.isValid()) {
        return undefined;
    }

    var doc = this.getDocument();
    var entity = new RDimAngularEntity(doc, this.data);
    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

DimAngular.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.firstEntity)) {
        ret.push(this.firstEntity.getId());
    }
    if (isEntity(this.secondEntity)) {
        ret.push(this.secondEntity.getId());
    }
    return ret;
};

