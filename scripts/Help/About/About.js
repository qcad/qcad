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
include("AboutCredits.js");
 

function About(guiAction) {
    Help.call(this, guiAction);
}

About.prototype = new Help();

About.prototype.beginEvent = function() {
    Help.prototype.beginEvent.call(this);

    var formWidget = this.createWidget("About.ui");

    this.head = "<head>\n"
         + "<style type='text/css'>\n"
         + "a { text-decoration:none }\n"
         + "h1 { font-family:sans;font-size:16pt;margin-bottom:8pt; }\n"
         + "h2 { font-family:sans;font-size:12pt;font-style:italic;margin-bottom:5pt; }\n"
         + "body,td { font-family:sans;font-size:9pt; }\n"
         + "}\n</style>\n"
         + "</head>";

    this.applicationName = qApp.applicationName;

    // init plugin view:
    var webView = formWidget.findChild("PluginsText");
    WidgetFactory.initWebView(webView, this, "openUrl");
    var webPage = webView.page();
    webPage.linkDelegationPolicy = QWebPage.DelegateAllLinks;
    this.initAboutPlugins(webView);

    formWidget.windowTitle = qsTr("About %1").arg(this.applicationName);

    // init about view:
    webView = formWidget.findChild("QCADText");
    WidgetFactory.initWebView(webView, this, "openUrl");
    this.initAboutQCAD(webView);

    // init scripts view:
    webView = formWidget.findChild("ScriptsText");
    WidgetFactory.initWebView(webView, this, "openUrl");
    this.initAboutScripts(webView);

    webView = formWidget.findChild("CreditsText");
    WidgetFactory.initWebView(webView, this, "openUrl");
    this.initCredits(webView);

    // init system view:
    var textEdit = formWidget.findChild("SystemText");
    this.initAboutSystem(textEdit);

    formWidget.exec();
};

About.prototype.initAboutQCAD = function(webView) {
    var html =
            "<html>"
            + this.head
            + "<body>"
            + "<h1>%1</h1>".arg(this.applicationName)
            + "<br/>"
            + "<table border='0'><tr>"
            + "<td><b>Version:</b> </td><td>%1.%2.%3.%4 (%5)</td>"
              .arg(RSettings.getMajorVersion())
              .arg(RSettings.getMinorVersion())
              .arg(RSettings.getRevisionVersion())
              .arg(RSettings.getBuildVersion())
              .arg(RSettings.getVersionString())
            + "</tr><tr>"
            + "<td><b>Build Date:</b> </td><td>%1</td>".arg(RSettings.getReleaseDate())
            + "</tr><tr>"
            + "<td><b>Qt Version:</b> </td><td>%1</td>".arg(RSettings.getQtVersion())
            + "</tr><tr>"
            + "<td><b>Compiler:</b> </td><td>%1</td>".arg(RSettings.getCompilerVersion())
            + "</tr></table>"
            + "<p>%1 is an application for computer-aided design (CAD).</p>".arg(qApp.applicationName)
            + "<p/>"
            + "<p>QCAD is free (open source) software.</p>"
            + "<p>Plugins and script add-ons are subject to their respective license (see 'About Plugins' tab).</p>"
            + "<p/>"
            + "<p>Internet: <a href='http://%1'>%1</a></p>".arg(qApp.organizationDomain)
            + "<p/>"
            + "<p>All brand or product names are trademarks or registered trademarks of their respective holders.</p>"
            + "<p/>"
            + "<p>Portions of this software © 2013 Digia Plc.</p>"
            + "<p>Portions of this software © 2012 Nokia Corporation and/or its subsidiary(-ies).</p>"
            + "<p/>"
            + "</body></html>";
    webView.setHtml(html);
};

