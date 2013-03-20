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

CheckForUpdates.getUrl = function() {
    // compile update info URL:
    var url = "http://www.ribbonsoft.com/qcad/version/";
    url += RSettings.getMajorVersion() + "_";
    url += RSettings.getMinorVersion() + "_";
    url += RSettings.getRevisionVersion() + "_";
    url += RSettings.getBuildVersion() + "_";
    // TODO:
    //url += RSettings.getVersionTicket();
    url += ".html";

    return url;
};

CheckForUpdates.prototype.beginEvent = function() {
    Help.prototype.beginEvent.call(this);

    // compile update info URL:
    var url = CheckForUpdates.getUrl();

    // set up dialog:
    var appWin = EAction.getMainWindow();
    var dialog = WidgetFactory.createDialog(CheckForUpdates.includeBasePath, "CheckForUpdatesDialog.ui", appWin);
    var webView = dialog.findChild("WebView");
    WidgetFactory.initWebView(webView, this, "openUrl");

    // load version info from ribbonsoft.com:
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

CheckForUpdates.postInit = function() {
    if (RSettings.hasQuitFlag()) {
        return;
    }

    // check for updates at startup:
    if (RSettings.getBoolValue("CheckForUpdates/AutoCheckUpdates", false)===true) {
        qDebug("checking for updates...");
        var html = download(CheckForUpdates.getUrl(), 3000);
        if (html.indexOf("<title>Up To Date</title>")!==-1) {
            qDebug("no updates available");
        }
        else if (html.indexOf("<title>Update Available</title>")!=-1) {
            qDebug("updates available");
            var action = RGuiAction.getByScriptFile("scripts/Help/CheckForUpdates/CheckForUpdates.js");
            if (!isNull(action)) {
                action.slotTrigger();
            }
        }
    }
};
