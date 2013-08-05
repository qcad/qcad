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

include("../Select.js");

function SelectContour(guiAction) {
    Select.call(this, guiAction);

    this.position = undefined;
    this.vTolerance = new RVector();

    this.setUiOptions("SelectContour.ui");
}

SelectContour.prototype = new Select();

SelectContour.State = {
    ChoosingEntity : 0
};

SelectContour.prototype.selectEntities = function(entityId) {
    var length;
    
    if (this.traversed[entityId]) {
        return;
    }

    var entity = this.doc.queryEntity(entityId);
    if (isNull(entity)) {
        return;
    }

    this.matchingEntities.push(entityId);

    // mark current entity as traversed:
    this.traversed[entityId] = true;

    // select all connected entities:
    var connectionPoints = entity.getEndPoints();
    for (var i = 0; i<connectionPoints.length; ++i) {
        var cp = connectionPoints[i];

        var box = new RBox(
            cp.operator_subtract(this.vTolerance),
            cp.operator_add(this.vTolerance)
        );

        // find connected entities:
        // candidates intersect with small box around end point:
        var candidates = this.doc.queryIntersectedEntitiesXY(box);

        // filter out candidates with end points outside range:
        var connectedEntities = [];
        var found = 0;
        length = candidates.length;
        for (var c = 0; c < length && found<=10; ++c) {
            var candidateId = candidates[c];
            if (this.traversed[candidateId]) {
                continue;
            }
            var candidate = this.doc.queryEntity(candidateId);
            var eps = candidate.getEndPoints();
            for (var k = 0; k < eps.length; ++k) {
                var ep = eps[k];
                if (ep.getDistanceTo(cp) <= this.vTolerance.x) {
                    connectedEntities.push(candidateId);
                    found++;
                    break;
                }
            }
        }

        candidates = undefined;

        length = connectedEntities.length;
        for (var ce = 0; ce < length; ++ce) {
            var cEntityId = connectedEntities[ce];

            // ignore chosen entity:
            if (cEntityId==entityId) {
                continue;
            }

            if (this.traversed[cEntityId]) {
                continue;
            }

            this.selectEntities(cEntityId);
        }

        connectedEntities = undefined;

    }

    connectionPoints = undefined;
};

SelectContour.prototype.beginEvent = function() {
    Select.prototype.beginEvent.call(this);

    this.doc = this.getDocument();
    this.di = this.getDocumentInterface();

    this.setState(SelectContour.State.ChoosingEntity);
};

SelectContour.prototype.setState = function(state) {
    this.di.setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    this.setLeftMouseTip(qsTr("Choose entity of contour"));
    this.setRightMouseTip(EAction.trCancel);
};

SelectContour.prototype.entityPickEvent = function(event) {
    this.traversed = new Object();
    this.matchingEntities = [];
    this.selectEntities(event.getEntityId());
    this.selectWithMode(this.matchingEntities);
};

SelectContour.prototype.entityPickEventPreview = function(event) {
    this.di.highlightEntity(event.getEntityId());
};

SelectContour.prototype.slotToleranceChanged = function(value) {
    this.vTolerance = new RVector(value, value);
};

