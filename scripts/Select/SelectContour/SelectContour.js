/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

include("../Select.js");

/**
 * \class SelectContour
 * \ingroup ecma_select
 * \brief Select connected entities.
 */
function SelectContour(guiAction) {
    Select.call(this, guiAction);

    this.tolerance = 0.0;

    this.setUiOptions("SelectContour.ui");
}

SelectContour.prototype = new Select();

SelectContour.State = {
    ChoosingEntity : 0
};

SelectContour.prototype.beginEvent = function() {
    Select.prototype.beginEvent.call(this);

    this.setState(SelectContour.State.ChoosingEntity);
};

SelectContour.prototype.setState = function(state) {
    var di = this.getDocumentInterface();
    di.setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    this.setLeftMouseTip(qsTr("Choose entity of contour"));
    this.setRightMouseTip(EAction.trCancel);
};

SelectContour.prototype.entityPickEvent = function(event) {
    this.selectEntities(event.getEntityId());
};

SelectContour.prototype.selectEntities = function(entityId) {
    var matchingEntities = SelectContour.getConnectedEntities(this.getDocument(), entityId, this.tolerance);
    this.selectWithMode(matchingEntities);
};

SelectContour.prototype.entityPickEventPreview = function(event) {
    var di = this.getDocumentInterface();
    di.highlightEntity(event.getEntityId());
};

SelectContour.prototype.slotToleranceChanged = function(value) {
    this.tolerance = value;
};

/**
 * \return Array of entity IDs of entities which are directly or indirectly
 * connected to the given entity, including the given entityId.
 */
SelectContour.getConnectedEntities = function(doc, entityId, tolerance, recursion) {
    if (isNull(recursion)) {
        recursion = false;
    }

    if (recursion===false) {
        SelectContour.traversed = {};
        SelectContour.matchingEntities = [];
    }

    if (SelectContour.traversed[entityId]) {
        return SelectContour.matchingEntities;
    }

    var entity = doc.queryEntity(entityId);
    if (isNull(entity)) {
        return SelectContour.matchingEntities;
    }

    var vTolerance = new RVector(tolerance, tolerance);

    SelectContour.matchingEntities.push(entityId);

    // mark current entity as traversed:
    SelectContour.traversed[entityId] = true;

    // select all connected entities:
    var connectionPoints = entity.getEndPoints();
    for (var i = 0; i<connectionPoints.length; ++i) {
        var cp = connectionPoints[i];

        var box = new RBox(
            cp.operator_subtract(vTolerance),
            cp.operator_add(vTolerance)
        );

        // find connected entities:
        // candidates intersect with small box around end point:
        var candidates = doc.queryIntersectedEntitiesXY(box);

        // filter out candidates with end points outside range:
        var connectedEntities = [];
        var found = 0;
        for (var c = 0; c < candidates.length && found<=10; ++c) {
            var candidateId = candidates[c];
            if (SelectContour.traversed[candidateId]) {
                continue;
            }
            var candidate = doc.queryEntity(candidateId);
            var eps = candidate.getEndPoints();
            for (var k = 0; k < eps.length; ++k) {
                var ep = eps[k];
                if (ep.getDistanceTo(cp) <= vTolerance.x) {
                    connectedEntities.push(candidateId);
                    found++;
                    break;
                }
            }
        }

        for (var ce = 0; ce < connectedEntities.length; ++ce) {
            var cEntityId = connectedEntities[ce];

            // ignore chosen entity:
            if (cEntityId===entityId) {
                continue;
            }

            if (SelectContour.traversed[cEntityId]) {
                continue;
            }

            SelectContour.getConnectedEntities(doc, cEntityId, tolerance, true);
        }
    }

    return SelectContour.matchingEntities;
};