About.prototype.initAboutPlugins = function(webView) {
    RPluginLoader.loadPlugins(false);
    var html =
            "<html>"
            + this.head
            + "<body>"
            + "<h1>%1</h1>".arg(qsTr("Plugins"))
            + "<hr/>";

    var numPlugins = RPluginLoader.countPlugins();

    if (numPlugins===0) {
        html += "No plugins found.";
    }
    else {
        for (var i=0; i<numPlugins; i++) {
            html += "<table border='0' width='100%'>";
            html += "<col width='25%'/>";
            html += "<col width='90%'/>";

            var text, url;

            var pluginInfo = RPluginLoader.getPluginInfo(i);

            // plugin about info:
            text = pluginInfo.get("Name", qsTr("No information available"));
            if (text==="Pro Tools") {
                if (isNull(pluginInfo.get("TrialExpired"))) {
                    this.applicationName = qApp.applicationName + " Professional";
                }
                else {
                    this.applicationName = qApp.applicationName + " Professional Trial";
                }
            }
            html += this.getTableRow(qsTr("Plugin:"), "<b>" + Qt.escape(text) + "</b>", false);

            // description:
            text = pluginInfo.get("Description");
            if (!isNull(text)) {
                html += this.getTableRow(qsTr("Description:"), text, false);
            }

            // plugin version:
            text = pluginInfo.get("Version", qsTr("Unknown"));
            html += this.getTableRow(qsTr("Version:"), text);

            // Qt plugin version:
            text = pluginInfo.get("QtVersion", qsTr("Unknown"));
            html += this.getTableRow(qsTr("Qt Version:"), text);

            // plugin license:
            text = pluginInfo.get("License", qsTr("Unknown"));
            html += this.getTableRow(qsTr("License:"), text);

            // plugin URL:
            text = pluginInfo.get("URL");
            if (!isNull(text)) {
                url = new QUrl(text);
                if (url.isValid()) {
                    html += this.getTableRow(
                        qsTr("Internet:"),
                        "<a href='%2'>%3</a>"
                            .arg(url.toString()).arg(url.host().replace(/^www./, "")),
                        false
                    );
                }
            }

            // trial:
            var exp = pluginInfo.get("TrialExpired");
            if (!isNull(exp)) {
                var color = "green";
                text = qsTr("Active");
                if (exp) {
                    color = "red";
                    text = qsTr("Inactive (restart)");
                }

                html += this.getTableRow(qsTr("Trial Version:"),
                    "<span style='color:" + color + "'>" + text + "</span>", false);
            }

            // file name:
            text = pluginInfo.get("FileName");
            if (!isNull(text)) {
                var fi = new QFileInfo(text);
                text = fi.fileName();
                url = QUrl.fromLocalFile(fi.absolutePath());
                html += this.getTableRow(qsTr("File:"), "<a href='" + url.toString() + "'>" + text + "</a>", false);
            }

            // plugin error:
            text = pluginInfo.get("Error");
            if (!isNull(text)) {
                html += this.getTableRow(qsTr("Error:"), text);
            }
            html += "</table>";
            html += "<hr/>";
        }
    }

    html += "</body>";
    html += "</html>";
    webView.setHtml(html);
};

About.prototype.initAboutScripts = function(webView) {
    var html =
            "<html>"
            + this.head
            + "<body>"
            + "<h1>%1</h1>".arg(qsTr("Script Add-Ons"))
            + "<hr/>";

    var addOns = AddOn.addOns;
    var numAddOns = addOns.length;

    if (numAddOns===0) {
        html += "No script add-ons found.";
    }
    else {
        var i;
        var scriptsPath = RS.getDirectoryList("scripts")[0];
        var scriptsDir = new QDir(scriptsPath);

        var sorted = [];
        for (i=0; i<numAddOns; i++) {
            var addOn = addOns[i];
            var path = addOn.getPath();
            if (path.startsWith(":")) {
                path = path.substring(1);
            }
            else {
                path = scriptsDir.relativeFilePath(path);
            }
            sorted.push([addOn.getClassName(), path]);
        }

        sorted = sorted.sort(function(a,b) { return a[1].localeCompare(b[1]); });

        html += "<table border='0' width='100%'>";
        html += "<col width='25%'/>";
        html += "<col width='75%'/>";

        for (i=0; i<sorted.length; i++) {
            html += "<tr><td>" + sorted[i][0] + "</td><td>" + sorted[i][1] + "</td></tr>"
        }
    }

    html += "</table>";
    html += "</body>";
    html += "</html>";
    webView.setHtml(html);
};

