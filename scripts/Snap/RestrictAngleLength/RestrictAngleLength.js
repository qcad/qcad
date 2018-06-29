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

include("scripts/Snap/Snap.js");

/**
 * RSnapRestriction implementation. Extends RRestrictAngleLength 
 * with an options toolbar which allows the user to enter the angle / length.
 */
function RRestrictAngleLengthExtension(di) {
    RRestrictAngleLength.call(this, di);

    this.action = new EAction(
         RGuiAction.getByScriptFile(RRestrictAngleLengthExtension.includeBasePath + "/RestrictAngleLength.js")
    );
    this.action.setUiOptions(RRestrictAngleLengthExtension.includeBasePath + "/RestrictAngleLength.ui");
    var restriction = this;

    this.action.slotRestrictAngleChanged = function(value) {
        restriction.setRestrictAngle(value);
    }
    this.action.slotAngleChanged = function(value) {
        restriction.setAngle(value);
    };
    this.action.slotBaseAngleChanged = function(value) {
        restriction.setBaseAngle(value);
    };

    this.action.slotRestrictLengthChanged = function(value) {
        restriction.setRestrictLength(value);
    }
    this.action.slotLengthChanged = function(value) {
        restriction.setLength(value);
    };
    this.action.slotBaseLengthChanged = function(value) {
        restriction.setBaseLength(value);
    };
}

RRestrictAngleLengthExtension.prototype = new RRestrictAngleLength();
RRestrictAngleLengthExtension.includeBasePath = includeBasePath;

RRestrictAngleLengthExtension.prototype.showUiOptions = function() {
    this.action.showUiOptions(false);
};

RRestrictAngleLengthExtension.prototype.hideUiOptions = function() {
    this.action.hideUiOptions();
};



/**
 * \class RestrictAngleLength
 * \ingroup ecma_snap
 * \brief Restriction of angle or distance.
 */
function RestrictAngleLength(guiAction) {
    Snap.call(this, guiAction);
}

RestrictAngleLength.prototype = new Snap();

RestrictAngleLength.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    var di = this.getDocumentInterface();

    var sr = di.getSnapRestriction();
    if (!isNull(sr)) {
        if (isOfType(sr, RRestrictAngleLength)) {
            di.setSnapRestriction(new RRestrictOff(di));

            var guiAction = RGuiAction.getByScriptFile("scripts/Snap/RestrictOff/RestrictOff.js");
            if (!isNull(guiAction)) {
                guiAction.slotTrigger();
            }

            this.terminate();
            return;
        }
    }

    di.setSnapRestriction(new RRestrictAngleLengthExtension(di));
    this.terminate();
};

