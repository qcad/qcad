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

include("scripts/Draw/Line/Line.js");
include("scripts/Modify/Offset/Offset.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class LineParallel
 * \brief Line parallel to existing line with distance.
 * \ingroup ecma_draw_line
 */
function LineParallel(guiAction) {
    Offset.call(this, guiAction);

    if (!isNull(guiAction)) {
        this.setUiOptions([LineParallel.includeBasePath + "/../Line.ui", LineParallel.includeBasePath + "/LineParallel.ui"]);
    }
}

LineParallel.prototype = new Offset();
LineParallel.includeBasePath = includeBasePath;

LineParallel.prototype.slotTypeAutoChanged = function(checked) {
    Line.slotTypeAutoChanged(this, checked);
};

LineParallel.prototype.slotTypeSegmentChanged = function(checked) {
    Line.slotTypeSegmentChanged(this, checked);
};

LineParallel.prototype.slotTypeRayChanged = function(checked) {
    Line.slotTypeRayChanged(this, checked);
};

LineParallel.prototype.slotTypeXLineChanged = function(checked) {
    Line.slotTypeXLineChanged(this, checked);
};
