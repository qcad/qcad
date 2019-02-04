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

include("../ModifyCorner.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Round
 * \brief Adds a rounding to two entities and optionally trims both entities.
 * \ingroup ecma_modify
 */
function Round(guiAction) {
    ModifyCorner.call(this, guiAction);

    this.radius = 1.0;

    this.setUiOptions("Round.ui");
}

Round.prototype = new ModifyCorner();

Round.includeBasePath = includeBasePath;

Round.prototype.getOperation = function(preview) {
    if (!isEntity(this.entity1) || !isEntity(this.entity2)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var success = Round.round(
            op,
            this.entity1.clone(), this.clickPos1,
            this.entity2.clone(), this.clickPos2,
            this.trim,
            this.radius,
            this.posSolution,
            preview);

    if (!success && !preview) {
        EAction.handleUserWarning(qsTr("The two entities cannot be rounded."));
    }

    return op;
};

/**
 * Rounds or extends the given entity2 to the intersection point of the
 * entity2 and the limitingShape.
 *
 * \param op Operation to use to add new objects and modify objects.
 * \param entity1 First entity which will be rounded.
 * \param clickPos1 Coordinate that was clicked when the user selected entity1.
 * \param entity2 Second entity which will be rounded.
 * \param clickPos2 Coordinate that was clicked when the user selected entity2.
 * \param trim true: Trim both entities to rounding arc.
 * \param radius Radius of rounding.
 * \param solutionPos Position that determines which solution to apply (optional, defaults to clickPos1)
 * \param preview Operation is used for preview.
 */
Round.round = function(op, entity1, clickPos1, entity2, clickPos2, trim, radius, solutionPos, preview) {
    if (!isEntity(entity1) || !isValidVector(clickPos1) ||
        !isEntity(entity2) || !isValidVector(clickPos2) ||
        !isBoolean(trim)) {
        return false;
    }

    var samePolyline = (entity1.getId()===entity2.getId() && isPolylineEntity(entity1));

    var shape1P = entity1.getClosestShape(clickPos1);
    var shape2P = entity2.getClosestShape(clickPos2);
    var shape1 = shape1P.data();
    var shape2 = shape2P.data();

    var newShapes = Round.roundShapes(shape1, clickPos1, shape2, clickPos2, trim, samePolyline, radius, solutionPos);

    if (newShapes.length===0) {
        return false;
    }

    // add new trimmed entities or polyline:
    if (trim && !modifyEntity(op, entity1, newShapes[0].data())) {
        if (!preview) {
            EAction.handleUserWarning(qsTr("First entity cannot be trimmed."));
        }
    }

    if (newShapes.length<3) {
        // rounding was within same polyline:
        return true;
    }

    if (trim && !modifyEntity(op, entity2, newShapes[2].data())) {
        if (!preview) {
            EAction.handleUserWarning(qsTr("Second entity cannot be trimmed."));
        }
    }

    // add rounding:
    op.addObject(new RArcEntity(entity1.getDocument(), new RArcData(newShapes[1].data())));

    return true;
};

/**
 * Rounds the given shape1 againt shape2.
 *
 * \param shape1 First shape which will be rounded.
 * \param clickPos1 Coordinate that was clicked when the user selected shape1.
 * \param shape2 Second shape which will be rounded.
 * \param clickPos2 Coordinate that was clicked when the user selected shape2.
 * \param trim true: Trim both shape to rounding arc.
 * \param radius Radius of rounding.
 * \param solutionPos Position that determines which solution to apply (optional, defaults to clickPos1)
 *
 * \return Array of three shapes: shape1 (trimmed), rounding, shape2 (trimmed)
 * or emtpy array.
 */
Round.roundShapes = function(shape1, clickPos1, shape2, clickPos2, trim, samePolyline, radius, solutionPos) {
    if (isNull(solutionPos)) {
        solutionPos = clickPos2;
    }

    return RShape.roundShapes(shape1, clickPos1, shape2, clickPos2, trim, samePolyline, radius, solutionPos);
};

Round.prototype.getAuxPreview = function() {
    var ret = [];

    if (!isNull(this.par1)) {
        ret.push(this.par1);
    }
    if (!isNull(this.par2)) {
        ret.push(this.par2);
    }

    return ret;
}

Round.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
};

