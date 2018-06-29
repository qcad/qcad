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
include("scripts/Modify/OffsetThrough/OffsetThrough.js");

/**
 * \class LineParallelThrough
 * \brief Line parallel to existing line through given point.
 * \ingroup ecma_draw_line
 */
function LineParallelThrough(guiAction) {
    OffsetThrough.call(this, guiAction);

    if (!isNull(guiAction)) {
        this.setUiOptions(["../Line.ui", "LineParallelThrough.ui"]);
    }
}

LineParallelThrough.prototype = new OffsetThrough();

LineParallelThrough.prototype.slotTypeAutoChanged = function(checked) {
    Line.slotTypeAutoChanged(this, checked);
};

LineParallelThrough.prototype.slotTypeSegmentChanged = function(checked) {
    Line.slotTypeSegmentChanged(this, checked);
};

LineParallelThrough.prototype.slotTypeRayChanged = function(checked) {
    Line.slotTypeRayChanged(this, checked);
};

LineParallelThrough.prototype.slotTypeXLineChanged = function(checked) {
    Line.slotTypeXLineChanged(this, checked);
};
