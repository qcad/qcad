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

    var webView = formWidget.findChild("QCADText");
    WidgetFactory.initWebView(webView, this, "openUrl");
    var html =
            "<html>"
            + "<body style'font-family:sans; font-size:13pt;'>"
            + "<b style='font-size:18pt'>%1</b>".arg(qApp.applicationName)
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
            + "<body style'font-family:sans; font-size:13pt;'>"
            + "<b style='font-size:18pt'>%1</b>".arg(qsTr("Plugins"))
            + "<br/>";

    var numPlugins = RPluginLoader.countPlugins();
    for (var i=0; i<numPlugins; i++) {
        var pluginInfo = RPluginLoader.getPluginInfo(i);

        html += "<br/>";
        html += "<b style='font-size:12pt'>%1</b>".arg(pluginInfo.getFileName())
        html += "<table border='0'>";
        html += "<col width='10%'/>";
        html += "<col width='90%'/>";

        var text = pluginInfo.getAboutString();
        if (text.length===0) {
            text = qsTr("No information available");
        }
        html += "<tr><td>%1 </td><td>%2</td></tr>".arg(qsTr("Plugin:")).arg(Qt.escape(text));

        text = pluginInfo.getVersionString();
        if (text.length===0) {
            text = qsTr("Unknown version");
        }
        html += "<tr><td>%1 </td><td>%2</td></tr>".arg(qsTr("Version:")).arg(Qt.escape(text));

        var err = pluginInfo.getErrorString();
        if (err.length!==0) {
            html += "<tr style='color:red'><td>%1 </td><td><div>%2</div></td></tr>"
                .arg(qsTr("Error:"))
                .arg(Qt.escape(err));
        }
        html += "</table>";
        html += "</body>";
        html += "</html>";
        webView.setHtml(html);
    }

    formWidget.exec();
};

About.prototype.openUrl = function(url) {
    QDesktopServices.openUrl(url);
};

