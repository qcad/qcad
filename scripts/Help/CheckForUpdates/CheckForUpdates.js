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

include("../Help.js");

function CheckForUpdates(guiAction) {
    Help.call(this, guiAction);
}

CheckForUpdates.prototype = new Help();

CheckForUpdates.includeBasePath = includeBasePath;

CheckForUpdates.prototype.getUrl = function() {
    return CheckForUpdates.getUrl();
};

CheckForUpdates.getUrl = function() {
    // compile update info URL:
    var url = "http://www.qcad.org/qcad/version/";
    url += RSettings.getMajorVersion() + "_";
    url += RSettings.getMinorVersion() + "_";
    url += RSettings.getRevisionVersion() + "_";
    url += RSettings.getBuildVersion();
    url += ".html";
    return url;
};

CheckForUpdates.prototype.beginEvent = function() {
    Help.prototype.beginEvent.call(this);

    // compile update info URL:
    var url = this.getUrl();

    // set up dialog:
    var appWin = EAction.getMainWindow();
    var dialog = WidgetFactory.createDialog(CheckForUpdates.includeBasePath, "CheckForUpdatesDialog.ui", appWin);
    var webView = dialog.findChild("WebView");
    WidgetFactory.initWebView(webView, this, "openUrl");

    // load version info from qcad.org:
    webView.setHtml("<p>" + qsTr("Checking for Updates...") + "</p>");
    webView.load(new QUrl(url));

    WidgetFactory.restoreState(dialog);

    // show dialog:
    dialog.exec();

    WidgetFactory.saveState(dialog);
};

CheckForUpdates.prototype.openUrl = function(url) {
    QDesktopServices.openUrl(url);
};
