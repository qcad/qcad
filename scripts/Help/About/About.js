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
 

function About(guiAction) {
    Help.call(this, guiAction);
}

About.prototype = new Help();

About.prototype.beginEvent = function() {
    Help.prototype.beginEvent.call(this);

    var formWidget = this.createWidget("About.ui");
    formWidget.windowTitle = qsTr("About %1").arg(qApp.applicationName);

    var f = 1.0;
    if (RS.getSystemId()=="win") {
        f = 0.75;
    }

    var head;
    head = "<head>\n"
         + "<style type='text/css'>\n"
         + "a { text-decoration:none }\n"
         + "h1 { font-family:sans;font-size:" + 18*f + "pt;margin-bottom:8pt; }\n"
         + "h2 { font-family:sans;font-size:" + 14*f + "pt;margin-bottom:5pt; }\n"
         + "body,td { font-family:sans;font-size:" + 11*f + "pt; }\n"
         + "}\n</style>\n"
         + "</head>";

    var webView = formWidget.findChild("QCADText");
    WidgetFactory.initWebView(webView, this, "openUrl");
    var html =
            "<html>"
            + head
            + "<body>"
            + "<h1>%1</h1>".arg(qApp.applicationName)
            + "<br/>"
            + "<table border='0'><tr>"
            + "<td><b>Version:</b> </td><td>%1</td>".arg(RSettings.getVersionString())
            + "</tr><tr>"
            + "<td><b>Date:</b> </td><td>%1</td>".arg(RSettings.getReleaseDate())
            + "</tr><tr>"
            + "<td><b>Qt Version:</b> </td><td>%4</td>".arg(RSettings.getQtVersion())
            + "</tr></table>"
            + "<p>%1 is an application for computer-aided design (CAD).</p>".arg(qApp.applicationName)
            + "<p/>"
            + "<p>QCAD is free (open source) software.</p>"
            + "<p/>"
            + "<p>Internet: <a href='http://www.qcad.org'>QCAD.org</a></p>"
            + "<p/>"
            + "<p>All brand or product names are trademarks or registered trademarks of their respective holders.</p>"
            + "<p/>"
            + "<p>Portions of this software © 2013 Digia Plc.</p>"
            + "<p>Portions of this software © 2012 Nokia Corporation and/or its subsidiary(-ies).</p>"
            + "<p/>"
            + "</body></html>";
    webView.setHtml(html);


    webView = formWidget.findChild("PluginsText");
    WidgetFactory.initWebView(webView, this, "openUrl");
    html =
            "<html>"
            + head
            + "<body>"
            + "<h1>%1</h1>".arg(qsTr("Plugins"))
            + "<hr/>";

    var numPlugins = RPluginLoader.countPlugins();

    if (numPlugins===0) {
        html += "No plugins found.";
    }
    else {
        for (var i=0; i<numPlugins; i++) {
            var pluginInfo = RPluginLoader.getPluginInfo(i);

            html += "<h2>%1</h2>".arg(pluginInfo.getFileName())
            html += "<table border='0'>";
            html += "<col width='10%'/>";
            html += "<col width='90%'/>";

            // plugin about info:
            var text = pluginInfo.getAboutString();
            if (text.length===0) {
                text = qsTr("No information available");
            }
            html += "<tr><td>%1 </td><td>%2</td></tr>".arg(qsTr("Plugin:")).arg(Qt.escape(text));

            // plugin version:
            text = pluginInfo.getVersionString();
            if (text.length===0) {
                text = qsTr("Unknown");
            }
            html += "<tr><td>%1 </td><td>%2</td></tr>".arg(qsTr("Version:")).arg(Qt.escape(text));

            // plugin license:
            text = pluginInfo.getLicense();
            if (text.length===0) {
                text = qsTr("Unknown");
            }
            html += "<tr><td>%1 </td><td>%2</td></tr>".arg(qsTr("License:")).arg(Qt.escape(text));

            // plugin URL:
            text = pluginInfo.getUrl();
            if (text.length!==0) {
                var url = new QUrl(text);
                if (url.isValid()) {
    //                var opt = new QUrl.FormattingOption(
    //                    QUrl.RemoveScheme, QUrl.RemoveAuthority, QUrl.RemovePath,
    //                    QUrl.RemoveQuery, QUrl.RemoveFragment,
    //                    QUrl.StripTrailingSlash
    //                );
                    //debugger;
                    html += "<tr><td>%1 </td><td><a href=\"%2\">%3</a></td></tr>"
                        .arg(qsTr("Internet:"))
                        .arg(url.toString())
                        .arg(url.host().replace(/^www./, ""));
                }
            }

            // plugin error:
            var err = pluginInfo.getErrorString();
            if (err.length!==0) {
                html += "<tr><td>%1 </td><td><div>%2</div></td></tr>"
                    .arg(qsTr("Error:"))
                    .arg(Qt.escape(err));
            }
            html += "</table>";
            html += "<hr/>";
        }
    }

    html += "</body>";
    html += "</html>";
    webView.setHtml(html);

    formWidget.exec();
};

About.prototype.openUrl = function(url) {
    QDesktopServices.openUrl(url);
};