About.prototype.initCredits = function(webView) {
    //var credits = include("AboutCredits.js");

    var html =
            "<html>"
            + this.head
            + "<body>"
            + "<h1>%1</h1>".arg(qsTr("Credits"))
            + "<hr/>";


    for (var i=0; i<credits.length; i++) {
        html += "<h2>%1</h2>".arg(credits[i][0])
        if (credits[i].length>1 && credits[i][1].length>1) {
            // table with names and credits:
            html += "<table border='0' width='100%'>";
            html += "<col width='40%'/>";
            html += "<col width='60%'/>";
            for (var k=1; k<credits[i].length; k++) {
                if (isArray(credits[i][k]) && credits[i][k].length>1) {
                    html += "<tr>";
                    html += "<td valign='top'>" + credits[i][k][0] + "</td>";
                    html += "<td valign='top'>" + credits[i][k][1] + "</td>";
                    html += "</tr>";
                }
            }
            html += "</table>";

            // list of names:
            var first = true;
            for (var k=1; k<credits[i].length; k++) {
                if (!isArray(credits[i][k])) {
                    if (!first) {
                        html += ", ";
                    }
                    html += credits[i][k];
                    first = false;
                }
            }
        }
    }

    html += "</body>";
    html += "</html>";

    webView.setHtml(html);
};

About.prototype.getTableRow = function(text1, text2, escape) {
    if (isNull(escape) || escape!==false) {
        text2 = Qt.escape(text2);
    }

    return "<tr><td valign='top'>%1 </td><td>%2</td></tr>".arg(text1).arg(text2);
};

About.prototype.initAboutSystem = function(textEdit) {
    var text = "";
    var i;

    text += "Versions";
    text += "\nQCAD version: %1.%2.%3.%4"
        .arg(RSettings.getMajorVersion())
        .arg(RSettings.getMinorVersion())
        .arg(RSettings.getRevisionVersion())
        .arg(RSettings.getBuildVersion());
    text += "\nDate: " + RSettings.getReleaseDate();
    text += "\nQt version: " + RSettings.getQtVersion();
    text += "\nCompiler version: " + RSettings.getCompilerVersion();

    text += "\nOS: ";
    if (RS.getSystemId()==="win") {
        text += "Windows";
    }
    if (RS.getSystemId()==="osx") {
        text += "Mac";
    }
    if (RS.getSystemId()==="linux") {
        text += "Linux";
    }
    text += "\nOS version: " + RSettings.getOSVersion();

    text += "\n";
    text += "\nLocale";
    text += "\nQCAD locale: " + RSettings.getLocale();
    var sysloc = QLocale.system();
    text += "\nName: " + sysloc.name();
    text += "\nCountry: " + sysloc.country();
    if (RSettings.getQtVersion().startsWith("4.8") || RSettings.getQtVersion().startsWith("5")) {
        text += "\nCountry name: " + sysloc.nativeCountryName();
    }
    text += "\nLanguage: " + sysloc.language();
    if (RSettings.getQtVersion().startsWith("4.8") || RSettings.getQtVersion().startsWith("5")) {
        text += "\nLanguage name: " + sysloc.nativeLanguageName();
    }
    text += "\nScript: " + sysloc.script();
    text += "\nScript name: " + QLocale.scriptToString(sysloc.script());
    text += "\nDecimal point: " + sysloc.decimalPoint();
    text += "\nNegative sign: " + sysloc.negativeSign();
    text += "\nPositive sign: " + sysloc.positiveSign();
    text += "\nText direction: " + sysloc.textDirection();
    text += "\nSystem codec: " + QTextCodec.codecForLocale().name();

    text += "\n";
    text += "\nArguments: " + RSettings.getOriginalArguments();

    var numPlugins = RPluginLoader.countPlugins();
    if (numPlugins>0) {
        text += "\n";
        text += "\nPlugins";
        for (i=0; i<numPlugins; i++) {
            var pluginInfo = RPluginLoader.getPluginInfo(i);
            var keys = pluginInfo.getKeys();
            for (var k=0; k<keys.length; k++) {
                text += "\n" + keys[k] + "=" + pluginInfo.get(keys[k]);
            }
            text += "\n"
        }
    }
    else {
        text += "\n";
    }

    var env = QProcessEnvironment.systemEnvironment();
    var keyValues = env.toStringList();
    text += "\nEnvironment";
    for (i=0; i<keyValues.length; i++) {
        var keyValue = keyValues[i];
        text += "\n" + keyValue;
    }

    textEdit.plainText = text;
}

About.prototype.openUrl = function(url) {
    QDesktopServices.openUrl(url);
};

