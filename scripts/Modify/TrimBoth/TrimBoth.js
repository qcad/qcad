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

include("../Trim/Trim.js");

/**
 * \class TrimBoth
 * \brief Trims two entities to each other.
 * \ingroup ecma_modify
 */
function TrimBoth(guiAction) {
    Trim.call(this, guiAction);

    this.trimBoth = true;
}

TrimBoth.prototype = new Trim();

TrimBoth.prototype.beginEvent = function() {
    Trim.prototype.beginEvent.call(this);
};

