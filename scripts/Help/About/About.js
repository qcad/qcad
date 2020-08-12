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
include("AboutCredits.js");
 

/**
 * \class About
 * \brief Shows about dialog.
 * \ingroup ecma_help
 */
function About(guiAction) {
    Help.call(this, guiAction);
}

About.prototype = new Help();

About.prototype.beginEvent = function() {
    Help.prototype.beginEvent.call(this);

    var dialog = this.createWidget("AboutDialog.ui");

    var f = 1;
    if (RS.getSystemId()==="osx") {
        f = 1.33;
    }

    var blue = "#0000cc";
    if (RSettings.hasDarkGuiBackground()) {
        blue = "#2E9AFE";
    }

    this.head = "<head>\n"
         + "<style type='text/css'>\n"
         + "body,td { font-family:Arial, Helvetica, sans-serif;font-size:%1pt; }\n".arg(9*f)
         + "a { text-decoration:none;color:" + blue +" }\n"
         + "h1 { font-size:%1pt;margin-bottom:8pt; }\n".arg(13*f)
         + "h2 { font-size:%1pt;font-style:italic;margin-bottom:5pt; }\n".arg(9*f)
         + "}\n</style>\n"
         + "</head>";

    this.applicationName = qApp.applicationName;
    this.version = undefined;
    this.iconFile = undefined;

    // init plugin view:
    var textBrowser = dialog.findChild("PluginsText");
    WidgetFactory.initTextBrowser(textBrowser, this, "openUrl");
    this.initAboutPlugins(textBrowser);

    dialog.windowTitle = qsTr("About %1").arg(this.applicationName);
    if (!isNull(this.iconFile)) {
        dialog.findChild("Icon").icon = new QIcon(this.iconFile);
    }

    // init about view:
    textBrowser = dialog.findChild("AppText");
    WidgetFactory.initTextBrowser(textBrowser, this, "openUrl");
    this.initAboutApp(textBrowser);

    // init scripts view:
    textBrowser = dialog.findChild("ScriptsText");
    WidgetFactory.initTextBrowser(textBrowser, this, "openUrl");
    this.initAboutScripts(textBrowser);

    textBrowser = dialog.findChild("CreditsText");
    WidgetFactory.initTextBrowser(textBrowser, this, "openUrl");
    this.initCredits(textBrowser);

    // init system view:
    var textEdit = dialog.findChild("SystemText");
    this.initAboutSystem(textEdit);

    // init licenses view:
    textBrowser = dialog.findChild("LicensesText");
    this.initAboutLicenses(textBrowser);

    dialog.exec();
    dialog.destroy();
    EAction.activateMainWindow();
};

