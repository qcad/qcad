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

ShowReadme.readmeFile = "readme.txt";

function ShowReadme(guiAction) {
    Help.call(this, guiAction);
}

ShowReadme.prototype = new Help();
ShowReadme.includeBasePath = includeBasePath;

ShowReadme.prototype.beginEvent = function() {
    Help.prototype.beginEvent.call(this);

    var formWidget = this.createWidget(ShowReadme.includeBasePath + "/ShowReadmeDialog.ui");

    var dontShow = formWidget.findChild("DontShowOnStartup");
    dontShow.checked = !RSettings.getBoolValue("Start/ShowReadme", true);
    dontShow.clicked.connect(this, function(checked) {
        RSettings.setValue("Start/ShowReadme", !checked);
    });
    
    var text = formWidget.findChild("Text");
    var file = new QFile(ShowReadme.readmeFile);
    var flags = new QIODevice.OpenMode(QIODevice.ReadOnly | QIODevice.Text);
    if (!file.open(flags)) {
        text.toPlainText() = qsTr("File \"%1\" doesn't exist.").arg(
                ShowReadme.readmeFile);
    } else {
        var textStream = new QTextStream(file);
        textStream.setCodec("UTF-8");
        var allLines = textStream.readAll();
        file.close();
        text.plainText = allLines;
    }
    formWidget.exec();
};

