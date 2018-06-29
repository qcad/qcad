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

function CheckForUpdates(guiAction) {
    Help.call(this, guiAction);
}

CheckForUpdates.prototype = new Help();

CheckForUpdates.includeBasePath = includeBasePath;

CheckForUpdates.prototype.getUrl = function() {
    return CheckForUpdates.getUrl();
};

CheckForUpdates.getBaseName = function() {
    var fileName = "";
    fileName += RSettings.getMajorVersion() + "_";
    fileName += RSettings.getMinorVersion() + "_";
    fileName += RSettings.getRevisionVersion() + "_";
    fileName += RSettings.getBuildVersion();
    return fileName;
};

CheckForUpdates.getUrl = function() {
    // compile update info URL:
    var url = "http://www.qcad.org/qcad/version/" + CheckForUpdates.getBaseName() + ".html";
    return url;
};

CheckForUpdates.prototype.beginEvent = function() {
    Help.prototype.beginEvent.call(this);

    // compile update info URL:
    var url = this.getUrl();

    // set up dialog:
    var appWin = EAction.getMainWindow();
    var dialog = WidgetFactory.createDialog(CheckForUpdates.includeBasePath, "CheckForUpdatesDialog.ui", appWin);
    var textBrowser = dialog.findChild("TextBrowser");
    WidgetFactory.initTextBrowser(textBrowser, this, "openUrl");

    // load version info from qcad.org:
    textBrowser.setHtml("<p>" + qsTr("Checking for Updates...") + "</p>");

    if (downloadToFile(url, RSettings.getDataLocation(), "updates.html", 10000)) {
        var fn = RSettings.getDataLocation() + "/updates.html";
        if (new QFileInfo(fn).exists()) {
            textBrowser.setSource(QUrl.fromLocalFile(fn));
        }
        else {
            textBrowser.setHtml("<p>" + qsTr("Version information not found.") + "</p>");
        }
    }
    else {
        textBrowser.setHtml("<p>" + qsTr("No connection to server or file not found. Please try again later.") + "</p>");
    }

    WidgetFactory.restoreState(dialog);

    // show dialog:
    dialog.exec();

    WidgetFactory.saveState(dialog);
    dialog.destroy();
    EAction.activateMainWindow();
};

CheckForUpdates.prototype.openUrl = function(url) {
    QDesktopServices.openUrl(url);
};