About.prototype.initAboutApp = function(textBrowser) {
    var version = RSettings.getVersionString();
    var versionComplete = "%1.%2.%3.%4"
        .arg(RSettings.getMajorVersion())
        .arg(RSettings.getMinorVersion())
        .arg(RSettings.getRevisionVersion())
        .arg(RSettings.getBuildVersion());

    if (!isNull(this.version)) {
        version = "";
        versionComplete = this.version;
    }

    var html =
            "<html>"
            + this.head
            + "<body>"
            + "<h1>%1</h1>".arg(this.applicationName)
            + "<hr/>";
            html +=
              "<table border='0'><tr>"
            + "<td><b>" + qsTr("Version:") + "</b> </td><td>%1 %2</td>"
              .arg(versionComplete)
              .arg(version.length>0 ? "("+version+")" : "")
            + "</tr><tr>"
            + "<td><b>" + qsTr("Internet:") + "</b> </td><td><a href='http://%1'>%1</a></td>".arg(qApp.organizationDomain)
            + "</tr><tr>"
            + "<td><b>" + qsTr("Build Date:") + "</b> </td><td>%1</td>".arg(RSettings.getReleaseDate())
            + "</tr><tr>"
            + "<td><b>" + qsTr("Revision:") + "</b> </td><td>%1</td>".arg(RSettings.getRevisionString().left(7))
            + "</tr><tr>"
            + "<td><b>" + qsTr("Qt Version:") + "</b> </td><td>%1</td>".arg(RSettings.getQtVersionString())
            + "</tr>";
            var bca = RS.getBuildCpuArchitecture();
            if (bca.length!==0) {
                html += "<tr><td><b>" + qsTr("Architecture:") + "</b> </td><td>%1</td>".arg(bca) + "</tr>";
            }
            html += "<tr><td><b>" + qsTr("Compiler:") + "</b> </td><td>%1</td>".arg(RSettings.getCompilerVersion()) + "</tr>";
            var lk = RSettings.getStringValue("License/LicenseKey", "");
            if (lk.length>0) {
                html += "<tr><td><b>" + qsTr("License Key:") + "</b> </td><td>%1</td>".arg(lk) + "</tr>";
            }
            html += "</table>";

            html += "<hr/>"
            + "<p>" + qsTr("%1 is an application for computer-aided design (CAD).").arg(this.applicationName) + "</p>"
            + "<p/>";

            if (this.applicationName!=="QCAD" && this.applicationName!=="QCAD Community Edition") {
                html += "<p>" + qsTr("%1 is based on QCAD, a free (open source) software.").arg(this.applicationName) + "</p>";
            }
            else {
                html += "<p>" + qsTr("%1 is free (open source) software.").arg("QCAD") + "<br/>"
                     + "" + qsTr("This means that everyone can <a href='%1'>get involved</a>!").arg("http://www.qcad.org/contribute") + "</p>"
                     + "" + qsTr("Additional tools, features and file formats including DWG are available in <a href='%1'>QCAD Professional</a> or <a href='%2'>QCAD/CAM</a>.").arg("https://qcad.org/shop").arg("https://qcad.org/shop");
            }

            html += "<p>" + qsTr("Plugins and script add-ons are subject to their respective license (see \"Plugins\" tab).") + "</p>"
            + "<p/>"
            + "<p>" + qsTr("All brand or product names are trademarks or registered trademarks of their respective holders.") + "</p>"
            + "<p/>"
            + "<p>© 2011-2020 RibbonSoft, GmbH.</p>"
            + "<p>" + qsTr("Portions of this software © %1 The Qt Company Ltd.").arg("2008-2020") + "</p>"
            + "<p>" + qsTr("Qt ships with QCAD under the <a href='%1'>LGPL Open Source license</a> which confers various rights to you as the user, including the right to recompile the Qt libraries for your platform. To do that follow the <a href='%2'>documentation shown on the Qt website</a>.").arg("http://www.gnu.org/licenses/lgpl-3.0.html").arg("http://doc.qt.io/qt-5/build-sources.html") + "</p>"
            + "<p>" + qsTr("The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.") + "</p>"
            + "<p/>"
            + "</body></html>";
    textBrowser.setHtml(html);
};

About.prototype.initAboutPlugins = function(textBrowser) {
    RPluginLoader.loadPlugins(false);
    var html =
            "<html>"
            + this.head
            + "<body>"
            + "<h1>%1</h1>".arg(qsTr("Plugins"))
            + "<hr/>";

    var numPlugins = RPluginLoader.countPlugins();

    if (numPlugins===0) {
        html += qsTr("No plugins found.");
    }
    else {
        var maxPri = undefined;
        for (var i=0; i<numPlugins; i++) {
            html += "<table border='0' width='100%'>";

            var text, url;

            var pluginInfo = RPluginLoader.getPluginInfo(i);

            // override priority:
            var pri = pluginInfo.get("OverridePriority");
            if (!isNull(pri)) {
                pri = parseInt(pri);
            }
            else {
                // default to lowest priority:
                pri = 0;
            }

            //qDebug("ID:", pluginInfo.get("ID"));
            //qDebug("pri:", pri);

            // plugin about info:
            text = pluginInfo.get("Name", qsTr("No information available"));
            html += this.getTableRow(qsTr("Plugin:"), "<b>" + Qt.escape(text) + "</b>", false);

            // overrides:
            if (isNull(maxPri) || pri>maxPri) {
                maxPri = pri;

                text = pluginInfo.get("NameOverride");
                if (!isNull(text)) {
                    this.applicationName = text;
                }

                text = pluginInfo.get("VersionOverride");
                if (!isNull(text)) {
                    this.version = text;
                }

                text = pluginInfo.get("IconOverride");
                if (!isNull(text)) {
                    this.iconFile = text;
                }
            }

            // ID:
            text = pluginInfo.get("ID");
            if (!isNull(text)) {
                html += this.getTableRow(qsTr("ID:"), text, false);
            }

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
                    if (!RSettings.isQt(5)) {
                        html += this.getTableRow(
                            qsTr("Internet:"),
                            "<a href='%2'>%3</a>"
                                .arg(url.toString()).arg(url.host().replace(/^www./, "")),
                            false
                        );
                    }
                    else {
                        // TODO Qt5:
                        var fixedUrl = url.toString();
                        fixedUrl = fixedUrl.replace("QUrl( \"", "");
                        fixedUrl = fixedUrl.replace("\" )", "");
                        html += this.getTableRow(qsTr("Internet:"), "<a href='%2'>%3</a>" .arg(fixedUrl).arg(fixedUrl), false);
                    }
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
                html += this.getTableRow(qsTr("Error:"),
                    "<span style='color:red'>" + text + "</span>", false);
            }
            html += "</table>";
            html += "<hr/>";
        }
    }

    if (this.applicationName==="QCAD") {
        this.applicationName = qApp.applicationName + " Community Edition";
    }

    html += "</body>";
    html += "</html>";
    textBrowser.setHtml(html);
};

