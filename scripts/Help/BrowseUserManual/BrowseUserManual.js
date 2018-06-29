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

include("scripts/Help/Help.js");

function BrowseUserManual(guiAction) {
    Help.call(this, guiAction);
}

BrowseUserManual.prototype = new Help();

BrowseUserManual.prototype.beginEvent = function() {
    Help.prototype.beginEvent.call(this);

    var locale = new QLocale(RSettings.getLocale());
    var dir = "en";

    if (locale.language()===QLocale.German) {
        dir = "de";
    }
    else if (locale.language()===QLocale.Japanese) {
        dir = "ja";
    }
    else if (locale.language()===QLocale.Slovenian) {
        dir = "sl";
    }

    Help.openUrl(
        "https://qcad.org/doc/qcad/%1.%2.%3/reference/%4/index.html"
        .arg(RSettings.getMajorVersion())
        .arg(RSettings.getMinorVersion())
        .arg(RSettings.getRevisionVersion())
        .arg(dir)
    );
};

