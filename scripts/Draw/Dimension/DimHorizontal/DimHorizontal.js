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

include("../DimRotated/DimRotated.js");

/**
 * \class DimHorizontal
 * \brief Draw horizontal dimension.
 * \ingroup ecma_draw_dimension
 */
function DimHorizontal(guiAction) {
    DimRotated.call(this, guiAction);

    this.setUiOptions("../Dimension.ui");
    this.data.setRotation(0.0);
}

DimHorizontal.prototype = new DimRotated();

