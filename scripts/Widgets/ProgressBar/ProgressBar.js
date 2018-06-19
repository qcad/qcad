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

include("scripts/WidgetFactory.js");
include("scripts/Widgets/StatusBar/StatusBar.js");

function ProgressBar() {
    ProgressBar.progressBar = undefined;
    ProgressBar.text = "";
}

/**
 * Progress bar widget in status bar.
 */
ProgressBar.postInit = function(basePath) {
    var widget = WidgetFactory.createWidget(basePath, "ProgressBar.ui");
    StatusBar.addWidget(widget, 1000, RSettings.getBoolValue("StatusBar/ProgressDisplay", true));

    ProgressBar.prepare();

    if (!isNull(ProgressBar.progressBar)) {
        ProgressBar.progressBar.visible = false;
    }

    var appWin = EAction.getMainWindow();
    appWin.progressText.connect(this, "setProgressText");
    appWin.progress.connect(this, "progress");
    appWin.progressEnd.connect(this, "progressEnd");
};

ProgressBar.prepare = function() {
    var appWin = EAction.getMainWindow();
    var statusBar = appWin.findChild("StatusBar");
    ProgressBar.progressLabel = statusBar.findChild("ProgressText");
    ProgressBar.progressBar = statusBar.findChild("ProgressBar");
    ProgressBar.progressDialog = appWin.findChild("ProgressDialog");
    ProgressBar.dialogMode = RSettings.getBoolValue("Appearance/ShowProgressDialog", false);
};

ProgressBar.setProgressText = function(text) {
    ProgressBar.prepare();

    if (ProgressBar.dialogMode===true) {
        if (!isNull(ProgressBar.progressDialog)) {
            ProgressBar.progressDialog.labelText = text;
        }
        else {
            ProgressBar.text = text;
        }
    }
    else {
        if (!isNull(ProgressBar.progressLabel)) {
            ProgressBar.progressLabel.text = text;
        }
    }
};

ProgressBar.progress = function(value) {
    ProgressBar.prepare();

    if (ProgressBar.dialogMode===true) {
        if (isNull(ProgressBar.progressDialog)) {
            ProgressBar.progressDialog = new QProgressDialog(ProgressBar.text, "", 0, 100, EAction.getMainWindow());
            ProgressBar.progressDialog.objectName = "ProgressDialog";
            ProgressBar.progressDialog.windowModality = Qt.ApplicationModal;
            ProgressBar.progressDialog.minimumDuration = 500;
            ProgressBar.progressDialog.setCancelButton(0);
        }
        ProgressBar.progressDialog.value = value;
        // don't process events if modal dialog does not block user from doing something:
        if (ProgressBar.progressDialog.visible) {
            QCoreApplication.processEvents();
        }
    }
    else {
        if (!isNull(ProgressBar.progressBar)) {
            if (!QCoreApplication.arguments().contains("-no-show")) {
                ProgressBar.progressBar.visible = true;
            }
            ProgressBar.progressBar.value = value;
        }
    }
    var appWin = EAction.getMainWindow();
    if (appWin.enabled) {
        appWin.disable();
    }
};

ProgressBar.progressEnd = function() {
    ProgressBar.prepare();

    if (ProgressBar.dialogMode===true) {
        if (!isNull(ProgressBar.progressDialog)) {
            ProgressBar.progressDialog.setValue(100);
        }
    }
    else {
        if (!isNull(ProgressBar.progressBar)) {
            ProgressBar.progressBar.reset();
            ProgressBar.setProgressText("");
            ProgressBar.progressBar.visible = false;
        }
    }
    var appWin = EAction.getMainWindow();
    if (!appWin.enabled) {
        appWin.enable();
    }
};

