/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

function BrowseAddOns(guiAction) {
    Help.call(this, guiAction);
}

BrowseAddOns.prototype = new Help();

BrowseAddOns.prototype.beginEvent = function() {
    Help.prototype.beginEvent.call(this);

    // old version:
    //Help.openUrl("http://www.qcad.org/add-ons");

    var formWidget = this.createWidget("BrowseAddOnsDialog.ui");
    this.webView = formWidget.findChild("Browser");
    WidgetFactory.initWebView(this.webView, this, "openUrl");
    var webPage = this.webView.page();
    webPage.linkDelegationPolicy = QWebPage.DelegateAllLinks;
    var url;

    if (hasPlugin("PROTOOLS") && hasPlugin("DWG")) {
        url = "http://www.qcad.org/add-ons/?edition=pro";
    }
    else {
        url = "http://www.qcad.org/add-ons/?edition=community";
    }

    //var html = download(url, 10000);
    //qDebug(html);
    //webView.setHtml(html, new QUrl("http://www.qcad.org/add-ons"));

    this.webView.loadFinished.connect(this, "afterLoading");
    this.webView.load(new QUrl(url));

    formWidget.exec();
};

BrowseAddOns.prototype.afterLoading = function(ok) {
    var webPage = this.webView.page();
    var mainFrame = webPage.mainFrame();

    // get all add-ons:
    var addOnNames = AddOn.getLocalAddOns();

    for (var i=0; i<addOnNames.length; i++) {
        var addOnName = addOnNames[i];

        var addOnDir = RSettings.getDataLocation() + QDir.separator + addOnName;
        var file = new QFile(addOnDir + "/version");
        var flags = new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text);
        var version = qsTr("Unknown");
        if (file.open(flags)) {
            var textStream = new QTextStream(file);
            version = textStream.readAll();
        }

        // show uninstall button for installed add on:
        mainFrame.evaluateJavaScript("document.getElementById('%1_uninstall').style.display = 'inline';".arg(addOnName));
        // show version of installed add on:
        mainFrame.evaluateJavaScript("document.getElementById('%1_installed_version').style.display = 'inline';".arg(addOnName));
        mainFrame.evaluateJavaScript("document.getElementById('%1_installed_version_number').innerHTML = '%2';".arg(addOnName).arg(version));

        // TODO: highlight installed versions, highlight available updates, etc.
    }

    qDebug("loaded");
};

BrowseAddOns.prototype.openUrl = function(url) {
    qDebug("link clicked: ", url);
    var appWin = EAction.getMainWindow();

    // analize URL:
    var path = url.path();
    var fi = new QFileInfo(path);
    var fileName = fi.fileName();

    // uninstall:
    if (url.fragment()==="uninstall") {
        var addOnName = new QFileInfo(path).fileName();
        var uninstallAddOns = RSettings.getStringListValue("BrowseAddOns/Uninstall", []);
        uninstallAddOns.push(addOnName);
        RSettings.setValue("BrowseAddOns/Uninstall", uninstallAddOns);

        QMessageBox.information(
            appWin,
            qsTr("Add-On"),
            qsTr("Add-on '%1' will be uninstalled when %2 is started the next time.").arg(addOnName).arg(qApp.applicationName)
        );
//        qDebug("uninstalling ", addOnName);
//        var addOnPath = RSettings.getDataLocation() + QDir.separator + addOnName;
//        if (removeDirectory(addOnPath)) {
//            qWarning("cannot remove dir: ", addOnPath);
//        }
        return;
    }

    // not a QCAD add-on: open in browser:
    if (!fileName.endsWith(".qcad.zip")) {
        Help.openUrl(url);
        return;
    }

    // base name, e.g. "XYAddOn-1.2.3"
    var baseName = fileName.substring(0, fileName.length-".qcad.zip".length);
    qDebug("baseName: ", baseName);

    // add on name, e.g. "XYAddOn"
    var addOnName = baseName;
    var dashIdx = addOnName.indexOf("-");
    if (dashIdx!==-1) {
        addOnName = addOnName.substring(0, dashIdx);
    }

    if (addOnName==="") {
        return;
    }
    qDebug("addOnName: ", addOnName);

    var version = baseName.substring(dashIdx+1);
    qDebug("version: ", version);

    // create dir:
    var targetDir = RSettings.getDataLocation() + QDir.separator + addOnName;
    new QDir().mkpath(targetDir);

    // download zip file:
    if (!downloadToFile(url.toString(), RSettings.getDataLocation(), 3000)) {
        qWarning("download error");
        return;
    }

    var fn = RSettings.getDataLocation() + "/" + fileName;
    if (!new QFileInfo(fn).exists()) {
        qWarning("downloaded file not found: ", fn);
        return;
    }

    qDebug("extracting file ", fn, " to ", targetDir);
    if (!RZip.unzipFile(fn, targetDir)) {
        qWarning("cannot unpack downloaded file: ", fn);
        return;
    }

    new QFile(fn).remove();

    var metaFileName = targetDir + "/version";
    var file = new QFile(metaFileName);
    var flags = new QIODevice.OpenMode(QIODevice.WriteOnly | QIODevice.Text);
    if (!file.open(flags)) {
        qWarning("cannot write to file", metaFileName);
        return;
    }

    var ts = new QTextStream(file);
    ts.writeString(version);
    file.close();

    QMessageBox.information(
        appWin,
        qsTr("Add-On"),
        qsTr("Add-on %1 was successfully downloaded and installed.").arg(addOnName) + "\n" +
        qsTr("Please restart %1 to load the add-on.").arg(qApp.applicationName)
    );
};