About.prototype.initAboutScripts = function(textBrowser) {
    var html =
            "<html>"
            + this.head
            + "<body>"
            + "<h1>%1</h1>".arg(qsTr("Script Add-Ons"))
            + "<hr/>";

    var addOns = AddOn.getAddOns();
    var numAddOns = addOns.length;

    if (numAddOns===0) {
        html += qsTr("No script add-ons found.");
    }
    else {
        var i;
        var scriptsPath = RS.getDirectoryList("scripts")[0];
        var scriptsDir = undefined;
        if (!isNull(scriptsPath)) {
            scriptsDir = new QDir(scriptsPath);
        }

        var sorted = [];
        for (i=0; i<numAddOns; i++) {
            var addOn = addOns[i];
            var path = addOn.getPath();
            if (path.startsWith(":")) {
                path = path.substring(1);
            }
            else {
                if (!isNull(scriptsDir)) {
                    path = scriptsDir.relativeFilePath(path);
                }
            }
            sorted.push([addOn.getClassName(), path]);
        }

        sorted = sorted.sort(function(a,b) { return a[1].localeCompare(b[1]); });

        html += "<table border='0' width='100%'>";

        for (i=0; i<sorted.length; i++) {
            html += "<tr><td>" + sorted[i][0] + "</td><td>" + sorted[i][1] + "</td></tr>"
        }
    }

    html += "</table>";
    html += "</body>";
    html += "</html>";
    textBrowser.setHtml(html);
};

