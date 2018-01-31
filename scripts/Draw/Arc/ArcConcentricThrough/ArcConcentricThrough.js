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

include("../../Line/LineParallelThrough/LineParallelThrough.js");

/**
 * \class ArcConcentric
 * \brief Arc concentric to another arc (with point).
 * \ingroup ecma_draw_arc
 */
function ArcConcentricThrough(guiAction) {
    LineParallelThrough.call(this, guiAction);

    this.setUiOptions("ArcConcentricThrough.ui");
}

ArcConcentricThrough.prototype = new LineParallelThrough();