About.prototype.initCredits = function(textBrowser) {
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
            for (var k=1; k<credits[i].length; k++) {
                if (isArray(credits[i][k]) && credits[i][k].length>1) {
                    html += "<tr>";
                    html += "<td width='30%' valign='top'>" + credits[i][k][0] + "</td>";
                    html += "<td width='70%' valign='top'>" + credits[i][k][1] + "</td>";
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

    textBrowser.setHtml(html);
};

About.prototype.getTableRow = function(text1, text2, escape) {
    if (isNull(escape) || escape!==false) {
        text2 = Qt.escape(text2);
    }

    return "<tr><td width='25%' valign='top'>%1 </td><td width='75%'>%2</td></tr>".arg(text1).arg(text2);
};

About.prototype.initAboutSystem = function(textEdit) {
    var text = "";
    var i;

    text += "Versions";
    if (!isNull(this.version)) {
        text += "\n%1 version: %2"
            .arg(qApp.applicationName)
            .arg(this.version);
    }
    else {
        text += "\n%1 version: %2.%3.%4.%5"
            .arg(qApp.applicationName)
            .arg(RSettings.getMajorVersion())
            .arg(RSettings.getMinorVersion())
            .arg(RSettings.getRevisionVersion())
            .arg(RSettings.getBuildVersion());
    }
    var lk = RSettings.getStringValue("License/LicenseKey", "");
    if (lk.length>0) {
        text += "\nLicense Key: " + lk;
    }
    text += "\nDate: " + RSettings.getReleaseDate();
    text += "\nQt version: " + RSettings.getQtVersionString();
    text += "\nCompiler version: " + RSettings.getCompilerVersion();
    text += "\nBuild date: " + RSettings.getReleaseDate();
    text += "\nRevision: " + RSettings.getRevisionString();
    text += "\nArchitecture: " + RS.getBuildCpuArchitecture();
    text += "\nDevice pixel ratio: " + RSettings.getDevicePixelRatio();

    text += "\nOS: ";
    if (RS.getSystemId()==="win") {
        text += "Windows";
    }
    if (RS.getSystemId()==="osx") {
        text += "macOS";
    }
    if (RS.getSystemId()==="linux") {
        text += "Linux";
    }
    if (RS.getSystemId()==="freebsd") {
        text += "FreeBSD";
    }
    if (RS.getSystemId()==="netbsd") {
        text += "NetBSD";
    }
    if (RS.getSystemId()==="openbsd") {
        text += "OpenBSD";
    }
    if (RS.getSystemId()==="solaris") {
        text += "Solaris";
    }
    text += "\nOS version: " + RSettings.getOSVersion();

    text += "\n";
    text += "\nLocale";
    text += "\n" + qApp.applicationName + " locale: " + RSettings.getLocale();
    var sysloc = QLocale.system();
    text += "\nName: " + sysloc.name();
    text += "\nCountry: " + sysloc.country();
    if (isFunction(sysloc.nativeCountryName)) {
        text += "\nCountry name: " + sysloc.nativeCountryName();
    }
    text += "\nLanguage: " + sysloc.language();
    if (isFunction(sysloc.nativeLanguageName)) {
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

    if (RS.getSystemId()==="win") {
        text += "\n"
        text += "\nOpenGL:\n" + RSettings.getOpenGLMessages().join("\n");
    }

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
};

About.prototype.initAboutLicenses = function(textBrowser) {
    var html =
            "<html>"
            + this.head
            + "<body>"
            + "<h1>%1</h1>".arg(qsTr("Licenses"))
            + "<hr/>";

    html += "<h2>libspatialindex</h2>"
    html += "<p>Permission is hereby granted, free of charge, to any person obtaining a "
          + "copy of this software and associated documentation files (the \"Software\"), "
          + "to deal in the Software without restriction, including without limitation "
          + "the rights to use, copy, modify, merge, publish, distribute, sublicense, "
          + "and/or sell copies of the Software, and to permit persons to whom the "
          + "Software is furnished to do so, subject to the following conditions:"
          + "<br/><br/>"
          + "The above copyright notice and this permission notice shall be included in "
          + "all copies or substantial portions of the Software."
          + "<br/><br/>"
          + "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
          + "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
          + "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE "
          + "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
          + "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING "
          + "FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER "
          + "DEALINGS IN THE SOFTWARE.</p>";

    html += "<h2>libstemmer</h2>"
    html += "<p>Copyright (c) 2001, Dr Martin Porter."
          + "<br/>All rights reserved."
          + "<br/><br/>"
          + "Redistribution and use in source and binary forms, with or without modification, "
          + "are permitted provided that the following conditions are met:"
          + "<br/><br/>"
          + " - Redistributions of source code must retain the above copyright notice, "
          + "   this list of conditions and the following disclaimer."
          + "<br/> - Redistributions in binary form must reproduce the above copyright notice, "
          + "   this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution."
          + "<br/><br/>"
          + "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" "
          + "AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED "
          + "WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. "
          + "IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, "
          + "INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT "
          + "NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR "
          + "PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, "
          + "WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) "
          + "ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY "
          + "OF SUCH DAMAGE.</p>"

    html += "<h2>numeraljs</h2>"
    html += "<p>Copyright (c) 2016, Adam Draper."
          + "<br/><br/>"
          + "Permission is hereby granted, free of charge, to any person "
          + "obtaining a copy of this software and associated documentation "
          + "files (the \"Software\"), to deal in the Software without "
          + "restriction, including without limitation the rights to use, "
          + "copy, modify, merge, publish, distribute, sublicense, and/or sell "
          + "copies of the Software, and to permit persons to whom the "
          + "Software is furnished to do so, subject to the following "
          + "conditions:"
          + "<br/><br/>"
          + " - The above copyright notice and this permission notice shall be "
          + "included in all copies or substantial portions of the Software."
          + "<br/> - Redistributions in binary form must reproduce the above copyright notice, "
          + "   this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution."
          + "<br/><br/>"
          + "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, "
          + "INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR "
          + "PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE "
          + "FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, "
          + "ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.</p>"

    var numPlugins = RPluginLoader.countPlugins();

    for (var i=0; i<numPlugins; i++) {
        var text, url;

        var pluginInfo = RPluginLoader.getPluginInfo(i);
        var lic = pluginInfo.get("LicenseText", "");
        if (lic.length>0) {
            html += "<h2>" + qsTr("Plugin:") + " " + new QFileInfo(pluginInfo.get("FileName")).fileName() + "</h2>"
            html += "<p>" + lic.replace(/\n/g, "<br/>") + "</p>";
        }
    }

    html += "</body>";
    html += "</html>";
    textBrowser.setHtml(html);
};

About.prototype.openUrl = function(url) {
    QDesktopServices.openUrl(url);
};

